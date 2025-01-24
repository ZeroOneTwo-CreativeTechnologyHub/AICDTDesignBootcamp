//Joella Lynch
//
//23/01/2025

#include <Adafruit_NeoPixel.h>

#define PIN 2          // Pin where the NeoPixel strip is connected
#define NUMPIXELS 24   // Number of LEDs in the strip

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int rabbitPosition = 0;     // Starting position of the rabbit
int turtlePosition = 0;     // Starting position of the turtle
bool rabbitIsResting = false;  // Whether the rabbit is resting
int raceSpeedTurtle = 1;    // Turtle moves 1 step per loop
int raceSpeedRabbit = 2;    // Rabbit moves 2 steps per loop initially (slower)

void setup() {
  strip.begin();
  strip.show();  // Initialize the strip
  randomSeed(analogRead(0));  // Seed the random number generator
}

void loop() {
  race();
}

void race() {
  // Clear previous positions
  strip.clear();

  // Draw the turtle (green)
  strip.setPixelColor(turtlePosition, strip.Color(0, 255, 0));

  // Draw the rabbit (brown)
  strip.setPixelColor(rabbitPosition, strip.Color(200, 55, 0));

  // Draw the pink finish line at the last LED (finish line)
  strip.setPixelColor(NUMPIXELS - 1, strip.Color(255, 105, 180)); // Pink color

  // Update the strip to show changes
  strip.show();
  delay(200);  // Longer delay to slow down the animation

  // Update race progress (turtle moves slowly, rabbit moves fast but pauses)
  if (!rabbitIsResting) {
    rabbitPosition += raceSpeedRabbit;  // Rabbit moves fast for 3/4 of the loop
  }

  // If the rabbit reaches 3/4 of the race, it stops (unless it wins)
  if (rabbitPosition >= NUMPIXELS * 0.75 && !rabbitIsResting) {
    rabbitIsResting = true;  // Rabbit rests for the rest of the loop, but check if it wins
  }

  // The turtle moves slowly but steadily
  turtlePosition += raceSpeedTurtle;

  // If the race finishes
  if (turtlePosition >= NUMPIXELS) {
    // Check if the rabbit wins randomly (2 out of 10 chance)
    bool rabbitWins = random(0, 10) < 4;  // 40% chance the rabbit wins

    if (rabbitWins) {
      // Rabbit wins, so it doesn't rest, just moves towards the finish line
      rabbitIsResting = false;
     
      // Keep moving the rabbit until it reaches the finish line
      while (rabbitPosition < NUMPIXELS - 1) {
        rabbitPosition += raceSpeedRabbit;  // Rabbit continues to move
        strip.clear();
        strip.setPixelColor(rabbitPosition, strip.Color(200, 55, 0));  // Update rabbit position
        strip.setPixelColor(turtlePosition, strip.Color(0, 255, 0));  // Update turtle position
        strip.setPixelColor(NUMPIXELS - 1, strip.Color(255, 105, 180));  // Finish line
        strip.show();
        delay(200);
      }

      // Display the winner (Rabbit)
      strip.setPixelColor(rabbitPosition, strip.Color(200, 55, 0));  // Final rabbit position
      strip.setPixelColor(NUMPIXELS - 1, strip.Color(255, 105, 180));  // Finish line (pink)
      strip.show();
      delay(1000);  // Display the winner for 1 second
    } else {
      // Turtle wins
      strip.clear();
      strip.setPixelColor(turtlePosition - 1, strip.Color(0, 255, 0));  // Final turtle position
      strip.setPixelColor(NUMPIXELS - 1, strip.Color(255, 105, 180));  // Finish line (pink)
      strip.show();
      delay(1000);  // Display the winner for 1 second
    }

    resetRace();  // Reset the race for a new round
  }

  // If the turtle reaches the last LED, the rabbit starts moving again
  if (turtlePosition >= NUMPIXELS * 0.9 && rabbitIsResting) {
    rabbitIsResting = false;  // Rabbit starts again once near finish
  }

  // Ensure positions stay within bounds (wrap around)
  rabbitPosition = rabbitPosition % NUMPIXELS;
  turtlePosition = turtlePosition % NUMPIXELS;
}

void resetRace() {
  // Reset positions and other race variables
  rabbitPosition = 0;
  turtlePosition = 0;
  rabbitIsResting = false;
}