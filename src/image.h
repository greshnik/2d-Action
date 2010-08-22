#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <SDL/SDL.h>
#include <vector>

using namespace std;

class CAnimdata
{
 public:
  CAnimdata(const char* path);
  vector <SDL_Surface*> image;
  vector <int> pause;
  int mNumFrames,mBuilt,mW,mH;
};

class CAnim
{
 public:
  int init(CAnimdata *base, SDL_Surface* screen);

  void draw();
  void clearBG();
  void updateBG();

  void setFrame(int nr) { mFrame = nr; }
  int getFrame() { return mFrame; }

  void setSpeed(float nr) { mSpeed = nr; }
  float getSpeed() { return mSpeed; }

  void toggleAnim() { mAnimating = !mAnimating; }
  void startAnim() {mAnimating = 1; }
  void stopAnim() {mAnimating = 0; }
  void rewind() {mFrame = 0; }

  void xadd(int nr) { mX+=nr; }
  void yadd(int nr) { mY+=nr; }
  void xset(int nr) { mX=nr; }
  void yset(int nr) { mY=nr; }
  int yget(){return mY;}
  int xget(){return mX;}
  void set(int xx, int yy) { mX=xx; mY=yy; }

 private:
  int mFrame;
  int mX, mY, mOldX, mOldY;
  int mAnimating;
  int mDrawn;
  float mSpeed;
  long mLastupdate;
  CAnimdata *AnimData;
  SDL_Surface *mBackreplacement;
  SDL_Surface *mScreen;
};

class Image{
public:
    vector <SDL_Surface*> img;
    vector <SDL_Surface*> watchimg;
    int LoadImage(const char* FileName);
    void DrawIMG(SDL_Surface* screen, SDL_Surface* image, int x, int y);
    void DrawIMG(SDL_Surface* screen, SDL_Surface* image, int x, int y,int w, int h, int sx, int sy);
};

#endif
