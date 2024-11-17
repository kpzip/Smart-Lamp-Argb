#include <Adafruit_NeoPixel.h>
#include "effects.h"
#define DEBUG                   // Comment out in final version to disable debug info being printed to the serial port
#define USE_DISTANCE_SENSOR     // Comment out to disable using the ultrasonic sensor for testing purposes

#define LEDPIN 6                // Connect the Data pin from the strip to this pin on the Arduino.
#define TRIG_PIN 2              // Pin connected to the Trigger input on the ultrasonic sensor
#define ECHO_PIN 3              // Pin connected to the Echo output on the ultrasonic sensor
#define MIN_POLL_DELAY_MS 10    // Minimum time between sending pulses on the Trigger pin (from the datasheet)
#define NUM_PIXELS 60           // The number of pixels in your LED strip.

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

const long wait_time = 100;      // Interval in ms between updates to the LED strip.
const int threshold_cm = 100;   // Threshold distance to trigger the lamp

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif
#ifdef USE_DISTANCE_SENSOR
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
#endif
  strip.begin();
  strip.clear();
  strip.show();
}
void loop() {

#ifdef USE_DISTANCE_SENSOR
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
#endif
#ifndef USE_DISTANCE_SENSOR
  float cm = 0.0;
#endif

#ifdef DEBUG
  // Debug info
  Serial.print("Distance\t=\t");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
#endif


  if (cm < threshold_cm) {
#ifdef DEBUG
    Serial.println("Lighting Activated");
#endif
    // Play around with different effects
    Effects::rainbow_wave(&strip, 6, wait_time);
    //Effects::retro_bulb_border_strobe(&strip, wait_time, 10, { .r = 255, .g = 0, .b = 0 });
    //Effects::rgb_drift(&strip, 10, 2);

  }
  else {
#ifdef DEBUG
    Serial.println("Lighting Not Activated");
#endif
    strip.clear();
    strip.show();
    delay(MIN_POLL_DELAY_MS);
  }
}