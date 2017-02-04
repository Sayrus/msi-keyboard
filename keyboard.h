#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include <string.h>
enum  e_mode 
{
      MODE_NORMAL = 1
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
class Keyboard
{
  public:
    Keyboard();
    ~Keyboard();
    void setMode(e_mode mode);
    void setMode(char* mode);
    void setColor(e_region region, e_color color, e_intensity intensity);
    void setColor(e_region region, s_color rgb);
  private:
    hid_device *handle;
};
#endif
