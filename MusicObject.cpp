#include"MusicObject.h"

LButton::LButton()
{
    WidthMenu = 0;
    HeightMenu = 0;
    PosMenuX = 0;
    PosMenuY = 0;
    CountFrame = 0;
}

bool LButton::LoadMenu(std::string path,SDL_Renderer *lRenderer)
{
    bool check = LoadImage(path,lRenderer);
    if(check = true)
    {
        WidthMenu = mRect.w;
        HeightMenu = mRect.h / 2;
    }
    return check;
}
void LButton::setClipMenu()
{
    if(WidthMenu > 0 && HeightMenu > 0)
    {
        MenuClip[0].x = 0;
        MenuClip[0].y = 0;
        MenuClip[0].w = WidthMenu;
        MenuClip[0].h = HeightMenu;

        MenuClip[1].x = 0;
        MenuClip[1].y = HeightMenu;
        MenuClip[1].w = WidthMenu;
        MenuClip[1].h = HeightMenu;
    }
}
void LButton::showMenu(const int& x,const int& y,SDL_Renderer* lRenderer)
{
    setClipMenu();
    PosMenuX = x;
    PosMenuY = y;
    mRect.x = PosMenuX;
    mRect.y = PosMenuY;
    SDL_Rect* CurrentClip = &MenuClip[CountFrame];
    SDL_Rect renderquad = {mRect.x,mRect.y,WidthMenu,HeightMenu};
    SDL_RenderCopy(lRenderer,mTexture,CurrentClip,&renderquad);
}
void LButton::handleEvent( SDL_Event* e )
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < PosMenuX )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > PosMenuX + WidthMenu )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < PosMenuY )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > PosMenuY + HeightMenu )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside && CountFrame != BUTTON_SPRITE_MOUSE_OVER_MOTION && CountFrame!= BUTTON_SPRITE_MOUSE_DOWN )
		{
			CountFrame = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
				CountFrame = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;

				case SDL_MOUSEBUTTONDOWN:
				CountFrame = BUTTON_SPRITE_MOUSE_DOWN;
				break;

			}
		}
	}
}
