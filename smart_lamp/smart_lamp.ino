#include <Adafruit_NeoPixel.h>
#define LEDPIN 6       // Connect the Data pin from the strip to this pin on the Arduino.
#define NUM_PIXELS 60  // The number of pixels in your LED strip.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);
const int TrigPin = 2;
const int EchoPin = 3;
float cm;
int wait = 100;  // Interval in ms between updates to the LED strip.
int i = 0;


void setup() {
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  strip.begin();
  strip.clear();
  strip.show();
}
void loop() {

  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  cm = pulseIn(EchoPin, HIGH) / 58.0;  //The echo time is converted into cm
  cm = (int(cm * 100.0)) / 100.0;      //Keep two decimal places
  Serial.print("Distance\t=\t");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();


  if (cm < 100) {

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
      delay(wait);
      strip.clear();
      strip.show();
    }

  } else {
    strip.clear();
    strip.show();
    delay(10);
  }
}