#pragma once

#include "CCNode.h"
#include "CCColorParameter.h"

class CCBox : public CCNode, public CCColorParameter {
protected:
	Vector2 size;
public:
	CCBox(Vector2 sz);

	void draw() override;
};