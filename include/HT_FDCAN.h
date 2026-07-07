#ifndef HT_FDCAN_WRAPPER
#define HT_FDCAN_WRAPPER

#include "stm32h7xx_hal.h"
#include "stm32h750xx.h"


#include "ACUInterface.h"
#include "VCFInterface.h"
#include "VCRInterface.h"

#include "hytech.h"
#include "DashCANInterfaceImpl.h"

// struct CANInterfaces
// {
// explicit CANInterfaces(
//     VCFInterface &vcf_int,
//     ACUInterface &acu_int,
//     DrivebrainInterface &db_int)
//     : vcf_interface(vcf_int),
//       acu_interface(acu_int),
//       db_interface(db_int) {}

// VCFInterface & vcf_interface;
// ACUInterface & acu_interface;
// DrivebrainInterface & db_interface;
// };

int FDCAN_Init();
void FDCAN1_GPIO_Init_PD0D1(void);
int FDCAN_write(uint32_t id, const uint8_t *data, uint8_t len);
int FDCAN_read(CANInterfaces &interfaces, unsigned long millis);
#endif