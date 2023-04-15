#include "CCBox.h"

CCBox::CCBox(Vector2 sz) {
	size = sz;
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

	Color c = col;
	c.a *= getOpacity();

	DrawRectanglePro(rec, getAnchorPoint(), getRotation(), c);

	c = WHITE;
	c.a *= getOpacity();
	DrawRectangleLinesEx(rec, 2.f, c);
}