#pragma once
#include <graphx.h>
#include <keypadc.h>
#include <math.h>
#include <tice.h>

#include "Common.h"
#include "Screen.h"

class MainScreen : public Screen {
   public:
    virtual void setup() override;
    virtual void draw() override;

    bool shouldStart = false;

   private:
    bool previousUp;
    bool previousDown;
    bool previousEnter;
};
