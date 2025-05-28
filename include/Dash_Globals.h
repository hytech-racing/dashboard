#ifndef DASH_GLOBALS_H
#define DASH_GLOBALS_H

#include <etl/singleton.h>
#include "SharedFirmwareTypes.h"

/* Interface and system data structs */
using VCFData_sInstance = etl::singleton<VCFData_s>;
using VCRData_sInstance = etl::singleton<VCRData_s>;


constexpr int NEOPIXEL_CONTROL_PIN = PC14;
constexpr int NEOPIXEL_COUNT = 12; // 12 neopixeles on dashboard

/* Interface and system data structs */
extern VCRData_s vcr_data; // NOLINT
#endif