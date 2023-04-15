#include "CCLabel.h"

#include "CCSpriteCache.h"

CCLabel::CCLabel(const char* lb) {
	type = ATSPRITE;
	opacity = 0.f;
	action_opacity = 1.f;
	label = lb;
}

void CCLabel::draw() {
	int defaultFontSize = 10;
	int fontSize = getScale() * 30.f;
	int spacing = fontSize / defaultFontSize;

	Color c = col;
	c.a *= getOpacity();

	DrawTextPro(GetFontDefault(), label, getPosition(), {0.f, 0.f}, getRotation(), 30 * getScale(), spacing, c);
}

const char* CCLabel::getText() {
	return label;
}
void CCLabel::setText(const char* t) {
	label = t;
}