#include "VuNoObject.h"

VuNo::VuNo()
{
    posVuNoX = 0;
    PosVuNoY = 0;
    WidthFrame = 0;
    HeightFrame = 0;
    frameCount = 0;
}
bool VuNo::LoadImageVuNo(std::string path,SDL_Renderer* vRenderer)
{
    bool check = LoadImage(path.c_str(),vRenderer);
    if(check == true)
    {
        WidthFrame = mRect.w / 8;
        HeightFrame = mRect.h;
    }
    return check;
}
void VuNo::setClip()
{
    if(WidthFrame > 0&& HeightFrame >0)
    {
        for(int i = 0; i< 8 ; i++)
        {
            VuNoClip[i].x = WidthFrame*i;
            VuNoClip[i].y = 0;
            VuNoClip[i].w = WidthFrame;
            VuNoClip[i].h = HeightFrame;
        }
    }
}
void VuNo::ShowImageVuNo(SDL_Renderer* vRenderer,MapCode& map_data,const int& posVuNoX_,const int& PosVuNoY_)
{
    setClip();
    setposVuNoX(posVuNoX_);
    setposVuNoY(PosVuNoY_);
    mRect.x = posVuNoX - map_data.startX;
    mRect.y = PosVuNoY - map_data.startY;
    frameCount++;
    if(frameCount >= 8)
    {
        frameCount = 0;
    }
    SDL_Rect* CurrentClip = &VuNoClip[frameCount];
    SDL_Rect renderquad = {mRect.x,mRect.y,WidthFrame,HeightFrame};
    SDL_RenderCopy(vRenderer,mTexture,CurrentClip,&renderquad);
}
