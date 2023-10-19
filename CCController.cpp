#include "CCController.h"

AnimationTimeline* CCController::timeline;

void CCController::init() {
	timeline = new AnimationTimeline();
}

int CCController::secondsToFrames(float sec, float delta) {
	return (int)((1.f / delta) * sec);
}