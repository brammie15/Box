#include "Headers/MainScreen.h"

#include <graphx.h>
#include <keypadc.h>
#include <tice.h>

#include "Headers/Common.h"
#include "Headers/Screen.h"
void MainScreen::setup() {
    previousUp = false;
    previousDown = false;
    previousEnter = false;
    gfx_Begin();

    gfx_SetTextFGColor(1);  //text color
    gfx_SetTextBGColor(255);
    //gfx_SetTextTransparentColor(5);
    gfx_SetTextConfig(gfx_text_clip);
    gfx_SetMonospaceFont(8);
    //gfx_SetTextScale(5, 5);
}

void MainScreen::draw() {
    kb_Scan();

    if (kb_IsDown(kb_KeyEnter) && !previousEnter) {
        this->shouldStart = true;
    }

    gfx_SetDrawBuffer();

    gfx_FillScreen(255);

    gfx_PrintStringXY("Box-IT", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 90);
    gfx_PrintStringXY("Press Enter to start", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100);
    gfx_SwapDraw();
}