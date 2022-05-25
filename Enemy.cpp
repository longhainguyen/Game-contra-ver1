#include"Enemy.h"

enemy::enemy()
{
    PosEnemyX = 0;
    PosEnemyY = 0;
    widthEnemy = 0;
    heightEnemy = 0;
    ValX = 0;
    ValY = 0;
    on_gound = false;
    frameCount = 0;
    comeBackTime = 0;
    StatusEnemy = MOVE_AROUND;
    BossHeart = 0;
    distacce_danban = 0;
    getHeroPosX = 0;
    getHeroPosY = 0;
    distacceToBeginFindHero = 0;

}
enemy::~enemy()
{

}
bool enemy::LoadImageEnemy(std::string path,SDL_Renderer* eRenderer)
{
    bool check = LoadTexture::LoadImage(path.c_str(),eRenderer);
    if(check == true )
    {
        widthEnemy = mRect.w / ENEMY_FRAME_NUM;
        heightEnemy = mRect.h;
    }
    return check;
}


void enemy::setClip()
{
    EnemyClip[0].x = 0;
    EnemyClip[0].y = 0;
    EnemyClip[0].w = widthEnemy;
    EnemyClip[0].h = heightEnemy;

    EnemyClip[1].x = widthEnemy;
    EnemyClip[1].y = 0;
    EnemyClip[1].w = widthEnemy;
    EnemyClip[1].h = heightEnemy;

    EnemyClip[2].x = widthEnemy*2;
    EnemyClip[2].y = 0;
    EnemyClip[2].w = widthEnemy;
    EnemyClip[2].h = heightEnemy;

    EnemyClip[3].x = widthEnemy*3;
    EnemyClip[3].y = 0;
    EnemyClip[3].w = widthEnemy;
    EnemyClip[3].h = heightEnemy;

    EnemyClip[4].x = widthEnemy*4;
    EnemyClip[4].y = 0;
    EnemyClip[4].w = widthEnemy;
    EnemyClip[4].h = heightEnemy;

    EnemyClip[5].x = widthEnemy*5;
    EnemyClip[5].y = 0;
    EnemyClip[5].w = widthEnemy;
    EnemyClip[5].h = heightEnemy;

    EnemyClip[6].x = widthEnemy*6;
    EnemyClip[6].y = 0;
    EnemyClip[6].w = widthEnemy;
    EnemyClip[6].h = heightEnemy;

    EnemyClip[7].x = widthEnemy*7;
    EnemyClip[7].y = 0;
    EnemyClip[7].w = widthEnemy;
    EnemyClip[7].h = heightEnemy;
}



void enemy::Show(SDL_Renderer* eRenderer)
{
    if(comeBackTime == 0)
    {
        mRect.x = PosEnemyX - mapX;
        mRect.y = PosEnemyY - mapY;
        frameCount++;
        if(frameCount >= 8)
        {
            frameCount = 0;
        }
        SDL_Rect* CurrentClip = &EnemyClip[frameCount];
        SDL_Rect renderquad = {mRect.x,mRect.y,widthEnemy,heightEnemy};
        SDL_RenderCopy(eRenderer,mTexture,CurrentClip,&renderquad);

    }
}
void enemy::MoveEnemy(MapCode &map_data)
{
    if(comeBackTime == 0)
    {
        ValX = 0;
        ValY += GIA_TOC_ROI;
        if(ValY >= 5)
        {
            ValY = 5;
        }
        if(InputMove.left == 1)
        {

            ValX -= ENEMY_SPEED;
        }
        else if(InputMove.right == 1)
        {
            ValX += ENEMY_SPEED;
        }
        CheckToMap(map_data);
    }
    if(comeBackTime > 0)
    {
        comeBackTime --;
        if(comeBackTime == 0)
        {
            PosEnemyX -= 200;
            LimLeft -= 200;
            LimRight -= 200;
            PosEnemyY = 0;
            ValX = 0;
        }
    }
}

void enemy::CheckToMap(MapCode& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    bool check = true;
    int height_min = heightEnemy < PIXEL_SIXE ? heightEnemy:PIXEL_SIXE;
    x1 = (PosEnemyX + ValX)/PIXEL_SIXE;
    x2 = (PosEnemyX + ValX + widthEnemy - 10)/PIXEL_SIXE;

    y1 = (PosEnemyY)/PIXEL_SIXE;
    y2 = (PosEnemyY + height_min - 10)/PIXEL_SIXE;

    if(x1 >= 0 && x2 < MAP_WIDTH && y1>=0 && y2<MAP_HEIGHT)
    {
        if(ValX >= 0)
        {
            int val1 = map_data.Array[y1][x2];
            int val2 = map_data.Array[y2][x2];

            if((map_data.Array[y1][x2] != PIXEL_EMPTY && val1 != PIXEL_HEART)||( map_data.Array[y2][x2] !=PIXEL_EMPTY && val2!= PIXEL_HEART))
            {
                PosEnemyX = x2*PIXEL_SIXE;
                PosEnemyX -= widthEnemy + 10;
            }
        }
        else if(ValX < 0)
        {
            if((map_data.Array[y1][x1] != PIXEL_EMPTY && map_data.Array[y1][x1] != PIXEL_HEART)||( map_data.Array[y2][x1] != PIXEL_EMPTY && map_data.Array[y2][x1]!= PIXEL_HEART))
            {
                PosEnemyX = (x1 + 1)*PIXEL_SIXE;
                ValX = 0;
            }
        }
    }

    int width_min = widthEnemy < PIXEL_SIXE ? widthEnemy:PIXEL_SIXE;
    x1 = (PosEnemyX)/PIXEL_SIXE;
    x2 =(PosEnemyX + width_min - 10)/PIXEL_SIXE;

    y1 = (PosEnemyY + ValY)/PIXEL_SIXE;
    y2 = (PosEnemyY + ValY + heightEnemy - 1 )/PIXEL_SIXE;

    if(x1 >= 0 && x2 < MAP_WIDTH && y1>=0 && y2<MAP_HEIGHT)
    {
        if(ValY > 0)
        {
            int val1 = map_data.Array[y2][x1];
            int val2 = map_data.Array[y2][x2];

            if((val1 != PIXEL_EMPTY && val1 != PIXEL_HEART)||( val2 != PIXEL_EMPTY && val2!= PIXEL_HEART))
            {
                PosEnemyY = y2*PIXEL_SIXE;
                PosEnemyY -= (heightEnemy + 1);
                ValY = 0;
                on_gound = true;
            }
        }
        else if(ValY < 0)
        {
            int val1 = map_data.Array[y1][x1];
            int val2 = map_data.Array[y1][x2];
            if((val1 != PIXEL_EMPTY && val1 != PIXEL_HEART)||( val2 != PIXEL_EMPTY && val2 != PIXEL_HEART))
            {
                PosEnemyY = (y1+1)*PIXEL_SIXE;
                ValY = 0;
            }
        }
    }
    PosEnemyX += ValX;
    PosEnemyY += ValY;
    if(PosEnemyX < 0)
    {
        PosEnemyX = 1;
    }
    else if(PosEnemyX + widthEnemy > PIXEL_SIXE*MAP_WIDTH)
    {
        PosEnemyX = PIXEL_SIXE* MAP_WIDTH - 1;
    }
    if(PosEnemyY >= SCREEN_HEIGHT)
    {
        comeBackTime = 60;
    }

}

void enemy::LoadInputTypeMoveFromStatus(SDL_Renderer* eRenderer)
{
    if(StatusEnemy == MOVE_NO)
    {

    }
    else if(StatusEnemy == MOVE_AROUND)
    {
        if(on_gound == true)
        {
             if(PosEnemyX > LimRight)
            {
                InputMove.left = 1;
                InputMove.right = 0;
                LoadImageEnemy("image//threat_left.png",eRenderer);

            }else if(PosEnemyX < LimLeft)
            {
                InputMove.left = 0;
                InputMove.right = 1;
                LoadImageEnemy("image//threat_right.png",eRenderer);
            }
        }
        else
        {
            if(InputMove.left == 1)
            {
                LoadImageEnemy("image//threat_left.png",eRenderer);
            }
            else if(InputMove.right == 1)
            {
                LoadImageEnemy("image//threat_right.png",eRenderer);
            }
        }

    }
}

void enemy::InnitDanBan(Danban* Danban_,SDL_Renderer* eRenderer,std::string path)
{
    if(Danban_ != NULL)
    {
        Danban_->LoadImage(path.c_str(),eRenderer);
        Danban_->setChieuBan(Danban::left);
        Danban_->SetValX(5);
        Danban_->SetValY(5);
        Danban_->setRectPos(this->mRect.x,this->mRect.y);
        DanbanList.push_back(Danban_);
    }
}
void enemy::MakeDanban(SDL_Renderer* eRenderer,const int& Xleft,const int& Yleft,MapCode& map_data)
{
    if(on_gound == true)
    {
        for(int i = 0;i<DanbanList.size(); i++)
        {
            Danban* eDanban = DanbanList.at(i);
            if(eDanban != NULL)
            {
                if(eDanban->getIsMove())
                {
                    int eDanban_distance = mRect.x - eDanban->getSDL_rect().x;
                    if(eDanban_distance < distacce_danban && eDanban > 0)
                    {
                        eDanban->HandleEnemy(Xleft,Yleft,map_data);
                        eDanban->render(eRenderer);
                    }
                    else
                    {
                        eDanban->setIsMove(false);
                    }
                }
                 else
                {
                    eDanban->setIsMove(true);
                    eDanban->setRectPos(this->mRect.x ,this->mRect.y );
                }
            }
        }
    }
    else if(on_gound ==  false && StatusEnemy == Move_FLY)
    {
        for(int i = 0;i<DanbanList.size(); i++)
        {
            Danban* eDanban = DanbanList.at(i);
            if(eDanban != NULL)
            {
                if(eDanban->getIsMove())
                {
                    eDanban->HandleEnemyisFlying(Xleft,Yleft,map_data);
                    eDanban->render(eRenderer);
                }
                 else
                {
                    eDanban->setIsMove(true);
                    eDanban->setRectPos(this->mRect.x ,this->mRect.y );
                }
            }
        }
    }
}

void enemy::RemoveDanBan(const int& idx)
{
    int Size = DanbanList.size();
    if(Size > 0 && idx <Size)
    {
        Danban* p_danban = DanbanList.at(idx);
        DanbanList.erase(DanbanList.begin() + idx);
        if(p_danban != NULL)
        {
            delete p_danban;
            p_danban = NULL;
        }
    }
}
void enemy::CreateEnemy(std::string path,const float& EposX,const float& EposY,SDL_Renderer* eRenderer)
{
    LoadImageEnemy(path.c_str(),eRenderer);
    setClip();
    setPosEnemyX(EposX);
    setPosEnemyY(EposY);
}
void enemy::RenderEnemy(MapCode& map_data,SDL_Renderer* eRenderer)
{
    setMapXY(map_data.startX,map_data.startY);
    MoveEnemy(map_data);
    Show(eRenderer);
}
void enemy::RenderCloud(MapCode& map_data,SDL_Renderer* eRenderer)
{
    setMapXY(map_data.startX,map_data.startY);
    Show(eRenderer);
}
void enemy::MoveToFindHero()
{
    int distance = PosEnemyX - getHeroPosX;
    if(distance < distacceToBeginFindHero && distance>= 0)
    {
        PosEnemyX -= 3;
    }
    else if(distance > -distacceToBeginFindHero && distance <= 0)
    {
        PosEnemyX += 3;
    }
}
