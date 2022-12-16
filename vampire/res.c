#include <stdio.h>
#include "res.h"




//load and crop tileset
int InitTileset() {
	printf("File Loading...\n");
	FILE* file=NULL;
	fopen_s(&file,TILESET_PATH, "r");
	if (file == NULL) {
		printf("File open failed...\n");
		return -1;
	}

	int x, y, w, h, f;
	char resName[256];
	while (fscanf_s(file, "%s %d %d %d %d %d", resName, sizeof(resName), &x, &y, &w, &h, &f)==6) {
		printf("%s %d %d %d %d %d", resName, x, y, w, h, f);
	}

}