/**
 * PERPETUAL SNAKE
 * 
 * This NeoPixel display is likened on the 'Snake' game:
 * The (blue) snake eats the (green) food and grows bigger with each food pixel it consumes.
 * But as soon as the snake eats it's own tail (i.e., becomes as big as the whole NeoPixel),
 * it perishes.
 * 
 * The snake in this case will keep regenerating, it will go on as long as it has power.
 * 
 * We know we have limited resources and limited time.
 * Will we choose to go on until we eat our own tail, or is there a way out?
 * Will we get much warning before we run out of space?
 */

// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        2 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 24 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 100 // Time (in milliseconds) to pause between pixels

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}




void loop() {
  pixels.clear(); // Set all pixel colors to 'off'
  int head = 2;
  int tail = 0;
  int food = 15;
  int midpoint = (NUMPIXELS + head) / 2;
  bool x = true;

  while (x) {
    int litup_count = 0;
    if (head == food) {
      head++;
      if (((tail != 0) && (head == (tail -1))) or ((tail == 0) && (head == NUMPIXELS))) {
        pixels.clear();
        for (int j = 60; j > 0; j--) {
          for (int i = 0; i < NUMPIXELS; i++) {
            pixels.setPixelColor(i, 0, 0, j);
          }
          pixels.show();
          delay(100);
        }
        delay(1500);
        pixels.clear();
        for(int i=0; i<NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(5, 0, 0));
        }
        pixels.show();
        delay(500);
        for(int i=0; i<NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        }
        pixels.show();
        delay(500);
        for(int i=0; i<NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(5, 0, 0));
        }
        pixels.show();
        delay(500);
        for(int i=0; i<NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        }
        pixels.show();
        delay(500);
        for(int i=0; i<NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(5, 0, 0));
        }
        pixels.show();
        delay(500);

        for(int i=0; i<NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(0, 0, 20));
        }
        pixels.show();
        delay(100);
        for(int j=0; j<(midpoint-1); j++){
          pixels.setPixelColor(midpoint-j, pixels.Color(0, 0, 0));
          pixels.setPixelColor(midpoint+j, pixels.Color(0, 0, 0));
          pixels.show();
          delay(100);
        }
        head = 2;
        tail = 0;
        food = 15;
        x = false;
      }
      else {
        food = random(1, 22);
      }
    }
    pixels.setPixelColor(food, pixels.Color(0, 20, 0));
    litup_count++;
    if (head > NUMPIXELS) {
        head = 0;
      }
    if (tail > NUMPIXELS) {
      tail = 0;
    }
    if (tail > head) {
      for(int i=tail; i<NUMPIXELS; i++) { // For each pixel in our snake
        pixels.setPixelColor(i, pixels.Color(0, 0, 20));
        litup_count++;
        
      }
      for(int i=0; i<=head; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 20));
        litup_count++;
      }
      
      pixels.show();   // Send the updated pixel colors to the hardware.
    
      delay(DELAYVAL); // Pause before next pass through loop
      pixels.clear();
      head++;
      tail++;
    }
    if (head > tail) {
      for(int i=tail; i<head; i++) { // For each pixel in our snake
        pixels.setPixelColor(i, pixels.Color(0, 0, 20));
        litup_count++;
        
      }
      pixels.show();   // Send the updated pixel colors to the hardware.

      delay(DELAYVAL); // Pause before next pass through loop
      pixels.clear();
      head++;
      tail++;
    }
  }
}
