#include"map.h"
#include <fstream>

void MapGame::loadMap(const char* filename)
{
    std::ifstream file(filename);
    if(file.is_open()){
        for(int i = 0; i < MAP_HEIGHT ; i++)
        {
            for(int j = 0; j < MAP_WIDTH ; j++)
            {
                int val;
                file >> val;
                mappy.Array[i][j] = val;
            }
        }
        file.close();
    }else{
        std::cout<<"Unable load file!"<<std::endl;
    }

}

void MapGame::loadPixel(SDL_Renderer* mRenderer)
{
    for(int i = 0; i < NUM_IMAGE_PIXELS;i++)
    {
        image[i].LoadImage(path_pixel[i].c_str(),mRenderer);
        /*if(image[i].LoadImage(path_pixel[i].c_str(),mRenderer) == true)
        {
            std::cout<<path_pixel[i]<<std::endl;
        }*/
    }
}

void MapGame::renderPixel(SDL_Renderer* gRenderer,const SDL_Rect* clip )
{
    int x1,x2, mapX;
    int y1,y2, mapY;

    x1 = mappy.startX % PIXEL_SIXE * -1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : PIXEL_SIXE);

    y1 = mappy.startY % PIXEL_SIXE * -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : PIXEL_SIXE);

    mapX = mappy.startX / PIXEL_SIXE ;
    mapY = mappy.startY / PIXEL_SIXE ;

    for(int i = y1; i <= y2 ; i+= PIXEL_SIXE)
    {
        mapX = mappy.startX / PIXEL_SIXE ;
        for(int j = x1 ; j <= x2 ; j+= PIXEL_SIXE)
        {
            int val = mappy.Array[mapY][mapX];
            if(val > 0){
                image[val].setRectPos(j,i);
                image[val].render(gRenderer,clip);
            }
            mapX++;
        }
         mapY++;
    }
    //std::cout<<x2<<std::endl;
}

MapGame::MapGame()
{
    mappy.startX = 0;
    mappy.startY = 0;
    mappy.distance = 0;
}

void MapGame::SetArrayPos()
{
    for(int i = 0; i<MAP_HEIGHT ; i++)
    {
        for(int j = 0;j< MAP_WIDTH;j++)
        {
            if(mappy.Array[i][j] != PIXEL_EMPTY)
            {
                mappy.ArrayPos[i][j].x = j * PIXEL_SIXE;
                mappy.ArrayPos[i][j].y = i * PIXEL_SIXE;
            }
        }
    }
}
