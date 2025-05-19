#include "ACUInterface.h"


void ACUInterface::receive_acu_ok_message(const CAN_message_t &can_msg) 
{
    ACU_OK_t unpacked_msg;
    Unpack_ACU_OK_hytech(&unpacked_msg, can_msg.buf, can_msg.len); // NOLINT (implicitly decay pointer)

    constexpr uint32_t acu_ok_init_timeout_ms = 2000;
    
    if (!unpacked_msg.bms_ok && (sys_time::hal_millis() - _acu_init_millis) > acu_ok_init_timeout_ms) {
        bms_ok = false;
    }

    if (!unpacked_msg.imd_ok && (sys_time::hal_millis() - _acu_init_millis) > acu_ok_init_timeout_ms) {
        imd_ok = false;
    }
}

void ACUInterface::receive_acu_voltages(const CAN_message_t &can_msg)
{
    BMS_VOLTAGES_t unpacked_msg;
    Unpack_BMS_VOLTAGES_hytech(&unpacked_msg, can_msg.buf, can_msg.len); // NOLINT (implicitly decay pointer)
    
    constexpr float critical_cell_voltage = 3.3f;
    _voltages_not_critical = HYTECH_low_voltage_ro_fromS(unpacked_msg.low_voltage_ro) > critical_cell_voltage;
}