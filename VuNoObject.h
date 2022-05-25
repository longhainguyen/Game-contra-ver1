#ifndef VUNOOBJECT_H_
#define VUNOOBJECT_H_

#include"unit.h"
#include"LoadTexture.h"

class VuNo:public LoadTexture
{
public:
    VuNo();
    ~VuNo(){};
    void setClip();
    bool LoadImageVuNo(std::string path,SDL_Renderer* vRenderer);
    void ShowImageVuNo(SDL_Renderer* vRenderer,MapCode& map_data,const int& posVuNoX_,const int& PosVuNoY_);
    void setposVuNoX(const int& x){posVuNoX = x;}
    void setposVuNoY(const int& y){PosVuNoY = y;}
private:
    int WidthFrame;
    int HeightFrame;
    int frameCount;
    SDL_Rect VuNoClip[8];
    int posVuNoX;
    int PosVuNoY;

};
#endif // VUNOOBJECT_H_
