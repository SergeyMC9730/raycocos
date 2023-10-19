#pragma once

#include "CCNode.h"

#include "CCColorParameter.h"

#include <string>

class CCLabel : public CCNode, public CCColorParameter {
protected:
	const char* label;
	Font _font;
public:
	CCLabel(const char* label);
	CCLabel(std::string label);

	const char* getText();
	void setText(const char *t);

	void setFont(Font fnt);

	void draw() override;
};