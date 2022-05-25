#include"TextObject.h"

TextObject::TextObject()
{
    ColorText.r = 255;
    ColorText.g = 255;
    ColorText.b = 255;
    tTexture = NULL;
    width = 0;
    height = 0;
}
TextObject::~TextObject()
{

}
bool TextObject::LoadFromRenderText(TTF_Font* font,SDL_Renderer* tRenderer)
{
    SDL_Surface* TextSurface = TTF_RenderText_Solid(font,text.c_str(),ColorText);
    if(TextSurface != NULL)
    {
        tTexture = SDL_CreateTextureFromSurface(tRenderer,TextSurface);
        width = TextSurface->w;
        height = TextSurface->h;

        SDL_FreeSurface(TextSurface);
    }
    return tTexture!= NULL;
}

void TextObject::Free()
{
    if(tTexture != NULL)
    {
        SDL_DestroyTexture(tTexture);
        tTexture = NULL;
    }
}
void TextObject::setColor(Uint8 red,Uint8 green,Uint8 blue)
{
    ColorText.r = red;
    ColorText.g = green;
    ColorText.b =  blue;
}
void TextObject::setColorFromTextColor(const int& type)
{
    if(type == RED_TEXT)
    {
        SDL_Color color = {255,0,0};
        ColorText = color;
    }
    else if(type == WHITE_TEXT)
    {
        SDL_Color color = {255,255,255};
        ColorText = color;
    }
    else if(type == BLACK_TEXT)
    {
        SDL_Color color = {0,0,0};
        ColorText = color;
    }
}
 void TextObject::RenderText(SDL_Renderer* tRenderer,int xp,int yp)
{
    SDL_Rect renderquad = {xp,yp,width,height};
    SDL_RenderCopy(tRenderer,tTexture,NULL,&renderquad);
}
