#include"character.h"

character::character()
{
    frame = 0;
    PosX = 0;
    PosY = 0;
    VelX = 0;
    VelY = 0;
    WidthFrame = 0;
    HeightFrame = 0;
    status = WALK_RIGHT;
    inputType.down = 0;
    inputType.jump = 0;
    inputType.left = 0;
    inputType.right = 0;
    inputType.up = 0;
    map_x_ = 0;
    map_y_ = 0;
    on_gound = false;
    come_back_time = 0;
    PosXatDanBan = 0;
    money = 0;
    ten_lua = 0;
    heart = 0;
}
character::~character()
{
    free();
}
bool character::LoadImageCharacter(std::string path,SDL_Renderer* mRenderer)
{
    bool check = LoadTexture::LoadImage(path.c_str(),mRenderer);

    if(check == true)
    {
        WidthFrame = mRect.w/8;
        HeightFrame = mRect.h;
    }
    return check;
}
void character::SetClips()
{
    if(WidthFrame > 0 && HeightFrame > 0)
    {
        FrameClip[0].x = 0;
        FrameClip[0].y = 0;
        FrameClip[0].w = WidthFrame;
        FrameClip[0].h = HeightFrame;

        FrameClip[1].x = WidthFrame;
        FrameClip[1].y = 0;
        FrameClip[1].w = WidthFrame;
        FrameClip[1].h = HeightFrame;

        FrameClip[2].x = WidthFrame*2;
        FrameClip[2].y = 0;
        FrameClip[2].w = WidthFrame;
        FrameClip[2].h = HeightFrame;

        FrameClip[3].x = WidthFrame*3;
        FrameClip[3].y = 0;
        FrameClip[3].w = WidthFrame;
        FrameClip[3].h = HeightFrame;

        FrameClip[4].x = WidthFrame*4;
        FrameClip[4].y = 0;
        FrameClip[4].w = WidthFrame;
        FrameClip[4].h = HeightFrame;

        FrameClip[5].x = WidthFrame*5;
        FrameClip[5].y = 0;
        FrameClip[5].w = WidthFrame;
        FrameClip[5].h = HeightFrame;

        FrameClip[6].x = WidthFrame*6;
        FrameClip[6].y = 0;
        FrameClip[6].w = WidthFrame;
        FrameClip[6].h = HeightFrame;

        FrameClip[7].x = WidthFrame*7;
        FrameClip[7].y = 0;
        FrameClip[7].w = WidthFrame;
        FrameClip[7].h = HeightFrame;

    }
}

void character::ShowCharacter(SDL_Renderer* mRenderer)
{
    if(on_gound == true)
    {
        if(status == WALK_LEFT)
        {
            LoadImageCharacter("image//player_left.png",mRenderer);
        }
        else if(status == WALK_RIGHT)
        {
            LoadImageCharacter("image//player_right.png",mRenderer);
        }
    }



    if(inputType.left == 1 || inputType.right == 1 )
    {
        frame ++;
    }
    else
    {
        frame = 0;
    }
    if(frame >= 7)
    {
        frame = 1;
    }

    mRect.x = PosX - map_x_;
    mRect.y = PosY - map_y_;

    SDL_Rect* current_clip = &FrameClip[frame];

    SDL_Rect renderquad = {mRect.x,mRect.y,WidthFrame,HeightFrame};
    SDL_RenderCopy(mRenderer,mTexture,current_clip,&renderquad);
}
void character::Handle(SDL_Event events,SDL_Renderer* pRenderer)
{
    if(events.type == SDL_KEYDOWN && events.key.repeat == 0)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                status = WALK_RIGHT;
                inputType.right = 1;
                inputType.left = 0;
                if(on_gound == true)
                {
                    LoadImageCharacter("image//player_right.png",pRenderer);
                }
                else
                {
                    LoadImageCharacter("image//jum_right.png",pRenderer);
                }
            }
            break;
        case SDLK_LEFT:
            {
                status = WALK_LEFT;
                inputType.left = 1;
                inputType.right = 0;
                if(on_gound == true)
                {
                    LoadImageCharacter("image//player_left.png",pRenderer);
                }
                else
                {
                    LoadImageCharacter("image//jum_left.png",pRenderer);
                }
            }
            break;
        }

    }
    else if (events.type == SDL_KEYUP && events.key.repeat == 0)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                status = WALK_RIGHT;
                inputType.right = 0;
                inputType.left = 0;
            }
            break;
        case SDLK_LEFT:
            {
                status = WALK_LEFT;
                inputType.left = 0;
                inputType.right = 0;
            }
            break;

        default:break;
        }
    }
    if(events.type == SDL_KEYDOWN)
    {
        if(events.key.keysym.sym == SDLK_UP)
        {
            inputType.jump = 1;
        }
    }
    if(events.type == SDL_MOUSEBUTTONDOWN){
            if(events.button.button == SDL_BUTTON_LEFT)
            {

                Danban* p_danban =  new Danban();
                p_danban->LoadImage("image//danban.png",pRenderer);
                p_danban->setRectPos(mRect.x + WidthFrame/2,mRect.y + 20);
                p_danban->SetValX(10);
                setPosXatDanBan(getPosX());

                if(status == WALK_RIGHT){
                    p_danban->setChieuBan(Danban::right);
                }
                if(status == WALK_LEFT){
                    p_danban->setChieuBan(Danban::left);
                }
                p_danban->setIsMove(true);

                p_list_dan_ban.push_back(p_danban);
            }
    }

}

void character::MoveCharacter(MapCode &mapDaTa)
{
        VelX = 0;
        VelY += 0.8;
        if(VelY >= TRONG_LUC)
        {
            VelY = TRONG_LUC;
        }
        if(inputType.right == 1)
        {
            VelX += PLAYER_SPEED;
        }
        else if(inputType.left == 1)
        {
            VelX -= PLAYER_SPEED;
        }
        if(inputType.jump == 1)
        {
            if(on_gound == true)
            {
                VelY = - PLAYER_JUMP;
            }
            on_gound = false;
            inputType.jump = 0;
        }
        ControlMap(mapDaTa);
        check_va_cham_voi_map(mapDaTa);

}

void character::HandlDanBan(SDL_Renderer* des,MapCode &mapDaTa)
{
    for(int i = 0 ;i< p_list_dan_ban.size();i++)
    {
        Danban* p_DanBan = p_list_dan_ban.at(i);
        if(p_DanBan != NULL)
        {
            if(p_DanBan->getIsMove() == true)
            {
                //float dan_distance = PosXatDanBan - p_DanBan->getPosDanBanX();
                //if(dan_distance < 0){
                //    dan_distance = - dan_distance;
                //}
                //if(dan_distance < 500){
                    p_DanBan->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT,mapDaTa);
                    p_DanBan->render(des);

                    p_DanBan->setGetStatusCharacter(status);
                //}else
                //{
                //    dan_distance = 0;
                //    p_DanBan->setIsMove(false);
                //}
                int PosXCurrent = p_DanBan->getPosDanBanX();
                int PosYCurrent = p_DanBan->getPosDanBanY();
            }
            if(p_DanBan->getIsMove() == false)
            {
                p_list_dan_ban.erase(p_list_dan_ban.begin()+ i);
                if(p_DanBan != NULL){

                    delete p_DanBan;
                    p_DanBan = NULL;
                }
            }
        }
    }
}


void character::roi_tu_do()
{
    PosY += 5;
}

void character::check_va_cham_voi_map(MapCode &map_data)
{
    Mix_Chunk *gTing = NULL;
    gTing = Mix_LoadWAV( "music//ting.wav" );
    int x = PosX - SCREEN_WIDTH/2;
    if(x < 0)
    {
        x = 0;
    }
    if(x + SCREEN_WIDTH + 73 >= PIXEL_SIXE*MAP_WIDTH)
    {
        x = PIXEL_SIXE*MAP_WIDTH - SCREEN_WIDTH  - 73 ;
    }

    // can tim vi tri cua nhan vat dang o o nao
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int height_min = HeightFrame < PIXEL_SIXE ? HeightFrame:PIXEL_SIXE;

    x1 = (PosX + VelX)/PIXEL_SIXE;
    x2 = (PosX + VelX + WidthFrame - 10)/PIXEL_SIXE;

    y1 = (PosY)/PIXEL_SIXE;
    y2 = (PosY + height_min - 10)/PIXEL_SIXE;

    if(x1 >= 0 && x2 < MAP_WIDTH && y1>=0 && y2<MAP_HEIGHT)
    {
        if(VelX >= 0)
        {
            int val1 = map_data.Array[y1][x2];
            int val2 = map_data.Array[y2][x2];
            if(val1 == PIXEL_MONEY || val2 == PIXEL_MONEY)
            {
                map_data.Array[y1][x2] = 0;
                map_data.Array[y2][x2] = 0;
                money ++;
                Mix_PlayChannel( -1, gTing, 0 );
            }
            if(val1 == PIXEL_HEART || val2 == PIXEL_HEART)
            {
                map_data.Array[y1][x2] = 0;
                map_data.Array[y2][x2] = 0;
                Mix_PlayChannel( -1, gTing, 0 );
                heart++;
            }
            if(map_data.Array[y1][x2] != PIXEL_EMPTY  || map_data.Array[y2][x2] !=PIXEL_EMPTY  )
            {
                PosX = x2*PIXEL_SIXE;
                PosX -= WidthFrame + 10;
            }
        }
        else if(VelX < 0)
        {
            int val1 = map_data.Array[y1][x1];
            int val2 = map_data.Array[y2][x1];
            if(val1 == PIXEL_MONEY || val2 == PIXEL_MONEY)
            {
                map_data.Array[y1][x1] = 0;
                map_data.Array[y2][x1] = 0;
                money++;
                Mix_PlayChannel( -1, gTing, 0 );
            }
            if(val1 == PIXEL_HEART || val2 == PIXEL_HEART)
            {
                map_data.Array[y1][x1] = 0;
                map_data.Array[y2][x1] = 0;
                heart++;
                Mix_PlayChannel( -1, gTing, 0 );
            }
            if(val1 != PIXEL_EMPTY || val2!= PIXEL_EMPTY )
            {
                PosX = (x1 + 1)*PIXEL_SIXE;
                VelX = 0;
            }
        }
    }
    int width_min = WidthFrame < PIXEL_SIXE ? WidthFrame:PIXEL_SIXE;
    x1 = (PosX)/PIXEL_SIXE;
    x2 =(PosX + WidthFrame - 10)/PIXEL_SIXE;

    y1 = (PosY + VelY)/PIXEL_SIXE;
    y2 = (PosY + VelY + HeightFrame - 1 )/PIXEL_SIXE;

    if(x1 >= 0 && x2 < MAP_WIDTH && y1>=0 && y2<MAP_HEIGHT)
    {
        if(VelY > 0)
        {
            int val1 = map_data.Array[y2][x1];
            int val2 = map_data.Array[y2][x2];
            if(val1 == PIXEL_MONEY|| val2 == PIXEL_MONEY)
            {
                map_data.Array[y2][x1] = 0;
                map_data.Array[y2][x2] = 0;
                money++;
                Mix_PlayChannel( -1, gTing, 0 );
            }
            if(val1 == PIXEL_HEART|| val2 == PIXEL_HEART)
            {
                map_data.Array[y2][x1] = 0;
                map_data.Array[y2][x2] = 0;
                heart++;
                Mix_PlayChannel( -1, gTing, 0 );
            }
            if(map_data.Array[y2][x1] != PIXEL_EMPTY || map_data.Array[y2][x2] != PIXEL_EMPTY )
            {
                PosY = y2*PIXEL_SIXE;
                PosY -= HeightFrame + 1;
                VelY = 0;
                on_gound = true;
            }
        }
        else if(VelY < 0)
        {
            int val1 = map_data.Array[y1][x1];
            int val2 = map_data.Array[y1][x2];
            if(val1 == 5|| val2 == 5)
            {
                map_data.Array[y1][x1] = 0;
                map_data.Array[y1][x2] = 0;
                money++;
                Mix_PlayChannel( -1, gTing, 0 );
            }
            if(val1 == PIXEL_HEART|| val2 == PIXEL_HEART)
            {
                map_data.Array[y1][x1] = 0;
                map_data.Array[y1][x2] = 0;
                heart++;
                Mix_PlayChannel( -1, gTing, 0 );
            }
            if(map_data.Array[y1][x1] != PIXEL_EMPTY  || map_data.Array[y1][x2] != PIXEL_EMPTY )
            {
                PosY = (y1+1)*PIXEL_SIXE;
                VelY = 0;
            }
        }
    }
    gTing = NULL;
    Mix_FreeChunk( gTing );
    PosX += VelX;
    PosY += VelY;
    if(PosX <= 0 )
    {
        PosX = 1;
    }else if(PosX > MAP_WIDTH*PIXEL_SIXE)
    {
        PosX = MAP_WIDTH*PIXEL_SIXE -1;
    }
    if(PosY <= 0)
    {
        VelY = 0;
    }

    //
    int y = PosX - SCREEN_WIDTH/2;
    if(y < 0)
    {
        y = 0;
    }
    if(y + SCREEN_WIDTH + 73 >= PIXEL_SIXE*MAP_WIDTH)
    {
        y = PIXEL_SIXE*MAP_WIDTH - SCREEN_WIDTH  - 73 ;
    }
    int distance_;
    if(y > x){
        distance_ = y - x;
    }else distance_ = x - y;
    map_data.distance = distance_;// lay khoang cach cua ban do sau moi lan nhan vat di chuyen

}

void character::ControlMap(MapCode &mapdota)
{
    mapdota.startX = PosX - SCREEN_WIDTH/2;
    if(mapdota.startX < 0)
    {
        mapdota.startX = 0;
    }
    if(mapdota.startX + SCREEN_WIDTH  + 73 >= PIXEL_SIXE*MAP_WIDTH)
    {
        mapdota.startX = PIXEL_SIXE*MAP_WIDTH - SCREEN_WIDTH  - 73 ;
    }
    /*
    mapdota.startY = PosY - SCREEN_HEIGHT/2;

    if(mapdota.startY < 0)
    {
        mapdota.startY = 0;
    }else if (mapdota.startY + SCREEN_HEIGHT >= PIXEL_SIXE*SCREEN_HEIGHT)
    {
        mapdota.startY = PIXEL_SIXE*SCREEN_HEIGHT - SCREEN_HEIGHT;
    }*/
}
void character::RemoveDanBan(const int& idx)
{
    int Size = p_list_dan_ban.size();
    if(Size > 0 && idx <Size)
    {
        Danban* p_danban = p_list_dan_ban.at(idx);
        p_list_dan_ban.erase(p_list_dan_ban.begin() + idx);
        if(p_danban != NULL)
        {
            delete p_danban;
            p_danban = NULL;
        }
    }
}
