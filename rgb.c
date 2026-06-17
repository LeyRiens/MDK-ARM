#include "rgb.h"

static const int PWM_BREATH = 499;
static const int PWM_OFF = 0;

struct LED* LED_Create(GPIO_TypeDef* port, uint16_t pin, bool is_breath_led, TIM_HandleTypeDef* htim, uint32_t channel) {
    struct LED* led = (struct LED*)malloc(sizeof(struct LED));
    led->is_breath_led = is_breath_led;
    led->port = port;
    led->pin = pin;
    led->pwm_compare = PWM_OFF;
    led->htim = htim;
    led->channel = channel;
    led->state = IDLE;
    return led;
}


void LED_SetState(struct LED *led, LED_State state) {
   led->state = state;
   switch (state) {
      case IDLE:
         LED_OFF(led);
         break;
      case ON:
         LED_ON(led);
         break;
      case BREATH:
         LED_BREATH(led);
         break;
   }
}




void LED_On(struct LED *led) {
    
    HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_SET);
    
    if (led->is_breath_led) {
        led->pwm_compare = PWM_OFF;
        __HAL_TIM_SetCompare(led->htim, led->channel, led->pwm_compare);
    }
    
}



void LED_Off(struct LED *led) {
    
    HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);
    
    if (led->is_breath_led) {
        led->pwm_compare = PWM_OFF;
        __HAL_TIM_SetCompare(led->htim, led->channel, led->pwm_compare);
    }
    
}


void LED_Breath(struct LED *led) {
    
    HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);
    
    if (led->is_breath_led) {
        led->pwm_compare = PWM_BREATH;
        __HAL_TIM_SetCompare(led->htim, led->channel, led->pwm_compare);
    }
    
}