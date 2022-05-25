#ifndef SKILL_H_
#define SKILL_H_

#include "LoadTexture.h"
#include"unit.h"

class dan_ban : public LoadTexture
{
public:
    dan_ban(){};
    ~dan_ban(){};
};

class skill
{

public:
    skill();
    ~skill();

    void ImageSkilLoadFromFile(std::string path,SDL_Renderer* sRenderer);
    void RenderSkill(SDL_Renderer* sRenderer);
private:
    int VelSkill;
    int sPosX;
    int sPoxY;
    dan_ban vien_dan;
};

#endif // SKILL_H_
