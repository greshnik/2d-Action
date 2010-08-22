#ifdef MYSDL_H

#else
#define MYSDL_H
#include <SDL/SDL.h>
#endif

class MySdlInit{
public:
	SDL_Surface* screen;
	Uint8* keys;
	SDL_Surface* cursor;
	SDL_Cursor* cursor2;
	SDL_Rect CurRect;
	int HWCur;
	MySdlInit (int width, int height, int bpp,int fs, const char* caption, const char* icon);
	void CreateSWCur(const char* fimage);
	void CreateHWCur(const char* image[]);
	void DrawScene();
};
