#include "TextureManager.hpp"
#include <iostream>

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

SDL_Texture *TextureManager::LoadTexture(SDL_Renderer *renderer, std::string filePath)
{

    char *bmpPath = nullptr;

    SDL_asprintf(&bmpPath, "%s", filePath.c_str());

    SDL_Surface *surface = SDL_LoadBMP(bmpPath);
    if (!surface)
    {
        SDL_Log("Couldn't load bitmap: %s", SDL_GetError());
        return nullptr;
    }

    SDL_free(bmpPath);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        SDL_Log("Couldn't create static texture: %s", SDL_GetError());
        return nullptr;
    }

    SDL_DestroySurface(surface);

    return texture;
}
