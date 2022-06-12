/*
 * motor.h
 *
 *  Created on: 12 cze 2022
 *      Author: Marcin
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "gpio.h"

static const uint8_t I_RATIO = 10;
static const float STEP = 1.8;


uint8_t turn_anticlockwise(uint8_t gpio_id);
uint8_t turn_clockwise(uint8_t gpio_id);

#endif /* INC_MOTOR_H_ */
