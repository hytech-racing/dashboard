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
  // USB_CDC_Init();
  HAL_Init();
  LED_Init();

  // SystemClock_Config();



  uint8_t blink_time = 0;
  uint8_t angle = 0;
  const uint8_t angle_difference = 11;

  while (1)
  {
    
    // still need to set up timers, dma, and clock config
    // for(int i = 0; i < NUM_NEOPIXELS; i++) {
    //   uint32_t rgb_color = hsl_to_rgb(angle + (i * angle_difference), 255, 127);
    //   led_set_RGB(i, (rgb_color >> 16) & 0xFF, (rgb_color >> 8) & 0xFF, rgb_color & 0xFF);
    // }

    // angle++;
    // led_render();


    if (blink_time > 500 / CYCLE_PD) {
      HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
      blink_time += CYCLE_PD;
      // CDC_Transmit_FS(TxBuffer, TxBufferLen);
    }
    HAL_Delay(CYCLE_PD);
  }
}

// void SystemClock_Config(void) {
//   RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//   RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

//   /** Supply configuration update enable
//   */
//   HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

//   /** Configure the main internal regulator output voltage
//   */
//   __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

//   while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

//   /** Initializes the RCC Oscillators according to the specified parameters
//   * in the RCC_OscInitTypeDef structure.
//   */
//   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
//   RCC_OscInitStruct.HSEState = RCC_HSE_ON;
//   RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//   RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
//   RCC_OscInitStruct.PLL.PLLM = 32;
//   RCC_OscInitStruct.PLL.PLLN = 335;
//   RCC_OscInitStruct.PLL.PLLP = 2;
//   RCC_OscInitStruct.PLL.PLLQ = 5;
//   RCC_OscInitStruct.PLL.PLLR = 2;
//   RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
//   RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
//   RCC_OscInitStruct.PLL.PLLFRACN = 2338;
//   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//   {
//     Error_Handler();
//   }

//   /** Initializes the CPU, AHB and APB buses clocks
//   */
//   RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
//                               |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
//                               |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
//   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//   RCC_ClkInitStruct.SYSCLKDivider = 2;
//   RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
//   RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
//   RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
//   RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
//   RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

//   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
//   {
//     Error_Handler();
//   }
// }

// void USB_CDC_Init(void) {

//   if (USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS) != USBD_OK)
//   {
//     Error_Handler();
//   }
//   if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC) != USBD_OK)
//   {
//     Error_Handler();
//   }
//   if (USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS) != USBD_OK)
//   {
//     Error_Handler();
//   }
//   if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
//   {
//     Error_Handler();
//   }

//   /* USER CODE BEGIN USB_DEVICE_Init_PostTreatment */
//   HAL_PWREx_EnableUSBVoltageDetector();
// }

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