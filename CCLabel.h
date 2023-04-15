#pragma once

#include "CCNode.h"

#include "CCColorParameter.h"

class CCLabel : public CCNode, public CCColorParameter {
protected:
	const char* label;
public:
	CCLabel(const char* label);

	const char* getText();
	void setText(const char *t);

	void draw() override;
};