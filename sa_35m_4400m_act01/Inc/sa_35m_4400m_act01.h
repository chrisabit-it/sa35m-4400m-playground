#ifndef SA_35M_4400M_H_
#define SA_35M_4400M_H_

#include "stm32f1xx_hal.h"
extern TIM_HandleTypeDef      htim1;

#define SPI_GPIOX             GPIOB
#define SPI_LE_PIN            GPIO_PIN_12
#define SPI_CLK_PIN           GPIO_PIN_13
#define SPI_DATA_PIN          GPIO_PIN_15

void sa_35m_4400m_Init(void);
void sa_35m_4400m_Loop(void);

#endif // SA_35M_4400M_H_
