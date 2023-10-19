#include "Easing.h"

#include <cmath>

#ifndef PI
#define PI 3.14159265358979323846
#endif

float Easings::update_outSine(float x) {
	return sin((x * PI) / 2);
}
float Easings::update_linear(float x) {
	return 1.f - x;
}
float Easings::update_inSine(float x) {
	return 1 - cos((x * PI) / 2);
}
float Easings::update_inOutSine(float x) {
	return -(cos(PI * x) - 1) / 2;
}
float Easings::update_inQuad(float x) {
	return x * x;
}
float Easings::update_outQuad(float x) {
	return 1.f - (1.f - x) * (1.f - x);
}
float Easings::update_inOutQuad(float x) {
	return x < 0.5f ? 2.f * x * x : 1 - pow(-2.f * x + 2.f, 2.f) / 2.f;
}
float Easings::update_inCubic(float x) {
	return x * x * x;
}
float Easings::update_outCubic(float x) {
	return 1.f - pow(1.f - x, 3.f);
}
float Easings::update_inOutCubic(float x) {
	return x < 0.5f ? 4.f * x * x * x : 1.f - pow(-2.f * x + 2.f, 3.f) / 2.f;
}
float Easings::update_inQuart(float x) {
	return x * x * x * x;
}
float Easings::update_outQuart(float x) {
	return 1.f - pow(1.f - x, 4.f);
}
float Easings::update_inOutQuart(float x) {
	return x < 0.5f ? 8.f * x * x * x * x : 1.f - pow(-2.f * x + 2.f, 4.f) / 2.f;
}
float Easings::update_inQuint(float x) {
	return x * x * x * x * x;
}
float Easings::update_outQuint(float x) {
	return 1.f - pow(1.f - x, 5.f);
}
float Easings::update_inOutQuint(float x) {
	return x < 0.5f ? 16.f * x * x * x * x * x : 1.f - pow(-2.f * x + 2.f, 5.f) / 2;
}
float Easings::update_inExpo(float x) {
	return x == 0.f ? 0.f : pow(2.f, 10.f * x - 10.f);
}
float Easings::update_outExpo(float x) {
	return x == 1.f ? 1.f : 1.f - pow(2.f, -10.f * x);
}
float Easings::update_inOutExpo(float x) {
	return x == 0.f ? 0.f : x == 1.f ? 1.f : x < 0.5f ? pow(2.f, 20.f * x - 10.f) / 2.f : (2.f - pow(2.f, -20.f * x + 10.f)) / 2.f;
}
float Easings::update_inCirc(float x) {
	return 1.f - sqrt(1.f - pow(x, 2.f));
}
float Easings::update_outCirc(float x) {
	return sqrt(1.f - pow(x - 1.f, 2.f));
}
float Easings::update_inOutCirc(float x) {
	return x < 0.5f ? (1.f - sqrt(1.f - pow(2.f * x, 2.f))) / 2.f : (sqrt(1.f - pow(-2.f * x + 2.f, 2.f)) + 1.f) / 2.f;
}
float Easings::update_inBack(float x) {
	float c1 = 1.70158f;
	float c3 = c1 + 1.f;

	return c3 * x * x * x - c1 * x * x;
}
float Easings::update_outBack(float x) {
	float c1 = 1.70158f;
	float c3 = c1 + 1.f;

	return 1.f + c3 * pow(x - 1.f, 3.f) + c1 * pow(x - 1.f, 2.f);
}
float Easings::update_inOutBack(float x) {
	float c1 = 1.70158f;
	float c2 = c1 * 1.525f;
	float c3 = c1 + 1.f;

	return x < 0.5f ? (pow(2.f * x, 2.f) * ((c2 + 1.f) * 2.f * x - c2)) / 2.f : (pow(2.f * x - 2.f, 2.f) * ((c2 + 1.f) * (x * 2.f - 2.f) + c2) + 2.f) / 2.f;
}
float Easings::update_inElastic(float x) {
	float c4 = (2.f * PI) / 3.f;

	return x == 0.f ? 0.f : x == 1.f ? 1.f : -pow(2.f, 10.f * x - 10.f) * sin((x * 10.f - 10.75f) * c4);
}
float Easings::update_outElastic(float x) {
	float c4 = (2.f * PI) / 3.f;

	return x == 0.f ? 0.f : x == 1.f ? 1.f : pow(2.f, -10.f * x) * sin((x * 10.f - 0.75f) * c4) + 1.f;
}

float Easings::update_inOutElastic(float x) {
	float c5 = (2.f * PI) / 4.5f;

	return x == 0.f ? 0.f : x == 1.f ? 1.f : x < 0.5f ? -(pow(2.f, 20.f * x - 10.f) * sin((20.f * x - 11.125f) * c5)) / 2.f : (pow(2.f, -20.f * x + 10.f) * sin((20.f * x - 11.125f) * c5)) / 2.f + 1.f;
}
float Easings::update_inBounce(float x) {
	return 1.f - update_outBounce(1.f - x);
}
float Easings::update_outBounce(float x) {
	float n1 = 7.5625f;
	float d1 = 2.75f;

	if (x < 1.f / d1) {
		return n1 * x * x;
	}
	else if (x < 2.f / d1) {
		return n1 * (x - (1.5f / d1)) * x + 0.75f;
	}
	else if (x < 2.5f / d1) {
		return n1 * (x - (2.25f / d1)) * x + 0.9375f;
	}
	else {
		return n1 * (x - (2.625f / d1)) * x + 0.984375f;
	}
}
float Easings::update_inOutBounce(float x) {
	return x < 0.5f ? (1.f - update_outBounce(1.f - 2.f * x)) / 2.f : (1.f + update_inBounce(2.f * x - 1.f)) / 2.f;
}