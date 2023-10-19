#include "CCLabel.h"

#include "CCSpriteCache.h"

CCLabel::CCLabel(const char* lb) {
	type = ATSPRITE;
	opacity = 0.f;
	action_opacity = 1.f;
	label = lb;
	_font = GetFontDefault();
}
CCLabel::CCLabel(std::string lb) {
	type = ATSPRITE;
	opacity = 0.f;
	action_opacity = 1.f;
	label = lb.c_str();
	_font = GetFontDefault();
}

void CCLabel::draw() {
	float defaultFontSize = (float)_font.baseSize;
	float fontSize = getScale() * defaultFontSize * 3.f;
	float spacing = fontSize / defaultFontSize * 1.f;

	Color c = col;
	c.a *= getOpacity();

	DrawTextPro(_font, label, getPosition(), {0.f, 0.f}, getRotation(), fontSize, spacing, c);
}

const char* CCLabel::getText() {
	return label;
}
void CCLabel::setText(const char* t) {
	label = t;
}

void CCLabel::setFont(Font fnt) {
	_font = fnt;
}