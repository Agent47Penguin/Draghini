#include <iostream>
#include "Draghini.h"

int main(int argc, char* argv[]) {
    WindowManager windowManager = WindowManager();

    if (windowManager.InitSDL() != 0) {
        return -1;
    } 
    
    Texture2D monke = Texture2D("assets/monke.png");

    while (!windowManager.ShouldClose()) {
        // Render
        windowManager.ClearBackground(RED);
        windowManager.DrawTexture2D(&monke);
        windowManager.Present();

        // Update
        windowManager.Update();
    }

    return 0;
}