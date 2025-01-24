//Yve Smith
//
//23.01.25

#include <Adafruit_NeoPixel.h>

#define PIN            2       // Pin where NeoPixel ring is connected
#define NUMPIXELS      24      // Number of pixels in the NeoPixel ring
#define BRIGHTNESS     50      // Brightness of the pixels (0-255)
#define MAX_BRIGHTNESS 255     // Maximum brightness level
#define MIN_BRIGHTNESS 50   
#define TWINKLE_RATE   100     // Rate at which twinkling occurs (lower is faster)

Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  ring.begin();
  ring.setBrightness(BRIGHTNESS);
  ring.show();  // Initialize all pixels to 'off'
}

void loop() {
  for (int i = 0; i < NUMPIXELS; i++) {
    // Soft warm glow (orange-yellow)
    int redValue = random(120, 255);  // Random red for a warm feel
    int greenValue = random(80, 180); // Random green to make it gentle
    int blueValue = random(20, 100);  // Low blue to keep it warm

    // Set the pixel with random brightness for the twinkling effect
    ring.setPixelColor(i, ring.Color(redValue, greenValue, blueValue));
  }

  // Light up the pixels with a gentle fade
  ring.show();
  
  // Delay before the next twinkle effect
  delay(TWINKLE_RATE);
  
  // Fade the pixels to black (off) one by one, giving the impression of twinkling out
  for (int i = 0; i < NUMPIXELS; i++) {
    int redValue = random(120, 255);  // Random red for the fading glow
    int greenValue = random(80, 180); // Random green for the fading glow
    int blueValue = random(20, 100);  // Low blue for the fading glow
    ring.setPixelColor(i, ring.Color(redValue, greenValue, blueValue));
    ring.show();
    delay(200);  // Slight delay for each pixel fade
  }
}
