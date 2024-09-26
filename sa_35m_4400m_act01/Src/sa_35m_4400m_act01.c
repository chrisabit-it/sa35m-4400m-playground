#include <sa_35m_4400m_act01.h>
#include "stm32f1xx_hal.h"

uint32_t words[] = {
    0x00580005,
    0x00EC8124,
    0x000004B3,
    0x00004E42,
    0x0800E1A9,
    0x0035B2C8
};

static void delay_ticks(uint8_t ticks, TIM_HandleTypeDef* htim) {
  __HAL_TIM_SET_COUNTER(htim,0);
  while (__HAL_TIM_GET_COUNTER(htim) < ticks);
}

void enable_line(void) {
  HAL_GPIO_WritePin(SPI_GPIOX, SPI_LE_PIN, GPIO_PIN_RESET);
  delay_ticks(1, &htim1);
}

void latch_data(void) {
  HAL_GPIO_WritePin(SPI_GPIOX, SPI_LE_PIN, GPIO_PIN_SET);
  delay_ticks(72, &htim1);
}

void spi_transfer(uint32_t word) {
  uint8_t i;

  //shift out the data
  for (i = 0; i < 32; i++) {
    HAL_GPIO_WritePin(SPI_GPIOX, SPI_DATA_PIN, (word & 0x80000000) != 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    word <<= 1;

    HAL_GPIO_WritePin(SPI_GPIOX, SPI_CLK_PIN, GPIO_PIN_SET);
    delay_ticks(5, &htim1);
    HAL_GPIO_WritePin(SPI_GPIOX, SPI_CLK_PIN, GPIO_PIN_RESET);
    delay_ticks(2, &htim1);
  }
  delay_ticks(72, &htim1); // 1us
}

void sa_35m_4400m_Init(void) {
  HAL_TIM_Base_Start(&htim1);
  enable_line();

  int len = sizeof(words) / sizeof(words[0]);
  for (int i = 0; i < len; i++) {
    spi_transfer(words[i]);
    latch_data();
    enable_line();
  }
}

void sa_35m_4400m_Loop(void) {
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_11);
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
  HAL_Delay(100);
}

