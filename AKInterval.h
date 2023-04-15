#pragma once

#include "AKSchedulable.h"

#include <functional>

class AKInterval : public AKSchedulable {
protected:
	std::function<void(AKInterval*)> callback;
	int interval;
	int ticks;
public:
	AKInterval(std::function<void(AKInterval*)> c, int i);

	void update(float delta) override;
};