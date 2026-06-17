#include "task.h" 
#include "rgb.h"
#include "botton.h"

void Task_Init(void) {
    LED * led_green = LED_Create(GPIOA, GPIO_PIN_7, TRUE, &htim3, TIM_CHANNEL_1);
    LED_ *led_red = LED_Create(GPIOA, GPIO_PIN_7, FALSE, NULL, 0);
    Button *button1 = Button_Create(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
    Button *button2 = Button_Create(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
   for(;;) {
        Button_UpdateState(button1);
        Button_UpdateState(button2);
        
      
}