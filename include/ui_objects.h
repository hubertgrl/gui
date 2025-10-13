#pragma once

#include <stdlib.h>

#include "wchar.h"
#include "stdbool.h"

#include "ui_config.h"

typedef enum
{
    DATA_TYPE_INT,
    DATA_TYPE_COLOR,
    DATA_TYPE_FLOAT,
    DATA_TYPE_CHAR,
    DATA_TYPE_WCHAR,
} ui_data_type_t;


typedef void (*ui_action_t)(void *);

// Interface objects definition
typedef struct
{
    int pos_x0;
    int pos_y0;
    int width;
    int height;
    color_t color;
    int radius;
} ui_object_area_t;

typedef struct
{
    int pos_x0;
    int pos_y0;
    int length;
    color_t color;
    const unsigned char *font;
    wchar_t *value;
} ui_object_text_t;

typedef struct
{
    int pos_x0;
    int pos_y0;
    int width;
    int height;
    int length;
    color_t color;
    int radius;
    const unsigned char *font;
    wchar_t *value;
    ui_action_t action;
    void *user_data;
    bool sw_state;
} ui_object_button_t;

typedef struct
{
    ui_object_button_t *button;
    ui_data_type_t data_type;
    void *data_pointer;
    void *data_state_true;
    void *data_state_false;
} ui_switch_data_t;
