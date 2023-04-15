#include  "raylib/src/raylib.h"

#include "CCController.h"
#include "AKSpriteAnimation.h"
#include "AKOpacityChange.h"
#include "AKTimer.h"
#include "AKInterval.h"

#include "CCSprite.h"
#include "CCLabel.h"

using namespace std;

int i2 = 1;

void create_hieffect() {
    auto timeline = CCController::timeline;

    auto sometext = new CCLabel("hi");

    auto key1 = new AKSpriteAnimation(GetMonitorRefreshRate(0), (Easing)GetRandomValue(0, 30));

    key1->setFinalScale(2.f);

    sometext->setPosition({
        (float)(GetRandomValue(0, GetScreenWidth() - 60.f)), (float)(GetRandomValue(0, GetScreenHeight() - 60.f))
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

    InitWindow(1280, 720, "raylib [core] example - basic window");
    SetTargetFPS(GetMonitorRefreshRate(0));

    CCController::init();

    char* labeldata = (char *)MemAlloc(128);

    auto iv = new AKInterval([&](AKInterval*) {
        create_hieffect();
    }, 1);
    auto iv2 = new AKInterval([&](AKInterval*) {
        auto timeline = CCController::timeline;
        snprintf(labeldata, 128, "OBJECTS: %d", timeline->getSize());
    }, 1);

    auto timeline = CCController::timeline;

    timeline->addToTimeline(iv);
    timeline->addToTimeline(iv2);

    auto lb = new CCLabel(labeldata);
    lb->setColor(GREEN);
    lb->setPosition({ 10.f, 30.f });
    lb->setScale(0.66666f);
    lb->setOpacity(1.f);

    timeline->addToTimeline(lb);

    while (!WindowShouldClose()) {
        timeline->update(GetFrameTime());
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();

    delete timeline;
    delete iv;
    delete iv2;
    delete lb;

	return 0;
}
