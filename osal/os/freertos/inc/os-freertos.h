#ifndef OS_FREERTOS_H
#define OS_FREERTOS_H

#include "FreeRTOS.h"
#include "task.h"

typedef struct
{
    TaskHandle_t IdleTaskId;
} FreeRTOS_GlobalVars_t;

extern FreeRTOS_GlobalVars_t FreeRTOS_GlobalVars;

// int32 OS_Rtems_TaskAPI_Impl_Init(void);
// int32 OS_Rtems_QueueAPI_Impl_Init(void);
// int32 OS_Rtems_BinSemAPI_Impl_Init(void);
// int32 OS_Rtems_CountSemAPI_Impl_Init(void);
// int32 OS_Rtems_MutexAPI_Impl_Init(void);
// int32 OS_Rtems_TimeBaseAPI_Impl_Init(void);
// int32 OS_Rtems_ModuleAPI_Impl_Init(void);
// int32 OS_Rtems_StreamAPI_Impl_Init(void);
// int32 OS_Rtems_DirAPI_Impl_Init(void);
// int32 OS_Rtems_FileSysAPI_Impl_Init(void);

// int32 OS_Rtems_TableMutex_Init(osal_objtype_t idtype);

#endif /* OS_FREERTOS_H */
