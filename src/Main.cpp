#include <iostream>
#include "Draghini.h"

int main(int argc, char* argv[]) {
    WindowManager windowManager = WindowManager();

    if (windowManager.InitSDL(NULL, 0, 0) != 0) {
        return -1;
    } 
    
    Texture2D monke = Texture2D("assets/monke.png");

    windowManager.SetTargetFPS(60);
    while (!windowManager.ShouldWindowClose()) {
        // Render
        windowManager.ClearBackground(RED);
        windowManager.DrawTexture2D(&monke);
        windowManager.Present();

        // Update
        windowManager.UpdateWindow();
    }

    return 0;
}