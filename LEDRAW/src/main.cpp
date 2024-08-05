#include <Arduino.h>

#if defined(__MK20DX256__) 
#pragma message "__MK20DX256__"
#endif

#pragma message "v114"

#define NUMPIXELS 3
const static int16_t pin = 7;

#define B16
#ifdef B16
	typedef uint16_t pixelType;
	pixelType startMask = 0x8000; 
	float maxValue = 28000.0f;
	uint16_t numChannelsPerPixel = 4;

#else
	typedef uint8_t pixelType;
	pixelType startMask = 0x80;
	float maxValue = 64.0f;
	uint16_t numChannelsPerPixel = 3;
#endif

pixelType * pixels;

// static constexpr uint32_t Cycles = F_CPU / 1840000;
static constexpr uint32_t Cycles = F_CPU / 800000;
static constexpr uint32_t CyclesT0h = Cycles * 1 / 4;
static constexpr uint32_t CyclesT1h = Cycles * 2 / 3;
// static constexpr uint32_t CyclesT0h = F_CPU / 4000000;
// static constexpr uint32_t CyclesT1h = F_CPU / 1250000;

uint32_t endTime;
uint16_t numStripChannels = numChannelsPerPixel * NUMPIXELS;

bool canShow() {
	uint32_t now = micros();
	if (endTime > now) {
		endTime = now;
	}
	// return (now - endTime) >= 300L;
	return (now - endTime) >= 1300L;
}

unsigned long nextJump;

void setup() {
	ARM_DEMCR |= ARM_DEMCR_TRCENA;
	ARM_DWT_CTRL |= ARM_DWT_CTRL_CYCCNTENA;
	free(pixels); 
	// numStripChannels = numChannelsPerPixel * NUMPIXELS; // 4 * 8 depois
	if ((pixels = (pixelType *)malloc(numStripChannels))) {
		(pixelType *)memset(pixels, 0x00, numStripChannels);
	}

	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	Serial.begin(115200);
}

void loopSeno() {
	for (int a=0; a<NUMPIXELS; a++) {
		float r = std::sin(millis() * 0.002f  + a * 0.5f) * maxValue + maxValue;
		float g = std::sin(millis() * 0.0015f + a * 0.5f) * maxValue + maxValue;
		float b = std::sin(millis() * 0.003f  + a * 0.5f) * maxValue + maxValue;
		float w = std::sin(millis() * 0.0025f + a * 0.5f) * maxValue + maxValue;
		pixels[a * numChannelsPerPixel + 0] = static_cast<pixelType>(r);
		pixels[a * numChannelsPerPixel + 1] = static_cast<pixelType>(g);
		pixels[a * numChannelsPerPixel + 2] = static_cast<pixelType>(b);
		// if (numChannelsPerPixel < 3) {
		pixels[a * numChannelsPerPixel + 3] = static_cast<pixelType>(w);
		// }

	}
}


void loop() {
	// if (millis() > nextJump) {
	// 	nextJump = millis() + 1000;
	// 	Serial.println(Cycles);
	// 	Serial.println(CyclesT0h);
	// 	Serial.println(CyclesT1h);
	// 	Serial.println("------");
	// }
	loopSeno();
	// for (int a=0; a<numChannelsPerPixel * NUMPIXELS; a++) {
	// 	pixels[a] = 0x00;
	// }

	// noInterrupts();
	while (!canShow())
	;

	pixelType *p = pixels;
	pixelType *end = p + numStripChannels;
	pixelType pix;
	pixelType mask;
	
	volatile uint8_t *set = portSetRegister(pin), *clr = portClearRegister(pin);
	uint32_t cyc;

	ARM_DEMCR |= ARM_DEMCR_TRCENA;
	ARM_DWT_CTRL |= ARM_DWT_CTRL_CYCCNTENA;

	cyc = ARM_DWT_CYCCNT + Cycles;
	while (p < end) {
		pix = *p++;
		for (mask = startMask; mask; mask >>= 1) {
			while (ARM_DWT_CYCCNT - cyc < Cycles)
			;
			cyc = ARM_DWT_CYCCNT;
			*set = 1;
			if (pix & mask) {
				while (ARM_DWT_CYCCNT - cyc < CyclesT1h)
				;
			} else {
				while (ARM_DWT_CYCCNT - cyc < CyclesT0h)
				;
			}
			*clr = 1;
		}
		// *p++;
	}
	while (ARM_DWT_CYCCNT - cyc < Cycles)
	;
	// interrupts();
	endTime = micros();
}
