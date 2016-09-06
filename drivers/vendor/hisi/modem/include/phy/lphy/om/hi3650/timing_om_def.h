

/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/

/************************************************************
                               �궨��
************************************************************/

/************************************************************
                             ���ݽṹ����
************************************************************/

/************************************************************
                             �ӿں�������
 ************************************************************/

#ifndef __TIMING_OM_DEF_H__
#define __TIMING_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#define LPHY_FEATURE_MAX_CARRIER_NUM_TRU 2

/************************************************************
                           1. REQ����Ͷ�Ӧ�����ݽṹ����
************************************************************/
enum LPHY_REQ_MSGID_TIMING_ENUM
{
    LPHY_REQ_TIMING_ENA_TRU = OM_CMD_ID(LPHY_TIMING_MID, OM_TYPE_REQ, 0x0),                    /*ʹ�ܶ�ʱ����ģ��*/
    LPHY_REQ_TIMING_PDP_ENA_TRU,
    LPHY_REQ_TIMING_EST_PERIOD,                 /*��ʱ��������*/
    LPHY_REQ_TIMING_PDP_FILTER,                 /*�˲���ʹ��*/
    LPHY_REQ_TIMING_LOOP_FILTER,                /*��·�˲�����׮*/
    LPHY_REQ_TIMING_CONST_ADVANCE,              /*�״�������ʱ���������С����������ǰ��*/
    LPHY_REQ_TIMING_PARA,                       /*������ʱ���ٲ���*/
    LPHY_REQ_TIMING_TRMS_PARA,                  /*����TRMS����Ĭ��ֵ*/
    LPHY_REQ_TIMING_TRMS_SAVE,                  /*����ʱ�ӵĴ洢ֵ*/
    LPHY_REQ_TIMING_RPT_SG,                     /*�ϱ���ʱOM���*/
    LPHY_REQ_TIMING_ENA_MBMS,                   /*ʹ��MBMS��ʱ����*/
    LPHY_REQ_TIMING_MBMS_PARA,                  /*�ಥ��ʱ���ٲ���*/
    LPHY_REQ_TIMING_MBMS_TRMS_PARA,             /*�ಥ��ʱ����ʱ����չ����*/
    LPHY_REQ_TIMING_MBMS_LOOP_FILTER,           /*�ಥ��·�˲�����׮*/
    LPHY_REQ_TIMING_MBMS_CONST_ADVANCE,         /*�ಥ����ڵ�������ǰ��*/
    LPHY_REQ_TIMING_MBMS_EST_PERIOD,            /*�ಥ��ʱ��������*/
    LPHY_REQ_TIMING_MBMS_LONG_PERIOD,           /*�ಥ����������*/
    LPHY_REQ_TIMING_TRMS_STUB,                  /*����trms��׮*/
    LPHY_REQ_TIMING_MBMS_TRMS_STUB,              /*�ಥtrms��׮*/
	LPHY_REQ_TIMING_BUTT
};

typedef UINT32 LPHY_REQ_MSGID_TIMING_ENUM_UINT32;
typedef struct __LPHY_REQ_TIMING_ENA_TRU_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;          /*0,��ʹ�ܶ�ʱģ��; 1,ʹ�ܶ�ʱ*/
    UINT16                      usRsv;          /*4�ֽڶ���*/
}LPHY_REQ_TIMING_ENA_TRU_STRU;
typedef struct __LPHY_REQ_TIMING_MBMS_ENABLE_STUB_STRU__
{
    OM_REQ_ENABLE_ENUM   enEna;          /*0,��ʹ�ܶ�ʱģ��; 1,ʹ�ܶ�ʱ*/
}LPHY_REQ_TIMING_MBMS_ENABLE_STUB_STRU;

typedef struct __LPHY_REQ_TIMING_EST_PERIOD_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;          /*0,��ʹ�ܶ�ʱģ��; 1,ʹ�ܶ�ʱ*/
    UINT16                      usPeriod;       /*����Ϊ��λ*/
}LPHY_REQ_TIMING_EST_PERIOD_STRU;

enum TIMING_REQ_EST_FILTER_ENUM
{
    TIMING_REQ_PDP_FILTER_TIME,                 /*ǿ��ʱ���˲���ʽ*/
    TIMING_REQ_PDP_FILTER_FREQ,                  /*ǿ��Ƶ���˲���ʽ*/
    TIMING_REQ_PDP_FILTER_BUTT
};
typedef UINT16 TIMING_REQ_EST_FILTER_ENUM_UINT16;

typedef struct __LPHY_REQ_TIMING_PDP_FILTER_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16           enEna;          /*0,��ʹ�ܶ�ʱģ��; 1,ʹ�ܶ�ʱ*/
    TIMING_REQ_EST_FILTER_ENUM_UINT16   enFilt;         /*1 �Զ�ʱ����ʹ�õ��˲������д�׮:0, ����׮��1, Ƶ��2ʱ��*/
}LPHY_REQ_TIMING_PDP_FILTER_STRU;

typedef struct __LPHY_REQ_TIMING_LOOP_FILTER_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;          /*��·�˲�ϵ��ʹ��*/
    UINT16                      usRsv;          /*4�ֽڶ���*/
    UINT32                      ulKi;           /*��·�˲�ϵ��*/
}LPHY_REQ_TIMING_LOOP_FILTER_STRU;
#if 0
typedef struct __LPHY_REQ_TIMING_ENA_MPS_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;          /*0,��ʹ�ܶྶ����ģ�飬1��ʹ�ܶྶ������� */
    UINT16                      usRsv;          /*4�ֽڶ���*/
}LPHY_REQ_TIMING_ENA_MPS_STRU;
#endif
typedef struct __LPHY_REQ_TIMING_CONST_ADVANCE_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16    enEna;           /*ǿ����ǰֵ,Ĭ��Ϊ16*4=64(0.25Ts) */
    INT16                        sAdvance;        /*����ʼ�������Ľ��ǿ����ǰ���ٸ�(0.25Ts)*/
}LPHY_REQ_TIMING_CONST_ADVANCE_STRU;

typedef struct __LPHY_REQ_TIMING_TRMS_PARA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16    enEna;           /*1 ��ϵͳ��ʱ�����ϱ�ʹ�ܣ�0�ر�ʹ�� */
    UINT16                       usSrchWinLen[6]; /*��������*/
    UINT16                       usTrmsParThrd[6];/*�����������ֵ*/
    UINT8                        ucAverCoef1[6];  /*{3, 6, 6, 4, 4, 4}ƽ��ֵ��������1*/
    UINT8                        ucStartPath[6];  /*����ʱ����չ�о��ĵ�һ�����ľ��������*/
    UINT8                        ucPowerFactor;   /*������������*/
    UINT8                        ucAverCoef2;     /*ƽ��ֵ��������2*/
    UINT8                        ucAverCoef3;     /*ƽ��ֵ��������3*/
    UINT8                        uc1D4MThreshold1;/*TrmsFlag�о�����1*/
    UINT8                        uc1D4MThreshold2;/*TrmsFlag�о�����2*/
    UINT8                        ucDefaultValue;  /*��ʼ������ֵ�������㷨����*/
    UINT8                        ucDefaultValue1; /*�ڶ������Ĭ����(δ��PAR����),�����㷨����*/
    UINT8                        ucRsv[3];
}LPHY_REQ_TIMING_TRMS_PARA_STRU;

typedef struct __LPHY_REQ_TIMING_PARA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    INT8         cSysTimieLimit[2][6];
    UINT16                 usWin1a[6];
    UINT16             usWin1bWin2[6];
    UINT16                 usTa[2][6];
    UINT16      usTrefParThreshold[6];
    UINT8    ucDrxPresyncEstPeriod[2];
    UINT8       ucRrcIdleEstPeriod[2];
    UINT8            ucOtherEstPeriod;
    UINT8                       ucRsv;            /*4�ֽڶ���*/
    UINT8                 ucCaTref[6];
}LPHY_REQ_TIMING_PARA_STRU;

typedef struct __LPHY_REQ_TIMING_ENA_MBMS_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16    enEna;           /*1,ʹ��MBMS��ʱ����; 0,��ʹ�ܶ�ʱ����*/
    UINT16                      usRsv;            /*4�ֽڶ���*/
}LPHY_REQ_TIMING_ENA_MBMS_STRU;

typedef struct __LPHY_REQ_TIMING_MBMS_PARA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16     enEna;
    UINT16                  usW1aLen[6];
    UINT16                  usW1bLen[6];
    UINT16                  usW2aLen[6];
    UINT16                  usW2bLen[6];
    UINT16                  usFPWLen[6];
    UINT16                      usTa[6];
    UINT16                      usTb[6];
    UINT16                   usT_par[6];
    UINT16       usParThreshold_Tref[6];
    UINT8                    ucTref1[6];
    UINT8                    ucTref2[6];
    UINT8                        ucM[6];
    UINT8               ucSampleR[4][6];
    INT16           sResetLowThreshHold;
    INT16          sResetHighThreshHold;
    INT16                          sRsv;
}LPHY_REQ_TIMING_MBMS_PARA_STRU;

typedef struct __LPHY_REQ_TIMING_MBMS_TRMS_PARA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16     enEna;
    UINT16                 usWinLen1[6];
    UINT16                 usWinLen2[6];
    UINT16                 usWinLen3[6];
    UINT16          usM_PAR_Threhold[6];
    UINT16         usM_PAR_Threhold1[6];
    UINT16         usM_PAR_Threhold2[6];
    UINT16         usM_PAR_Threhold3[6];
    UINT16        usM_PAR_Threhold_L[6];
    UINT16           usM_PowerFactor[6];
    UINT16          usM_PowerFactor1[6];
    UINT16          usM_PowerFactor2[6];
    UINT16          usM_PowerFactor3[6];
    UINT16                 usConsti[12];
    UINT16          usStartIndexi[3][6];
    UINT8          ucM_AVG_Threhold1[6];
    UINT8          ucM_AVG_Threhold2[6];
    UINT8          ucM_AVG_Threhold3[6];
    UINT8         ucM_AVG_Threhold_L[6];
    UINT8             ucM_Avg_Factor[6];
    UINT8            ucM_Avg_Factor1[6];
    UINT8            ucM_Avg_Factor2[6];
    UINT8            ucM_Avg_Factor3[6];
    UINT8                        ucM[6];
    UINT8                        ucQ[6];
    UINT8          ucPathPowerThrehold0;
    UINT8          ucPathPowerThrehold1;
    UINT8                       ucCycle;
    UINT8                 ucWin3EffFlag;
    UINT8         ucWinProtectTrmsValue;
    UINT8        ucWin1ProtectTrmsValue;
    UINT8        ucWin2ProtectTrmsValue;
    UINT8        ucWin3ProtectTrmsValue;
    UINT8            ucTrmsReserveValue;
    UINT8               ucTrmsInitValue;
    UINT8             ucTrmsNoPathValue;
    UINT8           ucTrmsNoTimingValue;
    UINT8                      ucRsv[2];
}LPHY_REQ_TIMING_MBMS_TRMS_PARA_STRU;


typedef struct __LPHY_REQ_TIMING_RPT_SG_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;          /*1 ��ϵͳ��ʱ�����ϱ�ʹ�ܣ�0�ر�ʹ�� */
    UINT16                      usRsv;          /*4�ֽڶ���*/
}LPHY_REQ_TIMING_RPT_SG_STRU;

typedef struct __LPHY_REQ_TIMING_RPT_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;          /*1 ��ϵͳ��ʱ�����ϱ�ʹ�ܣ�0�ر�ʹ�� */
    UINT16                      usRsv;          /*4�ֽڶ���*/
}LPHY_REQ_TIMING_RPT_STRU;

typedef struct __LPHY_REQ_TIMING_TRMS_SAVE_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT8       ucNum;
    UINT8       ucNum2Value;
}LPHY_REQ_TIMING_TRMS_SAVE_STRU;

typedef struct __LPHY_REQ_TIMING_TRMS_STUB_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT8       ucTrms;
    UINT8       ucRsv;
}LPHY_REQ_TIMING_TRMS_STUB_STRU;

typedef struct __LPHY_REQ_TIMING_MBMS_TRMS_STUB_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT8       ucTrms;
    UINT8       ucRsv;
}LPHY_REQ_TIMING_MBMS_TRMS_STUB_STRU;

/************************************************************
                           2. CNF���ݽṹ����
************************************************************/
typedef enum __LPHY_CNF_MSGID_TIMING__
{
    LPHY_CNF_TIMING_RESERVED            = OM_CMD_ID(LPHY_TIMING_MID, OM_TYPE_CNF, 0x0),
}LPHY_CNF_MSGID_TIMING_ENUM;


/************************************************************
                           3. Ind���ݽṹ����
************************************************************/
enum LPHY_IND_MSGID_TIMING_ENUM
{
    LPHY_IND_TIMING_RESERVED            = OM_CMD_ID(LPHY_TIMING_MID, OM_TYPE_IND, 0x0),
    LPHY_IND_TIMING_BUTT
};
typedef UINT16 LPHY_IND_MSGID_TIMING_ENUM_UINT16;

/************************************************************
                           4. SG ���ݽṹ����, �㷨��Ҫ��ͼ��
************************************************************/
enum LPHY_SG_MSGID_TIMING_ENUM
{
    LPHY_SG_TIMING_RPT            = OM_CMD_ID(LPHY_TIMING_MID, OM_TYPE_SG, 0x0),/*�ϱ���ʱ���е�SG��Ϣ*/
    LPHY_SG_PDP_RPT_PCC,
    LPHY_SG_PDP_RPT_SCC,
    LPHY_SG_PDP_RPT_MBMS,
    LPHY_TIMING_RPT,
    LPHY_TIMING_PCC,
    LPHY_TIMING_SCC,
    LPHY_TIMING_STT,
    LPHY_TIMING_STA,
	LPHY_SG_TIMING_BUTT
};
typedef UINT16 LPHY_SG_MSGID_TIMING_ENUM_UINT16;
typedef struct __TIMING_PDP_STRU__
{
    UINT32    aulPdp[512];
}TIMING_PDP_STRU;
typedef struct __TIMING_COUNTER_INFO_STRU__
{
    UINT32 ulAfn;           /*����֡��*/
    UINT32 ulAbs;           /*����ʱ��*/
    UINT32 ulSfn;           /*ϵͳ֡��*/
    UINT32 ulSysTime;       /*ϵͳ��ʱ��ǰ����ֵ*/
}TIMING_COUNTER_INFO_STRU;

/* ��ʱ�л����� */
enum TIMING_SWITCH_TYPE_ENUM
{
    TIMING_SWITCH_NONE                = 0,
    TIMING_SWITCH_REQ,
    TIMING_SWITCHBACK_REQ,
    TIMING_SWITCH_TYPE_BUTT
};
typedef UINT16 TIMING_SWITCH_TYPE_ENUM_UINT16;

/*��¼��ʱ��������״̬*/
enum TIMING_CMD_STATE_ENUM
{
    TIMING_CMD_STATE_STOP = 0,
    TIMING_CMD_STATE_START,
    TIMING_CMD_STATE_BUTT
};
typedef UINT16 TIMING_CMD_STATE_ENUM_UINT16;

/*��¼��ʱ����״̬*/
enum TIMING_SDR_STATE_ENUM
{
    TIMING_SDR_STATE_STOPPED = 0,
    TIMING_SDR_STATE_RUNNING,
    TIMING_SDR_STATE_BUTT
};
typedef UINT16 TIMING_SDR_STATE_ENUM_UINT16;

enum TIMING_STATE_ENUM
{
    TIMING_RUN_STATE = 0,
    TIMING_STOP_STATE,
    TIMING_STATE_BUTT
};
typedef UINT16 TIMING_STATE_ENUM_UINT16;

/*�����ʱ��������*/
enum TIMING_EVT_ENUM
{
    TIMING_EVT_NONE         = 0x0,          /*���¼�*/
    TIMING_EVT_STOP         = (1<<0),       /*ǰ������ֹͣ��ʱ���٣��˺���hold״̬*/
    TIMING_EVT_START        = (1<<1),       /*ǰ��������ʱ���٣��ָ���ʱ����*/
    TIMING_EVT_START_RESET  = (1<<2),       /*ǰ�˸�λ�����ó�ʱ�����ʱλ�ã� ���ָ���ʱ����*/
    TIMING_EVT_SWITCH_RESET = (1<<3),       /*ǰ���л���ʱ����*/
    TIMING_EVT_SWITCH_BACK  = (1<<4),       /*ǰ�˻��ж�ʱ����*/
    TIMING_EVT_TCS          = (1<<5),       /*����С�������������, ֪ͨ��ʱ���ٽ��н����ʱ����*/
    TIMING_EVT_EST          = (1<<6),       /*���ڶ�ʱƫ���������Ľ����ʱ����*/
    TIMING_EVT_MPS          = (1<<7),       /*�ྶ��������Ľ����ʱ����*/
    TIMING_EVT_PRESYNC      = (1<<8),       /*Ԥͬ�������ϵͳ��ʱ����*/
    TIMING_EVT_MBMS_LONGPERIOD = (1<<9),    /*�ಥ������*/
    TIMING_EVT_SWITCH_NORESET   = (1<<10),
    TIMING_EVT_SWITCH_CA_RESET   = (1<<11),
    TIMING_EVT_SWITCH_TRACKING   = (1<<12),
    TIMING_EVT_EST_MBMS    = (1<<13),
    TIMING_EVT_BUTT
};
typedef UINT32 TIMING_EVT_ENUM_UINT32;

enum TIMING_SWITCH_CONFIG_ENUM
{
	TIMING_TRACKING_MODE = 0,
	TIMING_SWITCH_RESET_MODE,
	TIMING_SWITCH_NO_RESET_MODE,
	TIMING_SWITCH_CONFIG_BUTT
};
typedef  UINT16   TIMING_SWITCH_CONFIG_ENUM_UINT16;
#define TIMING_SWITCH_NO_RESET_MODE_BBP_CONFIG  3

/*1. ��ʱƫ�����ģ�������㷨PDP����(3.3.2��)�Ͷ�ʱƫ�����(3.3.3)������*/
typedef struct __TIMING_EST_STRU__ /*estimate*/
{
    UINT32                          ulTruNoise;
    UINT32 			                ulTruRsrp;
    UINT16                          usAfcUnLockedFlag;  /*AFC�������*/
    UINT16                          usFirstPathCmpFlag; /*�׾������ȽϿ���,default 1*/

    UINT16                          usFilterInitFlag;   /*�˲����Ƿ��ʼ��*/
    UINT16                          usDurMaxSubFrmNum;  /*һ��������������֡��*/

    UINT16                          usDurSubFrmCounter; /*һ��������������֡��������������֡*/
    UINT16                          usVldMaxSubFrmNum;  /*һ����������Ч������֡����*/

    UINT16                          usVldSubFrmCounter; /*һ���������Ѿ���ɵ���Ч������֡����*/
    //UINT16                          usAlphaStateFlag;   //Alpha�˲���ʼ����־
    //UINT16                          usReserved;
    UINT16                          usSavedFilterPAR;   /*�˲���ķ����ֵ*/

    UINT16                          usSavedOncePAR;     /*���η����ֵ*/
    UINT16                          usLowPARThreshold;  /*������ȷ����ֵ��ֵ*/

    UINT16                          usLowPARFlagSuccNum;/*����������ȸ���*/
    UINT16                          usLowPARHoldFlag;   /*�������HoldFlagָʾ*/

    UINT16                          usIsCaclDone;       /*Ӳ��δ��������*/
    UINT16                          usSubFrmNumOfCaclDone;    /*Ӳ��δ��������*/

    INT16                           sDelta;             /*���һ�εĶ�ʱƫ�����ֵ,��λ:0.5Ts*/
    INT16                           usTrefParThreshold; /*������ǰ�������PAR��ֵ*/

    TIMING_SDR_STATE_ENUM_UINT16    enState;            /*��ʱƫ�����״̬��*/
    UINT16                          usExcTerminateFlag; /*���ι��ƽ�������ţ�Ŀǰ����Ϊ��ǰ����gap*/

    INT16                           sTref[2];           /*��ǰ��*/

    UINT8                           ucTimeCoef;
    UINT8                           ucFreqCoef;
    UINT8                           ucLeftCoef;
    UINT8                           ucRightCoef;
}TIMING_EST_STRU;

#if 0
/*2. �ྭ�������֣������㷨�ྭ����(3.3.4��)�����Ӧ�Ĺ��ܲ���*/
typedef struct __TIMING_MPS_STRU__
{

    UINT16                          usFilterInitFlag;   /*�˲����Ƿ��ʼ��*/
    INT16                           sSinglePAR;         /*���η����,for om*/
    INT16                           sFilterPAR;         /*�˲���ķ����, for om*/
    INT16                           usHoldFlag;         /*�ྶ�������, for om*/

    INT16                           sDelta1;            /*���һ�λ���ǰ0~5����Ķ�ʱƫ�����ֵ*/
    INT16                           sDelta0;            /*ǰ6~10����Ķ�ʱƫ�����ֵ*/

    UINT16                          usCollisionFlag;    /*С����ײ���*/
    UINT16                          usLastCalcTiming;   /*ǰһ�μ�����ײ��ϵͳ֡��*/

    TIMING_SDR_STATE_ENUM_UINT16    enState;            /*�ྶ����ƫ�����״̬��*/

    UINT16                          usThresholdCounter;              /*4�ֽڶ���*/
}TIMING_MPS_STRU;
#endif

/*3. �����ʱ���ٲ��֣������㷨��·�˲�(3.3.5)�����Ӧ�Ĺ��ܲ���*/
typedef struct __TIMING_DTT_STRU__
{
    /*�ⲿģ�鴥���������¼�*/
    TIMING_EVT_ENUM_UINT32          enEvents;           /*���붨ʱ�����¼�*/
    TIMING_EVT_ENUM_UINT32          enBakEvents;        /*�������붨ʱ�����¼�,������*/
    UINT32                          ulTcsValue;         /*С�����������ĵ�ǰС��ͬ��λ��: 0.25Ts*/
    INT16                           sEstDelta;          /*�����Ķ�ʱ����ƫ��, 0.5Ts��λ*/
    UINT16                           usReserved;//sMpsDelta;          /*0.5Ts��λ*/

    UINT16                          usCurKiIndex;       /*��ʱƫ�ǰ�˲�ϵ��*/
    UINT16                          usNcsCounter;       /*������*/
    UINT32                          ulCompItoFlag;
    INT32                           lLastAdjustRemain;  /*�ϴε���������*/
    UINT32                          ulBakDemodTime;     /*���ݵĽ����ʱλ��*/
    INT32                           lBakTimeAdjust;     /*���ݵĶ�ʱ������*/
    UINT16                          usBakKiIndex;       /*�����˲���ϵ��*/

    /*�����ǰ��ʱ�������ͣ������ʱ��������*/
    UINT16                          usResetFlag;        /*���ñ��*/
    INT32                           lTimeAdjust;        /*��ʱ����ֵ��0.25TS��λ*/
    UINT32                          ulDemodTime;        /*��һ��֡�����ʱλ��*/
    UINT32                          ulPenulDemodTime;     /*�����ڶ�����֡�Ľ����ʱ, ��λ: 0.25Ts*/
    UINT32                          ulLastDemodTime;      /*������һ����֡�Ľ����ʱ, ��λ: 0.25Ts*/
    UINT32                          ulCurDemodTime;       /*��ǰ��֡�Ľ����ʱ, ��λ: 0.25TS*/

}TIMING_DTT_STRU;

/*4. ϵͳ��ʱ���ٲ��֣������㷨ϵͳ��ʱ���㲿��(3.3.6��)*/
typedef struct __TIMING_STT_STRU__
{
    /*�ⲿģ�鴥�����¼�*/
    TIMING_EVT_ENUM_UINT32          enEvents;           /*���붨ʱ�����¼�*/
    INT16                           sResetCompDelta;    /*�����ʱͻ�䵼��ϵͳ��ʱ������0.25Ts*/
    UINT16                          usDemCounter;       /*�����ʱ�����������*/
    INT32                           lSingleIOAcc;       /*���뵥���ۼ���*/
    INT32                           lSysTimeAccValue;   /*ϵͳ��ʱ�����ۻ���ֵ*/
    INT32                           lLastAvgAcc;        /*ϵͳ��ʱ�ۺ�ƽ��ֵ*/
    INT32                           lLastCompsent;      /*�ۺ�ƽ���ü�ȥ���뵥���ۺ�ֵʣ�µĲ���ֵ*/
    INT32                           lLastRemainder;     /*��һ��ʣ�µĵ�����*/

    INT32                           lAdjustValue;       /*ϵͳ��ʱ������,0.5TS��λ*/
    UINT32                          ulSysTime;          /*ϵͳ��ʱλ��*/
}TIMING_STT_STRU;

/*5. �����ʱ�������֣����ݽ����ʱ���ٵĽ������Ӳ�����ж�ʱ����*/
typedef struct __TIMING_DTA_STRU__
{
    /*�ⲿģ�鴥�����¼�*/
    TIMING_EVT_ENUM_UINT32          enEvents;                    /*���붨ʱ�����¼�*/
    TIMING_EVT_ENUM_UINT32          enHwEvents;                  /*��������ĵ����¼�*/

    /*ԭʼ���������ʱ*/
    UINT32                          ulOrgNormalPenulDemodTime;   /*�����ڶ�����֡�Ľ����ʱ, ��λ: 0.25Ts*/
    UINT32                          ulOrgNormalLastDemodTime;    /*������һ����֡�Ľ����ʱ, ��λ: 0.25Ts*/
    UINT32                          ulOrgNormalCurDemodTime;     /*��ǰ��֡�Ľ����ʱ, ��λ: 0.25TS*/
    UINT32                          ulOrgNormalNextDemodTime;    /*��һ����֡�Ľ����ʱ, ��λ: 0.25TS*/

    /*�����ĵ��������ʱ*/
    UINT32                          ulNormalPenulDemodTime;     /*�����ڶ�����֡�Ľ����ʱ, ��λ: 0.25Ts*/
    UINT32                          ulNormalLastDemodTime;      /*������һ����֡�Ľ����ʱ, ��λ: 0.25Ts*/
    UINT32                          ulNormalCurDemodTime;       /*��ǰ��֡�Ľ����ʱ, ��λ: 0.25TS*/
    UINT32                          ulNormalNextDemodTime;      /*��һ����֡�Ľ����ʱ, ��λ: 0.25TS*/

    /*ͨ��ԭʼֵ������ĸ�AFC�ĵ�����*/
    INT32                           lNormalTimeAdjust;        /*����������*/

    /*�������*/
    UINT8                           ucErrResetFlag;           /*������ʱƫ��̫���µ����ñ��,�ϱ�Э��ջ����*/
    UINT8                           ucInitResetFlag;          /*��ʼ�����ñ��*/
    UINT8                           ucTcsResetFlag;           /*��С����������͵�ǰ�����ʱλ��ƫ��̫���µ����ñ��*/
    UINT8                           ucReserved;

    UINT8                           ucNormalEstAdjFlag;       /*�������Ƶ������*/
    UINT8                           ucSubRef;                 /*���������ö�ʱ��ǰ��*/
    UINT16                          usReserved;
    UINT32							pFpu;

}TIMING_DTA_STRU;
typedef struct __TIMING_MBMS_DTA_STRU__
{
    TIMING_EVT_ENUM_UINT32          enMbmsEvents;                /*���붨ʱ�����¼�*/
    TIMING_EVT_ENUM_UINT32          enMbmsHwEvents;              /*��������ĵ����¼�*/
    /*ԭʼ�ಥ�����ʱ*/
    UINT32                          ulOrgMbmsPenulDemodTime;     /*�����ڶ�����֡�Ľ����ʱ, ��λ: 0.25Ts*/
    UINT32                          ulOrgMbmsLastDemodTime;      /*������һ����֡�Ľ����ʱ, ��λ: 0.25Ts*/
    UINT32                          ulOrgMbmsCurDemodTime;       /*��ǰ��֡�Ľ����ʱ, ��λ: 0.25TS*/
    UINT32                          ulOrgMbmsNextDemodTime;      /*��һ����֡�Ľ����ʱ, ��λ: 0.25TS*/
    /*�����Ķಥ�����ʱ*/
    UINT32                          ulMbmsPenulDemodTime;       /*�����ڶ�����֡�Ľ����ʱ, ��λ: 0.25Ts*/
    UINT32                          ulMbmsLastDemodTime;        /*������һ����֡�Ľ����ʱ, ��λ: 0.25Ts*/
    UINT32                          ulMbmsCurDemodTime;         /*��ǰ��֡�Ľ����ʱ, ��λ: 0.25TS*/
    UINT32                          ulMbmsNextDemodTime;        /*��һ����֡�Ľ����ʱ, ��λ: 0.25TS*/

    /*ͨ��ԭʼֵ������ĸ�AFC�ĵ�����*/
    INT32                           lMbmsTimeAdjust;          /*�ಥ������*/
    INT32                           lAdjustValue;             /*��AFC�ĵ�����*/

    /*�������*/
    UINT8                           ucMbmsResetFlag;          /*�ಥ���ñ��*/
    UINT8                           ucMbmsEstAdjFlag;         /*�ಥ�������*/
    UINT8                           ucMbmsFlag;               /*�ಥ��ID���߷���ID����*/
    UINT8                           ucSubRef;                 /*���������ö�ʱ��ǰ��*/

}TIMING_MBMS_DTA_STRU;

/*6. ϵͳ��ʱ�������֣�����ϵͳ��ʱ���ٵĽ������Ӳ�����ж�ʱ����*/
typedef struct __TIMING_STA_STRU__
{
    /*�ⲿģ�鴥�����¼�*/
    TIMING_EVT_ENUM_UINT32          enEvents;           /*���붨ʱ�����¼�*/
    TIMING_EVT_ENUM_UINT32          enHwEvents;         /*����Ӳ�������¼�*/

    UINT32                          ulLastSysTime;      /*ǰһ��֡��ϵͳ��ʱ, ��λ: 0.25TS*/
    UINT32                          ulCurSysTime;       /*��ǰ��֡��ϵͳ��ʱ, ��λ: 0.25TS*/
    UINT32                          ulNextSysTime;      /*��һ����֡��ϵͳ��ʱ, ��λ: 0.25TS*/

    UINT32                          ulBakSysTime;       /*���ݵ�ϵͳ��ʱ, ��λ: 0.25TS*/
    /*�������һ����ϵͳ��ʱ��Ӧ�ļ����Ĵ��������е�ʱ��ͨ����Щֵ������ظ�SFN*/
    TIMING_COUNTER_INFO_STRU        stSysTimCntRegs;    /*��¼ϵͳ��ʱ��صļ����Ĵ���*/

}TIMING_STA_STRU;


/*7. ��ʱ���Ʋ��֣���Ҫ��¼�Ϳ��Ƶ�ǰ������ִ��״̬*/
typedef struct __timing_controller_stru__
{
    TIMING_CMD_STATE_ENUM_UINT16    enCmd;              /*��¼���������ܵ�����״̬*/
    TIMING_SWITCH_TYPE_ENUM_UINT16  enSwitchType;       /*��¼��ʱ�л�����*/
    UINT32                          ulCurSyncPos;       /*��ǰС����ͬ��λ��: 16Ts*/
    UINT32                          ulBakSyncPos;       /*����С����ͬ��λ��: 16Ts*/
    UINT16                         usSccTimingStartFlag;
    UINT16                         usMbmsTimingStartFlag;
    //UINT32                          ulBgsAnrSyncPos;    /*�����ѻ�ANRС����ͬ��λ��: 16Ts*/
    LTE_CELL_INFO_STRU              stCurCellInfo[LPHY_FEATURE_MAX_CARRIER_NUM_TRU];      /*��ǰС���Ĳ�����Ϣ*/
    LTE_CELL_INFO_STRU              stBakCellInfo;      /*����С���Ĳ�����Ϣ*/
    UINT16                          usPreSyncFlag;
    UINT16                          usReserved;
    //LTE_CELL_INFO_STRU              stBgsAnrCellInfo;   /*�����ѻ�ANRС���Ĳ�����Ϣ*/
}TIMING_CONTROLLER_STRU;


/*8. ʱ����չ���㲿�֣���Ӧ�㷨ʱ����չ����(3.3.7��)*/
typedef struct __timing_trms_stru__
{
    UINT16                          usTrms;             /*trms���*/
    UINT16                          usNoiseFlag1;       /*�쳣���*/
    UINT16                          usRawTrmsFlag;      /*�ֽڶ���*/
    UINT8                           ucCurSaveTrmsPos;   /*��ǰtrmsλ��*/
    UINT8                           ucVldSaveTrmsNum;   /*�������Ч����*/
    UINT8                           ucTrmsSave[32];     /*����32����ʷֵ*/
    UINT32                          ulSqrPowMulPosAcc;  /*���׾�*/
    UINT32                          ulValidPowMulPosAcc;/*һ�׾�*/
    UINT32                          ulMolecule;         /*����*/
    UINT32                          ulDenominator0;     /*����*/
    UINT32                          ulDenominator1;
    UINT32                          ulShiftM;
    UINT32                          ulValidPowMulPosAccInt;
    UINT32                          ulValidPowerAcc;
    UINT32                          ulPowerAve;
    UINT32                          ulPdpMaxPower;
    UINT32                          ulPdpSubMaxPower;
    UINT32                          ulValidPosMax;
    UINT32                          ulPowerTh;
    UINT32                          ulValidPowerAccRest;
    UINT32                          ulValidPowMulPosAccRest;
    UINT32                          ullSqrPowMulPosAccRest;
}TIMING_TRMS_STRU;
#if 0
typedef struct __timing_mbms_trms_stru__
{
    UINT32                          ulStateRegValue;    /*״̬�Ĵ���*/
    UINT32                          ulResultRegValue;   /*ʱ����չ�Ĵ���*/
    UINT16                          usSavedFilterPAR[3];/*�˲���ķ����ֵ*/
    UINT16                          usSavedOncePAR[3];   /*�˲���ķ����ֵ*/
    UINT32                          ulSaveTrmsAvg[4];   /*������ƽ���������ڵľ�ֵ����ʱ���ٺ�ʱ����չ����*/

    UINT8                           ucWin1ProtectFlag;  /*��1�������*/
    UINT8                           ucWin2ProtectFlag;  /*��2�������*/
    UINT8                           ucWin3ProtectFlag;  /*��3�������*/
    UINT8                           ucWin3ProtectFlag1; /*��3�������1*/
    UINT8                           ucWin3ProtectFlag2; /*��3�������2*/
    UINT8                           ucWinProtectFlag;   /*�ܴ��������*/
    UINT8                           ucWinTrmsValueL;    /*�ܴ�trmsֵ*/
    UINT8                           ucWin1TrmsValueL;   /*��1trmsֵ*/

    UINT16                          usTrms;             /*trms���*/
    UINT16                          usRsv;
}TIMING_MBMS_TRMS_STRU;
#endif
typedef struct __TIMING_MBMS_CTRL_STRU__
{
    TIMING_CMD_STATE_ENUM_UINT16    enCmd;              /*MBMSģ��Ĵ�������*/
    TIMING_SDR_STATE_ENUM_UINT16    enState;            /*MBMS��ʱƫ�����״̬��*/
    UINT16                          usAllocType;        /*MBMS��ÿ�������еķ���㲥֡��,1����4*/
    UINT16                          usAllocPeriod;      /*MBMS�ķ�������*/
    UINT16                          usAllocSubFrmNum;   /*MBMS��ÿ�������з������֡��*/
    UINT16                          usRsv;              /*4�ֽڶ���*/
    LTE_CELL_INFO_STRU              stCurCellInfo;      /*MBMS��Ӧ��С������*/
}TIMING_MBMS_CTRL_STRU;

typedef struct __TIMING_NORMAL_STRU__
{
    TIMING_EST_STRU                 stEst;              /*��ʱƫ�����*/
    TIMING_DTT_STRU                 stDtt;              /*�����ʱ����*/
    TIMING_TRMS_STRU                stTrms;             /*ʱ����չ����*/
    TIMING_DTA_STRU                 stDta;              /*�����ʱ����*/
}TIMING_NORMAL_STRU;

typedef struct __TIMING_MBMS_STRU__
{
    TIMING_EST_STRU                 stEst;              /*�ಥ��ʱ���ٹ���*/
    TIMING_DTT_STRU                 stDtt;              /*�ಥ��ʱ���ٽ����ʱ����*/
    TIMING_MBMS_DTA_STRU           stDta;
    //TIMING_MBMS_TRMS_STRU           stTrms;             /*�ಥʱ����չ*/
    TIMING_MBMS_CTRL_STRU           stCtrl;             /*�ಥ��ʱ���ٿ���*/
}TIMING_MBMS_STRU;

typedef struct __TIMING_INFO_STRU__
{
    UINT16                          usFreqId;           /*С��Ƶ��*/
    UINT16                          usCellId;           /*С��ID*/
    UINT32                          ulPosOfSubFrmZero;  /*��֡0ͬ��ͷ��Ӧ�ľ���ʱ��,��ʼ����ͬ��λ�� 0.25Ts*/
    UINT16                          usAfnOfSysFrmZero; /*ϵͳ֡0,��֡0ͬ��ͷ��Ӧ��mfn,��λΪ֡*/
    UINT16                          usSysFrmNum;        /*ά����Ӧ��ϵͳ֡��*/
    UINT8                           ucSubFrmNum;        /*ά����Ӧ����֡��*/
    UINT8                           ucSysFrmNumVld;     /*ά����ϵͳ֡���Ƿ���Ч:LPHY_TRUE ��ʾ��Ч, LPHY_FALSE��ʾ��Ч*/
    UINT8                           ucSubFrmNumVld;     /*ά������֡���Ƿ���Ч:LPHY_TRUE ��ʾ��Ч, LPHY_FALSE��ʾ��Ч*/
    UINT8                           ucValid;            /*�Ƿ�ʼ����ά��*/
}TIMING_INFO_STRU;


/*9. ��ʱģ��ṹ����*/
typedef struct __TIMING_MODULE_STRU__
{
    UINT16                          usSysFrmNum;        /*�ϱ�ʱ���ϵͳ֡��*/
    UINT16                          usSubFrmNum;        /*�ϱ�ʱ�̵���֡��*/
	TIMING_STATE_ENUM_UINT16        aenTimingState[LPHY_FEATURE_MAX_CARRIER_NUM_TRU];
	TIMING_STATE_ENUM_UINT16        enTimingMbmsState;
    LTE_DRX_TIMING_STATE_ENUM_UINT16    enPreSyncFlag;

    TIMING_NORMAL_STRU              stNormal[LPHY_FEATURE_MAX_CARRIER_NUM_TRU];           /*������ʱ���ٿ���*/
    TIMING_CONTROLLER_STRU          stCtrl;             /*��ʱ����*/
    TIMING_MBMS_STRU                stMbms;             /*MBMS�Ķ�ʱ���ٿ���*/
    TIMING_STT_STRU                 stStt;              /*ϵͳ��ʱ����*/
    //TIMING_DTA_STRU                 stDta;              /*�����ʱ����*/
    TIMING_STA_STRU                 stSta;              /*ϵͳ��ʱ����*/
    TIMING_INFO_STRU                stMaintainedInfo[3];/*λANR���ӵ�ά����ʱС��*/
}TIMING_MODULE_STRU;

typedef struct __TIMING_COMMON_STRU__
{
    UINT16                              usSysFrmNum;        /*�ϱ�ʱ���ϵͳ֡��*/
    UINT16                              usSubFrmNum;        /*�ϱ�ʱ�̵���֡��*/
    LTE_DRX_TIMING_STATE_ENUM_UINT16    enPreSyncFlag;
    TIMING_CMD_STATE_ENUM_UINT16        enCmd;              /*��¼���������ܵ�����״̬*/
    TIMING_SWITCH_TYPE_ENUM_UINT16      enSwitchType;       /*��¼��ʱ�л�����*/
    UINT16                              usSccTimingStartFlag;
    UINT32                              ulCurSyncPos;       /*��ǰС����ͬ��λ��: 16Ts*/
    UINT32                              ulBakSyncPos;       /*����С����ͬ��λ��: 16Ts*/
    LTE_CELL_INFO_STRU                  stBakCellInfo;      /*����С���Ĳ�����Ϣ*/
}TIMING_COMMON_STRU;

typedef struct __TIMING_CA_STRU__
{
    TIMING_STATE_ENUM_UINT16        enTimingState;
    UINT16                          usRev;

    /*�ⲿģ�鴥�����¼�*/
    TIMING_EVT_ENUM_UINT32          enEvents;                    /*���붨ʱ�����¼�*/
    TIMING_EVT_ENUM_UINT32          enHwEvents;                  /*��������ĵ����¼�*/

    TIMING_EST_STRU                 stEst;              /*��ʱƫ�����*/
    TIMING_DTT_STRU                 stDtt;              /*�����ʱ����*/
    LTE_CELL_INFO_STRU              stCurCellInfo;

}TIMING_CA_STRU;

typedef struct __TIMING_OM_STRU__
{
    TIMING_COMMON_STRU              stTruCommon;
    TIMING_CA_STRU                  astTruCa[LPHY_FEATURE_MAX_CARRIER_NUM];
    TIMING_STT_STRU                 stStt;              /*ϵͳ��ʱ����*/
    TIMING_STA_STRU                 stSta;              /*ϵͳ��ʱ����*/
}TIMING_OM_STRU;


/************************************************************
                           5. TRACE���ݽṹ����
************************************************************/
enum LPHY_TRACE_TIMING_ENUM
{
    LPHY_TRACE_TIMING_RESERVED              = OM_CMD_ID(LPHY_TIMING_MID, OM_TYPE_TRACE, 0x0),
    LPHY_TRACE_TIMING_TRACE_BINARY          = OM_CMD_ID(LPHY_TIMING_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_TIMING_TRACE,
    LPHY_TRACE_TIMING_BUTT
};
typedef UINT16 LPHY_TRACE_TIMING_ENUM_UINT16;

enum LPHY_TRACE_TIMING_TRACE_ENUM
{
    LPHY_TRACE_TIMING_TRACE_START_TRACK,
    LPHY_TRACE_TIMING_TRACE_STOP_TRACK,
    LPHY_TRACE_TIMING_TRACE_SWITCH,
    LPHY_TRACE_TIMING_TRACE_BUTT
};
typedef UINT16 LPHY_TRACE_TIMING_TRACE_ENUM_UINT16;

typedef struct __LPHY_TRACE_TIMING_TRACE_STRU__
{
    LPHY_TRACE_TIMING_TRACE_ENUM_UINT16  enStat;
}LPHY_TRACE_TIMING_TRACE_STRU;


typedef struct __TIMING_MBMS_PDP_STRU__
{
    UINT32    aulPdpMbms[1024];
}TIMING_MBMS_PDP_STRU;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TIMING_OM_DEF_H__ */