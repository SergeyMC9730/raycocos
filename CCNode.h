#pragma once

#include "AKSchedulable.h"

#include <vector>

#include "raylib/src/raylib.h"

class CCNode : public AKSchedulable {
protected:
	std::vector<CCNode*> children;
	std::vector<AKSchedulable*> actions;

	Vector2 position;
	float scale;
	float rotation;
	float opacity; // from 0 to 1

	Vector2 action_position;
	float action_scale;
	float action_rotation;
	float action_opacity; // from 0 to 1
public:
	CCNode();

	virtual void addChild(CCNode* child);
	virtual void runAction(AKSchedulable* action);

	virtual std::vector<CCNode*> getChildren();

	virtual void update(float delta) override;

	virtual void draw();

	virtual void setPosition(Vector2 pos);
	virtual void setScale(float s);
	virtual void setRotation(float rt);
	virtual void setOpacity(float op);

	virtual Vector2 getPosition();
	virtual float getScale();
	virtual float getRotation();
	virtual float getOpacity();
};