/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-04 13:11:03
*@FilePath: \DEMO\hardware\exit.c
*@Drscription: 
***********************************************************************/
#include "exit.h"
#include "core_cm7.h"
/***********************************************************************
*@Function:void IRNQ_priority(uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority,IRQn_Type IRQn) 
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-04 13:18:08
*@Drscription: 设置中断优先级
               优先级组只能设置4-7
               分组4：主优先级0-7 子优先级0-1
               分组5：主优先级0-3 子优先级0-3
               分组6：主优先级0-1 子优先级0-7
               分组7：无主优先级   子优先级0-15
***********************************************************************/
void IRQN_priority(uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority,IRQn_Type IRQn)
{
    uint8_t encode=0;

    NVIC_SetPriorityGrouping(PriorityGroup);
    encode=NVIC_EncodePriority(PriorityGroup,PreemptPriority,SubPriority);
    NVIC_SetPriority(IRQn,encode);   

}


