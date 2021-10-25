#pragma once

#include <tice.h>

#include "Common.h"
bool validPos(int8_t x, int8_t y);

bool moveBox(int16_t x, int16_t y, Object &b, Entitytypes board[5][5]);