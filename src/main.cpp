#include <mysdl.h>
#include <image.h>
#include <player.h>

/*
 * a - WORK WITH SDL
 * b - WORK WITH IMAGE
 * c - WORK WITH INIT ANIMATION
 * d - WORK WITH ANIMATION
 * e - WORK WITH MAP
 */
bool quit = false;
int main(int argc, char* argv[])
{
  MySdlInit* a = new MySdlInit(800,600,32,0,"qwert","data/icon.bmp");
  Image* b = new Image;
  CAnimdata* c = new CAnimdata("data/anim");
  CAnim* d = new CAnim;
  player* e = new player(1,6,a->screen);

  d->init(c,a->screen);
  d->set((int)(a->screen->w/2-100),(int)(a->screen->h/2-100)); //debug
  d->setSpeed(0.6);
  // General loop
  SDL_Event event;
  while (!quit)
    {
      while (SDL_PollEvent(&event))
	{
	  if(event.type==SDL_QUIT){ quit = true; }
	  if(event.type==SDL_KEYDOWN)
	    {
	      if(event.key.keysym.sym==SDLK_ESCAPE){ quit = true; }
	      if(event.key.keysym.sym==SDLK_SPACE)
		{
		  d->toggleAnim();
		}
	    }
	}
      a->keys = SDL_GetKeyState(NULL);
      if(a->keys[SDLK_UP])
	{ 
	  e->moveplayer(MV_UP,1);
	}
      if(a->keys[SDLK_DOWN])
	{ 
	  e->moveplayer(MV_DOWN,1);
	}
      if(a->keys[SDLK_LEFT])
	{
	  e->moveplayer(MV_LEFT,1);
	}
      if(a->keys[SDLK_RIGHT])
	{
	  e->moveplayer(MV_RIGHT,1);
	}
      // Rendering
      d->updateBG();
      d->clearBG();
      d->draw();
      a->DrawScene();
    }
  // Quit
  SDL_Quit();
  return 0;
}
