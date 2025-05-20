#include "Dash_Tasks.h"
#include "Dash_Constants.h"
#include "Dash_Globals.h"
#include "CANInterface.h"
#include "NeopixelController.h"
#include "SharedFirmwareTypes.h"

HT_TASK::TaskResponse init_can_task()
{
    DashCAN::can_setup();

    return HT_TASK::TaskResponse::YIELD;
}



HT_TASK::TaskResponse init_neopixels_task(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info)
{
    NeopixelControllerInstance::create(NEOPIXEL_COUNT, NEOPIXEL_CONTROL_PIN);
    NeopixelControllerInstance::instance().init_neopixels();
    digitalWrite(PA3, HIGH);
    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse run_update_neopixels_task(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info)
{
    NeopixelControllerInstance::instance().refresh_neopixels(VCFData_sInstance::instance(), VCRData_sInstance::instance(), DashCAN::CANInterfacesInstance::instance());
    return HT_TASK::TaskResponse::YIELD;
}