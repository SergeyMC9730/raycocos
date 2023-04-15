#pragma once

#include <vector>
#include "raylib/src/raylib.h"

#include "AKSchedulable.h"

class AnimationTimeline {
protected:
	std::vector<AKSchedulable*> keys;
public:
	virtual void addToTimeline(AKSchedulable* key);

	virtual void update(float delta);

	virtual int getSize();
};