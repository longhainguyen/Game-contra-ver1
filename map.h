#ifndef MAP_H_
#define MAP_H_

#include"unit.h"
#include"LoadTexture.h"

#define NUM_IMAGE_PIXELS 10

const std::string path_pixel[NUM_IMAGE_PIXELS] = {"map//0.png","map//1.png","map//2.png",
"map//3.png","map//4.png","map//5.png","map//6.png","map//7.png","map//8.png","map//9.png"};

class PixelMap:public LoadTexture
{
public:
    PixelMap(){};
    ~PixelMap(){};
};

class MapGame
{
public:
    MapGame();
    ~MapGame(){};

    void loadPixel(SDL_Renderer* mRenderer);
    void renderPixel(SDL_Renderer* gRenderer,const SDL_Rect* clip = NULL);
    void loadMap(const char* filename);
    MapCode getMapCode(){
        return mappy;
    }

    void SetMap(MapCode& map_data){
        mappy = map_data;
    };
    void SetArrayPos();
private:
    PixelMap image[NUM_IMAGE_PIXELS];
    MapCode mappy;
};

#endif // MAP_H_

