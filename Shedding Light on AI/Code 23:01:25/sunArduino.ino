//Chris Corner
//
//23.01.25

/*
The Eternal Dance of Light
In the quiet embrace of a celestial sphere, there existed a world where the sun danced an eternal waltz with the skies. 
This sun, a solitary beacon of golden radiance, moved with purpose—its journey carving time into the fabric of this miniature universe. 
The NeoCircle, as the inhabitants called it, was a ring of life and colour, where each LED held a piece of the story, and the sun was its ever-watchful guardian.
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Pin configuration and number of NeoPixels
#define LED_PIN    2
#define NUMPIXELS 24

int number;

Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 750 // Delay between updates

// Function to determine if a pixel is in the sunny hemisphere
bool isInSunnyHemisphere(int pixelIndex, int sunPosition) {
  if (sunPosition < NUMPIXELS / 2) {
    // Northern hemisphere is sunny
    return pixelIndex < NUMPIXELS / 2;
  } else {
    // Southern hemisphere is sunny
    return pixelIndex >= NUMPIXELS / 2;
  }
}

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  pixels.begin(); // Initialize NeoPixel strip
  pixels.setBrightness(30); // Adjust brightness
}

void loop() {
  for (number = 0; number < NUMPIXELS; number++) {
    pixels.clear();

    // Sky colors
    for (int i = 0; i < NUMPIXELS; i++) {
      if (isInSunnyHemisphere(i, number)) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 250)); // Light blue for sunny side
      } else {
        pixels.setPixelColor(i, pixels.Color(140, 0, 139)); // Dark purple for dark side
      }
    }

    // Sunrise effect (LEDs 0, 1, 2)
    if (number <= 4) { // Sunrise fades out after LED 4
      int fadeFactor = map(number, 0, NUMPIXELS / 4, 255, 0); // Fade from bright to off
      if (number != 0) pixels.setPixelColor(0, pixels.Color((255 * fadeFactor) / 255, (100 * fadeFactor) / 255, (150 * fadeFactor) / 255));
      if (number != 1) pixels.setPixelColor(1, pixels.Color((255 * fadeFactor) / 255, (100 * fadeFactor) / 255, (150 * fadeFactor) / 255));
      if (number != 2) pixels.setPixelColor(2, pixels.Color((255 * fadeFactor) / 255, (100 * fadeFactor) / 255, (150 * fadeFactor) / 255));
    }

    // Sunset effect (LEDs 12, 10, 11)
    if (number >= NUMPIXELS / 2 && number <= (NUMPIXELS / 2 + NUMPIXELS / 4)) { // Sunset fades out after LED 18
      int fadeFactor = map(number, NUMPIXELS / 2, NUMPIXELS / 2 + NUMPIXELS / 4, 255, 0); // Fade from bright to off
      if (number != 12) pixels.setPixelColor(12, pixels.Color((255 * fadeFactor) / 255, (150 * fadeFactor) / 255, 0));
      if (number != 10) pixels.setPixelColor(10, pixels.Color((255 * fadeFactor) / 255, (150 * fadeFactor) / 255, 0));
      if (number != 11) pixels.setPixelColor(11, pixels.Color((255 * fadeFactor) / 255, (150 * fadeFactor) / 255, 0));
    }

    // Sunrise effect (LEDs 13, 14, 15)
    if (number >= 13 && number < 16) { // Sunrise fades out after LED 18
      int fadeFactor = map(number, 13, 18, 255, 0); // Fade from bright to off
      if (number != 13) pixels.setPixelColor(13, pixels.Color((255 * fadeFactor) / 255, (100 * fadeFactor) / 255, (150 * fadeFactor) / 255));
      if (number != 14) pixels.setPixelColor(14, pixels.Color((255 * fadeFactor) / 255, (100 * fadeFactor) / 255, (150 * fadeFactor) / 255));
      if (number != 15) pixels.setPixelColor(15, pixels.Color((255 * fadeFactor) / 255, (100 * fadeFactor) / 255, (150 * fadeFactor) / 255));
    }

    // Sunset effect (LEDs 22, 23, 24)
    if (number >= 22 || number < 1) { // Sunset fades out after LED 3
      int fadeFactor = (number >= 22) ? map(number, 22, 27, 255, 0) : map(number + 24, 22, 27, 255, 0); // Handle wraparound
      if (number != 22) pixels.setPixelColor(22, pixels.Color((255 * fadeFactor) / 255, (150 * fadeFactor) / 255, 0));
      if (number != 23) pixels.setPixelColor(23, pixels.Color((255 * fadeFactor) / 255, (150 * fadeFactor) / 255, 0));
      if (number != 24) pixels.setPixelColor(24 % NUMPIXELS, pixels.Color((255 * fadeFactor) / 255, (150 * fadeFactor) / 255, 0));
    }

    // Sun: single LED overrides other effects
    pixels.setPixelColor(number, pixels.Color(210, 210, 0)); // Bright yellow sun

    pixels.show();
    delay(DELAYVAL);
  }
}
