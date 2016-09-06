
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#ifndef __OAM_CPHY_INTERFACE_H__
#define __OAM_CPHY_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
 ö����    :CPHY_OAM_WAKE_TYPE_ENUM_UINT32
 Э�����  :
 ASN.1���� :
 ö��˵��  :�������Ͷ���
*****************************************************************************/
enum CPHY_OAM_WAKE_TYPE_ENUM
{
    CPHY_OAM_NORMAL_WAKE                    = 0,
    CPHY_OAM_FORCE_WAKE                     = 1,
    CPHY_OAM_WAKE_TYPE_BUTT
};
typedef VOS_UINT32 CPHY_OAM_WAKE_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    :CPHY_WRITE_MBX_STATE_ENUM_UINT32
 Э�����  :
 ASN.1���� :
 ö��˵��  :CPROCд�����Ƿ����
*****************************************************************************/
enum CPHY_MBX_WRITE_STATE_ENUM
{
    CPHY_WRITE_MBX_COMPLETED           = 0,
    CPHY_WRITE_MBX_UNCOMPLETED         = 1,
    CPHY_WRITE_MBX_BUTT
};
typedef VOS_UINT32 CPHY_MBX_WRITE_STATE_ENUM_UINT32;

/*****************************************************************************
 ö����    :CPHY_READ_MBX_STATE_ENUM_UINT32
 Э�����  :
 ASN.1���� :
 ö��˵��  :CPROC�������Ƿ����
*****************************************************************************/
enum CPHY_MBX_READ_STATE_ENUM
{
    CPHY_READ_MBX_COMPLETED           = 0,
    CPHY_READ_MBX_UNCOMPLETED         = 1,
    CPHY_READ_MBX_BUTT
};
typedef VOS_UINT32 CPHY_MBX_READ_STATE_ENUM_UINT32;
/*****************************************************************************
 ö����        : CPHY_SLEEP_TYPE_ENUM
 ö��˵��      : CPHY˯������ö��
*****************************************************************************/
enum CPHY_SLEEP_TYPE_ENUM
{
    CPHY_SLEEP_TYPE_NONE           = 0,
    CPHY_SLEEP_TYPE_SHORT             ,
    CPHY_SLEEP_TYPE_DEEP              ,
    CPHY_SLEEP_TYPE_BUTT
};
typedef VOS_UINT32 CPHY_SLEEP_TYPE_ENUM_UINT32;


/*****************************************************************************
 ö����        : CPHY_WAKEUP_MODE_ENUM
 ö��˵��      : CPHY��������ö��
*****************************************************************************/
enum CPHY_WAKEUP_TYPE_ENUM
{
    CPHY_WAKEUP_MODE_1X                  = 0,
    CPHY_WAKEUP_MODE_HRPD                   ,
    CPHY_WAKEUP_MODE_BUTT
};
typedef VOS_UINT32 CPHY_WAKEUP_MODE_ENUM_UINT32;

/*****************************************************************************
 ö����        : CPHY_SLEEP_MODE_ENUM
 ö��˵��      : CPHY˯������ģ��Ϣö��
*****************************************************************************/
enum CPHY_SLEEP_MODE_ENUM
{
    CPHY_SLEEP_MODE_MASTER                ,
    CPHY_SLEEP_MODE_SLAVE                 ,
    CPHY_SLEEP_MODE_BUTT
};
typedef VOS_UINT32 CPHY_SLEEP_MODE_ENUM_UINT32;

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/
/*****************************************************************************
  6 STRUCT����
*****************************************************************************/




/*****************************************************************************
 �ṹ��    : CPHY_OAM_SHARE_INFO_STRU
 Э�����  :
 �ṹ˵��  : SRAM��CSDR��OAM֮����е͹�����Ϣ�����Ľṹ��
*****************************************************************************/
typedef struct
{
    volatile CPHY_SLEEP_TYPE_ENUM_UINT32        enSleepType;
    volatile CPHY_SLEEP_MODE_ENUM_UINT32        en1xMode;
    volatile CPHY_SLEEP_MODE_ENUM_UINT32        enHrpdMode;
    volatile CPHY_WAKEUP_MODE_ENUM_UINT32       enWakeUpMode;
    volatile CPHY_OAM_WAKE_TYPE_ENUM_UINT32     en1xWakeUpType;
    volatile CPHY_OAM_WAKE_TYPE_ENUM_UINT32     enHrpdWakeUpType;
    volatile CPHY_MBX_WRITE_STATE_ENUM_UINT32   enCprocWriteMbxState;
    volatile CPHY_MBX_READ_STATE_ENUM_UINT32    enCprocReadMbxState;
    volatile VOS_UINT32                         uw1xCfgBbpWakeClkSwitchTime;
    volatile VOS_UINT32                         uw1xBbpWakeClkSwitchIsrTime;
    volatile VOS_UINT32                         uwHrpdCfgBbpWakeClkSwitchTime;
    volatile VOS_UINT32                         uwHrpdBbpWakeClkSwitchIsrTime;
}CPHY_OAM_SHARE_INFO_STRU;


/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif /* __OAM_CPHY_INTERFACE_H__ */