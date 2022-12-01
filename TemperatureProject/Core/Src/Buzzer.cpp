
#include "Buzzer.h"
#include "main.h"


extern  TIM_HandleTypeDef htim3;
/**
 * @brief  Buzzer
 *         init the buzzer
 *         @note
 *
 *
 * @param  none
 * @retval none
 */
Buzzer::Buzzer() {
	_bzState = BUZZER_STATE_OFF;

}

/**
 * @brief  start
 *         start the buzzer
 *         @note
 *
 *
 * @param  none
 * @retval none
 */
void Buzzer::start()
{

	_bzState = BUZZER_STATE_ON;
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_Base_Start(&htim3);

}

/**
 * @brief  stop
 *         stop the buzzer
 *         @note
 *
 *
 * @param  none
 * @retval none
 */
void Buzzer::stop()
{

	_bzState = BUZZER_STATE_OFF;
	HAL_TIM_Base_Stop(&htim3);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}
