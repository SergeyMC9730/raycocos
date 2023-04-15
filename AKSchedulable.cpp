#include "AKSchedulable.h"

void AKSchedulable::update(float update) {}

void AKSchedulable::pause() {
	paused = true;
}
void AKSchedulable::unpause() {
	paused = false;
}
void AKSchedulable::destroy() {
	destroyed = true;
}
void AKSchedulable::destroy(std::function<void(void)> onSuccess) {
	destroy();
	onSuccessCallback = onSuccess;
}

bool AKSchedulable::isPaused() {
	return paused;
}
bool AKSchedulable::isDestroyed() {
	return destroyed;
}

AKType AKSchedulable::getType() {
	return type;
}

AKSchedulable::AKSchedulable() {
	paused = false;
	destroyed = false;
	parent = nullptr;
	type = ATSCHEDULABLE;
	this->onSuccessCallback = [&]() {};
}
AKSchedulable::~AKSchedulable() {
	onSuccessCallback();
}

void AKSchedulable::setParent(AKSchedulable* p) {
	parent = p;
}
AKSchedulable* AKSchedulable::getParent() {
	return parent;
}