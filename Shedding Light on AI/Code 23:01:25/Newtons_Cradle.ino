//Michal Cholerzynski
//
//23.01.25

#include <Adafruit_NeoPixel.h>

#define PIN            2      // Pin to which the LED ring is connected
#define NUM_LEDS      24     // Number of LEDs in the ring
#define BRIGHTNESS    50     // Brightness level (0-255)

Adafruit_NeoPixel ring(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  ring.begin();
  ring.setBrightness(BRIGHTNESS);
  ring.show();
}

void loop() {
  // Variables to track the position of the two moving pixels
  int leftPos = 0;    // Left-moving pixel starting at the first position
  int rightPos = NUM_LEDS - 1;  // Right-moving pixel starting at the last position
  
  // Move towards each other with rainbow effect
  while (leftPos < rightPos) {
    ring.clear();  // Clear the previous frame

    // Calculate the rainbow color for the left-moving pixel
    uint32_t leftColor = Wheel((leftPos * 255) / NUM_LEDS);  // Calculate color using HSV
    ring.setPixelColor(leftPos, leftColor);
    
    // Calculate the rainbow color for the right-moving pixel
    uint32_t rightColor = Wheel((rightPos * 255) / NUM_LEDS);  // Calculate color using HSV
    ring.setPixelColor(rightPos, rightColor);

    ring.show();  // Update the LED ring

    delay(50);  // Control the speed of the animation

    // Move the pixels: left one step to the right, right one step to the left
    leftPos++;
    rightPos--;
  }

  // Once the pixels meet, reverse the direction and move them back to their original positions
  while (leftPos > 0 && rightPos < NUM_LEDS - 1) {
    ring.clear();  // Clear the previous frame

    // Recalculate the rainbow color for the left-moving pixel
    uint32_t leftColor = Wheel((leftPos * 255) / NUM_LEDS);  // Calculate color using HSV
    ring.setPixelColor(leftPos, leftColor);
    
    // Recalculate the rainbow color for the right-moving pixel
    uint32_t rightColor = Wheel((rightPos * 255) / NUM_LEDS);  // Calculate color using HSV
    ring.setPixelColor(rightPos, rightColor);

    ring.show();  // Update the LED ring

    delay(50);  // Control the speed of the animation

    // Move the pixels back: left one step to the left, right one step to the right
    leftPos--;
    rightPos++;
  }

  // Pause before starting the next animation loop
  delay(0);  // Pause for a moment before starting over
}

// Function to generate a full RGB spectrum based on HSV color wheel
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  byte r, g, b;
  
  if (WheelPos < 85) {
    r = 255 - WheelPos * 3;
    g = 0;
    b = WheelPos * 3;
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    r = 0;
    g = WheelPos * 3;
    b = 255 - WheelPos * 3;
  } else {
    WheelPos -= 170;
    r = WheelPos * 3;
    g = 255 - WheelPos * 3;
    b = 0;
  }

  return ring.Color(r, g, b);  // Convert the r, g, b values into a packed 32-bit color
}
