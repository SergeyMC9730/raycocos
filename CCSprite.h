#pragma once

#include "CCNode.h"

#include <string>

class CCSprite : public CCNode {
protected:
	Texture2D texture;
public:
	CCSprite(Texture2D tex);
	CCSprite(Image img);
	CCSprite(std::string filename);

	Texture2D getTexture();
	void setTexture(Texture2D texture);
	void setTexture(std::string filename);

	void draw() override;
};