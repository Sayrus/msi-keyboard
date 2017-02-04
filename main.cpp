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
  e_color     newColor      = ConvertToEColor(color);
  e_mode      newMode       = ConvertToEMode(mode);
  e_intensity newIntensity  = ConvertToEIntensity(intensity); 
  if(!full) 
  {
    char*     region        = getCmdOption(argv, argv + argc, "-r");
    e_region  newRegion     = ConvertToERegion(region);
    keyboard.setColor(newRegion, newColor, newIntensity);
  }
  else
  {
    keyboard.setColor(e_region::REGION_LEFT, newColor, newIntensity);
    keyboard.setColor(e_region::REGION_MIDDLE, newColor, newIntensity);
    keyboard.setColor(e_region::REGION_RIGHT, newColor, newIntensity);
  }
  keyboard.setMode(newMode);
#ifdef WIN32
	system("pause");
#endif
	return 0;
}
