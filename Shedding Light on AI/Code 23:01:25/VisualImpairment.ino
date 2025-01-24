#include <Adafruit_NeoPixel.h>

#define PIN 2            // Pin connected to the NeoPixel ring
#define NUM_LEDS 24      // Number of LEDs in the ring
#define BRIGHTNESS 30    // Overall brightness (0-255)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();              // Initialize NeoPixel strip
  strip.setBrightness(BRIGHTNESS);
  strip.show();               // Clear all LEDs
}

void loop() {
  blurredVisionEffect();      // Blurred vision representation
  delay(1000);

  tunnelVisionEffect();       // Tunnel vision representation
  delay(1000);

  peripheralLossEffect();     // Peripheral vision loss representation
  delay(1000);

  fluctuatingVisionEffect();  // Vision fluctuation representation
  delay(1000);
}

// --- EFFECT 1: Blurred Vision ---
void blurredVisionEffect() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, dimColor(strip.Color(255, 255, 255), random(50, 200))); // Soft white
    if (i > 0) {
      strip.setPixelColor(i - 1, dimColor(strip.Color(0, 255, 255), random(20, 120))); // Adjacent with blue tint
    }
    strip.show();
    delay(50);
  }
  fadeToBlack(20); // Gradually fade out to simulate "blur clearing"
}

// --- EFFECT 2: Tunnel Vision ---
void tunnelVisionEffect() {
  for (int i = 0; i < NUM_LEDS / 2; i++) {
    strip.setPixelColor(i, strip.Color(255, 255, 255)); // Bright center
    strip.setPixelColor(NUM_LEDS - 1 - i, strip.Color(255, 255, 255)); // Symmetry
    strip.setPixelColor(i + 1, dimColor(strip.Color(100, 100, 100), 80)); // Edges dimmer
    strip.show();
    delay(100);
  }
  fadeToBlack(20); // Gradually fade to black
}

// --- EFFECT 3: Peripheral Loss ---
void peripheralLossEffect() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i >= NUM_LEDS / 4 && i < (3 * NUM_LEDS) / 4) {
      strip.setPixelColor(i, strip.Color(255, 255, 255)); // Bright center
    } else {
      strip.setPixelColor(i, dimColor(strip.Color(50, 50, 50), 20)); // Dim outer LEDs
    }
  }
  strip.show();
  delay(1000);
}

// --- EFFECT 4: Fluctuating Vision ---
void fluctuatingVisionEffect() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (random(0, 2) == 1) {
      strip.setPixelColor(i, strip.Color(255, 255, 255)); // Bright flash
    } else {
      strip.setPixelColor(i, dimColor(strip.Color(50, 50, 50), random(50))); // Dim flicker
    }
  }
  strip.show();
  delay(500);
}

// --- Utility Function: Dim a color by a percentage ---
uint32_t dimColor(uint32_t color, uint8_t brightness) {
  uint8_t r = (uint8_t)(color >> 16);
  uint8_t g = (uint8_t)(color >> 8);
  uint8_t b = (uint8_t)(color);
  r = (r * brightness) / 255;
  g = (g * brightness) / 255;
  b = (b * brightness) / 255;
  return strip.Color(r, g, b);
}

// --- Utility Function: Fade all LEDs to black ---
void fadeToBlack(int fadeValue) {
  for (int i = 0; i < NUM_LEDS; i++) {
    uint32_t color = strip.getPixelColor(i);
    strip.setPixelColor(i, dimColor(color, fadeValue));
  }
  strip.show();
  delay(50);
}
