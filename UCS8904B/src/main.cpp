#include <Arduino.h>

static const float twopi = PI * 2.0;
static const double mult = 0.1;

#include <NeoPixelBus.h>
const uint16_t PixelCount = 10;
const uint8_t PixelPin = 6;
NeoPixelBus<NeoRgbw64Feature, NeoWs2812xMethod> strip(PixelCount, PixelPin);

void setup() {
	strip.Begin();
	pinMode(13, OUTPUT);
}



void loop() {

	float maxValue = 28000.0f;
	for (int a=0; a<3; a++) {
		float r = std::sin(millis() * 0.002f  + a * 0.5f) * maxValue + maxValue;
		float g = std::sin(millis() * 0.0015f + a * 0.5f) * maxValue + maxValue;
		float b = std::sin(millis() * 0.001f  + a * 0.5f) * maxValue + maxValue;
		float w = std::sin(millis() * 0.0005f + a * 0.5f) * maxValue + maxValue;

		Rgbw64Color cor(
			static_cast<uint16_t>(r), 
			static_cast<uint16_t>(g),
			static_cast<uint16_t>(b),
			static_cast<uint16_t>(w)
		);
		strip.SetPixelColor(a, cor);

	}
	strip.Show();
}
