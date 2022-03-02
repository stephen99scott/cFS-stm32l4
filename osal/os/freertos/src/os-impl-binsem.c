#include "os-impl-binsem.h"

#include "os-shared-idmap.h"
#include "osapi-binsem.h"

OS_impl_binsem_internal_record_t OS_impl_bin_sem_table[OS_MAX_BIN_SEMAPHORES];

int32 OS_FreeRTOS_BinSemAPI_Impl_Init(void)
{
    memset(OS_impl_bin_sem_table, 0, sizeof(OS_impl_bin_sem_table));
    return OS_SUCCESS;
}

int32 OS_BinSemCreate_Impl(const OS_object_token_t *token, uint32 sem_initial_value, uint32 options)
{
   OS_impl_binsem_internal_record_t *impl;

   impl = OS_OBJECT_TABLE_GET(OS_impl_bin_sem_table, *token);

   impl->xBinSem = xSemaphoreCreateBinary();

   if (impl->xBinSem == NULL)
   {
      OS_DEBUG("Failed to create binary semaphore\n");
      return OS_SEM_FAILURE;
   }

   if (sem_initial_value >= 1) 
   {
      if (xSemaphoreGive(impl->xBinSem) != pdTRUE)
      {
         OS_DEBUG("Failed to give binary semaphore\n");
         return OS_SEM_FAILURE;
      }
   }

   return OS_SUCCESS;
}

int32 OS_BinSemFlush_Impl(const OS_object_token_t *token)
{
	return OS_ERR_NOT_IMPLEMENTED;
}

int32 OS_BinSemGive_Impl(const OS_object_token_t *token)
{
   OS_impl_binsem_internal_record_t *impl;

   impl = OS_OBJECT_TABLE_GET(OS_impl_bin_sem_table, *token);

   if (xSemaphoreGive(impl->xBinSem) != pdTRUE)
   {
      OS_DEBUG("Failed to give binary semaphore\n");
      return OS_SEM_FAILURE;
   }

   return OS_SUCCESS;
}

int32 OS_BinSemTake_Impl(const OS_object_token_t *token)
{
   OS_impl_binsem_internal_record_t *impl;

   impl = OS_OBJECT_TABLE_GET(OS_impl_bin_sem_table, *token);

   if (xSemaphoreTake(impl->xBinSem, portMAX_DELAY) != pdTRUE)
   {
      OS_DEBUG("Failed to take binary semaphore\n");
      return OS_SEM_FAILURE;
   }

   return OS_SUCCESS;
}

int32 OS_BinSemTimedWait_Impl(const OS_object_token_t *token, uint32 msecs)
{
   OS_impl_binsem_internal_record_t *impl;

   impl = OS_OBJECT_TABLE_GET(OS_impl_bin_sem_table, *token);

   if (xSemaphoreTake(impl->xBinSem, msecs/portTICK_PERIOD_MS) != pdTRUE)
   {
      OS_DEBUG("Timeout on binary semaphore\n");
      return OS_SEM_TIMEOUT;
   }

   return OS_SUCCESS;
}

int32 OS_BinSemDelete_Impl(const OS_object_token_t *token)
{
   OS_impl_binsem_internal_record_t *impl;

   impl = OS_OBJECT_TABLE_GET(OS_impl_bin_sem_table, *token);

   vSemaphoreDelete(impl->xBinSem);

   if (impl->xBinSem != NULL)
   {
      OS_DEBUG("Failed to delete binary semaphore\n");
      return OS_SEM_FAILURE;
   }

   return OS_SUCCESS;
}

int32 OS_BinSemGetInfo_Impl(const OS_object_token_t *token, OS_bin_sem_prop_t *bin_prop)
{
   OS_impl_binsem_internal_record_t *impl;

   impl = OS_OBJECT_TABLE_GET(OS_impl_bin_sem_table, *token);

   UBaseType_t count = uxSemaphoreGetCount(impl->xBinSem);

   bin_prop->value = count;

   return OS_SUCCESS;
}
