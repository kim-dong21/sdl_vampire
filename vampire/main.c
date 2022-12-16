#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "res.h"

//Screen dimension constants
SDL_Window* window;

	//The surface contained by the window
SDL_Surface* screenSurface;
SDL_Surface* image;
SDL_Surface* tempSur;
SDL_Texture* texture;
SDL_Texture* sprite;
SDL_Renderer* renderer;
SDL_Event event;
int run = 1;
int main(int argc, char* args[])
{
	//The window we'll be rendering to
	
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{	
		SDL_Rect* rect = malloc(sizeof(SDL_Rect) * 4);
		if (rect == NULL) printf("malloc error");
		//Create window
		window = SDL_CreateWindow("SDL INIT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0);
		image = IMG_Load("./0x72_DungeonTilesetII_v1.4/0x72_DungeonTilesetII_v1.4.png");
		texture = SDL_CreateTextureFromSurface(renderer, image);
		

		
		for (int i = 0,x=192,y=196,w=16,h=28; i < 4; i++,x+=16)
		{
			rect[i].x = x;
			rect[i].y = y;
			rect[i].w = w;
			rect[i].h = h;
		}

		InitTileset();

		SDL_Rect dst = {0,0,32,48};
		int i = 0;
		float fps = 0;
		int startTick = 0;

		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			while (run) {
				while(SDL_PollEvent(&event)) {
					switch (event.type) {
					case SDL_QUIT:
						run = 0;
						break;
					
					case SDL_KEYDOWN:
						switch (event.key.keysym.sym) {
						case SDLK_DOWN:
							dst.y += 30;
						}
						
					

					}

				}

				startTick = SDL_GetTicks();

				SDL_Delay(120);
				fps = 1000.0f / (float)(SDL_GetTicks() - startTick);
				printf("%f\n",fps);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
				SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, texture, &rect[i], &dst);
				SDL_RenderPresent(renderer);
				i++;
				if (i > 3)i = 0;
			}
		}
	}
	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}