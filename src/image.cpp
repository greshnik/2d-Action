#include <image.h>
#include <SDL/SDL.h>

int Image :: LoadImage(const char* FileName)
{
  SDL_Surface* temp, *temp2;
  temp2 = SDL_LoadBMP(FileName);
  if (temp2 != NULL) temp = SDL_DisplayFormat(temp2);
  img.push_back(temp);
  return 0;
}

void Image :: DrawIMG(SDL_Surface* screen,SDL_Surface* image, int x, int y)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_BlitSurface(image, NULL, screen, &dest);
}

void Image :: DrawIMG(SDL_Surface* screen, SDL_Surface* image, int x, int y,int w, int h, int sx, int sy)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_Rect src;
  src.x = sx;
  src.y = sy;
  src.w = w;
  src.h = h;
  SDL_BlitSurface(image, &src, screen, &dest);
}

CAnimdata::CAnimdata(const char* path)
{
  mW = 0; mH = 0;
  SDL_Surface* temp;
  char buf[255],name[255];
  int ppause = 0, r = 0, g = 0, b = 0, count = 0;
  char FileName[255];
  sprintf(FileName,"%s/info",path);
  FILE* fp = fopen(FileName,"r");
  if (!fp)
    {
      printf("Error: Can't open file: %s\n",FileName);
      exit(1);
    }
  fgets(buf,255,fp);
  sscanf(buf,"FILES: %d",&mNumFrames);
  mBuilt = 1;
  while(!feof(fp) && count<mNumFrames)
    {
      fgets(buf,255,fp);
      if(buf[0]!='#' && buf[0]!='\r' && buf[0]!='\n' && buf[0]!='\0' && strlen(buf)!=0)
	{
	  sscanf(buf,"%s %d %d %d %d",name,&ppause,&r,&g,&b);
	  sprintf(FileName,"%s/%s",path,name);
	  if((temp = SDL_LoadBMP(FileName)) == NULL) exit(1);
	  if(r>=0) SDL_SetColorKey(temp,SDL_SRCCOLORKEY,SDL_MapRGB(temp->format,r,g,b));
	  image.push_back(SDL_DisplayFormat(temp));
	  SDL_FreeSurface(temp);
	  pause.push_back(ppause);
	  if(!mW) mW = image[count]->w;
	  if(!mH) mH = image[count]->h;
	  ++count;
	}
    }
  fclose(fp);
}

int CAnim::init(CAnimdata* base, SDL_Surface* screen)
{
  mFrame = 0;
  mLastupdate = 0;
  AnimData = base;
  if (AnimData->mBuilt)
    {
      if(AnimData->mNumFrames>1) mAnimating=1;
      mBackreplacement = SDL_DisplayFormat(AnimData->image[0]);
    }
  mScreen = screen;
  return 0;
}

void CAnim::clearBG()
{
  if(mDrawn==1)
    {
      SDL_Rect dest;
      dest.x = mOldX;
      dest.y = mOldY;
      dest.w = AnimData->mW;
      dest.h = AnimData->mH;
      SDL_BlitSurface(mBackreplacement, NULL, mScreen, &dest);
    }
}

void CAnim::updateBG()
{
  SDL_Rect srcrect;
  srcrect.w = AnimData->image[0]->w;
  srcrect.h = AnimData->image[0]->h;
  srcrect.x = mX;
  srcrect.y = mY;
  mOldY = mY;
  mOldX = mX;
  SDL_BlitSurface(mScreen, &srcrect, mBackreplacement, NULL);
}

void CAnim::draw()
{
  if(mAnimating)
    {
      if(mLastupdate+AnimData->pause[mFrame]*mSpeed < SDL_GetTicks())
	{
	  mFrame++;
	  if(mFrame > AnimData->mNumFrames-1) mFrame=0;
	  mLastupdate = SDL_GetTicks();
	}
    }
  if(mDrawn == 0) mDrawn = 1;
  SDL_Rect dest;
  dest.x = mX; dest.y = mY; dest.h=100; dest.w=100;
  SDL_BlitSurface(AnimData->image[mFrame], NULL, mScreen, &dest);
}
