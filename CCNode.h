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
	Vector2 scaleXY;
	float action_rotation;
	float action_opacity; // from 0 to 1
	Vector2 anchorPoint;
	Vector2 contentSize;
public:
	CCNode();
	~CCNode();

	virtual void addChild(CCNode* child);
	virtual void runAction(AKSchedulable* action);

	virtual std::vector<CCNode*> getChildren();

	virtual void update(float delta) override;

	virtual void draw();

	virtual void setPosition(Vector2 pos);
	virtual void setPositionX(float x);
	virtual void setPositionY(float y);
	virtual void setScale(float s);
	virtual void setScaleX(float sX);
	virtual void setScaleY(float sY);
	virtual void setRotation(float rt);
	virtual void setOpacity(float op);
	virtual void setAnchorPoint(Vector2 anchor);
	virtual void setContentSize(Vector2 size);


	virtual Vector2 getPosition();
	virtual float getPositionX();
	virtual float getPositionY();
	virtual float getScale();
	virtual float getScaleX();
	virtual float getScaleY();
	virtual float getRotation();
	virtual float getOpacity();
	virtual Vector2 getAnchorPoint();
	virtual Vector2 getContentSize();
};