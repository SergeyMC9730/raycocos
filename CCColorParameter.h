#pragma once

#include "raylib/src/raylib.h"

class CCColorParameter {
protected:
	Color col;
public:
	virtual void setColor(Color c);
	virtual Color getColor();
};