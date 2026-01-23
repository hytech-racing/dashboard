#include "Dash_Tasks.h"

// pin definitions
#define LED_PIN PA3

#define SHARP_CS PB4
#define SHARP_CLK PB10
#define SHARP_MOSI PB15


HT_TASK::TaskResponse init_heartbeat(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info)
{
    SerialUSB.begin(115200);

    pinMode(LED_PIN, OUTPUT);
    return HT_TASK::TaskResponse::YIELD;
}

HT_TASK::TaskResponse heartbeat(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info)
{
    // Toggle an LED or perform other heartbeat actions
    static bool led_state = false;
    led_state = !led_state;
    digitalWrite(LED_PIN, led_state ? HIGH : LOW);

    return HT_TASK::TaskResponse::YIELD;
}

HT_TASK::TaskResponse init_neopixels_task(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info)
{
    NeopixelControllerInstance::create(NEOPIXEL_COUNT, NEOPIXEL_CONTROL_PIN);
    NeopixelControllerInstance::instance().init_neopixels();
    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse run_update_neopixels_task(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info)
{
    NeopixelControllerInstance::instance().refresh_neopixels(VCFData_sInstance::instance(), VCRData_sInstance::instance(), CANInterfacesInstance::instance());
    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse init_screen(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info)
{
    pinMode(PB4, OUTPUT);
    digitalWrite(PB4, LOW);

    HT_SPI_Init();
    // Create Display singleton
    HTXDisplayInstance::create(PB4); // TODO: Update to use a constant
    HTXDisplayInstance::instance().init(&hspi2);
    HTXDisplayInstance::instance().hytech_animation();
    return HT_TASK::TaskResponse::YIELD;
}

HT_TASK::TaskResponse screen_refresh(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info)
{
    if (spi_tx_complete)
    {
    HTXDisplayInstance::instance().draw_background();
    HTXDisplayInstance::instance().invert_display(VCFInterfaceInstance::instance().is_mech_brake_pressed());
    HTXDisplayInstance::instance().draw_vertical_pedal_bar(VCFInterfaceInstance::instance().get_curr_data().stamped_pedals.pedals_data.brake_percent, 17);
    HTXDisplayInstance::instance().draw_battery_bar(ACUInterfaceInstance::instance().get_curr_data().pack_voltage * 100.0 / 530.0);
    HTXDisplayInstance::instance().draw_icons(DrivebrainInterfaceInstance::instance().get_db_state_data().vn_status, VCRInterfaceInstance::instance().get_curr_car_state().drivetrain_state, DrivebrainInterfaceInstance::instance().get_db_state_data().drivebrain_in_ctrl);
    HTXDisplayInstance::instance().display_speeds(VCRInterfaceInstance::instance().get_curr_wheel_data().actual_speed);
    HTXDisplayInstance::instance().send_display_buffer(&hspi2);
    spi_tx_complete = false;
    }
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

HT_TASK::TaskResponse init_can(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info)
{
    // Create can singletons
    CANInterfacesInstance::create(VCFInterfaceInstance::instance(), ACUInterfaceInstance::instance(), VCRInterfaceInstance::instance(), DrivebrainInterfaceInstance::instance());
    
    FDCAN_Init();   
    return HT_TASK::TaskResponse::YIELD;
}

HT_TASK::TaskResponse can_read(const unsigned long& sys_micros, const HT_TASK::TaskInfo& task_info)
{
    FDCAN_read(CANInterfacesInstance::instance(), sys_time::hal_millis());
    return HT_TASK::TaskResponse::YIELD;
}