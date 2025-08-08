#pragma once

#include <stdint.h>

typedef struct _sticks_t {
    int16_t lx;
    int16_t ly;
    int16_t rx;
    int16_t ry;
    uint8_t dead_zone;
} sticks_t;

typedef struct _sticks_nor_t {
    float lx;
    float ly;
    float rx;
    float ry;
} sticks_nor_t;

sticks_nor_t normalize_sticks(sticks_t sticks);
