#ifndef DRAGHINI_H
#define DRAGHINI_H
#pragma once

/* Global Includes */
//----------------------------------------------------------------
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//----------------------------------------------------------------

/* Structs */
//----------------------------------------------------------------
typedef struct Vector2 {
    float x;
    float y;
} Vector2;

typedef struct Color {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} Color;

#define WHITE Color { 255, 255, 255, 255 }
#define RED   Color { 187, 0, 0, 255 }
//----------------------------------------------------------------

/* Texture2D */
//-----------------------------------------------------------------
class Texture2D {
    public:
        Texture2D(const char* filePath);
        ~Texture2D();
        void LoadTexture(SDL_Texture* texture);
        const char* GetFilePath();
        SDL_Texture* image;
    private:
        const char* fileLoc;
        //SDL_Texture* image;
        SDL_Rect srcRec;
        int width;
        int height;
};
//-----------------------------------------------------------------

/* Input Manager */
//----------------------------------------------------------------
class InputManager {
    public:
        InputManager() {}
        ~InputManager() {}
        void UpdateKeyboardState();
        bool ShouldClose();
        bool IsKeyDown(SDL_Scancode scanCode);
    private:
        const Uint8* keyboardState;
        SDL_Event event;
        bool shouldQuit;
};
//----------------------------------------------------------------

/* Window Manager */
//----------------------------------------------------------------
class WindowManager {
    public:
        WindowManager();
        ~WindowManager();
        int InitSDL(const char* title, int screenWidth, int screenHeight);
        void ClearBackground(Color color);
        void Present();
        void DrawTexture(SDL_Texture* texture);
        void DrawTexture2D(Texture2D* texture2D);
        void SetTargetFPS(int fps);
        void UpdateWindow();
        bool ShouldWindowClose();
        // --------------------------------------------------------------
    private:
        int windowWidth;
        int windowHeight;
        const char* windowTitle;
        int targetFPS;
        void LoadTexture2D(Texture2D* texture2D);
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event event;
        bool initializedSDL;
        InputManager inputManager;
};
//----------------------------------------------------------------

// ------------------------------ //
/*   Texture2D Implementation     */
// ------------------------------ //
Texture2D::Texture2D(const char* filePath) {
    fileLoc = filePath;
    image = NULL;
}
Texture2D::~Texture2D() {
    if(image != NULL) {
        SDL_DestroyTexture(image);
    }
}
void Texture2D::LoadTexture(SDL_Texture* texture) {
    // Get Width and Height
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    // Set Src Rect
    srcRec = SDL_Rect { 0, 0, width, height };

    // Set Image
    image = texture;
}
const char* Texture2D::GetFilePath() {
    return fileLoc;
}

// ------------------------------ //
/*         Input Manager          */
// ------------------------------ //
void InputManager::UpdateKeyboardState() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) shouldQuit = true;
    }
}

bool InputManager::ShouldClose() {
    return shouldQuit;
}

bool InputManager::IsKeyDown(SDL_Scancode scanCode) {
    return keyboardState[scanCode];
}

// ------------------------------ //
/*  WindowManager Implementation  */
// ------------------------------ //
WindowManager::WindowManager() {
    window = NULL;
    renderer = NULL;
    initializedSDL = false;
    targetFPS = 60;
}

WindowManager::~WindowManager() {
    if (window != NULL) {
        SDL_DestroyWindow(window);
        window = NULL;
    }
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (initializedSDL) {
        SDL_Quit();
    }
}

/* 
    Creates an SDL window with the desired parameters.
    If passed values are NULL and 0, then the a default window is created.
*/
int WindowManager::InitSDL(const char* title, int screenWidth, int screenHeight) {
    // Init Inputs
    if (title == NULL) windowTitle = "Draghini";
    else windowTitle = title;

    if (screenWidth == 0) windowWidth = 512;
    else windowWidth = screenWidth;

    if (screenHeight == 0) windowHeight = 512;
    else windowHeight = screenHeight;  

    // Initialize SDL Video Subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Failed to initialize SDL Video Subsystem. SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    else {
        initializedSDL = true;
    }

    // Create SDL Window
    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cout << "Failed to create SDL Window. SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cout << "Failed to create SDL Renderer. SDL Error: " << SDL_GetError() << std::endl;
    }

    return 0;
}

// Loads Texture2D
void WindowManager::LoadTexture2D(Texture2D* texture2D) {
    // Load texture
    SDL_Texture* sdlTexture = IMG_LoadTexture(renderer, texture2D->GetFilePath());
    if (sdlTexture == NULL) {
        std::cout << "Failed to load texture '" << texture2D->GetFilePath() << "'" << std::endl;
    }

    texture2D->LoadTexture(sdlTexture);
}

// Clears Background With Desired Color
void WindowManager::ClearBackground(Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

// Renders SDL_Texture
void WindowManager::DrawTexture(SDL_Texture* texture) {
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}

// Takes A Texture2D and Loads Texture If Missing And Then Renders Image
void WindowManager::DrawTexture2D(Texture2D* texture2D) {
    if (texture2D->image == NULL) {
        LoadTexture2D(texture2D);
    }
    SDL_RenderCopy(renderer, texture2D->image, NULL, NULL);
}

// Swaps Buffers and Presents Drawings
void WindowManager::Present() {
    SDL_RenderPresent(renderer);
}

void WindowManager::SetTargetFPS(int fps) {
    
}

void WindowManager::UpdateWindow() {
    // Check for SDL Events
    inputManager.UpdateKeyboardState();

    // Then Cap FPS
}

// Checks If Window Should Be Closed
bool WindowManager::ShouldWindowClose() {
    return inputManager.ShouldClose();
}

#endif // DRAGHINI_H