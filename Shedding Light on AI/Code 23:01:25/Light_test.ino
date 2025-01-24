//Amy Mccerery
//
//23.01.25

#include <Adafruit_NeoPixel.h>

// Define the pin connected to the NeoPixel ring
#define PIN 2

// Number of LEDs in the ring
#define NUM_LEDS 24

// Brightness level (0 to 255)
#define BRIGHTNESS 30

// Create the NeoPixel object
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// Define colors for Taylor Swift eras
uint32_t debut = strip.Color(0, 128, 0);       // Green
uint32_t fearless = strip.Color(255, 255, 0); // Yellow
uint32_t speakNow = strip.Color(128, 0, 128); // Purple
uint32_t red = strip.Color(255, 0, 0);        // Red
uint32_t nineteenEightyNine = strip.Color(255, 20, 147); // Pink (Hot Pink)
uint32_t reputation = strip.Color(255, 255, 255); // White
uint32_t lover = strip.Color(0, 191, 255);    // Blue (Deep Sky Blue)
uint32_t folklore = strip.Color(255, 140, 0); // Warm Amber
uint32_t midnights = strip.Color(0, 255, 255); // Cool Cyan

void setup() {
  strip.begin();               // Initialize the NeoPixel strip
  strip.setBrightness(BRIGHTNESS); // Set brightness
  strip.show();                // Clear all LEDs
}

void loop() {
  // Debut: Smooth Fading
  smoothFade(debut, 1000);

  // Fearless: Chasing Effect
  chasingEffect(fearless, 50);

  // Speak Now: Sparkle Effect
  sparkleEffect(speakNow, 20, 1000);

  // Red: Pulsating Brightness
  pulsateEffect(red, 1000);

  // 1989: Wiping Animation
  wipeEffect(nineteenEightyNine, 50);

  // Reputation: Flashing Strobe
  strobeEffect(reputation, 100, 10);

  // Lover: Color Wipes with Fades
  colorWipeWithFade(lover, 50);

  // Folklore/Evermore: Gentle Rainbow Blending
  rainbowBlend(folklore, 3000);

  // Midnights: Twinkling Stars
  twinkleEffect(midnights, 20, 1000);
}

// Smooth fading in and out
void smoothFade(uint32_t color, int duration) {
  for (int brightness = 0; brightness <= 255; brightness += 5) {
    strip.setBrightness(brightness);
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, color);
    }
    strip.show();
    delay(duration / 510); // Smooth fade in
  }
  for (int brightness = 255; brightness >= 0; brightness -= 5) {
    strip.setBrightness(brightness);
    strip.show();
    delay(duration / 510); // Smooth fade out
  }
  strip.setBrightness(BRIGHTNESS); // Reset brightness
}

// Chasing Effect
void chasingEffect(uint32_t color, int delayTime) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(delayTime);
    strip.setPixelColor(i, 0); // Turn off the LED after the chase
  }
}

// Sparkle Effect
void sparkleEffect(uint32_t color, int numSparkles, int duration) {
  unsigned long start = millis();
  while (millis() - start < duration) {
    int pixel = random(NUM_LEDS); // Pick a random LED
    strip.setPixelColor(pixel, color);
    strip.show();
    delay(50);
    strip.setPixelColor(pixel, 0); // Turn off the sparkle
    strip.show();
  }
}

// Pulsating Brightness
void pulsateEffect(uint32_t color, int duration) {
  for (int brightness = 0; brightness <= 255; brightness += 5) {
    strip.setBrightness(brightness);
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, color);
    }
    strip.show();
    delay(duration / 510);
  }
  for (int brightness = 255; brightness >= 0; brightness -= 5) {
    strip.setBrightness(brightness);
    strip.show();
    delay(duration / 510);
  }
  strip.setBrightness(BRIGHTNESS); // Reset brightness
}

// Wiping Animation
void wipeEffect(uint32_t color, int delayTime) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(delayTime);
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 0); // Turn off LED
    strip.show();
    delay(delayTime);
  }
}

// Strobe Effect
void strobeEffect(uint32_t color, int delayTime, int flashes) {
  for (int i = 0; i < flashes; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      strip.setPixelColor(j, color);
    }
    strip.show();
    delay(delayTime);
    for (int j = 0; j < NUM_LEDS; j++) {
      strip.setPixelColor(j, 0); // Turn off all LEDs
    }
    strip.show();
    delay(delayTime);
  }
}

// Color Wipe with Fade
void colorWipeWithFade(uint32_t color, int delayTime) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(delayTime);
  }
  smoothFade(color, 1000); // Fade out
}

// Gentle Rainbow Blending
void rainbowBlend(uint32_t baseColor, int duration) {
  for (int j = 0; j < 256; j++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      uint32_t color = strip.Color(
        (baseColor >> 16 & 0xFF) * j / 255,
        (baseColor >> 8 & 0xFF) * j / 255,
        (baseColor & 0xFF) * j / 255
      );
      strip.setPixelColor(i, color);
    }
    strip.show();
    delay(duration / 256);
  }
}

// Twinkling Stars
void twinkleEffect(uint32_t color, int numTwinkles, int duration) {
  unsigned long start = millis();
  while (millis() - start < duration) {
    for (int i = 0; i < numTwinkles; i++) {
      int pixel = random(NUM_LEDS); // Pick random LED
      strip.setPixelColor(pixel, color);
    }
    strip.show();
    delay(100);
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, 0); // Turn off all LEDs
    }
    strip.show();
  }
}
