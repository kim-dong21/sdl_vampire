#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string.h>

bool init(const char* title, int xpos, int ypos, int height, int width, int flas);
void render();
void close();

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* image = NULL;
SDL_Texture* texture = NULL;
SDL_Surface* screen = NULL;

using namespace std;

int main(int argv, char** args)
{
    bool game = false;
    bool running = false;

    game = init("SDL GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (game)
    {
        running = true;
    }
    else
    {
        return 1;
    }

    SDL_Event event;



    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    std::cout << "Window Closing...\n";
                    running = false;
                }
            }
        }
        render();
    }
    SDL_Delay(500);
    close();

    return 0;
}
bool init(const char* title, int xpos, int ypos, int height, int width, int flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        window = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        image = IMG_Load("/0x72_DungeonTilesetII_v1.4/frames/big_demon_idle_anim_f0.png");
        texture = SDL_CreateTextureFromSurface(renderer, image);
        
        if (image == NULL) cout << "IMG_Load() failed..." << SDL_GetError() << endl;
    }
    else
    {
        cout << "SDL_Init failed..." << SDL_GetError() << endl;
        return false; // SDL 초기화 실패
    }
    return true;
}

void render()
{
    cout << "rednering..." << endl;
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); //Black Color
    //SDL_RenderClear(renderer);
    SDL_Rect rect;
    rect.x = 30;
    rect.y = 30;
    rect.w = 30;
    rect.y = 30;
    
}

void close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}