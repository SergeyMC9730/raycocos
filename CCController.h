#pragma once

#include "AnimationTimeline.h"

namespace CCController {
	extern AnimationTimeline* timeline;
	void init();
	int secondsToFrames(float sec, float delta);
}