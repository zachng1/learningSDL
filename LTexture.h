#ifndef LTEXTURE
#define LTEXTURE

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class LTexture {
    public:
    LTexture();
    ~LTexture();

    bool loadFromFile(std::string path);
    void setRenderer(SDL_Renderer * renderer);
    void free();
    void render(int x, int y);

    int getWidth();
    int getHeight();

    private:
    SDL_Texture * mTexture;
    SDL_Renderer * pRenderer;

    int mWidth;
    int mHeight;
};

//LTexture.h
#endif