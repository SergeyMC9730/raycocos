#pragma once

#include "AKType.h"

#include <functional>

class AKSchedulable {
protected:
	bool paused;
	bool destroyed;

	AKType type;

	AKSchedulable* parent;

	std::function<void()> onSuccessCallback;
public:
	AKSchedulable();
	~AKSchedulable();

	std::vector<void*> object_container;

	virtual void update(float delta);
		
	virtual void pause();
	virtual void unpause();
	virtual void destroy(std::function<void(void)> onSuccess);
	virtual void destroy();

	virtual bool isPaused();
	virtual bool isDestroyed();

	virtual AKType getType();

	virtual void setParent(AKSchedulable* p);
	virtual AKSchedulable* getParent();
};