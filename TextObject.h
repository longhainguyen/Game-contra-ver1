#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "unit.h"
class TextObject
{
public:
    TextObject();
    ~TextObject();
    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
    };

    bool LoadFromFile(std::string path);
    bool LoadFromRenderText(TTF_Font* font,SDL_Renderer* tRenderer);
    void Free();

    void setColor(Uint8 red,Uint8 green,Uint8 blue);
    void setColorFromTextColor(const int& type);

    void RenderText(SDL_Renderer* tRenderer,int xp,int yp);
    int getWidth()const{return width;}
    int getHeight()const{return height;}
    void setText(const std::string& text_){text = text_;}
    std::string getText(){return text;}
private:
    std::string text;
    SDL_Color ColorText;
    SDL_Texture* tTexture;
    int width;
    int height;
};

#endif // TEXT_OBJECT_H_
