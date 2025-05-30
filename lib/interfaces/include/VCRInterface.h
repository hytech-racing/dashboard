#ifndef VCR_INTERFACE_H
#define VCR_INTERFACE_H

#include "etl/singleton.h"
#include "STM32_CAN.h"
#include "SharedFirmwareTypes.h"
#include "hytech.h"



struct MotorMechanics_s
{
    bool new_data : 1;
    unsigned long last_recv_millis = 0; 
    float actual_power; //watts
    float actual_torque; //newton meters
    float actual_speed; //rpm
};

struct VectorNavStatus_s
{
    uint8_t vn_status;
};
class VCRInterface 
{
    public:
        TorqueLimit_e get_torque_limit_mode() {return _torque_limit;}

        bool is_in_pedals_calibration_state() {return _is_in_pedals_calibration_state;}

        void receive_inv_dynamics(const CAN_message_t &can_msg, unsigned long curr_millis);

        MotorMechanics_s get_curr_wheel_data() {return _wheel_data;}

        void receive_vn_status(const CAN_message_t &can_msg);


        // void receive_dash_control_data(const CAN_message_t &can_msg)
        // {
        //     DASHBOARD_BUZZER_CONTROL_t unpacked_msg;
        //     Unpack_DASHBOARD_BUZZER_CONTROL_hytech(&unpacked_msg, can_msg.buf, can_msg.len);            

        //     if (unpacked_msg.dash_buzzer_flag) {
        //         BuzzerController::getInstance().activate(millis());
        //     }

        //     _is_in_pedals_calibration_state = unpacked_msg.in_pedal_calibration_state;

        //     if (unpacked_msg.torque_limit_enum_value < ((int) TorqueLimit_e::TCMUX_NUM_TORQUE_LIMITS)) // check for validity
        //     {
        //         _torque_limit = (TorqueLimit_e) unpacked_msg.torque_limit_enum_value;
        //     }
        // }
    private:
        TorqueLimit_e _torque_limit = TorqueLimit_e::TCMUX_LOW_TORQUE;
        bool _is_in_pedals_calibration_state = false;
        MotorMechanics_s _wheel_data; 
        VectorNavStatus_s _vn_status;
};


using VCRInterfaceInstance = etl::singleton<VCRInterface>;

#endif /* VCR_INTERFACE_H */