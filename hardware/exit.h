/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-04 13:10:52
*@FilePath: \DEMO\hardware\exit.h
*@Drscription: 
***********************************************************************/
#ifndef __EXIT__H
#define __EXIT__H

#include "fsl_common.h"

/*设置中断优先级*/
void IRQN_priority(uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority,IRQn_Type IRQn);


#endif /*__EXIT__H*/



