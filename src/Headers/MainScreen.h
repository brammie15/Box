#pragma once
#include <graphx.h>
#include <keypadc.h>
#include <math.h>
#include <tice.h>

#include "Common.h"
#include "Screen.h"
class MainScreen : Screen {
   public:
    void setup();
    void draw();
    bool shouldStart = false;
};