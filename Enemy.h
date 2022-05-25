#ifndef ENEMY_H_
#define ENEMT_H_

#include"unit.h"
#include"LoadTexture.h"
#include"Danban.h"

#define ENEMY_FRAME_NUM 8
#define GIA_TOC_ROI 0.8

class enemy:public LoadTexture
{
public:
    enemy();
    ~enemy();
    enum Move_Status_Enemy
    {
        MOVE_NO = 0,
        MOVE_AROUND = 1,
        Move_FLY = 2,

    };

    void setValX(const float &ValX_){ValX = ValX_;}
    void setValY(const float &ValY_){ValY = ValY_;}

    void setPosEnemyX(const float& x){PosEnemyX = x;}
    void setPosEnemyY(const float& y){PosEnemyY = y;}

    float getPosEnemyX()const{return PosEnemyX;}
    float getPosEnemyY()const{return PosEnemyY;}

    void setMapXY(const int& x,const int& y){mapX = x; mapY =y;}
    void setClip();
    void Show(SDL_Renderer* eRenderer);

    int getWidthEnemy()const{return widthEnemy;}
    int getHeightEnemy()const{return heightEnemy;}
    void setWidthGeight(const int& x,const int &y){widthEnemy = x; heightEnemy = y;}


    void MoveEnemy(MapCode &map_data);
    bool LoadImageEnemy(std::string path,SDL_Renderer* eRenderer);
    void CheckToMap(MapCode &map_data);

    void setStatusEnemy(const int& StatusEnemy_){StatusEnemy = StatusEnemy_;}
    void setDistanceMove(const int& LimLeft_,const int &LimRight_){LimLeft = LimLeft_;LimRight = LimRight_;}
    void setInputLeft(const int& ipLeft){InputMove.left = ipLeft;}
    void setInputRight(const int& ipRight){InputMove.right = ipRight;}
    void LoadInputTypeMoveFromStatus(SDL_Renderer* eRenderer);
    std::vector<Danban*>getDanBanList()const{return DanbanList;}
    void setDanBanList(const std::vector<Danban*>DanbanList_){DanbanList = DanbanList_;}
    void InnitDanBan(Danban* Danban_,SDL_Renderer* eRenderer,std::string path);
    void MakeDanban(SDL_Renderer* eRenderer,const int& Xleft,const int& Yleft,MapCode& map_data);
    void CreateEnemy(std::string path,const float& EposX,const float& EposY,SDL_Renderer* eRenderer);
    void RenderEnemy(MapCode& map_data,SDL_Renderer* eRenderer);
    void RenderCloud(MapCode& map_data,SDL_Renderer* eRenderer);
    bool getOnGound ()const{return on_gound;}
    void RemoveDanBan(const int& idx);
    int getBossHeart()const {return BossHeart;}
    void setBossHeart(const int& BossHeart_){BossHeart = BossHeart_;}
    void setDistancedanban(const int& x){distacce_danban = x;}
    int getDistancedanban()const{return distacce_danban;}
    void setPosHeroPos(const float& x,const float& y){getHeroPosX = x;getHeroPosY = y;}
    void MoveToFindHero();
    void setDistanceToFindHero(const int& x){distacceToBeginFindHero = x;}


private:
    bool on_gound;

    int mapX;
    int mapY;

    float ValX;
    float ValY;
    float PosEnemyX;
    float PosEnemyY;

    SDL_Rect EnemyClip[ENEMY_FRAME_NUM];

    int widthEnemy;
    int heightEnemy;
    int frameCount;
    int comeBackTime;

    int StatusEnemy;
    int LimLeft;
    int LimRight;
    std::vector<Danban*>DanbanList;
    input InputMove;
    int BossHeart;
    int distacce_danban;
    float getHeroPosX;
    float getHeroPosY;

    int distacceToBeginFindHero;


};

#endif // ENEMY_H_
