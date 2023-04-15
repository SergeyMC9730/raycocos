#pragma once

#include "AKSchedulable.h"

#include <functional>

class AKTimer : public AKSchedulable {
protected:
	std::function<void(AKTimer*)> callback;

	int length;
	int ticks;
public:
	AKTimer(std::function<void(AKTimer*)> c, int time);
	
	void update(float delta) override;
};