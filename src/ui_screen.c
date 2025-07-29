//
// Created by Hubert Gerl on 19/07/2025.
//

#include "ui_screen.h"

ui_stack_t g_ui_stack = {};

extern int screen_list_slot(void **list, int size)
{
    for (int i = 0; i < size; i++) {
        if (list[i] == NULL) return i;
    }
    return -1;
}

ui_screen_t *screen_create()
{
    ui_screen_t *screen = malloc(sizeof(ui_screen_t));
    screen->list_area = calloc(1, sizeof(ui_object_area_t*));
    screen->list_button = calloc(1, sizeof(ui_object_button_t*));
    screen->list_text = calloc(1, sizeof(ui_object_text_t*));

    if (!screen->list_area || !screen->list_button || !screen->list_text) {
        screen_destroy(screen);
        return NULL;
    }

    screen->list_area_size = 0;
    screen->list_button_size = 0;
    screen->list_text_size = 0;
    return screen;
}

void screen_destroy(ui_screen_t *screen)
{
    free(screen->list_area);
    free(screen->list_button);
    free(screen->list_text);
    free(screen);
}

bool screen_add_object(void ***list, int *size, void *object)
{
    int slot = screen_list_slot(*list, *size);
    if (slot == -1) {
        void **tmp = realloc(*list, (*size + 1) * sizeof(void*));
        if (*list != NULL) {
            *list = tmp;
            (*list)[*size] = object;
            (*size)++;
            return true;
        }
        return false;
    }
    {
        (*list)[slot] = object;
        return true;
    }
}

ui_stack_t *stack_create(ui_screen_t *screen)
{
    ui_stack_t *stack = malloc(sizeof(ui_stack_t));
    stack->top = 0;
    for (int i = 0; i < 10; i++) stack->list_screen[i] = NULL;
    stack->list_screen[0] = screen;
    return stack;
}

bool stack_push(ui_stack_t *stack, ui_screen_t *screen)
{
    if ((stack)->top < STACK_SIZE_MAX - 1) {
        (stack)->list_screen[((stack)->top) + 1] = screen;
        (stack)->top++;
        return true;
    }
    return false;
}

bool stack_pop(ui_stack_t *stack)
{
    if (stack->top > 0) {
        stack->list_screen[stack->top] = NULL;
        stack->top--;
        return true;
    }
    return false;
}

ui_screen_t *stack_top(ui_stack_t *stack)
{
    if (stack->top > -1)
        return stack->list_screen[stack->top];
    return NULL;
}

