#pragma once

#include "CCNode.h"

class CCSprite : public CCNode {
protected:
	Texture2D texture;
public:
	CCSprite(Texture2D tex);
	CCSprite(const char* filename);

	void draw() override;
};