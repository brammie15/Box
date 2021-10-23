#include <graphx.h>
#include <keypadc.h>
#include <tice.h>

#include "Headers/Common.h"
#include "Headers/Screen.h"
void Screen::setup() {
    gfx_Begin();

    gfx_SetTextFGColor(0);
    gfx_SetTextBGColor(255);

    gfx_SetTextConfig(gfx_text_clip);
    gfx_SetMonospaceFont(8);
}

void Screen::draw() {
    gfx_SetDrawBuffer();

    gfx_FillScreen(255);

    gfx_PrintStringXY("Box-IT", 0, 0);
}