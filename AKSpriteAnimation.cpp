#include "AKSpriteAnimation.h"

#include "CCNode.h"

#include <vector>

using namespace Easings;

namespace AKSpriteAnimationEasings {
	std::vector<std::function<float(float)>> vect = {
		update_linear, update_inSine, update_outSine, update_inOutSine,
		update_inQuad, update_outQuad, update_inOutQuad, update_inCubic,
		update_outCubic, update_inOutCubic, update_inQuart, update_outQuart,
		update_inOutQuart, update_inQuint, update_outQuint, update_inOutQuint,
		update_inExpo, update_outExpo, update_inOutExpo, update_inCirc,
		update_outCirc, update_inOutCirc, update_inBack, update_outBack,
		update_inOutBack, update_inElastic, update_outElastic, update_inOutElastic,
		update_inBounce, update_outBounce, update_inOutBounce
	};
}

AKSpriteAnimation::AKSpriteAnimation(int l) {
	length = l;
	current_frame = 0;

	paused = false;
	destroyed = false;

	easing = E_LINEAR;

	callbackSet = false;

	type = ATSPRITEANIMATION;

	if (length == 0) length = 1;

	scaleStart = 0.f;
	scaleEnd = 0.f;
	scale = 0.f;
	posStart = { 0.f, 0.f };
	posEnd = { 0.f, 0.f };
	pos = posStart;
	rotationStart = 0.f;
	rotationEnd = 0.f;
	rotation = 0.f;

	parent = nullptr;

	callback = [&](AKSpriteAnimation* self) {
		self->destroy();
	};
	callbackSet = true;
}

AKSpriteAnimation::AKSpriteAnimation(int l, Easing e) {
	length = l;
	current_frame = 0;

	paused = false;
	destroyed = false;

	callbackSet = false;

	easing = e;

	type = ATSPRITEANIMATION;

	if (length == 0) length = 1;

	scaleStart = 0.f;
	scaleEnd = 0.f;
	scale = 0.f;
	posStart = { 0.f, 0.f };
	posEnd = { 0.f, 0.f };
	pos = posStart;
	rotationStart = 0.f;
	rotationEnd = 0.f;
	rotation = 0.f;

	parent = nullptr;

	callback = [&](AKSpriteAnimation* self) {
		self->destroy();
	};
	callbackSet = true;
}

Vector2 AKSpriteAnimation::getPosition() {
	return pos;
}
float AKSpriteAnimation::getScale() {
	return scale;
}
float AKSpriteAnimation::getRotation() {
	return rotation;
}

void AKSpriteAnimation::update(float delta) {
	if (current_frame == length) {
		pause();
		if(callbackSet) callback(this);
		return;
	}

	float normalized = (float)current_frame / (float)length;
	float x;
	
	if (easing >= AKSpriteAnimationEasings::vect.size() || easing < 0) easing = E_LINEAR;
	x = AKSpriteAnimationEasings::vect[easing](normalized);

	pos.x = posEnd.x * x;
	pos.y = posEnd.y * x;
	scale = scaleEnd * x;
	rotation = rotationEnd * x;

	// if (posEnd.x < 1.f) pos.x = -pos.x;
	// if (posEnd.y < 1.f) pos.y = -pos.y;
	// if (scale < 1.f) scale = -scale;
	// if (rotation < 1.f) rotation = -rotation;

	current_frame++;
}

void AKSpriteAnimation::setStartPosition(Vector2 p) {
	pos = p;
	posStart = p;
}
void AKSpriteAnimation::setFinalPosition(Vector2 p) {
	posEnd = p;
}

void AKSpriteAnimation::setStartScale(float s) {
	scale = s;
	scaleStart = s;
}
void AKSpriteAnimation::setFinalScale(float s) {
	scaleEnd = s;
}

void AKSpriteAnimation::setStartRotation(float r) {
	rotation = r;
	rotationStart = r;
}
void AKSpriteAnimation::setFinalRotation(float r) {
	rotationEnd = r;
}

void AKSpriteAnimation::reset() {
	current_frame = 0;
	paused = false;
	destroyed = false;
	pos = posStart;
	scale = scaleStart;
}

void AKSpriteAnimation::setCallback(std::function<void(AKSpriteAnimation*)> c) {
	callback = c;
	callbackSet = true;
}