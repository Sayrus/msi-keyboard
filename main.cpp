#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string>
#include "hidapi.h"
#include "keyboard.h"
#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif
char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char* argv[])
{
#ifdef WIN32
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
#endif
  Keyboard    keyboard;
  bool        full          = cmdOptionExists(argv, argv + argc, "--full");
  char*       mode          = getCmdOption(argv, argv + argc, "-m");
  char*       color         = getCmdOption(argv, argv + argc, "-c");
  char*       intensity     = getCmdOption(argv, argv + argc, "-i");
  char*       color2        = getCmdOption(argv, argv + argc, "-c2");
  char*       intensity2    = getCmdOption(argv, argv + argc, "-i2");
  e_mode      newMode       = ConvertToEMode(mode);
  e_color     newColor      = ConvertToEColor(color);
  e_color     newColor2     = ConvertToEColor(color2);
  e_intensity newIntensity  = ConvertToEIntensity(intensity); 
  e_intensity newIntensity2 = ConvertToEIntensity(intensity2);
  double period = 0;
  switch(newMode)
  {
    case e_mode::MODE_DUAL:
      period = 2.0;
    case e_mode::MODE_WAVE:
      if(period == 0)
        period = 1.5;
    case e_mode::MODE_BREATH:
      if(period == 0)
        period = 1.0;
      {
        s_pairColor primary = { newColor, newIntensity };
        s_pairColor secondary = { newColor2, newIntensity2 };
        keyboard.setDualColor(primary, secondary, e_region::REGION_LEFT, period);
        keyboard.setDualColor(primary, secondary, e_region::REGION_MIDDLE, period);
        keyboard.setDualColor(primary, secondary, e_region::REGION_RIGHT, period);
      }
      break;
    case e_mode::MODE_GAMING:
      keyboard.setColor(e_region::REGION_LEFT, newColor, newIntensity);
      break;
    case e_mode::MODE_NORMAL:
    default:
      if(full)
      {
        keyboard.setColor(e_region::REGION_LEFT, newColor, newIntensity);
        keyboard.setColor(e_region::REGION_MIDDLE, newColor, newIntensity);
        keyboard.setColor(e_region::REGION_RIGHT, newColor, newIntensity);
      }
      else
      {
        char*     region        = getCmdOption(argv, argv + argc, "-r");
        e_region  newRegion     = ConvertToERegion(region);
        keyboard.setColor(newRegion, newColor, newIntensity);
      }
      break;
  }
  keyboard.setMode(newMode);
#ifdef WIN32
	system("pause");
#endif
	return 0;
}
