#include "main.h"
#include "eeprom.h"
#include "spi.h"

void EEPROM_Init(void)
{
  CS_Init(CS_PORT, CS_PIN);
  SPI_Init(SPI_PORT);
}

uint8_t EEPROM_ReadStatus(SPI_HandleTypeDef *SPIx)
{
  uint8_t cmd[] = {cmdRDSR, 0xff};
  uint8_t res[2];

  HAL_GPIO_WritePin(HOLD_PORT, HOLD_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);
  HAL_SPI_TransmitReceive(SPIx, &cmd, &res, 2, 100);

  return res[1];
}

void EEPROM_WriteEnable(SPI_HandleTypeDef *SPIx)
{
  uint16_t cmd = cmdWREN;

    while (WIP(EEPROM_ReadStatus(SPIx)));

    HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(SPIx, &cmd, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET);
}

void EEPROM_WriteDisable(SPI_HandleTypeDef *SPIx)
{
  uint16_t cmd = cmdWRDI;

    while (WIP(EEPROM_ReadStatus(SPIx)));

    HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(SPIx, &cmd, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET);
}

void EEPROM_WriteStatus(SPI_HandleTypeDef *SPIx)
{
  uint16_t cmd = cmdWRSR;
  uint16_t res[2];

  HAL_GPIO_WritePin(HOLD_PORT, HOLD_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);
  HAL_SPI_TransmitReceive(SPIx, &cmd, &res, 2, HAL_MAX_DELAY);
}