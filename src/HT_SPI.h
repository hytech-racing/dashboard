#ifndef HT_SPI_H
#define HT_SPI_H

#include <Arduino.h>

// Hadware SPI and DMA
extern SPI_HandleTypeDef hspi2;
extern DMA_HandleTypeDef hdma_spi2_tx;

extern bool spi_tx_complete;

extern "C"
{
  void DMA1_Stream0_IRQHandler(void);
  void SPI2_IRQHandler(void);
  void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi);
  void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);
}

void HT_SPI_Init();

#endif