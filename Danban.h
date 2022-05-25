#ifndef DANBAN_H_
#define DANBAN_H_

#include "unit.h"
#include "LoadTexture.h"

class Danban : public LoadTexture
{
public:
    Danban();
    ~Danban();

    enum chieu_dan_ban
    {
        left = 10,
        right = 20,
        up = 30,
        down = 40,
    };

    void SetValX(const int & x){ValX = x;}
    void SetValY(const int &y){
        ValY = y;
    }
    int getValX() const {
        return ValX;
    }
    int getValY() const{
        return ValY;
    }

    bool getIsMove () const{
        return isMove;
    }
    void setIsMove (const bool& check){
        isMove = check;
    }
    void HandleMove(const int & x_border,const int& y_border,MapCode &mapDaTa);
    void DanbanMove(MapCode &mapDaTa);


    void setChieuBan(const int& x){
        inputChieuBan = x;
    }
    int getChieuBan()const{
        return inputChieuBan;
    }
    int getPosDanBanX()const{
        return PosDanBanX;
    }
    int getPosDanBanY()const{
        return PosDanBanY;
    }
    void setPosDanBanXY(const int& x,const int& y)
    {
        PosDanBanX = x;
        PosDanBanY = y;
    }
    void set_Map_X_Y_dan(const int& x,const int& y)
    {
        Map_X_dan_ = x;
        Map_y_dan_ = y;
    }
    void setGetStatusCharacter(const int& x)
    {
        getStatusCharacter = x;
    }
    int GetGetStatusCharacter () const{
        return getStatusCharacter;
    }
    void HandleEnemy(const int & x_border, const int & y_border,MapCode &mapDaTa);
    void CreateDanBan(std::string path,SDL_Renderer* dRenderer);
    void RenderDanBan(MapCode& map_data,SDL_Renderer* dRenderer,const int& dValX,const int& ChieuBan);
    void setStatusCharacter2(const int& status){getStatusCharacter2 = status;}
    void HandleEnemyisFlying(const int & x_border, const int & y_border,MapCode &map_data);


private:
    int ValX;
    int ValY;

    int Map_X_dan_;
    int Map_y_dan_;

    int PosDanBanX;
    int PosDanBanY;

    int inputChieuBan;
    bool isMove;

    int getStatusCharacter;
    int getStatusCharacter2;
};

#endif // DANBAN_H_
