#include <Adafruit_NeoPixel.h>
#include <stdint.h>
#include "util.h"
#include "effects.h"

#define max_colors 20

// Wave length must not be > max_colors!
void Effects::rainbowWave(Adafruit_NeoPixel *strip, int wave_length, long wait, float max_hue=360, float saturation=100.0, float intensity=100.0, bool overflow=false, bool start_small=true) {
  int np = strip->numPixels();

  uint8_t r_space[max_colors], g_space[max_colors], b_space[max_colors] = {0};

  // Initialize rgb values
  int hue_step = max_hue/wave_length;
  float current_hue;
  for (int i = 0; i < wave_length; i++) {
    current_hue = hue_step * i;
    Util::RGBColor color = Util::hsv2rgb(current_hue, saturation, intensity);
    r_space[i] = color.r;
    g_space[i] = color.g;
    b_space[i] = color.b;
  }

  // Play wave effect
  for (int i = start_small ? -wave_length : 0; i < np; i++) {
    if (i - 1 >= 0) {
      strip->setPixelColor(i-1, 0, 0, 0);
    }

    for (int j = 0; j < wave_length; j++) {
      if ((overflow || i + j < np) && i + j >= 0) {
        strip->setPixelColor((i + j) % np, r_space[j], g_space[j], b_space[j]);
      }
    }
    strip->show();
    delay(wait);
    strip->clear();
    strip->show();
  }
}

void Effects::retroBulbBorderStrobe(Adafruit_NeoPixel *strip, long wait, long iterations, Util::RGBColor on_color, Util::RGBColor off_color={ .r = 0, .g = 0, .b = 0 }) {
  int np = strip->numPixels();

  for (long i = 0; i < iterations; i++) {
    for (int j = 0; j < np; j++) {
      if ((i + j) % 2 == 0) {
        strip->setPixelColor(j, on_color.r, on_color.g, on_color.b);
      }
      else {
        strip->setPixelColor(j, off_color.r, off_color.g, off_color.b);
      }
    }
    strip->show();
    delay(wait);
    strip->clear();
    strip->show();
  }
}

void Effects::rgbDrift(Adafruit_NeoPixel *strip, long speed, int cycles, float hue_step = 1, float max_hue=360, float saturation=100.0, float intensity=100.0) {
  int np = strip->numPixels();

  int iterations = cycles * (max_hue/hue_step);
  float current_hue = 0;
  Util::RGBColor color;
  for (int i = 0; i < iterations; i++) {
      color = Util::hsv2rgb(current_hue, saturation, intensity);
      for (int j = 0; j < np; j++) {
        strip->setPixelColor(j, color.r, color.g, color.b);
      }
      strip->show();
      delay(speed);
      strip->clear();
      strip->show();
      current_hue += hue_step;
      current_hue = fmod(current_hue, 360.0);
  }

}

