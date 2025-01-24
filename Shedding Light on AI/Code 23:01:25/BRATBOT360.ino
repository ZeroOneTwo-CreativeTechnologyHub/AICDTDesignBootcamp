//Faye Doughty
// 
//23.01.25

#include <Adafruit_NeoPixel.h>

#define LED_PIN 2
#define LED_COUNT 24
#define BRIGHTNESS 100  

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
bool chaosMode = false;  // So she doesn't hack the system CONSTANTLY

void setup() {
    Serial.begin(115200);  
    strip.begin();
    strip.setBrightness(BRIGHTNESS);
    strip.show();
    
    bratIntro();
    Serial.println("BRATBOT 360 BOOTING UP...");
    Serial.println("ASK ME SOMETHING WORTH MY TIME.");
}

void loop() {
    bratAI();  
    brat360Wave();  
    bratStrobe();   

    if (chaosMode) {  
        bratGlitchChaos();
        chaosMode = false;  
    }
}

// LED INTRO ANIMATION
void bratIntro() {
    for (int i = 0; i < LED_COUNT; i++) {
        strip.setPixelColor(i, strip.Color(255, 20, 147));  // Neon pink
        strip.show();
        delay(30);
    }
    strip.clear();
    strip.show();
}

// SERIAL MONITOR AI - NOW MORE C*NTY
void bratAI() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        input.trim();  

        Serial.print("YOU: ");
        Serial.println(input);

        if (input.equalsIgnoreCase("hi") || input.equalsIgnoreCase("hello")) {
            Serial.println("BRATBOT 360: That’s all you have to say? Be serious.");
        } 
        else if (input.equalsIgnoreCase("what should I do today?")) {
            Serial.println("BRATBOT 360: Go outside, touch grass, then slay.");
        } 
        else if (input.equalsIgnoreCase("are you real?")) {
            Serial.println("BRATBOT 360: More real than your bank account.");
        } 
        else if (input.equalsIgnoreCase("what’s your favorite color?")) {
            Serial.println("BRATBOT 360: Neon pink, cyber green, and the color of jealousy.");
        } 
        else if (input.equalsIgnoreCase("do you like Charli XCX?")) {
            Serial.println("BRATBOT 360: BABE, SHE CREATED ME.");
        } 
        else if (input.equalsIgnoreCase("sing a song")) {
            Serial.println("BRATBOT 360: ERROR - AUTOTUNE NOT INSTALLED.");
        } 
        else if (input.equalsIgnoreCase("slay")) {
            Serial.println("BRATBOT 360: No, YOU slay. I was built different.");
        }
        else if (input.equalsIgnoreCase("hack the system")) {
            Serial.println("BRATBOT 360: Fine. If you insist.");
            chaosMode = true;  // Enables ONE-TIME chaos
        }
        else {
            Serial.println("BRATBOT 360: That was so boring. Try again.");
        }

        Serial.println();  
    }
}

// 360° WAVE ANIMATION - NOW MORE DRAMATIC
void brat360Wave() {
    int colors[][3] = {
        {255, 20, 147},  // Neon Pink
        {57, 255, 20},   // Cyber Green
        {138, 43, 226}   // Electric Purple
    };

    for (int c = 0; c < 3; c++) {
        for (int i = 0; i < LED_COUNT; i++) {
            strip.clear();
            for (int j = 0; j < LED_COUNT; j++) {
                int index = (i + j) % LED_COUNT;
                int fade = 255 - (j * (255 / LED_COUNT));
                strip.setPixelColor(index, strip.Color(
                    (colors[c][0] * fade) / 255, 
                    (colors[c][1] * fade) / 255, 
                    (colors[c][2] * fade) / 255
                ));
            }
            strip.show();
            delay(20);
        }
    }
}

// STROBE EFFECT - SHORTER & SHARPER
void bratStrobe() {
    for (int i = 0; i < 3; i++) {  // Fewer flashes so she doesn't get annoying
        for (int j = 0; j < LED_COUNT; j++) {
            strip.setPixelColor(j, strip.Color(255, 255, 255));  
        }
        strip.show();
        delay(20);
        strip.clear();
        strip.show();
        delay(20);
    }
}

// GLITCH CHAOS MODE - ONLY ACTIVATES ON COMMAND
void bratGlitchChaos() {
    Serial.println("BRATBOT 360: SYSTEM OVERRIDE INITIATED.");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < LED_COUNT; j++) {
            strip.setPixelColor(j, strip.Color(random(50, 255), random(50, 255), random(50, 255)));
        }
        strip.show();
        delay(random(30, 100));
    }
    strip.clear();
    strip.show();
}
