#pragma once
#include <keypadc.h>
#include <tice.h>

#include "Box.h"
#include "Common.h"
#include "Player.h"
#include "Screen.h"

class GameScreen : public Screen {
   public:
    Entitytypes board[5][5];
    kb_key_t key;
    Object playerObj;
    Object boxes[2];
    Object goalObj;
    virtual void setup() override;
    virtual void draw() override;
    bool isRunning = true;
    //bool checkGoals(Object goal, Object box);
   private:
    bool previousRight;
    bool previousLeft;
    bool previousDown;
    bool previousUp;
    uint8_t currentLevel;
};
