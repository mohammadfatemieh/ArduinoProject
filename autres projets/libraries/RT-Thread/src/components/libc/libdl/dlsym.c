/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author      Notes
 * 2010-11-17     yi.qiu      first version
 */

#include "include/rtthread.h"

#ifdef RT_USING_MODULE

#include "dlmodule.h"


void *dlsym(void *handle, const char* symbol) {
    rt_dlmodule_t *module;
    int i;

    RT_ASSERT(handle != RT_NULL);
    module = (rt_dlmodule_t *)handle;

    for (i = 0; i < module->nsym; i++) {
        if (!rt_strcmp(module->symtab[i].name, symbol)) {
            return (void*)module->symtab[i].addr;
        }
    }

    return RT_NULL;
}
RTM_EXPORT(dlsym)

#endif /* RT_USING_MODULE */
