#include "CCNode.h"

#include "AKSpriteAnimation.h"
#include "AKOpacityChange.h"
#include "AKTimer.h"
#include "AKInterval.h"
#include "CCSprite.h"
#include "CCBox.h"
#include "CCLabel.h"
void CCNode::addChild(CCNode* child) {
	child->setParent(this);
	children.push_back(child);
}
CCNode::~CCNode() {
	for (auto child : children) {
		delete child;
	}
	for (auto sched : actions) {
		delete sched;
	}
}
void CCNode::update(float delta) {
	float x = 0;
	float y = 0;
	float rt = 0;
	float sc = 0;
	float op = 0;

	action_position = { 0.f, 0.f };
	action_rotation = 0.f;
	action_scale = 0.f;

	for (auto child : children) {
		child->update(delta);
	}

	int i = 0;

	while (i < actions.size()) {
		actions[i]->setParent(this);

		float ind_x = 0;
		float ind_y = 0;
		float ind_rt = 0;
		float ind_sc = 0;
		float ind_op = 0;

		actions[i]->update(delta);
		switch (actions[i]->getType()) {
		case ATSPRITEANIMATION: {
			auto spranim = static_cast<AKSpriteAnimation*>(actions[i]);
			ind_x = spranim->getPosition().x;
			ind_y = spranim->getPosition().y;
			ind_rt = spranim->getRotation();
			ind_sc = spranim->getScale();
			break;
		}
		case ATOPACITYCHANGE: {
			auto opanim = static_cast<AKOpacityChange*>(actions[i]);
			ind_op = opanim->getOpacity();
		}
		default: {}
		}

		if (actions[i]->isDestroyed()) {
			position.x += ind_x;
			position.y += ind_y;
			rotation += ind_rt;
			scale += ind_sc;
			setOpacity(ind_op);

			x -= ind_x;
			y -= ind_y;
			rt -= ind_rt;
			sc -= ind_sc;
			op -= ind_op;

			// printf("destroyed object %X\n", actions[i]);

			delete actions[i];

			// switch (actions[i]->getType()) {
			// default:
			// case ATSCHEDULABLE: {
			// 	delete actions[i];
			// 	break;
			// }
			// case ATTIMER: {
			// 	auto ttt = static_cast<AKTimer*>(actions[i]);
			// 	delete ttt;
			// 	break;
			// }
			// case ATINTERVAL: {
			// 	auto ttt = static_cast<AKInterval*>(actions[i]);
			// 	delete ttt;
			// 	break;
			// }
			// case ATOPACITYCHANGE: {
			// 	auto ttt = static_cast<AKOpacityChange*>(actions[i]);
			// 	delete ttt;
			// 	break;
			// }
			// case ATSPRITEANIMATION: {
			// 	auto ttt = static_cast<AKSpriteAnimation*>(actions[i]);
			// 	delete ttt;
			// 	break;
			// }
			// case ATNODE: {
			// 	auto ttt = static_cast<CCNode*>(actions[i]);
			// 	delete ttt;
			// 	break;
			// }
			// case ATSPRITE: {
			// 	auto ttt = static_cast<CCSprite*>(actions[i]);
			// 	delete ttt;
			// 	break;
			// }
			// case ATLABEL: {
			// 	auto ttt = static_cast<CCLabel*>(actions[i]);
			// 	delete ttt;
			// 	break;
			// }
			// case ATBOX: {
			// 	auto ttt = static_cast<CCBox*>(actions[i]);
			// 	delete ttt;
			// 	break;
			// }
			// }

			actions.erase(actions.begin() + i);
		}

		x += ind_x;
		y += ind_y;
		rt += ind_rt;
		sc += ind_sc;
		op += ind_op;

		i++;
	}

	action_position.x = x;
	action_position.y = y;
	action_rotation = rt;
	action_scale = sc;
	action_opacity = op;

	//printf("ap: %f %f | p: %f %f\n", action_position.x, action_position.y, getPosition().x, getPosition().y);

	draw();
}

void CCNode::draw() {}

std::vector<CCNode*> CCNode::getChildren() {
	return children;
}

void CCNode::runAction(AKSchedulable* action) {
	action->setParent(this);
	actions.push_back(action);
}

void CCNode::setPosition(Vector2 pos) {
	position = pos;
}
void CCNode::setPositionX(float x) {
	position.x = x;
}
void CCNode::setPositionY(float y) {
	position.y = y;
}
void CCNode::setScale(float s) {
	scale = s;
}
void CCNode::setScaleX(float s) {
	scaleXY.x = s;
}
void CCNode::setScaleY(float s) {
	scaleXY.y = s;
}
void CCNode::setRotation(float rt) {
	rotation = rt;
}
void CCNode::setOpacity(float op) {
	if (op < 0.f) op = 0.f;
	if (op > 1.f) op = 1.f;
	opacity = op;
}
void CCNode::setContentSize(Vector2 cs) {
	contentSize = cs;
}

Vector2 CCNode::getPosition() {
	//printf("getPosition()\n");
	float parentX = 0;
	float parentY = 0;
	CCNode* parent_nd = (CCNode *)getParent();
	if (parent_nd != nullptr) {
		Vector2 vec2 = parent_nd->getPosition();
		parentX += vec2.x;
		parentY += vec2.y;
	}
	Vector2 vec1 = position;
	vec1.x += action_position.x + parentX;
	vec1.y += action_position.y + parentY;
	return vec1;
}

float CCNode::getPositionX() {
	return getPosition().x;
}
float CCNode::getPositionY() {
	return getPosition().y;
}
void CCNode::setAnchorPoint(Vector2 anchor) {
	anchorPoint = anchor;
}
float CCNode::getScale() {
	//printf("getScale()\n");
	float additional_scale = 1.f;

	CCNode* parent_nd = (CCNode*)getParent();
	if (parent_nd != nullptr) {
		additional_scale *= parent_nd->getScale();
	}

	float action_scale2 = 1.f;

	if (action_scale > 0.f) {
		action_scale2 = action_scale;
	}

	return scale * (action_scale2 * additional_scale);
}
float CCNode::getScaleX() {
	return scaleXY.x + action_scale;
}
float CCNode::getScaleY() {
	return scaleXY.y + action_scale;
}
float CCNode::getRotation() {
	//printf("getRotation()\n");
	float additional_rotation = 0.f;

	CCNode* parent_nd = (CCNode*)getParent();
	if (parent_nd != nullptr) {
		additional_rotation += parent_nd->getRotation();
	}

	return rotation + action_rotation + additional_rotation;
}
float CCNode::getOpacity() {
	float parent = 1.f;

	CCNode *parent_nd = (CCNode *)getParent();
	if (parent_nd != nullptr) {
		parent *= parent_nd->getOpacity();
	}

	// printf("opacity: %f\n", parent);

	float raw = action_opacity + opacity;
	if (raw < 0.f) raw = 0.f;
	if (raw < 1.f) return raw * parent;
	if (raw > 1.f) return 1.f / (raw * parent);
	return 1.f / (raw * parent);
}
Vector2 CCNode::getAnchorPoint() {
	float parent_x = 0.f;
	float parent_y = 0.f;

	CCNode *parent_nd = (CCNode *)getParent();
	if (parent_nd != nullptr) {
		auto cs = parent_nd->getAnchorPoint();

		parent_x += cs.x;
		parent_y += cs.y;
	}

	auto res_cs = anchorPoint;

	res_cs.x += parent_x;
	res_cs.y += parent_y;

	return res_cs;
}
Vector2 CCNode::getContentSize() {
	float parent_x = 0.f;
	float parent_y = 0.f;

	CCNode *parent_nd = (CCNode *)getParent();
	if (parent_nd != nullptr) {
		auto cs = parent_nd->getContentSize();

		parent_x += cs.x;
		parent_y += cs.y;
	}

	auto res_cs = contentSize;

	res_cs.x += parent_x;
	res_cs.y += parent_y;

	return contentSize;
}

CCNode::CCNode() {
	position = { 0.f, 0.f };
	scale = 1.f;
	rotation = 0.f;
	opacity = 1.f;
	action_opacity = 1.f;
	type = ATNODE;
	action_position = { 0.f, 0.f };
	action_rotation = 0.f;
	action_scale = 0.f;
	anchorPoint = { 0.f, 0.f };
	scaleXY = { 1.f, 1.f };
	contentSize = { 0.f, 0.f };
}