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

bool ligado = true;
void loop() {
	Rgbw64Color cor(Rgbw64Color::Max, Rgbw64Color::Max, Rgbw64Color::Max, Rgbw64Color::Max);
	Rgbw64Color cor2(0, 0, 0, 0);

	for (int a=0; a<PixelCount; a++) {
		strip.SetPixelColor(a, ligado ? cor : cor2);
	}
	strip.Show();
	digitalWrite(13, ligado ? HIGH : LOW);
	delay(500);
	ligado = !ligado;
}

void old() {
	float tempo = (double)millis() * mult;

	for (uint16_t a=0; a<PixelCount; a++) {

	// for (uint16_t a=0; a<NUMPIXELS; a++) {
		float t { tempo + (float)a * 0.1 };
        float tr { t + twopi*.66 };
		tr = std::fmod(tr, twopi);
		// float seno = std::sin(tr) * Rgbw64Color::Max*.5f + Rgbw64Color::Max*.5f;
		// uint16_t v = static_cast<uint16_t>(constrain(seno, 0, 65535));

		// Rgbw64Color cor(v, v, v, v);
		// strip.SetPixelColor(a, cor);
		// uint8_t v = static_cast<uint8_t>(constrain(seno, 0, 255));
		// v = Adafruit_NeoPixel::gamma8(v);
		// pixels.setPixelColor(a, pixels.Color(v,v,v));
		// pixels2.setPixelColor(a, pixels.Color(v,v,v));
	}
 	// strip.Show();
	delay(22);
	// for (uint16_t a=50; a<NUMPIXELS; a++) {
	// 	uint8_t v = 255;
	// 	pixels.setPixelColor(a, pixels.Color(v,v,v));
	// 	pixels2.setPixelColor(a, pixels.Color(v,v,v));
	// }

	// pixels.show();
}

