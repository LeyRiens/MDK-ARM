#ifndef BOTTON_H
#define BOTTON_H
#include <main.h>

typedef enum {
    BUTTON_NONE=0,
    BUTTON_RELEASED,
    BUTTON_PRESSED
} Button_State;

struct Button {
    GPIO_TypeDef* port;
    uint16_t pin;
    GPIO_PinState stable_state;
    GPIO_PinState current_state;
    uint32_t last_change_time;
    Button_State state;
    bool is_state_changed;
};

struct Button* Button_Create(GPIO_TypeDef* port, uint16_t pin, GPIO_PinState stable_state);

Button_State Button_GetState(struct Button *button);

GPIO_PinState Button_ReadPin(struct Button *button);

void Button_UpdateState(struct Button *button);






#endif 