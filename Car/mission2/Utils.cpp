#include "Utils.h"

static void doSecondDelay(int ms);

void doSecondDelay(int ms) {
	volatile int sum = 0;
	for (int j = 0; j < 1000; j++) {
		for (int t = 0; t < ms; t++) {
			sum++;
		}
	}
}

void delay(int ms) {
	for (int i = 0; i < 1000; i++) {
		doSecondDelay(ms);
	}
}