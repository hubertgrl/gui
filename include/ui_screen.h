//
// Created by Hubert Gerl on 19/07/2025.
//

#pragma once

#include "ui_objects.h"


typedef struct ui_screen
{
    ui_object_area_t **list_area;
    int list_area_size;
    ui_object_button_t **list_button;
    int list_button_size;
    ui_object_text_t **list_text;
    int list_text_size;
} ui_screen_t;

typedef struct ui_stack
{
    ui_screen_t *list_screen[STACK_SIZE_MAX];
    int top;
} ui_stack_t;

extern ui_stack_t g_ui_stack;

ui_screen_t *screen_create();
void screen_destroy(ui_screen_t *screen);
bool screen_add_object(void ***list, int *size, void *object);

ui_stack_t *stack_create(ui_screen_t *screen);
bool stack_push(ui_stack_t *stack, ui_screen_t *screen);
bool stack_pop(ui_stack_t *stack);
ui_screen_t *stack_top(ui_stack_t *stack);







