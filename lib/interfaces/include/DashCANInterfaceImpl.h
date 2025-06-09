#ifndef DASHCANINTERFACEIMPL_H
#define DASHCANINTERFACEIMPL_H

#include "CANInterface.h"
#include "hytech.h"

#include "etl/delegate.h"
#include "etl/singleton.h"

#include "VCFInterface.h"
#include "ACUInterface.h"
#include "VCRInterface.h"
#include "DrivebrainInterface.h"


struct CANInterfaces {
    explicit CANInterfaces(VCFInterface &vcf_int, ACUInterface &acu_int, VCRInterface &vcr_int, DrivebrainInterface &db_int)
        : vcf_interface(vcf_int),
          acu_interface(acu_int),
          vcr_interface(vcr_int),
          db_interface(db_int) {}

    VCFInterface &vcf_interface;
    ACUInterface &acu_interface;
    VCRInterface &vcr_interface;
    DrivebrainInterface &db_interface;
};
    
using CANInterfacesInstance = etl::singleton<CANInterfaces>;


namespace DashCAN
{ 
    void dash_read_switch(CANInterfaces &interfaces, const CAN_message_t &msg, unsigned long millis);
    void write_CAN();
}
#endif   