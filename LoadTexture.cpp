#include"LoadTexture.h"
#include<iostream>

LoadTexture::LoadTexture()
{
    mTexture = NULL;
    mRect.x = 0;
    mRect.y = 0;
    mRect.w = 0;
    mRect.h = 0;
}

LoadTexture::~LoadTexture()
{
    free();
}

bool LoadTexture::LoadImage(std::string path, SDL_Renderer* mrenderer)
{
    free();
    SDL_Texture* NewTexture = NULL;

    SDL_Surface* LoadedSurface = IMG_Load(path.c_str());
    if(LoadedSurface != NULL)
    {
        SDL_SetColorKey(LoadedSurface,SDL_TRUE,SDL_MapRGB(LoadedSurface->format,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B));
        NewTexture = SDL_CreateTextureFromSurface(mrenderer,LoadedSurface);
        if(NewTexture != NULL)
        {
            mRect.w = LoadedSurface->w;
            mRect.h = LoadedSurface->h;
        }else {
            std::cout<<"Unable load NewTexture "<<std::endl;
        }
        SDL_FreeSurface(LoadedSurface);
    }else{
        std::cout<<"Unable load LoaedSurface "<<std::endl;
    }
    mTexture = NewTexture;
    return mTexture != NULL;
}

void LoadTexture::render(SDL_Renderer* mrenderer,const SDL_Rect* clip)
{
    SDL_Rect renderquad = {mRect.x,mRect.y,mRect.w,mRect.h};
    SDL_RenderCopy(mrenderer,mTexture,clip,&renderquad);
}

void LoadTexture::free()
{
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mRect.w = 0;
        mRect.h = 0;
    }
}


