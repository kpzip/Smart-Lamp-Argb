#include <Adafruit_NeoPixel.h>
#include "effects.h"
#define DEBUG                   // Comment out in final version to disable debug info being printed to the serial port

#define LEDPIN 6                // Connect the Data pin from the strip to this pin on the Arduino.
#define TRIG_PIN 2              // Pin connected to the Trigger input on the ultrasonic sensor
#define ECHO_PIN 3              // Pin connected to the Echo output on the ultrasonic sensor
#define MIN_POLL_DELAY_MS 10    // Minimum time between sending pulses on the Trigger pin (from the datasheet)
#define NUM_PIXELS 60           // The number of pixels in your LED strip.

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

const int wait_time = 100;      // Interval in ms between updates to the LED strip.
const int threshold_cm = 100;   // Threshold distance to trigger the lamp

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  strip.begin();
  strip.clear();
  strip.show();
}
void loop() {

  // Sequence to trigger an ultrasonic sensor read
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // take in the distance from the ultrasonic sensor and convert to centimeters
  float cm = pulseIn(ECHO_PIN, HIGH) / 58.0;
  // Keep two decimal places
  cm = (int(cm * 100.0)) / 100.0;

#ifdef DEBUG
  // Debug info
  Serial.print("Distance\t=\t");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
#endif


  if (cm < threshold_cm) {

    for (int i = 0; i < strip.numPixels() - 1; i++) {
      // starting at i, draw the 7 color rainbow}
      // a seven segment rainbow with red on the highest pixel
      int np = strip.numPixels();                      // we use the modulo function with this
      strip.setPixelColor(i % np, 0, 0, 0);            // off
      strip.setPixelColor((i + 1) % np, 25, 0, 25);    // violet
      strip.setPixelColor((i + 2) % np, 255, 0, 255);  // indigo
      strip.setPixelColor((i + 3) % np, 0, 0, 150);    // blue
      strip.setPixelColor((i + 4) % np, 0, 150, 0);    // green
      strip.setPixelColor((i + 5) % np, 255, 255, 0);  // yellow
      strip.setPixelColor((i + 6) % np, 110, 70, 0);   // orange
      strip.setPixelColor((i + 7) % np, 150, 0, 0);    // red
      strip.show();
      delay(wait_time);
      strip.clear();
      strip.show();
    }

  }
  else {
    strip.clear();
    strip.show();
    delay(MIN_POLL_DELAY_MS);
  }
}