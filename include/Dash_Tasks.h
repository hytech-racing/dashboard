#ifndef DASH_TASKS_H
#define DASH_TASKS_H

#include "CANInterface.h"
#include "DashCANInterfaceImpl.h"
#include <ht_sched.hpp>
#include <ht_task.hpp>

#include "Dash_Constants.h"
#include "Dash_Globals.h"
#include "NeopixelController.h"
#include "SharedFirmwareTypes.h"

#include "HT_SPI.h"
#include "HT_FDCAN.h"

// Interface Includes
#include "VCFInterface.h"
#include "VCRInterface.h"
#include "EncoderInterface.h"
// #include "lcdInterface.h"
#include "newDisplay.h"
#include "bitmaps.h"
#include "etl/delegate.h"

HT_TASK::TaskResponse init_heartbeat(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info);
HT_TASK::TaskResponse heartbeat(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info);

HT_TASK::TaskResponse init_can(const unsigned long &sysMicros, const HT_TASK::TaskInfo &taskInfo);
HT_TASK::TaskResponse can_read(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

HT_TASK::TaskResponse init_neopixels_task(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info);
HT_TASK::TaskResponse run_update_neopixels_task(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info);

HT_TASK::TaskResponse init_screen(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info);
HT_TASK::TaskResponse screen_refresh(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info);

HT_TASK::TaskResponse init_can(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info);
HT_TASK::TaskResponse can_read(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

HT_TASK::TaskResponse init_encoders(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info);

#endif /* DASH_TASKS_H */  