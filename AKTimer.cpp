#include "AKTimer.h"

AKTimer::AKTimer(std::function<void(AKTimer*)> c, int time) {
	callback = c;
	length = time;
	ticks = 0;
	paused = false;
	destroyed = false;
	type = ATTIMER;
}

void AKTimer::update(float delta) {
	if (ticks == length) {
		pause();
		callback(this);
	}

	ticks++;
}