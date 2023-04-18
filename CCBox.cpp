#include "CCBox.h"
#include "CCColors.h"

CCBox::CCBox(Vector2 sz) {
	size = sz;
	type = ATBOX;
}

void CCBox::draw() {
	Vector2 size2 = size;
	float sc = getScale();
	size2.x *= sc;
	size2.y *= sc;

	Rectangle rec;
	auto pos = getPosition();
	rec.x = pos.x;
	rec.y = pos.y;
	rec.width = size2.x;
	rec.height = size2.y;

	auto op = getOpacity();

	Color c = col;
	c.a *= op;
	Color c2 = col;
	c2.r += 32;
	c2.g += 32;
	c2.b += 32;
	c2.a *= op;

	DrawRectangleGradientV(rec.x, rec.y, rec.width, rec.height, c, c2);

	//DrawRectanglePro(rec, getAnchorPoint(), getRotation(), c);

	c = CCColors::rainbow;
	c.a *= op;
	DrawRectangleLinesEx(rec, 2.f, c);
}