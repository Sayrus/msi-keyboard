#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include <string.h>
enum  e_mode 
{
      MODE_NORMAL = 1,
      MODE_GAMING = 2,
      MODE_BREATH = 3,
      MODE_AUDIO  = 4, // NEED FIX
      MODE_WAVE   = 5, // Wave may need a fix
      MODE_DUAL   = 6
};
e_mode ConvertToEMode(char* mode);
enum  e_region
{
      REGION_LEFT   = 1,
      REGION_MIDDLE = 2,
      REGION_RIGHT  = 3
};
e_region ConvertToERegion(char* region);
enum  e_color
{
      COLOR_NONE    = 0,
      COLOR_RED     = 1,
      COLOR_ORANGE  = 2,
      COLOR_YELLOW  = 3,
      COLOR_GREEN   = 4,
      COLOR_SKY     = 5,
      COLOR_BLUE    = 6,
      COLOR_PURPLE  = 7,
      COLOR_WHITE   = 8
};
e_color ConvertToEColor(char *color);
enum  e_intensity
{
      INTENSITY_HIGH    = 0,
      INTENSITY_MEDIUM  = 1,
      INTENSITY_LOW     = 2,
      INTENSITY_LIGHT   = 3
};
e_intensity ConvertToEIntensity(char* intensity);
struct  s_color
{
  char  red;
  char  green;
  char  blue;
};
struct        s_pairColor
{
  e_color     color;
  e_intensity intensity;
};
class Keyboard
{
  public:
    Keyboard();
    ~Keyboard();
    void  debug(unsigned char buffer[]);
    void  setColors(e_color primaryColor, e_intensity primaryIntensity, e_color secondaryColor, e_intensity secondaryIntensity);
    void  setMode(e_mode mode);
    void  setMode(char* mode);
    void  setColor(e_region region, e_color color, e_intensity intensity);
    void  setColor(e_region region, s_color rgb);
    void  setDualColor(s_pairColor primary, s_pairColor secondary, e_region region, double period);
    int   ComputeRampSpeed(double comp1, double comp2, double period);
  private:
    hid_device *handle;
    int colorPalette[9][4][4]={{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},{{0,170,0,0},{0,255,0,0},{0,255,32,16},{0,238,80,48}},{{0,170,64,0},{0,187,112,0},{0,204,170,16},{0,238,204,48}},{{0,128,128,0},{0,238,238,0},{0,255,255,32},{0,238,238,48}},{{0,16,255,0},{0,176,255,0},{0,32,221,32},{0,170,238,48}},{{0,0,170,255},{0,0,255,255},{0,80,255,238},{0,144,238,255}},{{0,0,0,170},{0,0,0,255},{0,0,255,255},{0,80,204,238}},{{0,21,0,160},{0,48,0,255},{0,187,170,255},{0,255,255,255}},{{0,176,255,176},{0,176,255,176},{0,176,255,176},{0,176,255,176}}};
};
#endif
