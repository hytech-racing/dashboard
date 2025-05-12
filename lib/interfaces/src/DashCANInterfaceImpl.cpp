#include "DashCANInterfaceImpl.h"

DashCAN::DashCAN(STM32_CAN* dashCAN)
{
    _dashCAN = dashCAN;

    // begin can and set baud rate to 500kb
    _dashCAN->begin();
    _dashCAN->setBaudRate(500000);
}

void DashCAN::read_CAN()
{
    while (_dashCAN->read(_msg)) {
        switch (_msg.id) {
            case 0x7E8: // OBD-II request
                // Handle OBD-II request
                break;
            case 0x7E0: // OBD-II response
                // Handle OBD-II response
                break;
            default:
                // Handle other messages
                break;
        }
    }
}