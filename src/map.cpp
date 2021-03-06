#include <map.h>
#include <stdio.h>

map::map(SDL_Surface* screen)
{
  gscreen = screen;
  mapx = 1;
  mapy = 1;
  greedx = 100;
  greedy = 100;
  sscanf(mmap[0],"%i %i\n",&MapH,&MapW);
  ShowW = (int)(gscreen->w/greedx)+2;
  ShowH = (int)(gscreen->h/greedy)+2; 
}

void map::loadmap()
{
  SDL_Surface* temp = SDL_LoadBMP("data/1map.bmp");
  map1 = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("data/0map.bmp");
  bgmap = SDL_DisplayFormat(temp);
}

void map::RenderingMap(int rsh,int rsw, int reh,int rew,int posx,int posy)
{
  int temp = rsw, tempx = 0, tempy = 0;
  SDL_Rect a;
  a.w = greedx; a.h = greedy;
  tempx = posx-greedx; tempy = posy-greedy;
  for (;rsh<reh;++rsh)
    {
      for(;rsw<rew;++rsw)
	{
	  a.x = tempx;
	  a.y = tempy;
	  if(mmap[rsh][rsw] == '1')
	    {
	      SDL_BlitSurface(map1,NULL,gscreen,&a);
	    }
	  else
	    {
	      SDL_BlitSurface(bgmap, NULL, gscreen, &a);
	    }
	  tempx += greedx;
	}
      tempy += greedy;
      tempx = posx-greedx;
      rsw = temp;
    }
}

bool map::endmap(int mx, int my)
{
  int temp=0;
  temp = mx - (int)(ShowW/2);
  if(temp <= 0) return true;
  temp = mx + (int)(ShowW/2);
  if(temp >= MapW) return true;
  temp = my + (int)(ShowH/2);
  if(temp >= MapH) return true;
  temp = my - (int)(ShowH/2);
  if(temp <= 0) return true;
  return false;
}

void map::onmove(int mx,int my, int posx, int posy)
{
  int temp=0,temp2=0,i=0,j=0,ww=ShowW,hh=ShowH;
  temp = mx-(int)(ShowW/2);
  j = temp+1;
  ww += temp;
  // check j ww value
  temp2 = my-(int)(ShowH/2);
  i = temp2+1;
  hh += temp2;
  // check i hh value
  if (i < 1) 
    {
      i = 1; 
      hh = ShowH;
    }
  //rendering map
  RenderingMap(i,j,hh+1,ww+1,posx,posy);
}
