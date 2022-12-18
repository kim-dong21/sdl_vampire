#include <stdio.h>
#include <SDL_image.h>
#include "res.h"


extern SDL_Renderer* renderer;
Texture textures[TEXTURE_SIZE];
int texturesCount = 0;

SDL_Texture* loadSDLTexture(const char* path) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL) {
		printf("Failed to load image %s\nSDL_image Error: %s\n",path,SDL_GetError());
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Failed to create textrue from %s\nSDL Error: %s\n", path, SDL_GetError());
		}
		else {
			SDL_FreeSurface(loadedSurface);
		}
	}

	return newTexture;

}


void initTexture(Texture* self,SDL_Texture* origin,int w,int h,int f) {
	self->origin = origin;
	self->w = w;
	self->h = h;
	self->f = f;//frames
	self->crops = malloc(sizeof(SDL_Rect) * f);
	if (self->crops == NULL) printf("Failed allocation..\n");
}

//load and crop tileset
int loadTileset(const char* path,SDL_Texture* origin) {
	printf("File Loading...\n");

	FILE* file=NULL;
	fopen_s(&file,path, "r");
	if (file == NULL) {
		printf("File open failed...\n");
		return -1;
	}

	int x, y, w, h, f;
	char resName[256];

	//open file info and init textures
	while (fscanf_s(file, "%s %d %d %d %d %d", resName, sizeof(resName), &x, &y, &w, &h, &f)==6) {
		printf("%s %d %d %d %d %d\n", resName, x, y, w, h, f);
		Texture* p = &textures[texturesCount++];
		initTexture(p, origin, w, h, f);
		for (int i = 0; i < f; i++) {
			p->crops[i].x = x + i * w;
			p->crops[i].y = y;
			p->crops[i].w = w;
			p->crops[i].h = h;
		}
	}

}