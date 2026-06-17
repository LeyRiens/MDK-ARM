#include "botton.h"

const int BUTTON_DELAY_MS = 50;


struct Button* Button_Create(GPIO_TypeDef* port, uint16_t pin, GPIO_PinState stable_state) {
    struct Button* button = (struct Button*)malloc(sizeof(struct Button));
    button->port = port;
    button->pin = pin;
    button->stable_state = stable_state;
    button->current_state = stable_state;
    button->last_change_time = 0;
    button->state = BUTTON_NONE;
    button->is_state_changed = FALSE;
    return button;
}

Button_State Button_GetState(struct Button *button) {
    if (button->is_state_changed) {
        button->is_state_changed = FALSE;
        return button->state;
    }else {
        return BUTTON_NONE;
    }
}

GPIO_PinState Button_ReadPin(struct Button *button) {
    return HAL_GPIO_ReadPin(button->port, button->pin);
}

void Button_UpdateState(struct Button *button) {
    GPIO_PinState pin_state = Button_ReadPin(button);
    uint32_t current_time = HAL_GetTick();
    
    if (pin_state != button->current_state) {
        button->current_state = pin_state;
        button->last_change_time = current_time;
    } else if ((current_time - button->last_change_time) >= BUTTON_DELAY_MS) {
        if (button->current_state == button->stable_state) {
            if (button->state != BUTTON_RELEASED) {
                button->state = BUTTON_RELEASED;
                button->is_state_changed = TRUE;
            }
        } else {
            if (button->state != BUTTON_PRESSED) {
                button->state = BUTTON_PRESSED;
                button->is_state_changed = TRUE;
            }
        }
    }
}