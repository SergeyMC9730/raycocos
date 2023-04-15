#pragma once

#include "AKSchedulable.h"
#include "Easing.h"
#include <functional>
#include "raylib/src/raylib.h"

// AKSpriteAnimation is destroyed after completing by default.
class AKSpriteAnimation : public AKSchedulable {
protected:
	int length;
	int current_frame;

	Vector2 posStart;
	Vector2 posEnd;
	Vector2 pos;

	float scaleStart;
	float scaleEnd;
	float scale;

	float rotationStart;
	float rotationEnd;
	float rotation;

	Easing easing;

	std::function<void(AKSpriteAnimation*)> callback;
	bool callbackSet;
public:
	void update(float delta) override;

	virtual Vector2 getPosition();
	virtual float getScale();
	virtual float getRotation();

	virtual void setStartPosition(Vector2 p);
	virtual void setFinalPosition(Vector2 p);

	virtual void setStartScale(float s);
	virtual void setFinalScale(float s);

	virtual void setStartRotation(float r);
	virtual void setFinalRotation(float r);

	virtual void reset();

	virtual void setCallback(std::function<void(AKSpriteAnimation*)> c);

	AKSpriteAnimation(int l);
	AKSpriteAnimation(int l, Easing e);
};