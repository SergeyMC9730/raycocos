#pragma once

#include "AKSchedulable.h"

#include <functional>

// AKOpacityChange is destroyed after completing by default.
class AKOpacityChange : public AKSchedulable {
protected:
	float from;
	float to;
	int time;
	float opacity;
	int time_passed;
	std::function<void(AKOpacityChange*)> onEndCallback;
public:
	AKOpacityChange(float a, float b, int t);
	AKOpacityChange(float a, float b, int t, std::function<void(AKOpacityChange *)> onEnd);

	void update(float delta) override;
	virtual float getOpacity();
};