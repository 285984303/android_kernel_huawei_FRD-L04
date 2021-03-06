/*
 * voice_proxy_vowifi.c - HW voice proxy vowifi in kernel, it is used for pass through voice
 * data between audio hal and hifi for vowifi.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */

#include <linux/miscdevice.h>
#include "voice_proxy.h"

#define WIFI_RX_DATA_SIZE sizeof(struct voice_proxy_wifi_rx_notify)
#define WIFI_TX_DATA_SIZE sizeof(struct voice_proxy_wifi_tx_notify)
#define DTS_COMP_VOICE_PROXY_VOWIFI_NAME "hisilicon,voice_proxy_vowifi"

#define VOICE_PROXY_WAKE_UP_VOWIFI_READ  _IO('P',  0x1)

LIST_HEAD(recv_vowifi_rx_queue);
LIST_HEAD(send_vowifi_tx_queue);

struct vowifi_priv {
	spinlock_t vowifi_read_lock;

	wait_queue_head_t vowifi_read_waitq;

	int32_t vowifi_read_wait_flag;

	/* this is used for counting the size of recv_vowifi_rx_queue*/
	int32_t vowifi_rx_cnt;

	/* this is used for counting the size of send_vowifi_tx_queue*/
	int32_t vowifi_tx_cnt;

	/* vowifi rx voice data confirm*/
	bool vowifi_rx_cnf;

	/* vowifi rx first voice data*/
	bool first_vowifi_rx;

	/* vowifi rx voice data time stamp*/
	int64_t vowifi_rx_stamp;

	/* this handle is get from voice proxy when register sign init callback*/
	int32_t sign_handle;
};

static struct vowifi_priv priv;

static void vowifi_sign_init(void)
{
	logi("Enter %s\n", __FUNCTION__);
	priv.vowifi_rx_cnf = false;
	priv.first_vowifi_rx = true;
}

static int32_t vowifi_add_tx_data(int8_t *rev_buf, uint32_t buf_size)
{
	int32_t ret = 0;
	struct voice_proxy_data_node *node = NULL;

	BUG_ON(NULL == rev_buf);

	if (priv.vowifi_tx_cnt > VOICE_PROXY_QUEUE_SIZE_MAX) {
		loge("out of queue, vowifi_tx_cnt(%d)>QUEUE_SIZE_MAX(%d)\n",
			 priv.vowifi_tx_cnt, VOICE_PROXY_QUEUE_SIZE_MAX);
		spin_lock_bh(&priv.vowifi_read_lock);
		priv.vowifi_read_wait_flag++;
		spin_unlock_bh(&priv.vowifi_read_lock);
		wake_up(&priv.vowifi_read_waitq);

		return -ENOMEM;
	}

	ret = voice_proxy_create_data_node(&node, rev_buf, buf_size);
	if (ret) {
		loge("data_node kmalloc failed\n");
		return ret;
	}

	logi("vowifi_tx_cnt:%d\n", priv.vowifi_tx_cnt);
	spin_lock_bh(&priv.vowifi_read_lock);
	list_add_tail(&node->list_node, &send_vowifi_tx_queue);
	priv.vowifi_tx_cnt++;
	priv.vowifi_read_wait_flag++;
	spin_unlock_bh(&priv.vowifi_read_lock);
	wake_up(&priv.vowifi_read_waitq);

	return 0;
}

static void vowifi_get_rx_data(int8_t *data, uint32_t *size)
{
	struct voice_proxy_data_node *node = NULL;

	BUG_ON(NULL == data);
	BUG_ON(NULL == size);

	if (!list_empty_careful(&recv_vowifi_rx_queue)) {
		node = list_first_entry(&recv_vowifi_rx_queue,
						struct voice_proxy_data_node,
						list_node);

		BUG_ON(*size < node->list_data.size);

		*size = node->list_data.size;
		memcpy(data, node->list_data.data, *size);

		list_del_init(&node->list_node);
		kfree(node);
		node = NULL;

		if (priv.vowifi_rx_cnt > 0) {
			priv.vowifi_rx_cnt--;
		}
		priv.first_vowifi_rx = false;
		priv.vowifi_rx_cnf = false;
	} else {
		*size = 0;
	}
}

static void vowifi_receive_rctp_om_tx_ntf(int8_t *rev_buf, uint32_t buf_size)
{
	int32_t ret = 0;
	loge("vowifi_receive_rctp_om_tx_ntf\n");
	BUG_ON(NULL == rev_buf);

	ret = vowifi_add_tx_data(rev_buf, buf_size);
	if (ret) {
		loge("send vowifi tx data to read func failed\n");
		return;
	}

}

static void vowifi_receive_ajb_om_tx_ntf(int8_t *rev_buf, uint32_t buf_size)
{
	int32_t ret = 0;
	loge("vowifi_receive_ajb_om_tx_ntf\n");
	BUG_ON(NULL == rev_buf);

	ret = vowifi_add_tx_data(rev_buf, buf_size);
	if (ret) {
		loge("send vowifi tx data to read func failed\n");
		return;
	}

}

static void vowifi_receive_tx_ntf(int8_t *rev_buf, uint32_t buf_size)
{
	int32_t ret = 0;
	static int32_t cnt = 0;

	BUG_ON(NULL == rev_buf);

	ret = vowifi_add_tx_data(rev_buf, buf_size);
	if (ret) {
		loge("send vowifi tx data to read func failed\n");
		return;
	}

	voice_proxy_add_work_queue_cmd(ID_PROXY_VOICE_WIFI_TX_CNF);

	cnt++;
	logi("receive wifi rx ntf msg: cnt:%d\n", cnt);
}

static void vowifi_receive_rx_cnf(int8_t *rev_buf, uint32_t buf_size)
{
	int32_t ret = 0;
	static int32_t cnt = 0;

	ret = voice_proxy_add_cmd(ID_VOICE_PROXY_WIFI_RX_CNF);
	if (ret) {
		loge("send wifi rx data cnf failed\n");
	}

	cnt++;
	logi("receive wifi rx cnf msg: cnt:%d\n", cnt);
}

static void vowifi_handle_rx_ntf(int8_t *data, uint32_t *size, uint16_t *msg_id)
{
	logi("msg id ID_PROXY_VOICE_WIFI_RX_NTF\n");

	BUG_ON(NULL == data);
	BUG_ON(NULL == size);
	BUG_ON(NULL == msg_id);

	voice_proxy_set_send_sign(priv.first_vowifi_rx, &priv.vowifi_rx_cnf, &priv.vowifi_rx_stamp);

	if (priv.first_vowifi_rx || priv.vowifi_rx_cnf) {
		vowifi_get_rx_data(data, size);
	} else {
		*size = 0;
	}
	*msg_id = ID_PROXY_VOICE_WIFI_RX_NTF;
}

static void vowifi_handle_rx_cnf(int8_t *data, uint32_t *size, uint16_t *msg_id)
{
	logi("msg id ID_VOICE_PROXY_WIFI_RX_CNF\n");

	BUG_ON(NULL == data);
	BUG_ON(NULL == size);
	BUG_ON(NULL == msg_id);

	priv.vowifi_rx_cnf = true;
	priv.vowifi_rx_stamp = voice_proxy_get_time_ms();

	vowifi_get_rx_data(data, size);
	*msg_id = ID_PROXY_VOICE_WIFI_RX_NTF;
}

static ssize_t vowifi_read(struct file *file, char __user *user_buf, size_t size, loff_t *ppos)
{
	int ret = 0;
	struct voice_proxy_data_node *node = NULL;

	if (file->f_flags & O_NONBLOCK) {
		loge("file->f_flags & O_NONBLOCK(%d) fail\n", file->f_flags & O_NONBLOCK);
		return -EINVAL;
	}

	if (size < WIFI_TX_DATA_SIZE) {
		loge("param err, size(%zd) < WIFI_TX_DATA_SIZE(%ld)\n", size, WIFI_TX_DATA_SIZE);
		return -EINVAL;
	}

	spin_lock_bh(&priv.vowifi_read_lock);
	if (list_empty_careful(&send_vowifi_tx_queue)) {
		spin_unlock_bh(&priv.vowifi_read_lock);
		ret = wait_event_interruptible(priv.vowifi_read_waitq, priv.vowifi_read_wait_flag > 0);
		if (ret) {
			if (ret != -ERESTARTSYS) {
				loge("wait event interruptible fail, 0x%x.\n", ret);
			}

			return -EBUSY;
		}
		spin_lock_bh(&priv.vowifi_read_lock);
	}

	priv.vowifi_read_wait_flag = 0;

	if (!list_empty_careful(&send_vowifi_tx_queue)) {
		node = list_first_entry(&send_vowifi_tx_queue,
						struct voice_proxy_data_node,
						list_node);

		list_del_init(&node->list_node);
		if (priv.vowifi_tx_cnt > 0) {
			priv.vowifi_tx_cnt--;
		}
		spin_unlock_bh(&priv.vowifi_read_lock);

		if (size < node->list_data.size) {
			loge("size(%zd) < node->list_data.size(%d)\n", size, node->list_data.size);
			kfree(node);
			node = NULL;
			return -EAGAIN;
		}

		if (copy_to_user(user_buf, node->list_data.data, node->list_data.size)) {
			loge("copy_to_user fail\n");
			ret = -EFAULT;
		} else {
			ret = node->list_data.size;
		}
		kfree(node);
		node = NULL;
	} else {
		spin_unlock_bh(&priv.vowifi_read_lock);
		ret = -EAGAIN;
		loge("list is empty, read again\n");
	}

	return ret;
}

static int32_t vowifi_add_rx_data(int8_t *data, uint32_t size)
{
	int32_t ret = 0;
	struct voice_proxy_data_node *node = NULL;

	BUG_ON(NULL == data);

	if (priv.vowifi_rx_cnt > VOICE_PROXY_QUEUE_SIZE_MAX) {
		loge("out of queue, rx cnt(%d)>(%d)\n", priv.vowifi_rx_cnt, VOICE_PROXY_QUEUE_SIZE_MAX);
		return -ENOMEM;
	}

	ret = voice_proxy_create_data_node(&node, data, size);
	if (ret) {
		loge("node kmalloc failed\n");
		return -EFAULT;
	}

	list_add_tail(&node->list_node, &recv_vowifi_rx_queue);
	priv.vowifi_rx_cnt++;

	return size;
}

static ssize_t vowifi_write(struct file *filp, const char __user *buff, size_t size, loff_t *offp)
{
	int32_t ret = 0;
	int8_t data[WIFI_RX_DATA_SIZE];

	if (WIFI_RX_DATA_SIZE < size) {
		loge("para error, size:%zd(>%ld)\n", size, WIFI_RX_DATA_SIZE);
		return -EINVAL;
	}

	memset(data, 0, sizeof(data));
	if (copy_from_user(data, buff, size)) {
		loge("copy_from_user fail\n");
		return -EFAULT;
	}

	ret = voice_proxy_add_data(vowifi_add_rx_data, data, size, ID_PROXY_VOICE_WIFI_RX_NTF);
	if (ret <= 0) {
		loge("call voice_proxy_add_data fail\n");
		return -EFAULT;
	}

	logi("write size = %zd\n", size);

	return size;
}

static void vowifi_wake_up_read(void)
{
	spin_lock_bh(&priv.vowifi_read_lock);
	priv.vowifi_read_wait_flag++;
	spin_unlock_bh(&priv.vowifi_read_lock);
	wake_up(&priv.vowifi_read_waitq);
}

static long vowifi_ioctl(struct file *fd, unsigned int cmd, unsigned long arg)
{
	long ret = 0;
	void __user *data = (void __user *)arg;

	if (!(void __user *)arg) {
		loge("Input buff is NULL\n");
		return -EINVAL;
	}

#ifdef CONFIG_COMPAT
	data = (void __user *)compat_ptr(arg);
#endif

	switch (cmd) {
		case VOICE_PROXY_WAKE_UP_VOWIFI_READ:
			logi("receive VOICE_PROXY_WAKE_UP_VOWIFI_READ cmd\n");
			vowifi_wake_up_read();
			break;

		default:
			loge("ioctl: Invalid CMD = 0x%x\n", (int32_t)cmd);
			ret = -EINVAL;
			break;
	}

	return (long)ret;
}

static int vowifi_open(struct inode *finode, struct file *fd)
{
	logi("Enter %s\n", __FUNCTION__);
	return 0;
}

static int vowifi_close(struct inode *node, struct file *filp)
{
	logi("Enter %s\n", __FUNCTION__);
	spin_lock_bh(&priv.vowifi_read_lock);
	priv.vowifi_read_wait_flag++;
	spin_unlock_bh(&priv.vowifi_read_lock);
	wake_up(&priv.vowifi_read_waitq);
	return 0;
}

static const struct file_operations vowifi_misc_fops = {
	.owner = THIS_MODULE,
	.open = vowifi_open,
	.read = vowifi_read,
	.write = vowifi_write,
	.release = vowifi_close,
	.unlocked_ioctl = vowifi_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl   = vowifi_ioctl,
#endif
};

static struct miscdevice vowifi_misc_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "voice_proxy_vowifi",
	.fops = &vowifi_misc_fops,
};

static int vowifi_probe(struct platform_device *pdev)
{
	int32_t ret = 0;

	memset(&priv, 0, sizeof(priv));

	printk("voice proxy vowifi prob,pdev name[%s]\n", pdev->name);

	priv.vowifi_read_wait_flag = 0;

	spin_lock_init(&priv.vowifi_read_lock);
	init_waitqueue_head(&priv.vowifi_read_waitq);

	ret = misc_register(&vowifi_misc_device);
	if (ret) {
		loge("vowifi misc register fail\n");
		return ret;
	}

	vowifi_sign_init();

	ret = voice_proxy_register_msg_callback(ID_VOICE_PROXY_RCTP_OM_INFO_NTF, vowifi_receive_rctp_om_tx_ntf);
	BUG_ON(0 != ret);
	ret = voice_proxy_register_msg_callback(ID_VOICE_PROXY_AJB_OM_INFO_NTF, vowifi_receive_ajb_om_tx_ntf);
	BUG_ON(0 != ret);
	ret = voice_proxy_register_msg_callback(ID_VOICE_PROXY_WIFI_TX_NTF, vowifi_receive_tx_ntf);
	BUG_ON(0 != ret);
	ret = voice_proxy_register_msg_callback(ID_VOICE_PROXY_WIFI_RX_CNF, vowifi_receive_rx_cnf);
	BUG_ON(0 != ret);
	ret = voice_proxy_register_cmd_callback(ID_PROXY_VOICE_WIFI_RX_NTF, vowifi_handle_rx_ntf);
	BUG_ON(0 != ret);
	ret = voice_proxy_register_cmd_callback(ID_VOICE_PROXY_WIFI_RX_CNF, vowifi_handle_rx_cnf);
	BUG_ON(0 != ret);

	voice_proxy_register_sign_init_callback(vowifi_sign_init, &priv.sign_handle);

	return ret;
}

static int vowifi_remove(struct platform_device *pdev)
{
	logi("Enter %s\n", __FUNCTION__);
	misc_deregister(&vowifi_misc_device);
	voice_proxy_deregister_msg_callback(ID_VOICE_PROXY_WIFI_TX_NTF);
	voice_proxy_deregister_msg_callback(ID_VOICE_PROXY_WIFI_RX_CNF);

	voice_proxy_deregister_cmd_callback(ID_PROXY_VOICE_WIFI_RX_NTF);
	voice_proxy_deregister_cmd_callback(ID_VOICE_PROXY_WIFI_RX_CNF);

	voice_proxy_deregister_sign_init_callback(priv.sign_handle);

	return 0;
}


static const struct of_device_id vowifi_match_table[] = {
	{
		.compatible = DTS_COMP_VOICE_PROXY_VOWIFI_NAME,
		.data = NULL,
	},
	{}
};

static struct platform_driver vowifi_driver = {
	.driver = {
		.name  = "voice proxy vowifi",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(vowifi_match_table),
	},
	.probe = vowifi_probe,
	.remove = vowifi_remove,
};

static int __init vowifi_init( void )
{
	int32_t ret = 0;

	printk("Audio:voice proxy vowifi init\n");

	ret = platform_driver_register(&vowifi_driver);
	if (ret) {
		loge("voice proxy vowifi driver register fail,ERROR is %d\n", ret);
	}

	return ret;
}

static void __exit vowifi_exit( void )
{
	platform_driver_unregister(&vowifi_driver);
}

module_init(vowifi_init);
module_exit(vowifi_exit);

MODULE_DESCRIPTION("voice proxy vowifi driver");
MODULE_AUTHOR("Huawei Technologies Co., Ltd.");
MODULE_LICENSE("GPL");

