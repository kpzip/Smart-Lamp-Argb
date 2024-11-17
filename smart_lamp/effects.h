#include <Adafruit_NeoPixel.h>
#include "util.h"
#ifndef EFFECTS_H
#define EFFECTS_H

namespace Effects {
  void rainbow_wave(Adafruit_NeoPixel *strip, int wave_length, long wait, float max_hue=360, float saturation=100.0, float intensity=100.0, bool overflow=false, bool start_small=true);
  void retro_bulb_border_strobe(Adafruit_NeoPixel *strip, long wait, long iterations, Util::RGBColor on_color, Util::RGBColor off_color={ .r = 0, .g = 0, .b = 0 });
  void rgb_drift(Adafruit_NeoPixel *strip, long speed, int cycles, float hue_step = 1, float max_hue=360, float saturation=100.0, float intensity=100.0);
}

#endif