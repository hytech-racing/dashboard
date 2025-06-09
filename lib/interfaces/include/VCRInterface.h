#ifndef VCR_INTERFACE_H
#define VCR_INTERFACE_H

#include "etl/singleton.h"
#include "H7FDCAN.h"
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

struct VehicleState_s
{
    uint8_t drivetrain_state;
};

class VCRInterface 
{
    public:
        TorqueLimit_e get_torque_limit_mode() {return _torque_limit;}

        bool is_in_pedals_calibration_state() {return _is_in_pedals_calibration_state;}

        void receive_inv_dynamics(const CAN_message_t &can_msg, unsigned long curr_millis);

        MotorMechanics_s get_curr_wheel_data() {return _wheel_data;}

        void receive_vehicle_state(const CAN_message_t &can_msg, unsigned long curr_millis);

        VehicleState_s get_curr_car_state() {return _car_state;}

    private:
        TorqueLimit_e _torque_limit = TorqueLimit_e::TCMUX_LOW_TORQUE;
        bool _is_in_pedals_calibration_state = false;
        MotorMechanics_s _wheel_data; 
        VehicleState_s _car_state;
};


using VCRInterfaceInstance = etl::singleton<VCRInterface>;

#endif /* VCR_INTERFACE_H */