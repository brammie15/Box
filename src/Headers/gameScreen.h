#pragma once
#include <graphx.h>
#include <keypadc.h>
#include <math.h>
#include <tice.h>

#include "Headers/Levels.h"
#include "Headers/box.h"
#include "Headers/common.h"
#include "Headers/player.h"
#include "Headers/screen.h"
class GameScreen : public Screen {
   public:
    uint8_t board[5][5];
    kb_key_t key;
    Object player;
    Object box;
    Object goal;
    bool previousUp;
    bool previousDown;
    bool previousLeft;
    bool previousRight;
    bool checkGoals(Object goal, Object box);
};