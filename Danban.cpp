#include "Danban.h"


Danban::Danban()
{
    ValX = 0;
    ValY = 0;
    inputChieuBan = right;
    PosDanBanX = 0;
    PosDanBanY = 0;
    isMove = false;
    getStatusCharacter = 0;
    getStatusCharacter2 = 0;
}
Danban::~Danban()
{
    free();
}

void Danban::HandleMove(const int & x_border, const int & y_border,MapCode &mapDaTa)// dan se bi mat khi va cham voi ban do
{

    int distance_X_ = mapDaTa.distance;

    PosDanBanX = mRect.x + mapDaTa.startX;
    PosDanBanY = mRect.y + mapDaTa.startY;
    if (isMove == true)
    {
        int vitriDanSeDen_X;
        int vitriDanSeDen_Y = mRect.y;

        if(inputChieuBan == left){
            vitriDanSeDen_X = PosDanBanX - ValX;
        }else if(inputChieuBan == right ){
            vitriDanSeDen_X = PosDanBanX + ValX;
        }


        int x = PosDanBanX / PIXEL_SIXE;
        int y = PosDanBanY / PIXEL_SIXE;

        if(mapDaTa.Array[y][x] == 0){
            if(inputChieuBan == left){
                mRect.x = mRect.x - ValX + distance_X_;
                if(getStatusCharacter == 0){// 0 : character moving right
                    mRect.x = mRect.x - ValX - 1.3*distance_X_;
                }
            }
            else if(inputChieuBan == right )
            {
                mRect.x = mRect.x + ValX - distance_X_;
                if(getStatusCharacter == 1){// 1 : character moving left
                    mRect.x = mRect.x+ ValX + 1.3*distance_X_;
                }
            }
            else if(inputChieuBan == up)
            {
                mRect.y -= ValX;
            }
            else if(inputChieuBan == down)
            {
                mRect.y -= ValX;
            }
        }else isMove = false;

    }



}
void Danban::DanbanMove(MapCode& map_data)
{
    if(inputChieuBan == left)
    {
        mRect.x -= ValX;
    }else if(inputChieuBan == right)
    {
        mRect.x += ValX;
    }
    mRect.x = PosDanBanX - map_data.startX;
    mRect.y = PosDanBanY - map_data.startY;
}
void Danban::CreateDanBan(std::string path,SDL_Renderer* dRenderer)
{
    bool check = LoadImage(path.c_str(),dRenderer);
}
void Danban::RenderDanBan(MapCode& map_data,SDL_Renderer* dRenderer,
                          const int& dValX,const int& ChieuBan)
{
    ValX = dValX;
    setChieuBan(ChieuBan);
    DanbanMove(map_data);
    setRectPos(mRect.x,mRect.y);
    render(dRenderer);
}

void Danban::HandleEnemy(const int & x_border, const int & y_border,MapCode &mapDaTa)
{
    if(inputChieuBan == right)
    {
        mRect.x += ValX;
        if(mRect.x > x_border)
        {
            isMove = false;
        }
    }
    else if(inputChieuBan == left)
    {
        if(getStatusCharacter2 == 0) //moving right
        {
           mRect.x = mRect.x - ValX - mapDaTa.distance;
        }else if(getStatusCharacter2 == 1)
        {
            mRect.x = mRect.x - ValX + mapDaTa.distance;
        }
        if(mRect.x  < 0)
        {
            isMove = false;
        }
    }
}
void Danban::HandleEnemyisFlying(const int & x_border, const int & y_border,MapCode &mapDaTa)
{
    mRect.y += ValY;
    if(getStatusCharacter2 == 0) //moving right
    {
           mRect.x = mRect.x - mapDaTa.distance;
    }else if(getStatusCharacter2 == 1)
    {
            mRect.x = mRect.x + mapDaTa.distance;
    }
    if(mRect.y > y_border || mRect.y < 0)
    {
        isMove = false;
    }
}
