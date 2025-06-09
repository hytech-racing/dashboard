#include "DrivebrainInterface.h"

void DrivebrainInterface::receive_db_state_data(const CAN_message_t &can_msg)
{
    DRIVEBRAIN_STATE_DATA_t unpacked_msg;
    Unpack_DRIVEBRAIN_STATE_DATA_hytech(&unpacked_msg, can_msg.buf, can_msg.len);

    _db_state_data.drivebrain_in_ctrl = unpacked_msg.drivebrain_in_control;
    _db_state_data.vn_status = unpacked_msg.vn_gps_status;
}