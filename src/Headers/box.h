#pragma once

#include <tice.h>

#include "common.h"
bool validPos(int8_t x, int8_t y);

bool moveBox(int16_t x, int16_t y, Object &b, uint8_t board[5][5]);