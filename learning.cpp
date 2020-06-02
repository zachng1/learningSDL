#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "LTexture.h"

bool init();
bool loadMedia();
void close();
SDL_Texture * loadTexture(std::string path);


int SCREEN_WIDTH = 500;
int SCREEN_HEIGHT = 500;

SDL_Window * gWindow = nullptr;
SDL_Renderer * gRenderer = nullptr;

LTexture frontTexture;
LTexture backTexture;

int main(int argc, char ** argv) {
    bool quit = false;
    SDL_Event e;
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;

    if (!init()) {
        std::cout << "Failed to initialise" << std::endl;
        close();
        return 1;
    }
    frontTexture.setRenderer(gRenderer);
    backTexture.setRenderer(gRenderer);

    if (!loadMedia()) {
        std::cout << "Failed to load media" << std::endl;
        close();
        return 1;
    }

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        backTexture.render(0, 0);
        frontTexture.render(0, 0);

        SDL_RenderPresent(gRenderer);
    }
    close();
    return 0;
}

bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Could not initialise. Error:" << SDL_GetError() << std::endl;
        success = false;
    }

    else {
        gWindow = SDL_CreateWindow("SDL tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
            std::cout << "Window could not be created. Error:" << SDL_GetError() << std::endl;
            success = false;
        }
        else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == nullptr) {
                std::cout << "Could no create renderer. Error:" << SDL_GetError() << std::endl;
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xFF);
                int imgFlags = IMG_INIT_JPG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    std::cout << "SDL_image jpeg lib could not init. Error:" << SDL_GetError() << std::endl;
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia() {
    bool success = true;
    if (!frontTexture.loadFromFile("data/porcorosso.jpg")) {
        success = false;
    }
    if (!backTexture.loadFromFile("data/mononoke.jpg")) {
        success = false;
    }

    return success;
}

void close() {
    frontTexture.free();
    backTexture.free();

    //this also destroys gScreenSurface
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture * loadTexture(std::string path) {
    SDL_Texture * newTexture = nullptr;
    SDL_Surface * loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cout << "Could not load image. Error:" << SDL_GetError() << std::endl;
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == nullptr) {
            std::cout << "Could not create new texture. Error:" << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}