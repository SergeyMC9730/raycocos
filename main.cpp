#include  "raylib/src/raylib.h"

#include "CCController.h"
#include "AKSpriteAnimation.h"
#include "AKOpacityChange.h"
#include "AKTimer.h"
#include "AKInterval.h"

#include "CCSprite.h"
#include "CCLabel.h"

#include "CCBox.h"

using namespace std;

int messages_sent = 0;

void create_message(const char* msg) {
    if (messages_sent < 0) messages_sent = 0;

    auto timeline = CCController::timeline;
    auto sz1 = MeasureTextEx(GetFontDefault(), msg, 30, 3);

    auto offset = new Vector2;
    offset->x = (messages_sent * 10.f);

    auto vec_p = new Vector2;

    sz1.x += 10.f;
    sz1.y += 10.f;

    auto box = new CCBox(sz1);
    box->setColor(DARKBROWN);
    box->setPosition({ 0.f + (messages_sent * 10.f), -sz1.y });
    box->setOpacity(1.f);
    auto label = new CCLabel(msg);
    label->setOpacity(1.f);
    label->setColor(WHITE);
    label->setScale(0.9f);
    //label->addChild(box);
    label->setPosition({ 10.f + (messages_sent * 10.f), -sz1.y + 8.f });

    vec_p->x = sz1.x;
    vec_p->y = sz1.y;

    auto mov3 = new AKSpriteAnimation(GetMonitorRefreshRate(0) / 1.5f, E_OUTQUART);
    mov3->setFinalPosition({ 0.f, sz1.y });

    auto mov4 = new AKSpriteAnimation(GetMonitorRefreshRate(0) / 1.5f, E_OUTQUART);
    mov4->setFinalPosition({ 0.f, sz1.y });

    mov3->object_container.push_back(box);
    mov3->object_container.push_back(vec_p);
    mov3->object_container.push_back(offset);
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

        auto op1 = new AKOpacityChange(1.f, 0.f, GetMonitorRefreshRate(0), [&](AKOpacityChange* self) {
            self->destroy();
            self->getParent()->destroy();
        });
        auto op2 = new AKOpacityChange(1.f, 0.f, GetMonitorRefreshRate(0), [&](AKOpacityChange* self) {
            self->destroy();
            self->getParent()->destroy();
            messages_sent--;
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

        auto mov1 = new AKSpriteAnimation(GetMonitorRefreshRate(0), E_INQUART);
        mov1->setFinalPosition({ 0.f, -vec->y });

        auto mov2 = new AKSpriteAnimation(GetMonitorRefreshRate(0), E_INQUART);
        mov2->setFinalPosition({ 0.f, -vec->y });

        nd1->runAction(op1);
        nd2->runAction(op2);
        nd1->runAction(mov1);
        nd2->runAction(mov2);
    }, GetMonitorRefreshRate(0));

    timer->object_container.push_back(label);
    timer->object_container.push_back(box);
    timer->object_container.push_back(vec_p);
    timer->object_container.push_back(offset);
    timer->object_container.push_back(mov3);
    timer->object_container.push_back(mov4);

    box->runAction(mov3);
    label->runAction(mov4);

    timeline->addToTimeline(box);
    timeline->addToTimeline(label);
    timeline->addToTimeline(timer);

    messages_sent++;
}

void create_hieffect() {
    auto timeline = CCController::timeline;

    auto sometext = new CCLabel(".");

    auto key1 = new AKSpriteAnimation(GetMonitorRefreshRate(0), (Easing)GetRandomValue(0, 30));

    key1->setFinalScale(2.f);

    sometext->setPosition({
        (float)(GetRandomValue(0, GetScreenWidth())), (float)(GetRandomValue(0, GetScreenHeight()) - 30.f)
    });
    sometext->setColor(SKYBLUE);

    auto op = new AKOpacityChange(1.f, 0.f, GetMonitorRefreshRate(0) + 1, [&](AKOpacityChange* self) {
        self->destroy();
        self->getParent()->destroy();
    });
    sometext->runAction(op);
    sometext->runAction(key1);
    timeline->addToTimeline(sometext);
}

int main()
{

    InitWindow(1920, 1080, "raylib [core] example - basic window");
    SetTargetFPS(GetMonitorRefreshRate(0));

    bool infullscreen = false;

    CCController::init();

    char* labeldata = (char *)MemAlloc(128);
    char* labeldata2 = (char*)MemAlloc(128);

    bool stop_hieffect = false;

    auto lb = new CCLabel(labeldata);
    lb->setColor(GREEN);
    lb->setPosition({ 10.f, 70.f });
    lb->setScale(0.66666f);
    lb->setOpacity(1.f);
    auto lbfps = new CCLabel(labeldata2);
    lbfps->setColor(GREEN);
    lbfps->setPosition({ 10.f, 50.f });
    lbfps->setScale(0.66666f);
    lbfps->setOpacity(1.f);

    std::vector<CCNode*> hide_list;

    auto iv = new AKInterval([&](AKInterval*) {
        if(!stop_hieffect) create_hieffect();
    }, 1);
    auto iv2 = new AKInterval([&](AKInterval*) {
        auto timeline = CCController::timeline;

        snprintf(labeldata, 128, "OBJECTS: %d", timeline->getSize());
        snprintf(labeldata2, 128, "FPS: %d", GetFPS());

        if (IsKeyPressed(KEY_S)) {
            stop_hieffect = !stop_hieffect;
            if (stop_hieffect) {
                create_message("Screen saver is disabled.");
            }
            else {
                create_message("Screen saver is enabled.");
            }
        }
        if (IsKeyPressed(KEY_F)) {
            ToggleFullscreen();
            infullscreen = !infullscreen;

            if (infullscreen) {
                int i = 0;
                while (i < hide_list.size()) {
                    hide_list[i]->setOpacity(0.f);
                    auto op = new AKOpacityChange(1.f, 0.f, GetMonitorRefreshRate(0) / 3     + 1);
                    hide_list[i]->runAction(op);
                    i++;
                }
            }
            else {
                int i = 0;
                while (i < hide_list.size()) {
                    hide_list[i]->setOpacity(0.f);
                    auto op = new AKOpacityChange(0.f, 1.f, GetMonitorRefreshRate(0) / 3 + 1);
                    hide_list[i]->runAction(op);
                    i++;
                }
            }
        }
    }, 1);

    auto timeline = CCController::timeline;

    timeline->addToTimeline(iv);
    timeline->addToTimeline(iv2);
    timeline->addToTimeline(lb);
    timeline->addToTimeline(lbfps);
    
    hide_list.push_back(lb);
    hide_list.push_back(lbfps);

    while (!WindowShouldClose()) {
        timeline->update(GetFrameTime());
        
        BeginDrawing();
        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();

    delete timeline;
    delete iv;
    delete lb;

	return 0;
}
