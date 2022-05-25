#include"unit.h"

bool SDLunit::checkCollision(SDL_Rect a,SDL_Rect b)
{
    int leftA,leftB;
    int rightA,rightB;
    int topA,topB;
    int bottomA,bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if(bottomA <= topB)
    {
        return false;
    }
    if(topA >= bottomB)
    {
        return false;
    }
    if(rightA <= leftB)
    {
        return false;
    }
    if(leftA >= rightB)
    {
        return false;
    }
    return true;
}

int SDLunit::ShowMenu(SDL_Renderer* gRenderer,TTF_Font* font,const std::string menu1,const std::string menu2,const std::string menu3)
{
    LoadTexture imageMenu;
    bool check = imageMenu.LoadImage("image//AnhNen.png",gRenderer);
    if(check ==  false)
    {
        return 1;
    }

    const int NumText = 2;
    SDL_Rect PosText[NumText];
    PosText[0].x = 50;
    PosText[0].y = 200;
    PosText[1].x = 50;
    PosText[1].y = 300;

    TextObject TextMenu[NumText], WinOrLost;


    TextMenu[0].setText(menu1);
    TextMenu[0].setColorFromTextColor(TextObject::WHITE_TEXT);
    TextMenu[0].LoadFromRenderText(font,gRenderer);



    TextMenu[1].setText(menu2);
    TextMenu[1].setColorFromTextColor(TextObject::WHITE_TEXT);
    TextMenu[1].LoadFromRenderText(font,gRenderer);

    SDL_Rect a;
    a.x = 50;
    a.y = 100;
    WinOrLost.setText(menu3);
    WinOrLost.setColorFromTextColor(TextObject::WHITE_TEXT);
    WinOrLost.LoadFromRenderText(font,gRenderer);

    int x,y;
    SDL_Event event;
    while(true)
    {
        imageMenu.render(gRenderer);
        WinOrLost.RenderText(gRenderer,a.x,a.y);
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
                {
                    x = event.motion.x;
                    y = event.motion.y;
                    for(int i = 0; i < NumText ; i++)
                    {
                        if( x > PosText[i].x && x < PosText[i].x + TextMenu[i].getWidth()
                           && y > PosText[i].y && y < TextMenu[i].getHeight() + PosText[i].y)
                        {
                            TextMenu[i].setColorFromTextColor(TextObject::RED_TEXT);
                            TextMenu[i].LoadFromRenderText(font,gRenderer);
                        }
                        else
                        {
                            TextMenu[i].setColorFromTextColor(TextObject::WHITE_TEXT);
                            TextMenu[i].LoadFromRenderText(font,gRenderer);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    x = event.motion.x;
                    y = event.motion.y;
                    for(int i = 0; i < NumText ; i++)
                    {
                        if( x > PosText[i].x && x < PosText[i].x + TextMenu[i].getWidth()
                               && y > PosText[i].y && y < TextMenu[i].getHeight() + PosText[i].y)
                        {
                            return i;
                        }

                    }
                }
                break;
            default: break;
            }
        }
    TextMenu[0].RenderText(gRenderer,PosText[0].x,PosText[0].y);
    TextMenu[1].RenderText(gRenderer,PosText[1].x,PosText[1].y);
    SDL_RenderPresent(gRenderer);
    }
    return 1;
}

int SDLunit::Random(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
