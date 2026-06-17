
#ifndef RGB_H
#define RGB_H
#include <main.h>
#include <stdbool.h>
typedef enum {
   IDLE=0,
   ON,
   BREATH
} LED_State;



struct LED {
   bool is_breath_led;
   GPIO_TypeDef* port;
   uint16_t pin;
   uint8_t pwm_compare;
   TIM_HandleTypeDef* htim;
   uint32_t channel;
   LED_State state;
};

struct LED* LED_Create(GPIO_TypeDef* port, uint16_t pin, bool is_breath_led, TIM_HandleTypeDef* htim, uint32_t channel);

void LED_SetState(struct LED *led, LED_State state);

void LED_On(struct LED *led);

void LED_Off(struct LED *led);

void LED_Breath(struct LED *led);


#endif