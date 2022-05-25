#ifndef MUSIC_OBJECT_H_
#define MUSIC_OBJECT_H_

#include "unit.h"
#include"LoadTexture.h"

class LButton:public LoadTexture
{
    public:
	    LButton();
	    ~LButton(){};

	    enum LButtonSprite
        {
            BUTTON_SPRITE_MOUSE_OUT = 0,
            BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
            BUTTON_SPRITE_MOUSE_DOWN = 2,
            BUTTON_SPRITE_MOUSE_UP = 3,
            BUTTON_SPRITE_TOTAL = 4
        };

        bool LoadMenu(std::string path,SDL_Renderer* lRenderer);
        void setClipMenu();
		void setPosMenuX(const int& x){PosMenuX = x;}
		void setPosMenuY(const int& y){PosMenuY = y;}
		void showMenu(const int& x,const int& y,SDL_Renderer* lRenderer);
		void handleEvent( SDL_Event* e );
		void setPosition( int x, int y );
		int getCountFrame()const{return CountFrame;}
		void setCountFrame(const int & x){CountFrame = x;}

    private:
        int CountFrame;
	    SDL_Rect MenuClip[2];
	    int WidthMenu;
	    int HeightMenu;
	    int PosMenuX;
	    int PosMenuY;
};


#endif // MUSIC_OBJECT_H_
