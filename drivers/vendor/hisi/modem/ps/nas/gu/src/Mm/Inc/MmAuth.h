

#ifndef _MM_AUTH_H_
#define _MM_AUTH_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasUsimmApi.h"


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*******************************************************************************
  3 枚举定义
*******************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/
/* 模块名＋意义＋HEADER */


/*****************************************************************************
  6 消息定义
*****************************************************************************/

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/
VOS_VOID MM_GsmAuthProc(VOS_VOID);

VOS_VOID MM_UsimGsmAuth(VOS_VOID);

VOS_VOID MM_SimAuth(VOS_VOID);

VOS_VOID MM_SndGsmAuthenReq(VOS_VOID);

VOS_VOID MM_RcvSimAuthCnf(VOS_VOID* Msg);

VOS_UINT8 MM_RcvGsmAuthenticationCnf(VOS_VOID* pMsg);

VOS_VOID MM_HandleGsmAuthenFail(VOS_VOID);

VOS_VOID NAS_MML_SecContext2GTO3G(VOS_UINT8 *pucIk, VOS_UINT8 *pucCk, VOS_UINT8 *pucKc);

extern VOS_UINT8 Mm_ComRandJudge(VOS_VOID);

extern VOS_VOID Mm_ComAuthenRcvUsimCnfSuccess(VOS_VOID);

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

#endif /* end of MmAuth.h*/
