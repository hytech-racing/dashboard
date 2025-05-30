#ifndef ACU_INTERFACE_H
#define ACU_INTERFACE_H

#include "SharedFirmwareTypes.h"
#include "etl/singleton.h"
#include "hytech.h"
#include <STM32_CAN.h>
#include "SystemTimeInterface.h"

class ACUInterface  
{
    public:
        //ACUInterface() = delete;

        ACUInterface(){
            _acu_init_millis = sys_time::hal_millis();
        }

        void receive_acu_ok_message(const CAN_message_t &msg);


        ACUCoreData_s get_curr_data() {return _last_recvd_data;}

        bool get_voltages_not_critical() {return _voltages_not_critical;}

        void receive_acu_voltages(const CAN_message_t &msg);

        bool bms_ok = true;
        bool imd_ok = false;
    private: 
        ACUCoreData_s _last_recvd_data;
        bool _voltages_not_critical = false;

        unsigned long _acu_init_millis;

};



using ACUInterfaceInstance = etl::singleton<ACUInterface>;

#endif /* ACU_INTERFACE_H */