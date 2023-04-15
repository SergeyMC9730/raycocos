#pragma once

#include "CCNode.h"

class CCLabel : public CCNode {
protected:
	const char* label;
	Color col;
public:
	CCLabel(const char* label);

	void setColor(Color c);
	Color getColor();

	const char* getText();
	void setText(const char *t);

	void draw() override;
};