#ifndef DASH_TASKS_H
#define DASH_TASKS_H

#include <STM32_CAN.h>
#include "DashCANInterfaceImpl.h"
#include <ht_sched.hpp>
#include <ht_task.hpp>




HT_TASK::TaskResponse init_can_task();
HT_TASK::TaskResponse read_can_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

HT_TASK::TaskResponse init_neopixels_task(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info);
HT_TASK::TaskResponse run_update_neopixels_task(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info);

HT_TASK::TaskResponse init_screen_task(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info);
HT_TASK::TaskResponse screen_refresh_task(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info);

#endif /* DASH_TASKS_H */  