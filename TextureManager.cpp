#include "TextureManager.h"
#include "include/SDL2/SDL_image.h"
#include "include/SDL2/SDL.h"

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(std::string fileName,
    std::string id, SDL_Renderer* pRenderer)
{
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

    if(pTempSurface == 0)
    {
        return false;
    }

    SDL_Texture* pTexture = 
        SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    //if thats ok, add texture to list
    if(pTexture != 0)
    {
        m_textureMap[id] = pTexture;
        return true;
    }

    //if we reach here something bad has happened
    return false;
}

void TextureManager::draw(std::string id, int x, int y, int width,
                    int height, SDL_Renderer* pRenderer, 
                    SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id],
                    &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width,
                    int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, 
                    double angle, int alpha, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = width * currentFrame;
    srcRect.y = height * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    
    SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
    SDL_RenderCopyEx(pRenderer, m_textureMap[id],
                    &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::clearFromTextureMap(std::string id)
{
    m_textureMap.erase(id);
}

void TextureManager::drawTile(std::string id, int margin, int spacing, 
    int x, int y, int width, int height, int currentRow, int currentFrame,
    bool H, bool V, bool D,
    SDL_Renderer *pRenderer)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
   
    //we must now deal with tiles that have been flipped
    SDL_RendererFlip flip;
    double angle;
    if (H == false && V == false && D == true)
    {   
        angle = 90;
        flip = SDL_FLIP_VERTICAL;
    }
    else if (H == false && V == true && D == false)
    {
        angle = 0;
        flip = SDL_FLIP_VERTICAL;
    }
    else if (H == true && V == false && D == false)
    {
        angle = 0;
        flip = SDL_FLIP_HORIZONTAL;
    }
    else if (H == false && V == true && D == true)
    {
        angle = 90;
        flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    }
    else if (H == true && V == false && D == true)
    {
        angle = 90;
        flip = SDL_FLIP_NONE;
    }
    else if (H == true && V == true && D == false)
    {
        angle = 0;
        flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    }
    else if (H == true && V == true && D == true)
    {
        angle = 90;
        flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | 
                        SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    }
    else
    {
        angle = 0;
        flip = SDL_FLIP_NONE;
    }

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, 
        &destRect, angle, 0, flip);
}
