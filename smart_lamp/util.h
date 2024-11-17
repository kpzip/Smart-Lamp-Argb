#ifndef UTIL_H
#define UTIL_H
#include <stdint.h>

namespace Util {
  typedef struct RGBColor {
	  uint8_t r;
	  uint8_t g;
	  uint8_t b;
  } RGBColor;
  RGBColor hsv2rgb(float H, float S, float V);
}

#endif