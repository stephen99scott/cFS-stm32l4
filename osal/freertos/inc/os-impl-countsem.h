#ifndef OS_IMPL_COUNTSEM_H
#define OS_IMPL_COUNTSEM_H

#include "osconfig.h"
#include "os-freertos.h"
#include "semphr.h"

typedef struct
{
	SemaphoreHandle_t xCountSem;
} OS_impl_countsem_internal_record_t;

extern OS_impl_countsem_internal_record_t OS_impl_count_sem_table[OS_MAX_COUNT_SEMAPHORES];

#endif /* OS_IMPL_COUNTSEM_H */
