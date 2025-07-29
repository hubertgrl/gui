//
// Created by Hubert Gerl on 17/07/2025.
//

#include "ui_main.h"

void highlight_button(int button_number)
{
    if (button_number <= g_ui_stack.list_screen[g_ui_stack.top]->list_button_size) {
        ui_object_button_t *button_ptr = g_ui_stack.list_screen[g_ui_stack.top]->list_button[button_number];
        button_highlight(button_number);
        dirty_region(button_to_region(*button_ptr));
    }
}

bool button_to_switch(ui_object_button_t *button_ptr, void *target_ptr, ui_data_type_t target_data_type,
                      void *target_state_true_ptr, void *target_state_false_ptr)
{
    ui_switch_data_t *switch_data = malloc(sizeof(ui_switch_data_t));
    if (switch_data != NULL) {
        button_ptr->color = RED;
        button_ptr->sw_state = false;
        button_ptr->action = switch_action;
        switch_data->button = button_ptr;
        switch_data->data_pointer = target_ptr;
        switch_data->data_type = target_data_type;
        switch_data->data_state_true = target_state_true_ptr;
        switch_data->data_state_false = target_state_false_ptr;
        button_ptr->user_data = switch_data;
        return true;
    }
    free(switch_data);
    return false;
}
