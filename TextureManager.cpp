//
// Created by Yacov Averbuch on 18/02/2019.
//

#include "TextureManager.h"

SDL_Renderer * TextureManager::renderer = nullptr;

SDL_Texture * TextureManager::LoadTexture(const char *fileName)
{
    SDL_Surface * tmpSurfase = IMG_Load(fileName);

    if (not tmpSurfase)
    {
        std::cerr << "can't load picture '" << fileName << "'\n";
        std::cerr << IMG_GetError() << std::endl;

    }
    else
    {
        // std::cout << "picture '" << fileName << "' loaded successfully\n";
    }

    SDL_Texture * tex = SDL_CreateTextureFromSurface(TextureManager::renderer, tmpSurfase);
    SDL_FreeSurface(tmpSurfase);
    return tex;
}

void TextureManager::init(SDL_Renderer *ren)
{
    renderer = ren;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(TextureManager::renderer, tex, & src, & dest);
}


