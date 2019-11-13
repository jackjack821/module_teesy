
#ifndef _FSM_H_
#define _FSM_H_
 
#include <stdint.h>
#include <stddef.h>
 
typedef struct FsmTable_s
{
    uint8_t event;                /* 触发事件 */
    uint8_t CurState;             /* 当前状态 */
    void (*eventActFun)(void *);  /* 动作函数 */
    uint8_t NextState;            /* 跳转状态 */
}FsmTable_T;
 
typedef struct FSM_s
{
    FsmTable_T *FsmTable;         /* 状态迁移表 */
    uint8_t curState;             /* 状态机当前状态 */
    uint8_t stuMaxNum;            /* 状态机状态迁移数量 */
}FSM_T;
 
/*********************************************************************************
使用方法：1.创建FSM_T对象；
          2.创建FsmTable_T表；
          3.调用FSM_Init()初始化；
          4.程序轮询FSM_EventHandle()运行状态机。
*********************************************************************************/
void FSM_Init(FSM_T *pFsm, FsmTable_T *pTable, uint8_t stuMaxNum, uint8_t curState);
void FSM_EventHandle(FSM_T *pFsm, uint8_t event, void *parm);
#endif
