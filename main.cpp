#include"unit.h"
#include"LoadTexture.h"
#include"character.h"
#include"map.h"
#include"Enemy.h"
#include"LTime.h"
#include"VuNoObject.h"
#include"TextObject.h"


LoadTexture LoadBG;
TTF_Font* font_time = NULL;

Mix_Music *gMusic = NULL;
Mix_Chunk *gHigh = NULL;

bool Init();
bool LoadBackground();
void close();
std::vector<enemy*>EnemyList(SDL_Renderer* aRenderer);
std::vector<enemy*>CloudList(SDL_Renderer* aRenderer);

int main(int argc,char *argv[])
{
    bool quit = false;
    LTime fps_timer;

    if(Init() == false)
    {
        return -1;
    }
    if(LoadBackground() == false )
    {
        return -1;
    }

    TTF_Font* p_font = NULL;
    p_font = TTF_OpenFont("font//ARCADE.ttf",80);
    int ret_menu = SDLunit::ShowMenu(renderer,p_font,"Play Game","Exit","");
    if(ret_menu == 1)
    {
        quit = true;
    }


again_label:

    TextObject timeGame,countMoney,countHeart;
    TextObject countHeartBoss;
    timeGame.setColorFromTextColor(TextObject::WHITE_TEXT);
    countMoney.setColorFromTextColor(TextObject::WHITE_TEXT);
    countHeart.setColorFromTextColor(TextObject::WHITE_TEXT);
    countHeartBoss.setColorFromTextColor(TextObject::WHITE_TEXT);

    // create music
    gMusic = Mix_LoadMUS( "music//FlyAway.wav" );
    if( gMusic == NULL )
	{
		quit = false;
	}
	gHigh = Mix_LoadWAV( "music//high.wav" );
	if( gHigh == NULL )
	{
		quit = true;
	}




    VuNo v_VuNo;
    v_VuNo.LoadImageVuNo("image//vuno.png",renderer);


    character hero;
    hero.LoadImageCharacter("image//player_right.png",renderer);
    hero.setHeart(3);

    MapGame maplol;
    maplol.loadMap(DATA_FILE);
    maplol.loadPixel(renderer);
    MapCode map_data = maplol.getMapCode();

    hero.SetClips();
    hero.setPos(65,100);

    std::vector<enemy*>aCreep = EnemyList(renderer);
    enemy* Boss;
    Boss = new enemy();
    Boss->CreateEnemy("image//boss2.png",5700,0,renderer);
    Danban* BossDanBan = new Danban();
    Boss->InnitDanBan(BossDanBan,renderer,"image//ngoisao.png");
    Boss->setBossHeart(BOSS_HEART);
    //Load image red cloud

    std::vector<enemy*>cloud = CloudList(renderer);


    while(!quit)
    {
        fps_timer.start();
        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                switch( e.key.keysym.sym )
						{
                            case SDLK_9:
							if( Mix_PlayingMusic() == 0 )
							{
								Mix_PlayMusic( gMusic, -1 );// bat nhac nen
							}
							else
							{
								if( Mix_PausedMusic() == 1 )
								{
									Mix_ResumeMusic();
								}
								else
								{
									Mix_PauseMusic();
								}
							}
							break;

							case SDLK_0:
							Mix_HaltMusic();
							break;
						}
            }
            hero.Handle(e,renderer);
            Boss->setDistancedanban(SDLunit::Random(300,1000));
        }
        SDL_SetRenderDrawColor(renderer,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
        SDL_RenderClear(renderer);

        LoadBG.render(renderer,NULL);

                hero.HandlDanBan(renderer,map_data);
                hero.MoveCharacter(map_data);
                hero.SetMapXY(map_data.startX,map_data.startY);
                hero.ShowCharacter(renderer);
                int statusOfCharacter = hero.getStatusCharacter();//danh cho viec load dan ban cua creep khi  nhan vat di chuyen

                SDL_Rect HeroRect;// lay toa do cua hero
                        HeroRect.x = hero.getSDL_rect().x;
                        HeroRect.y = hero.getSDL_rect().y;
                        HeroRect.w = hero.getWidthFrame();
                        HeroRect.h = hero.getHeigthFrame();
                // cloud render
                for(int j = 0 ;j<cloud.size() ; j++)
                {
                    cloud.at(j)->RenderCloud(map_data,renderer);
                    cloud.at(j)->setPosHeroPos(hero.getPosX(),hero.getposY());
                    cloud.at(j)->setDistanceToFindHero(300);
                    cloud.at(cloud.size() -1)->setDistanceToFindHero(2000);
                    cloud.at(j)->MakeDanban(renderer,SCREEN_WIDTH,SCREEN_HEIGHT,map_data);
                    cloud.at(j)->MoveToFindHero();
                    std::vector<Danban*>listDanbanOfCloud = cloud.at(j)->getDanBanList();

                    bool check3;
                    for(int i = 0;i < listDanbanOfCloud.size();i++)
                    {
                        if(listDanbanOfCloud.at(i) != NULL)
                        {
                             listDanbanOfCloud.at(i)->setStatusCharacter2(statusOfCharacter);//dung de load dan cua creep khi nhan vat di chuyen
                             check3 = SDLunit::checkCollision(listDanbanOfCloud.at(i)->getSDL_rect(),HeroRect);
                             if(check3 == true)
                             {
                                 if(hero.getHeart() <= 0){cloud.at(i)->RemoveDanBan(0);}
                                    hero.setHeart(hero.getHeart()-1);
                                    hero.setPos(10,10);
                                    SDL_Delay(1000);
                                    break;
                             }
                        }
                    }
                }




                //boss render
                Boss->RenderEnemy(map_data,renderer);
                Boss->MakeDanban(renderer,SCREEN_WIDTH,SCREEN_HEIGHT,map_data);
                Boss->setDistanceToFindHero(400);
                Boss->MoveToFindHero();


                // check va cham giua hero va Boss.
                std::vector<Danban*> listDanbanOfBoss = Boss->getDanBanList();
                bool check1,check2;
                SDL_Rect BossRect;
                    BossRect.x = Boss->getSDL_rect().x;
                    BossRect.y = Boss->getSDL_rect().y;
                    BossRect.w = Boss->getWidthEnemy();
                    BossRect.h = Boss->getHeightEnemy();
                check2 = SDLunit::checkCollision(BossRect,HeroRect);
                if( check2)
                    {
                        if(hero.getHeart() <= 0){Boss->RemoveDanBan(0);}
                        hero.setHeart(hero.getHeart()-1);
                        hero.setPos(65,100);
                        SDL_Delay(1000);
                    }
                for(int i = 0 ; i< listDanbanOfBoss.size() ;i++)//check va cham hero va dan cua boss
                {
                    if(listDanbanOfBoss.at(i) != NULL)
                        {
                            listDanbanOfBoss.at(i)->setStatusCharacter2(statusOfCharacter);//lay dc trang thai nhan vat khi dan dang duoc ban
                            check1 = SDLunit::checkCollision(listDanbanOfBoss.at(i)->getSDL_rect(),HeroRect);
                            if(check1 == true)
                            {
                                if(hero.getHeart() <= 0){Boss->RemoveDanBan(0);}
                                hero.setHeart(hero.getHeart()-1);
                                hero.setPos(10,10);
                                SDL_Delay(1000);
                                break;
                            }
                        }
                }



                // Khoi tao cac quai vat creep
                for(int i = 0 ;i<aCreep.size() ;i++)
                {
                    enemy* bCreep = aCreep.at(i);
                    if(bCreep != NULL)
                    {

                        bCreep->setMapXY(map_data.startX,map_data.startY);
                        bCreep->MakeDanban(renderer,SCREEN_WIDTH,SCREEN_HEIGHT,map_data);
                        bCreep->LoadInputTypeMoveFromStatus(renderer);
                        bCreep->MoveEnemy(map_data);
                        bCreep->Show(renderer);

                        SDL_Rect HeroRect;// check va cham giua hero va cac creep.
                        HeroRect.x = hero.getSDL_rect().x;
                        HeroRect.y = hero.getSDL_rect().y;
                        HeroRect.w = hero.getWidthFrame();
                        HeroRect.h = hero.getHeigthFrame();
                        std::vector<Danban*> listDanbanOfCreep = bCreep->getDanBanList();
                        bool check1,check2;
                        for(int j = 0;j<listDanbanOfCreep.size();j++)
                        {
                            if(listDanbanOfCreep.at(j) != NULL)
                            {
                                listDanbanOfCreep.at(j)->setStatusCharacter2(statusOfCharacter);//lay dc trang thai nhan vat khi dan dang duoc ban
                                check1 = SDLunit::checkCollision(listDanbanOfCreep.at(j)->getSDL_rect(),HeroRect);
                                if(check1 == true)
                                {

                                    break;
                                }
                            }
                        }
                        SDL_Rect rectCreep;
                        rectCreep.x = bCreep->getSDL_rect().x;
                        rectCreep.y = bCreep->getSDL_rect().y;
                        rectCreep.w = bCreep->getWidthEnemy();
                        rectCreep.h = bCreep->getHeightEnemy();
                        check2 = SDLunit::checkCollision(rectCreep,HeroRect);
                        if( check2||check1)
                        {
                            if(hero.getHeart() <= 0){bCreep->RemoveDanBan(0);}
                            hero.setHeart(hero.getHeart()-1);
                            hero.setPos(65,100);
                            SDL_Delay(1000);
                        }
                    }
                }


                // khoi tao ban do map
                maplol.SetMap(map_data);
                maplol.renderPixel(renderer,NULL);

                // check va cham giua dan nhan vat voi creep
                std::vector<Danban*>DanbanOfHero = hero.get_list_dan_ban();
                for(int i = 0; i<DanbanOfHero.size();i++)
                {
                    Danban* hDanBan = DanbanOfHero.at(i);
                    if(hDanBan != NULL)
                    {
                        for(int z = 0;z<aCreep.size() ; z++)
                        {
                            enemy* creep = aCreep.at(z);
                            if(creep != NULL)
                            {
                                SDL_Rect a;
                                a.x = creep->getSDL_rect().x;
                                a.y = creep->getSDL_rect().y;
                                a.w = creep->getWidthEnemy();
                                a.h = creep->getHeightEnemy();
                                SDL_Rect b = hDanBan->getSDL_rect();
                                bool check1 = SDLunit::checkCollision(a,b);
                                if(check1)
                                {
                                    Mix_PlayChannel( -1, gHigh, 0 );
                                    v_VuNo.ShowImageVuNo(renderer,map_data,creep->getPosEnemyX()-50,creep->getPosEnemyY()- 60);
                                    hero.RemoveDanBan(i);
                                    creep->free();
                                    aCreep.erase(aCreep.begin() + z);
                                }
                            }
                        }
                        // check va cham giua dan cua nhan vat voi boss
                        if(aCreep.size() <= 9)
                        {
                            SDL_Rect a;
                            a.x = Boss->getSDL_rect().x;
                            a.y = Boss->getSDL_rect().y;
                            a.w = Boss->getWidthEnemy();
                            a.h = Boss->getHeightEnemy();
                            SDL_Rect b = hDanBan->getSDL_rect();
                            bool check1 = SDLunit::checkCollision(a,b);
                            if(check1)
                            {
                                Mix_PlayChannel( -1, gHigh, 0 );
                                v_VuNo.ShowImageVuNo(renderer,map_data,Boss->getPosEnemyX()-50,Boss->getPosEnemyY()- 60);
                                hero.RemoveDanBan(i);
                                Boss->setBossHeart(Boss->getBossHeart()- 1);
                                if(Boss->getBossHeart() <= 0)
                                {

                                    Boss->RemoveDanBan(0);
                                    Boss->free();
                                    Boss->setWidthGeight(0,0);

                                }
                            }
                        }

                    }
                }
                // Nhan vat roi xuong vuc
                if(hero.getposY() > SCREEN_HEIGHT)
                {
                    hero.setPos(65 ,100);
                    hero.setHeart(hero.getHeart() -1);
                    SDL_Delay(1000);
                }
                // hien thi chi so mang
                std::string str_heart = "Heart : ";
                str_heart += std::to_string(hero.getHeart());
                countHeart.setText(str_heart);
                countHeart.LoadFromRenderText(font_time,renderer);
                countHeart.RenderText(renderer,SCREEN_WIDTH - 800,15);
                // hien thi chi so tien
                std::string str_money = "Monney : ";
                str_money += std::to_string(hero.getMoney());
                countMoney.setText(str_money);
                countMoney.LoadFromRenderText(font_time,renderer);
                countMoney.RenderText(renderer,SCREEN_WIDTH - 600,15);
                // hien thi chi so thoi gian
                std::string str_time = "Time: ";
                Uint32 time_val = SDL_GetTicks()/1000;
                Uint32 val_time = (500 - time_val);

                if(val_time <= 0)
                {
                }
                else
                {
                    std::string str_val = std::to_string(val_time);
                    str_time += str_val;

                    timeGame.setText(str_time);
                    timeGame.LoadFromRenderText(font_time,renderer);
                    timeGame.RenderText(renderer,SCREEN_WIDTH - 300,15);
                }
        if(Boss->getBossHeart() >= 0)
        {
            std::string str_boss = "Boss Heart: ";
            str_boss += std::to_string(Boss->getBossHeart());
            countHeartBoss.setText(str_boss);
            countHeartBoss.LoadFromRenderText(font_time,renderer);
            countHeartBoss.RenderText(renderer,SCREEN_WIDTH - 150,15);
        }


        if(val_time <= 0 || hero.getHeart() <= 0)
        {
            SDL_Delay(1000);
            int ret_menu2 = SDLunit::ShowMenu(renderer,p_font,"Play again","Quit","You Lost");
            if(ret_menu2 == 1)
            {
                quit = true;
                continue;
            }
            else
            {
                quit = false;
                goto again_label;
            }
        }
        if(hero.getMoney() >= 30 && Boss->getBossHeart() <= 0)
        {
            SDL_Delay(1000);
            int ret_menu3 = SDLunit::ShowMenu(renderer,p_font,"Play again","Quit","You Win");
            if(ret_menu3 == 1)
            {
                quit = true;
                continue;
            }
            else{
                quit = false;
                goto again_label;
            }
        }





        SDL_RenderPresent(renderer);
        // chi so thoi gian cho nhan vat
        int real_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND;

        if(real_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_time;

            if(delay_time >= 0){
                SDL_Delay(delay_time);
            }
        }
    }
    for(int i = 0;i < aCreep.size();i++)
    {
        if(aCreep.at(i)!=NULL)
        {
            aCreep.at(i)->free();
            aCreep.at(i) = NULL;
        }
    }
    for(int i = 0;i < cloud.size();i++)
    {
        if(cloud.at(i)!=NULL)
        {
            cloud.at(i)->free();
            cloud.at(i) = NULL;
        }
    }
    if(Boss != NULL)
    {
        Boss->free();
        Boss = NULL;
    }

    Mix_FreeChunk( gHigh );

    gHigh = NULL;
    Mix_FreeMusic( gMusic );
	gMusic = NULL;
	font_time = NULL;
	p_font =  NULL;
    Mix_Quit();
    close();
    return 0;
}

std::vector<enemy*>EnemyList(SDL_Renderer* aRenderer)
{
    std::vector<enemy*>Eneny_list;

    enemy* creep = new enemy[NUM_OF_ENEMYS];
    for(int i = 0;i<NUM_OF_ENEMYS ; i++)
    {
        enemy* acreep = creep + i;
        if(acreep != NULL)
        {
            acreep->LoadImageEnemy("image//threat_level.png",aRenderer);
            acreep->setClip();
            acreep->setStatusEnemy(enemy::MOVE_NO);
            acreep->setPosEnemyX(700 + i*500);
            acreep->setPosEnemyY(250);
            acreep->setDistancedanban(300);
            Danban* eDanban = new Danban();
            acreep->InnitDanBan(eDanban,aRenderer,"image//hinhtron.png");
            Eneny_list.push_back(acreep);
        }
    }
    return Eneny_list;
}
std::vector<enemy*>CloudList(SDL_Renderer* aRenderer)
{
    std::vector<enemy*>Cloud_List;
    enemy* aCloud = new enemy[NUM_OF_ENEMYS];
    for(int i = 0 ; i<NUM_OF_ENEMYS ; i++)
    {
        enemy* bCloud = aCloud + i;
        if(bCloud != NULL)
        {
            bCloud->CreateEnemy("image//cloud.png",400 + i*560,0,aRenderer);
            bCloud->setStatusEnemy(enemy::Move_FLY);
            Danban* aDanban = new Danban();
            bCloud->InnitDanBan(aDanban,aRenderer,"image//ngoisao.png");
            Cloud_List.push_back(bCloud);
        }
    }
    return Cloud_List;
}

bool Init()
{
    bool check = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    int rett = SDL_Init(SDL_INIT_AUDIO);
    if(ret < 0 || rett < 0)
    {
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

    window = SDL_CreateWindow("There's no one at all",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

    if(window == NULL)
    {
        check = false;
    }else{
        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        if(renderer == NULL)
        {
            check = false;
        }else{
            SDL_SetRenderDrawColor(renderer,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                check = false;
        }
        if(TTF_Init() == -1)
        {
            check = false;
        }
        font_time = TTF_OpenFont("font//ARCADE.ttf",15);
        if(font_time == NULL)
        {
            check = false;
        }
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            std::cout<< "SDL_mixer could not initialize! SDL_mixer Error:"<<std::endl;
            Mix_GetError();
            check = false;
        }
    }
    return check;

}

bool LoadBackground()
{
    bool load = LoadBG.LoadImage("image//bg1.jpg",renderer);
    if(load == false)
        return false;
    return true;
}

void close()
{
    LoadBG.free();
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    IMG_Quit();
    SDL_Quit();
}
