#ifndef DASHCANINTERFACEIMPL_H
#define DASHCANINTERFACEIMPL_H

#include <STM32_CAN.h>
#include "hytech.h"



class DashCAN
{
    private:
        STM32_CAN* _dashCAN;
        CAN_message_t _msg;
    public:
        DashCAN(STM32_CAN* dashCAN);
        void read_CAN();
        void write_CAN();
}
#endif


