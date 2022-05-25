#ifndef LOAD_TEXTURE_H_
#define LOAD_TEXTURE_H_

#include"unit.h"

class LoadTexture
{
public:
    LoadTexture();
    ~LoadTexture();

    void setRectPos(const int& x,const int &y){mRect.x = x; mRect.y = y;}

    SDL_Rect getSDL_rect()const{
       return mRect;
    }

    virtual bool LoadImage(std::string path, SDL_Renderer* mRenderer);
    void render(SDL_Renderer* mRenderer,const SDL_Rect* clip = NULL);

    void free();

protected:
    SDL_Texture* mTexture;
    SDL_Rect mRect;
};

#endif // LOAD_TEXTURE_H_


