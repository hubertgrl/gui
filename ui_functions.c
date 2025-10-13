#include "ui_functions.h"

void return_action(void *empty)
{
    stack_pop(&g_ui_stack);
}

void swap_action(void *screen)
{
    stack_push(&g_ui_stack, screen);
}

void switch_action(void *data)
{
    if (data == NULL) return;

    ui_switch_data_t *switch_data = data;
    void *target = switch_data->data_pointer;

    if (target == NULL || switch_data->button == NULL) return;

    ui_object_button_t *switch_ptr = switch_data->button;
    switch_ptr->sw_state = !switch_ptr->sw_state;
    void *value = NULL;
    if (switch_ptr->sw_state == false) {
        switch_ptr->color = RED;
        value = switch_data->data_state_false;
    }
    else if (switch_ptr->sw_state == true) {
        switch_ptr->color = GREEN;
        value = switch_data->data_state_true;
    }
    if (value == NULL) return;
    switch (switch_data->data_type) {
    case DATA_TYPE_INT:
        *((int*)target) = *((int*)value);
        break;
    case DATA_TYPE_COLOR:
        *((color_t*)target) = *((color_t*)value);
        break;
    case DATA_TYPE_WCHAR:
        *((wchar_t**)target) = *((wchar_t**)value);
        break;
    case DATA_TYPE_FLOAT:
        *((float*)target) = *((float*)value);
        break;
    default:
        // nieobsługiwany typ
        break;
    }
    dirty_region(button_to_region(*switch_ptr));
}


