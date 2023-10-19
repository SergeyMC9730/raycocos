#include "CCMessageBox.h"
#include "CCController.h"
#include "CCColors.h"
#include "CCBox.h"
#include "CCLabel.h"
#include "AKTimer.h"
#include "AKSpriteAnimation.h"
#include "AKOpacityChange.h"

int CCMessageBoxData::messages_sent = 0;

CCMessageBox::CCMessageBox(const char* msg) {
	message = msg;
}

void CCMessageBox::update(float delta) {
	destroy();

	auto messages_sent = &CCMessageBoxData::messages_sent;
	if (*messages_sent < 0) *messages_sent = 0;

	auto timeline = CCController::timeline;
	auto sz1 = MeasureTextEx(GetFontDefault(), message, 30, 3);
	auto offset = new Vector2;
	auto vec_p = new Vector2;

	offset->x = (*messages_sent * 10.f);
	sz1.x += 10.f;
	sz1.y += 10.f;
	vec_p->x = sz1.x;
	vec_p->y = sz1.y;

	auto box = new CCBox(sz1);
	auto label = new CCLabel(message);

	box->setColor(DARKGRAY);
	box->setPosition({ offset->x, -sz1.y });
	box->setOpacity(1.f);

	label->setOpacity(1.f);
	label->setColor(WHITE);
	label->setScale(0.9f);
	label->setPosition({ 10.f + offset->x, -sz1.y + 8.f });

	auto mov3 = new AKSpriteAnimation(CCController::secondsToFrames(0.5f, delta), E_OUTQUART);
	auto mov4 = new AKSpriteAnimation(CCController::secondsToFrames(0.5f, delta), E_OUTQUART);

	mov3->setFinalPosition({ 0.f, sz1.y });
	mov3->object_container.push_back(box);
	mov3->object_container.push_back(vec_p);
	mov3->object_container.push_back(offset);

	mov4->setFinalPosition({ 0.f, sz1.y });
	mov4->object_container.push_back(label);
	mov4->object_container.push_back(vec_p);
	mov4->object_container.push_back(offset);

	mov3->setCallback([&](AKSpriteAnimation* self) {
		CCNode* nd = static_cast<CCNode*>(self->object_container[0]);
		auto vec = reinterpret_cast<Vector2*>(self->object_container[1]);
		auto vec2 = reinterpret_cast<Vector2*>(self->object_container[2]);
		nd->setPosition({ vec2->x, -vec->y });
	});
	mov4->setCallback([&](AKSpriteAnimation* self) {
		CCNode* nd = static_cast<CCNode*>(self->object_container[0]);
		auto vec = reinterpret_cast<Vector2*>(self->object_container[1]);
		auto vec2 = reinterpret_cast<Vector2*>(self->object_container[2]);
		nd->setPosition({ vec2->x + 10.f, -vec->y + 8.f });
	});

    auto timer = new AKTimer([&](AKTimer* self) {
        self->destroy();

        CCNode* nd1 = static_cast<CCNode*>(self->object_container[0]);
        CCNode* nd2 = static_cast<CCNode*>(self->object_container[1]);
        auto vec = reinterpret_cast<Vector2*>(self->object_container[2]);
        auto ofs = reinterpret_cast<Vector2*>(self->object_container[3]);
        auto pmov3 = reinterpret_cast<AKSpriteAnimation*>(self->object_container[4]);
        auto pmov4 = reinterpret_cast<AKSpriteAnimation*>(self->object_container[5]);

        nd1->setOpacity(0.f);
        nd2->setOpacity(0.f);

        auto op1 = new AKOpacityChange(1.f, 0.f, CCController::secondsToFrames(0.5f, delta), [&](AKOpacityChange* self) {
            self->destroy();
            self->getParent()->destroy();
        });
        auto op2 = new AKOpacityChange(1.f, 0.f, CCController::secondsToFrames(0.5f, delta), [&](AKOpacityChange* self) {
            self->destroy();
            self->getParent()->destroy();
            auto messages_sent = &CCMessageBoxData::messages_sent;
            *messages_sent -= 1;
            auto pvec = reinterpret_cast<Vector2*>(self->object_container[0]);
            auto pofs = reinterpret_cast<Vector2*>(self->object_container[1]);
            auto ppmov3 = reinterpret_cast<AKSpriteAnimation*>(self->object_container[2]);
            auto ppmov4 = reinterpret_cast<AKSpriteAnimation*>(self->object_container[3]);;
            delete pvec;
            delete pofs;
            ppmov3->destroy();
            ppmov4->destroy();
        });

        op2->object_container.push_back(vec);
        op2->object_container.push_back(ofs);
        op2->object_container.push_back(pmov3);
        op2->object_container.push_back(pmov4);

        auto mov1 = new AKSpriteAnimation(CCController::secondsToFrames(0.5f, delta), E_INQUART);
        mov1->setFinalPosition({ 0.f, -vec->y });

        auto mov2 = new AKSpriteAnimation(CCController::secondsToFrames(0.5f, delta), E_INQUART);
        mov2->setFinalPosition({ 0.f, -vec->y });

        nd1->runAction(op1);
        nd2->runAction(op2);
        nd1->runAction(mov1);
        nd2->runAction(mov2);
    }, CCController::secondsToFrames(1.f, delta));

    timer->object_container.push_back(label);
    timer->object_container.push_back(box);
    timer->object_container.push_back(vec_p);
    timer->object_container.push_back(offset);
    timer->object_container.push_back(mov3);
    timer->object_container.push_back(mov4);

    timeline->addToTimeline(timer);

    box->runAction(mov3);
    label->runAction(mov4);

    timeline->addToTimeline(box);
    timeline->addToTimeline(label);;

    *messages_sent += 1;
}