#ifndef CHARACTER_H_
#define CHARACTER_H_


#include"unit.h"
#include"LoadTexture.h"
#include"Danban.h"

#define TRONG_LUC 10

class character:public LoadTexture
{
public:
    character();
    ~character();


    enum WalkType
    {
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
        WALK_JUMP = 2,
    };
    bool LoadImageCharacter(std::string path,SDL_Renderer* mRenderer);
    void ShowCharacter(SDL_Renderer* mRenderer);
    void Handle(SDL_Event events,SDL_Renderer* pRenderer);
    void SetClips();

    void setPos(const float& x,const float& y){
        PosX = x;
        PosY = y;
    }
    float setPosY(const float& y){PosY = y;}
    float getPosX(){
        return PosX;
    }
    float getposY()
    {
        return PosY;
    }
    void roi_tu_do();
    void check_va_cham_voi_map(MapCode &maplol);


    void SetMapXY(const int map_x,const int map_y)
    {
        map_x_ = map_x;
        map_y_ = map_y;
    };
    void ControlMap(MapCode &mapdota);
    void SetListDanBan(std::vector<Danban*>list_dan_ban){
        p_list_dan_ban = list_dan_ban;
    };
    std::vector<Danban*>get_list_dan_ban()const{
        return p_list_dan_ban;
    }
    void HandlDanBan(SDL_Renderer* des,MapCode &mapDaTa);

    void RemoveDanBan(const int& idx);
    void MoveCharacter(MapCode &mapDaTa);
    SDL_Rect getSDL_rectOfCharacter()
    {
        SDL_Rect a;
        a.x = mRect.x;
        a.y = mRect.y;
        a.h = HeightFrame;
        a.w = WidthFrame/8;
        return a;
    }
    int getWidthFrame()const{return WidthFrame;}
    int getHeigthFrame()const{return HeightFrame;}
    float getPosXatDanBan()const {return PosXatDanBan;}
    void setPosXatDanBan(const float& PosXatDanBan_){PosXatDanBan = PosXatDanBan_;}
    int getStatusCharacter()const{return status;}
    int getMoney()const{return money;}
    int getHeart()const{return heart;}
    void setHeart(const int& heart_){heart = heart_;}


private:
    std::vector<Danban*> p_list_dan_ban;
    float VelX;
    float VelY;

    float PosX;
    float PosY;

    int WidthFrame;
    int HeightFrame;

    SDL_Rect FrameClip[8];
    input inputType;
    int frame;
    int status;

    int map_x_;
    int map_y_;

    bool on_gound;
    int come_back_time;
    float PosXatDanBan;
    int money;
    int ten_lua;
    int heart;
};

#endif // CHARACTER_H_
