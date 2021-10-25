#pragma once

class Screen {
   public:
    virtual void setup();
    virtual void draw();
    bool isRunning;
};
