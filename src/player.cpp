#include <player.h>
#include <map.h>

player::player(int coordmapx, int coordmapy, SDL_Surface *screen)
{
  mapx = coordmapx; mapy = coordmapy;
  posx = 0; posy = 0;
  mymap = new map(screen);
  mymap->loadmap();
  mymap->onmove(mapx,mapy,posx,posy);
}

void player::moveplayer(mpointer direction,int speed)
{
  int mod;
  printf("%i %i\n",mapx,mapy);
  switch(direction)
    {
    case 0:// up
      if (!CheckCollision(direction,posx,posy))
	{
	  posy += speed;
	  if (posy > 100)
	    {
	      posy -= 100;
	      mapy--;
	    }
	  mymap->onmove(mapx,mapy,posx,posy);
	}
      break;
    case 1:// down
      if (!CheckCollision(direction,posx,posy))
	{
	  posy -= speed;
	  if(posy*(-1) > 100)
	    {
	      posy += 100;
	      mapy++;
	    }
	  mymap->onmove(mapx,mapy,posx,posy);
	}
      break;
    case 2:// left
      if (!CheckCollision(direction,posx,posy))
	{
	  posx += speed;
	  if(posx > 100)
	    {
	      posx -= 100;
	      mapx--;
	    }
	  mymap->onmove(mapx, mapy, posx, posy);
	}
      break;
      
    case 3:// right
      if (!CheckCollision(direction,posx,posy))
	{
	  posx -= speed;
	  if (posx*(-1) > 100)
	    {
	      posx += 100;
	      mapx++;
	    }
	  mymap->onmove(mapx, mapy, posx, posy);
	  break;
	}
    }
}

bool player::CheckCollision(mpointer direction, int posx, int posy)
{
  switch (direction)
    {
    case 0://up
      if (mmap[mapy-1][mapx] != '0') return true;
      break;
    case 1://down
      if (mmap[mapy+1][mapx] != '0') return true;
      break;
    case 2://left
      if ((mmap[mapy][mapx-1] != '0') & (posx == 100)) return true;
      break;
    case 3://right
      if (mmap[mapy][mapx+1] != '0') return true;
      break;
    defaut:
      return false;
      break;
    }
}
