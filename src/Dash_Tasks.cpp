#include "Dash_Tasks.h"
#include "Dash_Constants.h"
#include "Dash_Globals.h"
#include "CANInterface.h"
#include "DashCANInterfaceImpl.h"
#include "NeopixelController.h"
#include "SharedFirmwareTypes.h"

//Interface Includes
#include "VCFInterface.h"
#include "VCRInterface.h"
#include "lcdInterface.h"

#include "etl/delegate.h"

//Variable Definition
uint8_t dashDisplay::current_page = 0; // idk why but it doesnt like when its defined in a different file

HT_TASK::TaskResponse init_neopixels_task(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info)
{
    NeopixelControllerInstance::create(NEOPIXEL_COUNT, NEOPIXEL_CONTROL_PIN);
    NeopixelControllerInstance::instance().init_neopixels();
    digitalWrite(PA3, HIGH);
    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse run_update_neopixels_task(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info)
{
    NeopixelControllerInstance::instance().refresh_neopixels(VCFData_sInstance::instance(), VCRData_sInstance::instance(), CANInterfacesInstance::instance());
    return HT_TASK::TaskResponse::YIELD;
}

HT_TASK::TaskResponse init_screen_task(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info)
{
    dashDisplay::init();
    dashDisplay::startup();
    return HT_TASK::TaskResponse::YIELD;
}

HT_TASK::TaskResponse screen_refresh_task(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info)
{
    dashDisplay::draw_background_bitmap();
    dashDisplay::draw_vertical_pedal_bar(VCFInterfaceInstance::instance().get_curr_data().stamped_pedals.pedals_data.brake_percent, 17);
    dashDisplay::draw_battery_bar(ACUInterfaceInstance::instance().get_curr_data().pack_voltage * 100.0 / 530.0);
    dashDisplay::draw_icons(2/*DrivebrainInterfaceInstance::instance().get_db_state_data().vn_status*/, 0, 0, 1);
    
    switch(dashDisplay::current_page)
    {
        case 0:
            dashDisplay::display_speeds(VCRInterfaceInstance::instance().get_curr_wheel_data().actual_speed);
            break;
    }

    if (!(ACUInterfaceInstance::instance().imd_ok && ACUInterfaceInstance::instance().bms_ok))
    {
        lcdHelper::draw_popup("DANGER! GET OUT FAST!");
    }

    lcdHelper::display_refresh();
    return HT_TASK::TaskResponse::YIELD;
}