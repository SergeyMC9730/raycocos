#include "AKOpacityChange.h"

AKOpacityChange::AKOpacityChange(float a, float b, int t) {
	if (a < 0.f) a = 0.f;
	if (a > 1.f) a = 1.f;
	if (b < 0.f) b = 0.f;
	if (b > 1.f) b = 1.f;
	if (t == 0) t = 1;
	from = a;
	to = b;
	opacity = from;
	time = t;
	type = ATOPACITYCHANGE;
	time_passed = 0;
	onEndCallback = [&](AKOpacityChange* self) {
		self->destroy();
	};
}
AKOpacityChange::AKOpacityChange(float a, float b, int t, std::function<void(AKOpacityChange*)> onEnd) {
	if (a < 0.f) a = 0.f;
	if (a > 1.f) a = 1.f;
	if (b < 0.f) b = 0.f;
	if (b > 1.f) b = 1.f;
	if (t == 0) t = 1;
	from = a;
	to = b;
	opacity = from;
	time = t;
	type = ATOPACITYCHANGE;
	time_passed = 0;
	onEndCallback = onEnd;
}

void AKOpacityChange::update(float delta) {
	if (time_passed == time) {
		opacity = to;
		pause();
		onEndCallback(this);
		return;
	}

	float normalized = (float)time_passed / (float)time;
	if (to == 0.f) {
		opacity = 1.f - normalized;
	}
	else {
		opacity = to * normalized;
	}

	time_passed++;
}

float AKOpacityChange::getOpacity() {
	return opacity;
}