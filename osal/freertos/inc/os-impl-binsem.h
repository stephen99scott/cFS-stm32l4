#ifndef OS_IMPL_BINSEM_H
#define OS_IMPL_BINSEM_H

#include "osconfig.h"
#include "os-freertos.h"
#include "semphr.h"

typedef struct
{
    SemaphoreHandle_t xBinSem;
} OS_impl_binsem_internal_record_t;

extern OS_impl_binsem_internal_record_t OS_impl_bin_sem_table[OS_MAX_BIN_SEMAPHORES];

#endif /* OS_IMPL_BINSEM_H */
