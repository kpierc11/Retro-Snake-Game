#pragma once
#include <string>
#include <unordered_map>

#include <SDL3/SDL.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_render.h>

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    SDL_Texture *LoadTexture(SDL_Renderer *renderer, std::string filePath);

    SDL_Surface *mSurface;
    char *mBmpPath;
    std::string mFilePath;
    SDL_Texture *mTexture;
    std::unordered_map<std::string, SDL_Texture *> mTextures;
};
