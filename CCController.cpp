#include "CCController.h"

AnimationTimeline* CCController::timeline;

void CCController::init() {
	timeline = new AnimationTimeline();
}