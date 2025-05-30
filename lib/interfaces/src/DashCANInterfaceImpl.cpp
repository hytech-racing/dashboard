#include "DashCANInterfaceImpl.h"



void DashCAN::dash_read_switch(CANInterfaces &interfaces, const CAN_message_t &msg, unsigned long millis)
{
    switch (msg.id) {
              // case DASHBOARD_BUZZER_CONTROL_CANID:
              // {
              //     interfaces.vcr_interface.receive_dash_control_data(_msg);
              //     break;
              // } 
              case BMS_VOLTAGES_CANID:
              {
                  interfaces.acu_interface.receive_acu_voltages(msg);
                  break;
              }
              case ACU_OK_CANID: 
              {
                  interfaces.acu_interface.receive_acu_ok_message(msg);
                  break;
              }
              case PEDALS_SYSTEM_DATA_CANID: 
              {
                  interfaces.vcf_interface.receive_pedals_message(msg, millis);
                  break;
              }
              case INV1_DYNAMICS_CANID:
              {
                interfaces.vcr_interface.receive_inv_dynamics(msg, millis);
                break;
              }
              case DRIVEBRAIN_STATE_DATA_CANID:
              {
                interfaces.db_interface.receive_db_state_data(msg);
                break;
              }

              default:
                  break;
          }
}