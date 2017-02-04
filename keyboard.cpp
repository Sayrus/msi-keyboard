#include <stdlib.h>
#include <stdio.h>
#include "hidapi.h"
#include "keyboard.h"
#define BUFFER_SIZE 8

e_mode ConvertToEMode(char* mode)
{
  if(!mode)
    return e_mode::MODE_NORMAL;
  if(strcmp(mode, "normal") == 0)
    return e_mode::MODE_NORMAL;
  if(strcmp(mode, "gaming") == 0)
    return e_mode::MODE_GAMING;
  if(strcmp(mode, "breath") == 0)
    return e_mode::MODE_BREATH;
  if(strcmp(mode, "audio") == 0)
    return e_mode::MODE_AUDIO;
  if(strcmp(mode, "wave") == 0)
    return e_mode::MODE_WAVE;
  if(strcmp(mode, "dual") == 0)
    return e_mode::MODE_DUAL;
  return e_mode::MODE_NORMAL;
}
e_region ConvertToERegion(char* region)
{
  if(!region)
    return e_region::REGION_MIDDLE;
  if(strcmp(region, "left") == 0)
    return e_region::REGION_LEFT;
  if(strcmp(region, "right") == 0)
    return e_region::REGION_RIGHT;
  return e_region::REGION_MIDDLE;
}
e_color ConvertToEColor(char* color)
{
  if(!color)
    return e_color::COLOR_NONE;
  if(strcmp(color, "red") == 0)
    return e_color::COLOR_RED;
  if(strcmp(color, "orange") == 0)
    return e_color::COLOR_ORANGE;
  if(strcmp(color, "yellow") == 0)
    return e_color::COLOR_YELLOW;
  if(strcmp(color, "green") == 0)
    return e_color::COLOR_GREEN;
  if(strcmp(color, "sky") == 0)
    return e_color::COLOR_SKY;
  if(strcmp(color, "blue") == 0)
    return e_color::COLOR_BLUE;
  if(strcmp(color, "purple") == 0)
    return e_color::COLOR_PURPLE;
  if(strcmp(color, "white") == 0)
    return e_color::COLOR_WHITE;
  return e_color::COLOR_NONE;
}
e_intensity ConvertToEIntensity(char* intensity)
{
  if(!intensity)
    return e_intensity::INTENSITY_HIGH;
  if(strcmp(intensity, "medium") == 0)
    return e_intensity::INTENSITY_MEDIUM;
  if(strcmp(intensity, "low") == 0)
    return e_intensity::INTENSITY_LOW;
  if(strcmp(intensity, "light") == 0)
    return e_intensity::INTENSITY_LIGHT;
  return e_intensity::INTENSITY_HIGH;
}

Keyboard::Keyboard() :
  handle(NULL)
{
  handle = hid_open(0x1770, 0xff00, 0);
  if(!handle)
  {
    printf("Cannot open USB device");
    return;
  }
}

Keyboard::~Keyboard()
{
  if(handle)
  {
    hid_close(handle);
  }
}
void Keyboard::debug(unsigned char buffer[])
{
  if(!handle)
    return;
  hid_send_feature_report(handle, buffer, BUFFER_SIZE);
}
void Keyboard::setColors(e_color primaryColor, e_intensity primaryIntensity, e_color secondaryColor, e_intensity secondaryIntensity)
{
  if(!handle)
    return;
  unsigned char buffer[BUFFER_SIZE] = {0};
  buffer[0] = 1;
  buffer[1] = 2;
  buffer[2] = 67;
  buffer[7] = 236;
  for(int i = 1; i < 9; i += 3)
  {
    buffer[3] = i;
    buffer[4] = static_cast<unsigned int>(primaryColor);
    buffer[5] = static_cast<unsigned int>(primaryIntensity);
    buffer[6] = 0;
    hid_send_feature_report(handle, buffer, BUFFER_SIZE);
    buffer[3] = i + 1;
    buffer[4] = static_cast<unsigned int>(secondaryColor);
    buffer[5] = static_cast<unsigned int>(secondaryIntensity);
    hid_send_feature_report(handle, buffer, BUFFER_SIZE);
    buffer[3] = i + 2;
    // I will keep buffer[4-6] = 2 until I figure out what changing one of them does to the keyboard
    buffer[4] = 2;
    buffer[5] = 2;
    buffer[6] = 2;
    hid_send_feature_report(handle, buffer, BUFFER_SIZE);
  } 
}
void Keyboard::setMode(e_mode mode)
{
  if(!handle)
    return;
  unsigned char buffer[BUFFER_SIZE] = {0};
  buffer[0] = 1;
  buffer[1] = 2;
  buffer[2] = 65;
  buffer[3] = static_cast<unsigned int>(mode);
  buffer[4] = 0;
  buffer[5] = 0;
  buffer[6] = 0;
  buffer[7] = 236;
  hid_send_feature_report(handle, buffer, BUFFER_SIZE);
}

void Keyboard::setMode(char* mode)
{
  Keyboard::setMode(ConvertToEMode(mode));
}

void Keyboard::setColor(e_region region, e_color color, e_intensity intensity)
{
  if(!handle)
    return;
  unsigned char buffer[BUFFER_SIZE] = {0};
  buffer[0] = 1;
  buffer[1] = 2;
  buffer[2] = 66;
  buffer[3] = static_cast<unsigned int>(region);
  buffer[4] = static_cast<unsigned int>(color);
  buffer[5] = static_cast<unsigned int>(intensity);
  buffer[6] = 0;
  buffer[7] = 236;
  hid_send_feature_report(handle, buffer, BUFFER_SIZE);
}

void Keyboard::setColor(e_region region, s_color rgb)
{
  if(!handle)
    return;
  unsigned char buffer[BUFFER_SIZE] = {0};
  buffer[0] = 1;
  buffer[1] = 2;
  buffer[2] = 64;
  buffer[3] = static_cast<unsigned int>(region);
  buffer[4] = rgb.red;
  buffer[5] = rgb.green;
  buffer[6] = rgb.blue;
  buffer[7] = 236;
  hid_send_feature_report(handle, buffer, BUFFER_SIZE);
}

