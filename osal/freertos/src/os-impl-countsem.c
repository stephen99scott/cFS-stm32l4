#include "os-impl-countsem.h"

#include "os-shared-idmap.h"
#include "osapi-countsem.h"

OS_impl_countsem_internal_record_t OS_impl_count_sem_table[OS_MAX_COUNT_SEMAPHORES];

int32 OS_FreeRTOS_CountSemAPI_Impl_Init(void)
{
    memset(OS_impl_count_sem_table, 0, sizeof(OS_impl_count_sem_table));
    return (OS_SUCCESS);
}

int32 OS_CountSemCreate_Impl(const OS_object_token_t *token, uint32 sem_initial_value, uint32 options)
{
	OS_impl_countsem_internal_record_t *impl;

	impl = OS_OBJECT_TABLE_GET(OS_impl_count_sem_table, *token);

	impl->xCountSem = xSemaphoreCreateCounting(0xFFFFFFFF, sem_initial_value);

	if (impl->xCountSem == NULL)
	{
		OS_DEBUG("Failed to create counting semaphore\n");
		return OS_SEM_FAILURE;
	}

	return OS_SUCCESS;
}

int32 OS_CountSemGive_Impl(const OS_object_token_t *token)
{
   OS_impl_countsem_internal_record_t *impl;

   impl = OS_OBJECT_TABLE_GET(OS_impl_count_sem_table, *token);

   if (xSemaphoreGive(impl->xCountSem) != pdTRUE)
   {
      OS_DEBUG("Failed to give counting semaphore\n");
      return OS_SEM_FAILURE;
   }

   return OS_SUCCESS;
}

int32 OS_CountSemTake_Impl(const OS_object_token_t *token)
{
   OS_impl_countsem_internal_record_t *impl;

   impl = OS_OBJECT_TABLE_GET(OS_impl_count_sem_table, *token);

   if (xSemaphoreTake(impl->xCountSem, portMAX_DELAY) != pdTRUE)
   {
      OS_DEBUG("Failed to take counting semaphore\n");
      return OS_SEM_FAILURE;
   }

   return OS_SUCCESS;
}

int32 OS_CountSemTimedWait_Impl(const OS_object_token_t *token, uint32 msecs)
{
   OS_impl_countsem_internal_record_t *impl;

   impl = OS_OBJECT_TABLE_GET(OS_impl_count_sem_table, *token);

   if (xSemaphoreTake(impl->xCountSem, msecs/portTICK_PERIOD_MS) != pdTRUE)
   {
      OS_DEBUG("Timeout on counting semaphore\n");
      return OS_SEM_TIMEOUT;
   }

   return OS_SUCCESS;
}

int32 OS_CountSemDelete_Impl(const OS_object_token_t *token)
{
   OS_impl_countsem_internal_record_t *impl;

   impl = OS_OBJECT_TABLE_GET(OS_impl_count_sem_table, *token);

   vSemaphoreDelete(impl->xCountSem);

   if (impl->xCountSem != NULL)
   {
      OS_DEBUG("Failed to delete counting semaphore\n");
      return OS_SEM_FAILURE;
   }

   return OS_SUCCESS;
}

int32 OS_CountSemGetInfo_Impl(const OS_object_token_t *token, OS_count_sem_prop_t *count_prop)
{
   OS_impl_countsem_internal_record_t *impl;

   impl = OS_OBJECT_TABLE_GET(OS_impl_count_sem_table, *token);

   UBaseType_t count = uxSemaphoreGetCount(impl->xCountSem);

   count_prop->value = count;

   return OS_SUCCESS;
}
