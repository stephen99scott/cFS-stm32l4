#include "os-freertos.h"

#include "os-shared-common.h"
#include "os-shared-idmap.h"

FreeRTOS_GlobalVars_t FreeRTOS_GlobalVars = {0};

int32 OS_API_Impl_Init(osal_objtype_t idtype)
{
   int32 return_code = OS_ERR_NOT_IMPLEMENTED;

   // return_code = OS_FreeRTOS_TableMutex_Init(idtype);
   // if (return_code != OS_SUCCESS)
   // {
   //    return return_code;
   // }

   // switch (idtype)
   // {
   //    case OS_OBJECT_TYPE_OS_TASK:
   //       return_code = OS_FreeRTOS_TaskAPI_Impl_Init();
   //       break;
   //    case OS_OBJECT_TYPE_OS_QUEUE:
   //       return_code = OS_FreeRTOS_QueueAPI_Impl_Init();
   //       break;
   //    case OS_OBJECT_TYPE_OS_BINSEM:
   //       return_code = OS_FreeRTOS_BinSemAPI_Impl_Init();
   //       break;
   //    case OS_OBJECT_TYPE_OS_COUNTSEM:
   //       return_code = OS_FreeRTOS_CountSemAPI_Impl_Init();
   //       break;
   //    case OS_OBJECT_TYPE_OS_MUTEX:
   //       return_code = OS_FreeRTOS_MutexAPI_Impl_Init();
   //       break;
   //    case OS_OBJECT_TYPE_OS_MODULE:
   //       return_code = OS_FreeRTOS_ModuleAPI_Impl_Init();
   //       break;
   //    case OS_OBJECT_TYPE_OS_TIMEBASE:
   //       return_code = OS_FreeRTOS_TimeBaseAPI_Impl_Init();
   //       break;
   //    case OS_OBJECT_TYPE_OS_STREAM:
   //       return_code = OS_FreeRTOS_StreamAPI_Impl_Init();
   //       break;
   //    case OS_OBJECT_TYPE_OS_DIR:
   //       return_code = OS_FreeRTOS_DirAPI_Impl_Init();
   //       break;
   //    case OS_OBJECT_TYPE_OS_FILESYS:
   //       return_code = OS_FreeRTOS_FileSysAPI_Impl_Init();
   //       break;
   //    default:
   //       break;
   //  }

   return return_code;
}

void OS_IdleLoop_Impl(void)
{
   FreeRTOS_GlobalVars.IdleTaskId = xTaskGetCurrentTaskHandle();
   ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
}

void OS_ApplicationShutdown_Impl(void)
{
   xTaskNotifyGive(FreeRTOS_GlobalVars.IdleTaskId);
}
