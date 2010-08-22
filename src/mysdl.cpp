#include <stdio.h>
#include <SDL/SDL.h>
#include <mysdl.h>

MySdlInit::MySdlInit(int width, int height, int bpp,int fs, const char* caption, const char* icon){
	if(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0){
		printf("Unable to init SDL: %s\n",SDL_GetError());
		exit(1);
	}
	SDL_WM_SetCaption(caption, NULL);
	SDL_WM_SetIcon(SDL_LoadBMP(icon), NULL);
	screen=SDL_SetVideoMode(width,height,bpp,SDL_HWSURFACE|SDL_DOUBLEBUF);
	if (screen == NULL){
		printf("Unable to set video: %s\n",SDL_GetError());
		exit(1);
	}
}

void MySdlInit::CreateSWCur(const char* fimage)
{
  SDL_Surface* temp;
  HWCur = 0;
  temp = SDL_LoadBMP(fimage);
  cursor = SDL_DisplayFormat(temp);
  SDL_SetColorKey(cursor,SDL_SRCCOLORKEY,SDL_MapRGB(cursor->format,255,255,255));
  SDL_ShowCursor(0);
}

void MySdlInit::CreateHWCur(const char* image[])
{
  int i, row, col;
  Uint8 data[4*32];
  Uint8 mask[4*32];
  int hot_x, hot_y;
  i = -1;
  for( row=0; row<32; ++row ) 
    {
      for ( col=0; col<32; ++col ) 
	{
	  if ( col % 8 ) 
	    {
	      data[i] <<= 1;
	      mask[i] <<= 1;
	    } else 
	    {
	      ++i;
	      data[i] = mask[i] = 0;
	    }
	  switch (image[4+row][col]) 
	    {
	    case '.' :
	      data[i] |= 0x01;
	      break;
	    case 'a' :
	      mask[i] |= 0x01;
	      break;
	    case ' ' :
	      break;
	    }
	}
    }
  sscanf(image[4+row], "%d,%d", &hot_x, &hot_y);
  SDL_Cursor* cur = SDL_CreateCursor(data, mask, 32, 32, hot_x, hot_y);
  SDL_SetCursor(cur);
}

void MySdlInit::DrawScene()
{
  if (HWCur){
    //SDL_GetMouseState((int*)&CurRect.x,(int*)&CurRect.y);
    //SDL_BlitSurface(cursor,NULL,screen,&CurRect);
  }
  SDL_Flip(screen);
}
