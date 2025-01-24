#include <Adafruit_NeoPixel.h>

#define LED_PIN 2         // Pin connected to NeoPixel
#define NUM_LEDS 24       // Number of LEDs in the ring/strip

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// 🎨 Nemo Colors
uint32_t water = strip.Color(0, 0, 255);       // Deep blue ocean
uint32_t nemoOrange = strip.Color(255, 80, 0); // Bright orange
uint32_t nemoWhite = strip.Color(255, 255, 255); // White stripes
uint32_t black = strip.Color(0, 0, 0);         // Off (for tail flicker)
uint32_t talkColor = strip.Color(0, 255, 0);   // Green for when Nemo "talks"

int fishLength = 5;  // Nemo's size
int fishPos = 0;     // Nemo's position

void setup() {
  Serial.begin(9600);  // Start Serial for AI interactions
  strip.begin();
  strip.setBrightness(255); // Max brightness
  strip.show(); // Turn all LEDs off initially

  Serial.println("🐠 Nemo 2.0 AI Assistant Ready!");
  Serial.println("Type 'weather', 'joke', or 'hello' to talk to Nemo!");
}

void loop() {
  swimNemo();
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "weather") {
      tellWeather();
    } else if (command == "joke") {
      tellJoke();
    } else if (command == "hello") {
      greetUser();
    } else {
      Serial.println("🤖 Nemo: I don't understand that command! Try 'weather', 'joke', or 'hello'.");
    }
  }
  delay(80); // Speed of Nemo swimming
}

// 🐠 Make Nemo swim
void swimNemo() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, water); // Fill with water color
  }

  for (int i = 0; i < fishLength - 1; i++) {
    int pos = (fishPos + i) % NUM_LEDS;

    if (i == 1 || i == 3) {
      strip.setPixelColor(pos, nemoWhite);  // White stripes
    } else {
      strip.setPixelColor(pos, nemoOrange); // Orange body
    }
  }

  int tailPos = (fishPos + fishLength - 1) % NUM_LEDS;
  strip.setPixelColor(tailPos, millis() % 300 < 150 ? nemoOrange : black); // Flickering tail

  strip.show();
  fishPos = (fishPos + 1) % NUM_LEDS; // Move Nemo forward
}

// ☀️ Tell the weather
void tellWeather() {
  Serial.println("🤖 Nemo: Sunny with a high of 75! Perfect for a swim—uh, I mean, a walk!");
  animateTalking();
}

// 😂 Tell a joke
void tellJoke() {
  Serial.println("🤖 Nemo: Why don’t fish do well in school?");
  delay(1500);
  Serial.println("🤖 Nemo: Because they work below sea level! 😂");
  animateTalking();
}

// 👋 Greet the user
void greetUser() {
  Serial.println("🤖 Nemo: Hello there! I'm here to help, just like my dad once did for me!");
  animateTalking();
}

// 🎤 Animate Nemo "talking"
void animateTalking() {
  for (int i = 0; i < 5; i++) {
    strip.fill(talkColor); // Green when talking
    strip.show();
    delay(200);

    strip.fill(black); // Turn off LEDs briefly
    strip.show();
    delay(200);
  }
  strip.fill(water); // Restore ocean background
  strip.show();
}
