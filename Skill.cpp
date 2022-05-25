#include"Skill.h"

skill::skill()
{
    VelSkill = 0;
    sPosX = 0;
    sPoxY = 0;
}
skill::~skill()
{

}
void skill::ImageSkilLoadFromFile(std::string path,SDL_Renderer* sRenderer)
{
    vien_dan.LoadImage(path.c_str(),sRenderer);
}
void skill::RenderSkill(SDL_Renderer* sRenderer)
{
    vien_dan.setRectPos(sPosX,sPoxY);
    vien_dan.render(sRenderer,NULL);
}
