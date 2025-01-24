#include <Adafruit_NeoPixel.h>

#define PIN 2 // Pin for the NeoPixels
#define NUMPIXELS 24 // Number of pixels in the strip

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(10);// Initialize all pixels to 'off'
}

void loop() {
  deepSeaAnimalPattern1(); // Jellyfish - Blue glow
  delay(3000);
  
  deepSeaAnimalPattern2(); // Anglerfish - Yellow flicker
  delay(3000);
  
  deepSeaAnimalPattern3(); // Squid - Pink/Purple pulsing
  delay(3000);
  
  deepSeaAnimalPattern4(); // Octopus - Random color shifting
  delay(3000);
  
  deepSeaAnimalPattern5(); // Deep-Sea Fish - Green glow
  delay(3000);
  
  deepSeaAnimalPattern6(); // Cuttlefish - White pulsing
  delay(3000);
}

void deepSeaAnimalPattern1() {
  // Representing a jellyfish (bioluminescent glow)
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 255)); // Blue glow
  }
  strip.show();
}

void deepSeaAnimalPattern2() {
  // Representing a deep-sea anglerfish (dim yellow light with flicker)
  for (int i = 0; i < NUMPIXELS; i++) {
    if (random(10) < 2) {
      strip.setPixelColor(i, strip.Color(255, 255, 0)); // Yellow flicker
    } else {
      strip.setPixelColor(i, strip.Color(0, 0, 0)); // Dark
    }
  }
  strip.show();
}

void deepSeaAnimalPattern3() {
  // Representing a squid (pulsing light)
  for (int i = 0; i < NUMPIXELS; i++) {
    int brightness = random(50, 255);
    strip.setPixelColor(i, strip.Color(brightness, 10, 10 - brightness)); // Purple to pink
  }
  strip.show();
  
  delay(2000);  // Squid color stays on for 1 second
  
  // Turn off after pulsing
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0)); // Off
  }
  strip.show();
}

void deepSeaAnimalPattern4() {
  // Representing a deep-sea octopus (color-shifting)
  for (int i = 0; i < NUMPIXELS; i++) {
    int r = random(0, 255); // Random red value
    int g = random(0, 255); // Random green value
    int b = random(0, 255); // Random blue value
    strip.setPixelColor(i, strip.Color(r, g, b)); // Random color
  }
  strip.show();
}

void deepSeaAnimalPattern5() {
  // Representing a deep-sea fish (green glow)
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0)); // Green glow
  }
  strip.show();
}

void deepSeaAnimalPattern6() {
  // Representing a cuttlefish (pulsing white)
  for (int i = 0; i < NUMPIXELS; i++) {
    int brightness = random(50, 255); // Random brightness
    strip.setPixelColor(i, strip.Color(10, 10, brightness)); // White pulsing
  }
  strip.show();
  
  delay(1000);  // Cuttlefish pulsing stays on for 1 second
  
  // Turn off after pulsing
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0)); // Off
  }
  strip.show();

  delay(1500);
}
