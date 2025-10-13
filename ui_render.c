//
// Created by Hubert Gerl on 21/07/2025.
//

#include "ui_render.h"
#include "font6x9.h"

dirty_manager_t g_dirty_manager = {.counter = 0, .button_highlighted = 0};

void button_highlight(int button_number)
{
    g_dirty_manager.button_highlighted = button_number;
}

void dirty_region(dirty_region_t region)
{
    if (g_dirty_manager.counter < DIRTY_REGIONS_MAX) {
        g_dirty_manager.list[g_dirty_manager.counter] = region;
        g_dirty_manager.counter++;
    }
}

bool if_dirty(dirty_region_t object)
{
    for (int i = 0; i < g_dirty_manager.counter; i++) {
        dirty_region_t region = g_dirty_manager.list[i];
        if (!(region.pos_x0 >= object.pos_x1 &&
            region.pos_y0 >= object.pos_y0 &&
            region.pos_x1 <= object.pos_x0 &&
            region.pos_y1 <= object.pos_y0))
            return true;
    }
    return false;
}

dirty_region_t area_to_region(ui_object_area_t area)
{
    dirty_region_t region = {
        .pos_x0 = area.pos_x0,
        .pos_y0 = area.pos_y0,
        .pos_x1 = area.pos_x0 + area.width,
        .pos_y1 = area.pos_y0 + area.height,
    };
    return region;
}

dirty_region_t button_to_region(ui_object_button_t button)
{
    dirty_region_t region = {
        .pos_x0 = button.pos_x0,
        .pos_y0 = button.pos_y0,
        .pos_x1 = button.pos_x0 + button.width,
        .pos_y1 = button.pos_y0 + button.height,
    };
    return region;
}

void print_area(ui_object_area_t area)
{
    hagl_fill_rounded_rectangle(area.pos_x0, area.pos_y0, area.pos_x0 + area.width,
                                area.pos_y0 + area.height, area.radius, BLACK);
    hagl_draw_rounded_rectangle(area.pos_x0, area.pos_y0, area.pos_x0 + area.width,
                                area.pos_y0 + area.height, area.radius, area.color);
}

void print_text(ui_object_text_t text)
{
    hagl_put_text(text.value, text.pos_x0, text.pos_y0, text.color,
                  font6x9);
}

void print_button(ui_object_button_t button, bool if_highlighted)
{
    int border_color = GREY;
    if (if_highlighted == true) border_color = WHITE;
    hagl_fill_rounded_rectangle(button.pos_x0 - CHAR_MARGIN,
                                button.pos_y0 - CHAR_MARGIN,
                                button.pos_x0 + button.width + CHAR_MARGIN + 1,
                                button.pos_y0 + button.height + CHAR_MARGIN,
                                button.radius, BLACK);
    hagl_put_text(button.value, button.pos_x0, button.pos_y0, button.color,
                  font6x9);
    hagl_draw_rounded_rectangle(button.pos_x0 - CHAR_MARGIN,
                                button.pos_y0 - CHAR_MARGIN,
                                button.pos_x0 + button.width + CHAR_MARGIN + 1,
                                button.pos_y0 + button.height + CHAR_MARGIN,
                                button.radius, border_color);
}

void ui_print()
{
    ui_screen_t* screen = g_ui_stack.list_screen[g_ui_stack.top];
    static int old_top = -1;
    if (old_top != g_ui_stack.top || g_dirty_manager.counter >= DIRTY_REGIONS_MAX) // Fully re-draw screen
    {
        _UI_CLEAR_ALL;
        for (int i = 0; i < (screen->list_area_size); i++) {
            print_area(*screen->list_area[i]);
        }
        for (int i = 0; i < (screen->list_button_size); i++) {
            dirty_region_t object = button_to_region(*screen->list_button[i]);
            if (if_dirty(object)) {
                if (i == g_dirty_manager.button_highlighted) print_button(*screen->list_button[i], true);
                else print_button(*screen->list_button[i], false);
            }
        }
        for (int i = 0; i < (screen->list_text_size); i++) {
            print_text(*(screen->list_text[i]));
        }
        old_top = g_ui_stack.top;
        g_dirty_manager.counter = 0;
        lcd_copy();
    }
    else if (g_dirty_manager.counter < DIRTY_REGIONS_MAX && g_dirty_manager.counter > 0) // Re-draw only dirty regions
    {
        for (int i = 0; i < g_dirty_manager.counter; i++) {
            _UI_CLEAR_REGION(g_dirty_manager.list[i]);
        }
        for (int i = 0; i < (screen->list_area_size); i++) {
            dirty_region_t object = area_to_region(*screen->list_area[i]);
            if (if_dirty(object)) print_area(*screen->list_area[i]);
        }
        for (int i = 0; i < (screen->list_button_size); i++) {
            dirty_region_t object = button_to_region(*screen->list_button[i]);
            if (if_dirty(object)) {
                if (i == g_dirty_manager.button_highlighted) print_button(*screen->list_button[i], true);
                else print_button(*screen->list_button[i], false);
            }
        }
        for (int i = 0; i < (screen->list_text_size); i++) {
            print_text(*(screen->list_text[i]));
        }
        g_dirty_manager.counter = 0;
        lcd_copy();
    }
    else {
        for (int i = 0; i < (screen->list_text_size); i++) {
            print_text(*(screen->list_text[i]));
        }
        g_dirty_manager.counter = 0;
        lcd_copy();
    }
}

