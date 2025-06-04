#ifndef DRIVEBRAIN_INTERFACE_H
#define DRIVEBRAIN_INTERFACE_H

#include "etl/singleton.h"
#include "CANInterface.h"
#include "SharedFirmwareTypes.h"
#include "hytech.h"


struct DrivebrainStateData_s
{
    bool drivebrain_in_ctrl;
    uint8_t vn_status;
};

class DrivebrainInterface
{
    public: 

        void receive_db_state_data(const CAN_message_t &can_msg);

        DrivebrainStateData_s get_db_state_data() {return _db_state_data;}
    private:
        DrivebrainStateData_s _db_state_data;
};

using DrivebrainInterfaceInstance = etl::singleton<DrivebrainInterface>;

#endif