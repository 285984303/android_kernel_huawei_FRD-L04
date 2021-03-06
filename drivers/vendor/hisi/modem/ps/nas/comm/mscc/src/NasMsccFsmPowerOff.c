/******************************************************************************

            Copyright 2014, Huawei Technologies Co. Ltd.

 ******************************************************************************
File Name       :   NasMsccFsmPowerOff.c
Author          :   k902809
Version         :
Date            :   2015-01-30
Description     :   Contains FSM tables and act tables for MSCC Power-off flow FSM.
                    Interface definistions
Function list   :
History         :
    1) Date :
       Author:
       Modification:
******************************************************************************/


/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasMsccFsmPowerOff.h"
#include "NasMntn.h"
#include "NasMsccFsmPowerOffTbl.h"
#include "NasMsccSndImsa.h"
#include "NasMsccSndInternalMsg.h"

#include "NasMsccSndMma.h"
#include "NasComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MSCC_FSM_POWER_OFF_C

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*****************************************************************************
  6 函数实现
*****************************************************************************/


VOS_UINT32 NAS_MSCC_RcvMmaPowerOffReq_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    ulModuleId                          = 0;

    NAS_MSCC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* Check the module order is valid or not in power off module order list */
    if (VOS_TRUE == NAS_MSCC_IsModuleOrderValid_PowerOff())
    {
        ulRslt = NAS_MSCC_GetNextModuleId_PowerOff(&ulModuleId);
        if (VOS_TRUE == ulRslt)
        {
            /* Send power off request to respective module */
            NAS_MSCC_SndPowerOffReq(ulModuleId);
            return VOS_TRUE;
        }
    }

    NAS_TRACE_HIGH("NAS_MSCC_RcvMmaPowerOffReq_PowerOff_Init: There is empty module list");

    /* Complete the power off flow */
    NAS_MSCC_ProcPowerOffComplete();

    return VOS_TRUE;

}


#if (FEATURE_IMS == FEATURE_ON)

VOS_UINT32 NAS_MSCC_RcvImsaPowerOffCnf_PowerOff_WaitImsaPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    ulModuleId                          = 0;

    /* Stop the timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_IMSA_POWER_OFF_CNF);

    NAS_MSCC_SndMmaImsSwitchStateInd(NAS_MSCC_PIF_IMS_SWITCH_STATE_OFF);

    /* Get the next module id */
    ulRslt = NAS_MSCC_GetNextModuleId_PowerOff(&ulModuleId);
    if (VOS_TRUE == ulRslt)
    {
        /* Send power off request to respective module */
        NAS_MSCC_SndPowerOffReq(ulModuleId);
        return VOS_TRUE;
    }

    /* Complete the power off flow */
    NAS_MSCC_ProcPowerOffComplete();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvTiWaitImsaPowerOffCnfExpired_PowerOff_WaitImsaPowerOffCnf(

    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    ulModuleId                          = 0;

    /* Log the warning */
    NAS_TRACE_HIGH("NAS_MSCC_RcvTiWaitImsaPowerOffCnfExpired_PowerOff_WaitImsaPowerOffCnf:time expired!");

    NAS_MSCC_SndMmaImsSwitchStateInd(NAS_MSCC_PIF_IMS_SWITCH_STATE_OFF);

    /* IMSA power off operation expired then get next module to power off */
    ulRslt = NAS_MSCC_GetNextModuleId_PowerOff(&ulModuleId);
    if (VOS_TRUE == ulRslt)
    {
        /* Fo Power off next module */
        NAS_MSCC_SndPowerOffReq(ulModuleId);

        return VOS_TRUE;
    }

    /* If no module is there then send internal message to main FSM */
    NAS_MSCC_ProcPowerOffExpired();

    return VOS_TRUE;
}
#endif



VOS_UINT32 NAS_MSCC_RcvMmcPowerOffCnf_PowerOff_WaitMmcPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;


    ulModuleId                          = 0;

    /* Stop the MMC Power off protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_POWER_OFF_CNF);

    /* Get the next module id */
    ulRslt = NAS_MSCC_GetNextModuleId_PowerOff(&ulModuleId);
    if (VOS_TRUE == ulRslt)
    {
        /* Send power off request to respective module */
        NAS_MSCC_SndPowerOffReq(ulModuleId);
        return VOS_TRUE;
    }

    /* Complete the power off flow */
    NAS_MSCC_ProcPowerOffComplete();

    return VOS_TRUE;

}



VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPowerOffCnfExpired_PowerOff_WaitMmcPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    ulModuleId                          = 0;

    /* Log the warning */
    NAS_TRACE_HIGH("NAS_MSCC_RcvTiWaitMmcPowerOffCnfExpired_PowerOff_WaitMmcPowerOffCnf:time expired!");

    /* MMC power off operation expired then get next module to power off */
    ulRslt = NAS_MSCC_GetNextModuleId_PowerOff(&ulModuleId);
    if (VOS_TRUE == ulRslt)
    {
        /* Fo Power off next module */
        NAS_MSCC_SndPowerOffReq(ulModuleId);

        return VOS_TRUE;
    }

    /* If no module is there then send internal message to main FSM */
    NAS_MSCC_ProcPowerOffExpired();

    return VOS_TRUE;
}


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)


VOS_UINT32 NAS_MSCC_RcvXsdPowerOffCnf_PowerOff_WaitXsdPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    NAS_TRACE_HIGH("Receive Msg!");

    ulModuleId                          = 0;

    /* Stop the XSD Power off protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_XSD_POWER_OFF_CNF);

    /* Get the next module id */
    ulRslt = NAS_MSCC_GetNextModuleId_PowerOff(&ulModuleId);
    if (VOS_TRUE == ulRslt)
    {
        /* Send power off request to respective module */
        NAS_MSCC_SndPowerOffReq(ulModuleId);
        return VOS_TRUE;
    }

    /* Complete the power off flow */
    NAS_MSCC_ProcPowerOffComplete();

    return VOS_TRUE;

}


VOS_UINT32 NAS_MSCC_RcvTiWaitXsdPowerOffCnfExpired_PowerOff_WaitXsdPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    ulModuleId                          = 0;

    /* Log the warning */
    NAS_TRACE_HIGH("NAS_MSCC_RcvTiWaitXsdPowerOffCnfExpired_PowerOff_WaitXsdPowerOffCnf:time expired!");

    /* MMC power off operation expired then get next module to power off */
    ulRslt = NAS_MSCC_GetNextModuleId_PowerOff(&ulModuleId);
    if (VOS_TRUE == ulRslt)
    {
        /* Fo Power off next module */
        NAS_MSCC_SndPowerOffReq(ulModuleId);

        return VOS_TRUE;
    }

    /* If no module is there then send internal message to main FSM */
    NAS_MSCC_ProcPowerOffExpired();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvHsdPowerOffCnf_PowerOff_WaitHsdPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    NAS_TRACE_HIGH("Receive Msg!");

    ulModuleId                          = 0;

    /* Stop the HSD Power off protection timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_POWER_OFF_CNF);

    /* Get the next module id */
    ulRslt = NAS_MSCC_GetNextModuleId_PowerOff(&ulModuleId);
    if (VOS_TRUE == ulRslt)
    {
        /* Send power off request to respective module */
        NAS_MSCC_SndPowerOffReq(ulModuleId);
        return VOS_TRUE;
    }

    /* Complete the power off flow */
    NAS_MSCC_ProcPowerOffComplete();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvTiWaitHsdPowerOffCnfExpired_PowerOff_WaitHsdPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    ulModuleId                          = 0;

    /* Log the warning */
    NAS_TRACE_HIGH("NAS_MSCC_RcvTiWaitHsdPowerOffCnfExpired_PowerOff_WaitHsdPowerOffCnf:time expired!");

    /* MMC power off operation expired then get next module to power off */
    ulRslt = NAS_MSCC_GetNextModuleId_PowerOff(&ulModuleId);
    if (VOS_TRUE == ulRslt)
    {
        /* Fo Power off next module */
        NAS_MSCC_SndPowerOffReq(ulModuleId);

        return VOS_TRUE;
    }

    /* If no module is there then send internal message to main FSM */
    NAS_MSCC_ProcPowerOffExpired();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvXsdPowerSaveCnf_PowerOff_WaitCLPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           uc1xActFlg;
    VOS_UINT8                           ucHrpdActFlg;
    VOS_UINT8                           uc3gppActFlg;

    ucHrpdActFlg   = NAS_MSCC_GetHrpdActiveFlg();
    uc3gppActFlg   = NAS_MSCC_Get3gppActiveFlg();
    uc1xActFlg     = NAS_MSCC_Get1xActiveFlg();

    if ((VOS_FALSE  == ucHrpdActFlg)
     && (VOS_FALSE  == uc3gppActFlg)
     && (VOS_FALSE  == uc1xActFlg))
    {
        NAS_MSCC_ProcPowerSaveComplete();
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvHsdPowerSaveCnf_PowerOff_WaitCLPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           uc1xActFlg;
    VOS_UINT8                           ucHrpdActFlg;
    VOS_UINT8                           uc3gppActFlg;

    ucHrpdActFlg   = NAS_MSCC_GetHrpdActiveFlg();
    uc3gppActFlg   = NAS_MSCC_Get3gppActiveFlg();
    uc1xActFlg     = NAS_MSCC_Get1xActiveFlg();

    if ((VOS_FALSE == ucHrpdActFlg)
     && (VOS_FALSE == uc3gppActFlg)
     && (VOS_FALSE == uc1xActFlg))
    {
        NAS_MSCC_ProcPowerSaveComplete();
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmcPowerSaveCnf_PowerOff_WaitCLPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           uc1xActFlg;
    VOS_UINT8                           ucHrpdActFlg;
    VOS_UINT8                           uc3gppActFlg;

    ucHrpdActFlg   = NAS_MSCC_GetHrpdActiveFlg();
    uc3gppActFlg   = NAS_MSCC_Get3gppActiveFlg();
    uc1xActFlg     = NAS_MSCC_Get1xActiveFlg();

    if ((VOS_FALSE == ucHrpdActFlg)
     && (VOS_FALSE == uc3gppActFlg)
     && (VOS_FALSE == uc1xActFlg))
    {
        NAS_MSCC_ProcPowerSaveComplete();
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvTiWaitCLPowerSaveCnfExpired_PowerOff_WaitCLPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitCLPowerSaveCnfExpired_PowerOff_WaitCLPowerSaveCnf: timer out");

    NAS_MSCC_ProcPowerSaveComplete();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvTiScanTimerExpired_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           uc1xActFlg;
    VOS_UINT8                           ucHrpdActFlg;
    VOS_UINT8                           uc3gppActFlg;

    NAS_MSCC_SaveCurEntryMsg(ulEventType, pstMsg);

    ucHrpdActFlg   = NAS_MSCC_GetHrpdActiveFlg();
    uc3gppActFlg   = NAS_MSCC_Get3gppActiveFlg();
    uc1xActFlg     = NAS_MSCC_Get1xActiveFlg();

    if ((VOS_FALSE == ucHrpdActFlg)
     && (VOS_FALSE == uc3gppActFlg)
     && (VOS_FALSE == uc1xActFlg))
    {
        NAS_MSCC_ProcPowerSaveComplete();

        return VOS_TRUE;
    }

    if (VOS_TRUE == uc3gppActFlg)
    {
        NAS_MSCC_SndMmcPowerSaveReq();
    }

    if (VOS_TRUE == ucHrpdActFlg)
    {
        NAS_MSCC_SndHsdPowerSaveReq();
    }

    if (VOS_TRUE == uc1xActFlg)
    {
        NAS_MSCC_SndXsdPowerSaveReq(NAS_MSCC_PIF_POWER_SAVE_TYPE_SLEEP);
    }

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_POWER_OFF_STA_WAIT_CL_POWER_SAVE_CNF);

    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_CL_POWER_SAVE_CNF, TI_NAS_MSCC_WAIT_CL_POWER_SAVE_CNF_LEN);

    return VOS_TRUE;
}

VOS_UINT32 NAS_MSCC_RcvHsdPowerSaveCnf_PowerOff_WaitHrpdLtePowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucHrpdActFlg;
    VOS_UINT8                           uc3gppActFlg;

    ucHrpdActFlg   = NAS_MSCC_GetHrpdActiveFlg();
    uc3gppActFlg   = NAS_MSCC_Get3gppActiveFlg();

    if ((VOS_FALSE  == ucHrpdActFlg)
     && (VOS_FALSE  == uc3gppActFlg))
    {
        NAS_MSCC_ProcPowerSaveComplete();
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmcPowerSaveCnf_PowerOff_WaitHrpdLtePowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucHrpdActFlg;
    VOS_UINT8                           uc3gppActFlg;

    ucHrpdActFlg   = NAS_MSCC_GetHrpdActiveFlg();
    uc3gppActFlg   = NAS_MSCC_Get3gppActiveFlg();

    if ((VOS_FALSE  == ucHrpdActFlg)
     && (VOS_FALSE  == uc3gppActFlg))
    {
        NAS_MSCC_ProcPowerSaveComplete();
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmaCdmaMoCallSuccessNtf_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucHrpdActFlg;
    VOS_UINT8                           uc3gppActFlg;

    NAS_MSCC_SaveCurEntryMsg(ulEventType, pstMsg);

    ucHrpdActFlg   = NAS_MSCC_GetHrpdActiveFlg();
    uc3gppActFlg   = NAS_MSCC_Get3gppActiveFlg();

    if ((VOS_FALSE == ucHrpdActFlg)
     && (VOS_FALSE == uc3gppActFlg))
    {
        NAS_MSCC_ProcPowerSaveComplete();

        return VOS_TRUE;
    }

    if (VOS_TRUE == uc3gppActFlg)
    {
        NAS_MSCC_SndMmcPowerSaveReq();
    }

    if (VOS_TRUE == ucHrpdActFlg)
    {
        NAS_MSCC_SndHsdPowerSaveReq();
    }

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_POWER_OFF_STA_WAIT_HRPD_LTE_POWER_SAVE_CNF);

    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_CL_POWER_SAVE_CNF, TI_NAS_MSCC_WAIT_CL_POWER_SAVE_CNF_LEN);

    return VOS_TRUE;
}
#endif



VOS_VOID NAS_MSCC_SndPowerOffReq(
    VOS_UINT32                                      ulReceivePid
)
{
    switch (ulReceivePid)
    {
        case WUEPS_PID_MMC:
        {
             /* Send Power off request to MMC */
            (VOS_VOID)NAS_MSCC_SndMmcPowerOffReq(NAS_MSCC_GetPowerOffCause());

            /* Set the next state to wait Power off cnf from MMC*/
            NAS_MSCC_SetCurrFsmState(NAS_MSCC_POWER_OFF_STA_WAIT_MMC_POWER_OFF_CNF);

            /* Start the timer TI_NAS_MSCC_WAIT_MMC_POWER_OFF_CNF */
            (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_MMC_POWER_OFF_CNF, TI_NAS_MSCC_WAIT_MMC_POWER_OFF_CNF_LEN);
        }
            break;

#if (FEATURE_ON == FEATURE_IMS)
        case PS_PID_IMSA:
        {
            /* Send Power off request to IMSA */
            NAS_MSCC_SndImsaStopReq();

            /* Set the next state to wait Power off cnf from IMSA*/
            NAS_MSCC_SetCurrFsmState(NAS_MSCC_POWER_OFF_STA_WAIT_IMSA_POWER_OFF_CNF);

            /* Start timer TI_NAS_IMSA_WAIT_IMSA_POWER_OFF_CNF */
            (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_IMSA_POWER_OFF_CNF, TI_NAS_MSCC_WAIT_IMSA_POWER_OFF_CNF_LEN);
        }
            break;
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case UEPS_PID_XSD:
        {
             /* Send Power off request to XSD */
            NAS_MSCC_SndXsdPowerOffReq((VOS_UINT32)NAS_MSCC_GetPowerOffCause());

            /* Set the next state to wait Power off cnf from XSD*/
            NAS_MSCC_SetCurrFsmState(NAS_MSCC_POWER_OFF_STA_WAIT_XSD_POWER_OFF_CNF);

            /* Start timer TI_NAS_MSCC_WAIT_XSD_POWER_OFF_CNF*/
            (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_XSD_POWER_OFF_CNF, TI_NAS_MSCC_WAIT_XSD_POWER_OFF_CNF_LEN);
        }
            break;

        case UEPS_PID_HSD:
        {
             /* Send Power off request to HSD */
            NAS_MSCC_SndHsdPowerOffReq((VOS_UINT32)NAS_MSCC_GetPowerOffCause());

            /* Set the next state to wait Power off cnf from HSD*/
            NAS_MSCC_SetCurrFsmState(NAS_MSCC_POWER_OFF_STA_WAIT_HSD_POWER_OFF_CNF);

            /* Start the timer TI_NAS_MSCC_WAIT_HSD_POWER_OFF_CNF */
            (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_HSD_POWER_OFF_CNF, TI_NAS_MSCC_WAIT_HSD_POWER_OFF_CNF_LEN);
        }
            break;
#endif

        default:
            NAS_TRACE_HIGH("\n*NAS_MSCC_SndPowerOffReq():ulReceivePid \n");
            break;
    }

    return;
}



NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32 NAS_MSCC_GetPowerOffCause(VOS_VOID)
{
    NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32                    enPowerOffCause;

    enPowerOffCause = ((MMA_MSCC_POWER_OFF_REQ_STRU *)NAS_MSCC_GetCurrFsmEntryMsgBufferAddr())->enCause;

    return enPowerOffCause;

}



VOS_VOID NAS_MSCC_ProcPowerOffComplete(VOS_VOID)
{
    /* Send power off message to main FSM */
    NAS_MSCC_SndPowerOffRslt(NAS_MSCC_POWEROFF_RSLT_POWER_OFF);

    /* Quit sub FSM */
    NAS_MSCC_QuitFsmL2();

    return;
}



VOS_VOID NAS_MSCC_ProcPowerOffExpired(VOS_VOID)
{
    /* Send power off message to main FSM */
    NAS_MSCC_SndPowerOffRslt(NAS_MSCC_POWEROFF_RSLT_POWER_OFF);

    /* Quit sub FSM */
    NAS_MSCC_QuitFsmL2();
}


VOS_VOID NAS_MSCC_ProcPowerSaveComplete(VOS_VOID)
{
    NAS_MSCC_MSG_STRU                  *pstEntryMsg = VOS_NULL_PTR;

    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_CL_POWER_SAVE_CNF);

    pstEntryMsg = NAS_MSCC_GetCurrFsmEntryMsgAddr();

    if (NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF) == pstEntryMsg->ulEventType)
    {
        /* Send power off message to main FSM */
        NAS_MSCC_SndPowerOffRslt(NAS_MSCC_POWEROFF_RSLT_POWER_SAVE_HRPD_LTE);
    }
    else
    {
        /* Send power off message to main FSM */
        NAS_MSCC_SndPowerOffRslt(NAS_MSCC_POWEROFF_RSLT_POWER_SAVE);
    }


    /* Quit sub FSM */
    NAS_MSCC_QuitFsmL2();

    return;
}



VOS_UINT32 NAS_MSCC_RcvMsccPowerSaveReq_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSCC_POWER_SAVE_REQ_STRU  *pstIntPowerSaveReq = VOS_NULL_PTR;
    VOS_UINT16                          i;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ul1xExistFlag;

    ul1xExistFlag = VOS_FALSE;
#endif

    pstIntPowerSaveReq = (NAS_MSCC_MSCC_POWER_SAVE_REQ_STRU *)pstMsg;



    for (i = 0; i < pstIntPowerSaveReq->usRatNum; i++)
    {
        switch (pstIntPowerSaveReq->aenRat[i])
        {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            case NAS_MSCC_PIF_NET_RAT_TYPE_1X:
                {
                    NAS_MSCC_SndXsdPowerSaveReq(NAS_MSCC_PIF_POWER_SAVE_TYPE_UNKNOWN);

                    ul1xExistFlag = VOS_TRUE;
                }
                break;

            case NAS_MSCC_PIF_NET_RAT_TYPE_HRPD:
                {
                    NAS_MSCC_SndHsdPowerSaveReq();
                }
                break;
#endif

            case NAS_MSCC_PIF_NET_RAT_TYPE_LTE:
                {
                    NAS_MSCC_SndMmcPowerSaveReq();
                }
                break;

            default:
                break;
        }
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == ul1xExistFlag)
    {
        NAS_MSCC_SetCurrFsmState(NAS_MSCC_POWER_OFF_STA_WAIT_CL_POWER_SAVE_CNF);
    }
    else
#endif
    {
        NAS_MSCC_SetCurrFsmState(NAS_MSCC_POWER_OFF_STA_WAIT_HRPD_LTE_POWER_SAVE_CNF);
    }

    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_CL_POWER_SAVE_CNF, TI_NAS_MSCC_WAIT_CL_POWER_SAVE_CNF_LEN);

    return VOS_TRUE;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



