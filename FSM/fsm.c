#include "fsm.h"
 
/*==================================================================
* Function  : FSM_StateTransfer
* Description : 状态转换
* Input Para  : 
* Output Para : 
* Return Value: 
==================================================================*/
static void FSM_StateTransfer(FSM_T *pFsm, uint8_t state)
{
    pFsm->curState = state;
}
 
/*==================================================================
* Function  : FSM_EventHandle
* Description : 状态机处理函数
* Input Para  : pFsm状态机对象, event触发事件, parm动作执行参数
* Output Para : 
* Return Value: 
==================================================================*/
void FSM_EventHandle(FSM_T *pFsm, uint8_t event, void *parm)
{
    FsmTable_T *pAcTable = pFsm->FsmTable;
    void (*eventActFun)(void *) = NULL;
    uint8_t NextState;
    uint8_t CurState = pFsm->curState;
    uint8_t flag = 0;
      
    for (uint8_t i = 0; i < pFsm->stuMaxNum; i++)// 遍历状态表
    {
        if (event == pAcTable[i].event && CurState == pAcTable[i].CurState)
        {
            flag = 1;
            eventActFun = pAcTable[i].eventActFun;
            NextState = pAcTable[i].NextState;
            break;
        }
    }
    if (flag)
    {
        if (eventActFun != NULL)
        {
            eventActFun(parm);  // 执行相应动作
        }
        FSM_StateTransfer(pFsm, NextState); // 状态转换
    }
    else
    {
         printf("there is no match\n");
    }
}
 
/*==================================================================
* Function  : FSM_Init
* Description : 状态机初始化
* Input Para  : pFsm状态机对象，pTable状态迁移表，stuMaxNum迁移表数量
*               curState当前状态
* Output Para : 
* Return Value: 
==================================================================*/
void FSM_Init(FSM_T *pFsm, FsmTable_T *pTable, uint8_t stuMaxNum, uint8_t curState)
{
    pFsm->FsmTable = pTable;
    pFsm->curState = curState;
    pFsm->stuMaxNum = stuMaxNum;
}





