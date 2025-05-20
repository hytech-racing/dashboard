#ifndef DASHCANINTERFACEIMPL_H
#define DASHCANINTERFACEIMPL_H

#include <STM32_CAN.h>
#include "hytech.h"

#include "etl/delegate.h"
#include "etl/singleton.h"

#include "VCFInterface.h"
#include "ACUInterface.h"
#include "VCRInterface.h"



struct CANInterfaces {
    explicit CANInterfaces(VCFInterface &vcf_int, ACUInterface &acu_int, VCRInterface &vcr_int)
        : vcf_interface(vcf_int),
          acu_interface(acu_int),
          vcr_interface(vcr_int) {}

    VCFInterface &vcf_interface;
    ACUInterface &acu_interface;
    VCRInterface &vcr_interface;
};
    

struct DashCANInterfaceObjects {

    DashCANInterfaceObjects(etl::delegate<void(CANInterfaces &, const CAN_message_t &, unsigned long)> recv_switch, STM32_CAN * stm_can): STM_CAN(stm_can),can_recv_switch(recv_switch) 
    {} 

    
    STM32_CAN* STM_CAN;

    static CAN_message_t CAN_inMsg;
    etl::delegate<void(CANInterfaces &, const CAN_message_t &, unsigned long)> can_recv_switch;
    
};

namespace DashCAN
{ 
    void can_setup();
    void dash_read_switch(CANInterfaces &interfaces, const CAN_message_t &msg, unsigned long millis);
    void write_CAN();

    using DashCANInterfaceObjectsInstance = etl::singleton<DashCANInterfaceObjects>;
    using CANInterfacesInstance = etl::singleton<CANInterfaces>;
}
#endif   