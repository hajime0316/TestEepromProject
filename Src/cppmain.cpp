#include "cppmain.hpp"

// include for CubeMX
#include "main.h"
#include "tim.h"
#include "gpio.h"

#include "stm32_access_flash_byte.hpp"

static uint8_t sw_sum;
static int led_flag = 0;

Stm32AccessFlashByte* memory;

void setup() {
    HAL_TIM_Base_Start_IT(&htim6);
    memory = new Stm32AccessFlashByte(0);
    sw_sum = memory->get();
}

void loop() {
    if(HAL_GPIO_ReadPin(SW_GPIO_Port, SW_Pin) == GPIO_PIN_RESET && led_flag == 0) {
        led_flag = 1;
        HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);

        // sw_sumをインクリメント
        sw_sum++;

        // eepromにsw_sumを記録
        memory->save(sw_sum);
    }
    else if (HAL_GPIO_ReadPin(SW_GPIO_Port, SW_Pin) == GPIO_PIN_RESET && led_flag == 1) {
        HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
    }
    else if(HAL_GPIO_ReadPin(SW_GPIO_Port, SW_Pin) == GPIO_PIN_SET && led_flag == 1) {
        led_flag = 0;
        HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
    }
}

//**************************
//    タイマ割り込み関数
//**************************
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  // 5msecタイマ
  if(htim->Instance == TIM6) {
    HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
  }
}
