#include "AKInterval.h"

AKInterval::AKInterval(std::function<void(AKInterval*)> c, int i) {
	callback = c;
	interval = i;
	ticks = 0;
	paused = false;
	destroyed = false;
	type = ATINTERVAL;
}

void AKInterval::update(float delta) {
	if (ticks == interval) {
		callback(this);
		ticks = 0;
	}

	ticks++;
}