 #include "main.h"
// #include "led.h"

// #include "usbd_core.h"
// #include "usbd_desc.h"
// #include "usbd_cdc.h"
// #include "usbd_cdc_if.h"

// USBD_HandleTypeDef hUsbDeviceFS;

// TIM_HandleTypeDef htim2;
// DMA_HandleTypeDef hdma_tim2_ch1;

// uint8_t TxBuffer[] = "Hello World! From STM32 USB CDC Device To Virtual COM Port\r\n";
// uint8_t TxBufferLen = sizeof(TxBuffer);

// https://www.thevfdcollective.com/blog/stm32-and-sk6812-rgbw-led

#define CYCLE_PD 10

void LED_Init(void);
void SystemClock_Config(void);
void USB_CDC_Init(void);
void Error_Handler(void);

int main(void)
{
  HAL_Init();
  LED_Init();




  uint8_t blink_time = 0;

  while (1)
  {
  HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
  


    // if (blink_time > 500 / CYCLE_PD) {
    //   HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
    //   blink_time += CYCLE_PD;
    //   // CDC_Transmit_FS(TxBuffer, TxBufferLen);
    // }
  HAL_Delay(500);
  }
}

void LED_Init(void)
{
  LED_GPIO_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}

void Error_Handler(void)
{
  while (1)
  {
    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
    HAL_Delay(100);
  }
}