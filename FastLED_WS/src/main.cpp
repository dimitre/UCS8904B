#include <FastLED.h>
#define NUM_LEDS 3
#define DATA_PIN 6
CRGB leds[NUM_LEDS];
 
void setup() { 
	FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds,NUM_LEDS);
	// FastLED.setBrightness(84);
}
 
void loopSeno() {
	float maxValue = 28000.0f;
	for (int a=0; a<3; a++) {
		float r = std::sin(millis() * 0.002f  + a * 0.5f) * maxValue + maxValue;
		float g = std::sin(millis() * 0.0015f + a * 0.5f) * maxValue + maxValue;
		float b = std::sin(millis() * 0.001f  + a * 0.5f) * maxValue + maxValue;
		float w = std::sin(millis() * 0.0005f + a * 0.5f) * maxValue + maxValue;
		uint16_t red16 = static_cast<uint16_t>(r);
		uint8_t r1 = red16 >> 8;
		uint8_t r2 = red16 & 0xFF;
		CRGB cor = CRGB(r1, r2, 0);
	}
}

void loop() { 
	loopSeno();
	FastLED.show(); 
	delay(10);
}