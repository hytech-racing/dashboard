#include "Dash_Tasks.h"




//Variable Definition


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
    // HTXDisplayInstance::instance().invert_display(false);
    // HTXDisplayInstance::instance().init();
    return HT_TASK::TaskResponse::YIELD;
}

HT_TASK::TaskResponse screen_refresh_task(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info)
{
    // HTXDisplayInstance::instance().invert_display(VCFInterfaceInstance::instance().is_mech_brake_pressed());
    // HTXDisplayInstance::instance().clear_display_buffer();
    // HTXDisplayInstance::instance().draw_vertical_pedal_bar(VCFInterfaceInstance::instance().get_curr_data().stamped_pedals.pedals_data.brake_percent, 17);
    // HTXDisplayInstance::instance().draw_battery_bar(ACUInterfaceInstance::instance().get_curr_data().pack_voltage * 100.0 / 530.0);
    // HTXDisplayInstance::instance().draw_icons(1/*DrivebrainInterfaceInstance::instance().get_db_state_data().vn_status*/, 1, 1, 0);

    // switch (HTXDisplayInstance::instance().current_page)
    // {
    //     case 0:
    //         HTXDisplayInstance::instance().display_speeds(VCRInterfaceInstance::instance().get_curr_wheel_data().actual_speed);
    //         break;
    // }

    // if (!(ACUInterfaceInstance::instance().imd_ok))
    // {
    //     HTXDisplayInstance::instance().draw_popup("DANGER! GET OUT FAST!");
    // }

    // HTXDisplayInstance::instance().display_refresh();
    return HT_TASK::TaskResponse::YIELD;
}

HT_TASK::TaskResponse main_display_task(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info)
{
    
}