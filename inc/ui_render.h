//
// Created by Hubert Gerl on 21/07/2025.
//

#pragma once

#include "ui_screen.h"
#include "hagl.h"

#define _UI_CLEAR_ALL (hagl_fill_rectangle(0, 0, LCD_WIDTH, LCD_HEIGHT, BLACK))

#define _UI_CLEAR_REGION(region) (hagl_fill_rectangle(region.pos_x0, region.pos_y0, region.pos_x1, region.pos_y1, BLACK))
// Draws straight lines on lcd X and Y axis
#define _SHOW_AXIS                                                               \
{                                                                            \
hagl_draw_line(LCD_WIDTH / 2, 0, LCD_WIDTH / 2 + 1, LCD_HEIGHT, WHITE);  \
hagl_draw_line(0, LCD_HEIGHT / 2, LCD_WIDTH, LCD_HEIGHT / 2 + 1, WHITE); \
}

#define DIRTY_REGIONS_MAX 8

typedef struct dirty_region
{
    int pos_x0;
    int pos_x1;
    int pos_y0;
    int pos_y1;
} dirty_region_t;

typedef struct dirty_manager
{
    dirty_region_t list[DIRTY_REGIONS_MAX];
    int counter;
    int button_highlighted;
} dirty_manager_t;

void button_highlight(int button_number);
void dirty_region(dirty_region_t region);
dirty_region_t area_to_region(ui_object_area_t area);
dirty_region_t button_to_region(ui_object_button_t button);

void ui_print();


