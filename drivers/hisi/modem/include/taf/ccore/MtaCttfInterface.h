

#ifndef __MTACTTFINTERFACE_H__
#define __MTACTTFINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

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

enum MTA_CTTF_MSG_TYPE_ENUM{

    /* ��Ϣ���� */                              /* ��ϢID */                    /* ��ע */
    /* ���2����Ϣ */
    ID_MTA_CTTF_EVDO_SYS_EVENT_SET_REQ        = 0x0001,          /* _H2ASN_MsgChoice MTA_CTTF_EVDO_SYS_EVENT_SET_REQ_STRU */
    ID_MTA_CTTF_EVDO_SIG_MASK_SET_REQ         = 0x0002,          /* _H2ASN_MsgChoice MTA_CTTF_EVDO_SIG_MASK_SET_REQ_STRU */
    ID_CTTF_MTA_EVDO_REVA_RLINK_INFO_IND      = 0x0003,          /* _H2ASN_MsgChoice CTTF_MTA_EVDO_REVA_RLINK_INFO_STRU */
    ID_CTTF_MTA_EVDO_SIG_EXEVENT_IND          = 0x0004,          /* _H2ASN_MsgChoice CTTF_MTA_EVDO_SIG_EXEVENT_IND_STRU */

    ID_MTA_CTTF_MSG_TYPE_BUTT
};

typedef VOS_UINT16 MTA_CTTF_MSG_TYPE_ENUM_UINT16;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT32                          ulDoSysEvent;
} MTA_CTTF_EVDO_SYS_EVENT_SET_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT32                          ulDoSigMask;
} MTA_CTTF_EVDO_SIG_MASK_SET_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT32                          ulParaLen;
    VOS_UINT8                           aucContent[4];
} CTTF_MTA_EVDO_REVA_RLINK_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT32                          ulParaLen;
    VOS_UINT8                           aucContent[4];
} CTTF_MTA_EVDO_SIG_EXEVENT_IND_STRU;

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

#endif /* end of MtaCttfInterface.h */

