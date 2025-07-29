//
// Created by Hubert Gerl on 18/07/2025.
//
#pragma once

#include "hagl.h"

// Character font values
#define CHAR_HEIGHT 6
#define CHAR_WIDTH 4
#define CHAR_MARGIN 2

// #define DEFAULT_FONT font6x9

#define STACK_SIZE_MAX 10

#define DIRTY_REGIONS_MAX 8


// Center of lcd in X axis
#define _X_CENTER(len) (LCD_WIDTH / 2 - (len / 2) * (CHAR_WIDTH + CHAR_MARGIN))
