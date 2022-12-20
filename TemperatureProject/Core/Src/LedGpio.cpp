
#include "LedGpio.h"
#include "cmsis_os.h"

extern LedGpio* redLed;

/**
 * @brief  LedGpio
 *         init the led
 *         @note
 *
 *
 * @param  GPIO_TypeDef* gpioPort - the port of the led
 * @param uint16_t gpioPin - the pin of the led
 * @retval none
 */
LedGpio::LedGpio(GPIO_TypeDef* gpioPort,uint16_t gpioPin)
{
	_gpioPort = gpioPort;
	_gpioPin = gpioPin;
	_state = LED_STATE_OFF;
	_delay = 100;
}

/**
 * @brief  on
 *         switch on the led
 *         @note
 *
 *
 * @param  none
 * @retval none
 */
void LedGpio::on()
{
	_state = LED_STATE_ON;
	HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_SET);
}

/**
 * @brief  off
 *         switch off the led
 *         @note
 *
 *
 * @param  none
 * @retval none
 */
void LedGpio::off()
{
	_state = LED_STATE_OFF;
	HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_RESET);
}

/**
 * @brief  blink
 *         blink the led
 *         @note
 *
 *
 * @param  none
 * @retval none
 */
void LedGpio::blink()
{
	_state = LED_STATE_BLINK;
}

/**
 * @brief  getState
 *         get the led state
 *         @note
 *
 *
 * @param  none
 * @retval the state of led
 */
LedState LedGpio::getState()
{
	return _state;
}

/**
 * @brief  getDelay
 *         get the delay of led
 *         @note
 *
 *
 * @param  none
 * @retval the delay of led
 */
uint16_t LedGpio::getDelay()
{
	return _delay;
}

/**
 * @brief  getPort
 *         get the port of led
 *         @note
 *
 *
 * @param  none
 * @retval the port of led
 */
GPIO_TypeDef* LedGpio::getPort()
{
	return _gpioPort;
}

/**
 * @brief  getPin
 *         get the pin of led
 *         @note
 *
 *
 * @param  none
 * @retval the pin of led
 */
uint16_t LedGpio::getPin()
{
	return _gpioPin;
}

/**
 * @brief  ledBlinkTask
 *         manage the blink of led
 *         @note
 *
 *
 * @param  void* argument - a potentioal argument
 * @retval none
 */
extern "C" void ledBlinkTask(void* argument)
{
	for(;;){
		if(redLed->getState() == LED_STATE_BLINK){
			HAL_GPIO_TogglePin(redLed->getPort(), redLed->getPin());
		}
		osDelay(redLed->getDelay());
	}
}

