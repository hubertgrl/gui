//
// Created by Hubert Gerl on 17/07/2025.
//

#pragma once

#include "stdio.h"
#include "stdbool.h"

#include "wchar.h"

#include "hagl.h"

#include "ui_screen.h"
#include "ui_config.h"
#include "ui_render.h"
#include "ui_functions.h"
#include  "ui_objects.h"

#define _UI_TOP(stack) (*stack_top(stack))

#define _SCREEN_ADD_AREA(screen, area_ptr) \
screen_add_object((void***)&(screen->list_area), &(screen->list_area_size), (void*)area_ptr)
#define _SCREEN_ADD_TEXT(screen, text_ptr) \
screen_add_object((void***)&(screen->list_text), &(screen->list_text_size), (void*)text_ptr)
#define _SCREEN_ADD_BUTTON(screen, button_ptr) \
screen_add_object((void***)&(screen->list_button), &(screen->list_button_size), (void*)button_ptr)

#define _STACK_CREATE(screen) { \
.list_screen[0] = screen,   \
.top = 0}

#define _GLOBAL_STACK_INIT(screen) (g_ui_stack.list_screen[0] = screen, g_ui_stack.top = 0)
#define _GLOBAL_STACK_TOP stack_top(&g_ui_stack)

#define _TEXT_CREATE(text_pos_x0, text_pos_y0, text_color, text_value) \
    {                                               \
        .pos_x0 = (text_pos_x0),                             \
        .pos_y0 = (text_pos_y0),                             \
        .length = (sizeof(text_value) / sizeof(wchar_t)),          \
        .color = (text_color),                             \
        .value = (text_value),                             \
    }
#define _AREA_CREATE(area_pos_x0, area_pos_y0, area_width, area_height, area_color, area_radius) \
    {                                                           \
    .pos_x0 = (area_pos_x0),                                \
    .pos_y0 = (area_pos_y0),                                \
    .width = (area_width),                                  \
    .height = (area_height),                                \
    .color = (area_color),                                  \
    .radius = (area_radius),                                \
    }
#define _BUTTON_CREATE(button_pos_x0, button_pos_y0, button_color, button_radius, button_value, button_action, button_user_data)                                         \
    {                                                                                                        \
        .pos_x0 = (button_pos_x0),                                                                           \
        .pos_y0 = (button_pos_y0),                                                                           \
        .width = ((sizeof(button_value) - 1) / sizeof(wchar_t) * (CHAR_WIDTH + CHAR_MARGIN) - CHAR_MARGIN),  \
        .height = CHAR_HEIGHT,                                                                                \
        .length = ((sizeof(button_value) - 1) / sizeof(wchar_t)),                                            \
        .color = (button_color),                                                                             \
        .radius = (button_radius),                                                                           \
        .value = (button_value),                                                                             \
        .action = (button_action),                                                                           \
        .sw_state = false,                                                                                   \
        .user_data = button_user_data,                                                                       \
    }

#define _BUTTON_ACTION(button) button.action(button.user_data)


void highlight_button(int button_number);

bool button_to_switch(ui_object_button_t *button_ptr, void *target_ptr, ui_data_type_t target_data_type,
                      void *target_state_true_ptr, void *target_state_false_ptr);







