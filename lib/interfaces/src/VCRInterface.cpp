#include "VCRInterface.h"

void VCRInterface::receive_inv_dynamics(const CAN_message_t &can_msg, unsigned long curr_millis) 
{
    // Unpack the message
    INV1_DYNAMICS_t unpacked_msg;
    Unpack_INV1_DYNAMICS_hytech(&unpacked_msg, can_msg.buf, can_msg.len);

    // Update inverter interface with new data
    _wheel_data.actual_power = unpacked_msg.actual_power_w; // NOLINT (watts)
    _wheel_data.actual_torque = HYTECH_actual_torque_nm_ro_fromS(unpacked_msg.actual_torque_nm_ro);
    _wheel_data.actual_speed = unpacked_msg.actual_speed_rpm;
    _wheel_data.new_data = true;
    _wheel_data.last_recv_millis = curr_millis;
}

void VCRInterface::receive_vehicle_state(const CAN_message_t &can_msg)
{
    CAR_STATES_t unpacked_msg;
    Unpack_CAR_STATES_hytech(&unpacked_msg, can_msg.buf, can_msg.len); //NOLINT
    _vehicle_state_value = static_cast<VehicleState_e>(unpacked_msg.vehicle_state);
    _drivetrain_state_value = static_cast<DrivetrainState_e>(unpacked_msg.drivetrain_state);
    _is_db_in_ctrl = unpacked_msg.drivebrain_in_control;
}