#include "LTexture.h"

LTexture::LTexture() {
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture() {
    free();
}

bool LTexture::loadFromFile(std::string path) {
    free();

    SDL_Texture * newTexture = nullptr;

    SDL_Surface * loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cout << "Could not load image. Error:" << SDL_GetError() << std::endl;
    }
    else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, ((Uint32 *)(loadedSurface->pixels))[(loadedSurface->pitch * 5) + (loadedSurface->pitch / 2)]);
        newTexture = SDL_CreateTextureFromSurface(pRenderer, loadedSurface);
        if (newTexture == nullptr) {
            std::cout <<"Could not render texture. Error:" << SDL_GetError() << std::endl;
        }
        else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return mTexture != nullptr;
}

void LTexture::setRenderer(SDL_Renderer * renderer) {
    pRenderer = renderer;
}

void LTexture::free() {
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render(int x, int y) {
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    SDL_RenderCopy(pRenderer, mTexture, nullptr, nullptr);
}

int LTexture::getWidth() {
    return mWidth;
}
int LTexture::getHeight() {
    return mHeight;
}