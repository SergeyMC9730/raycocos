#include  "raylib/src/raylib.h"

#include <string>

#include "CCController.h"
#include "CCLabel.h"
#include "CCSprite.h"
#include "AKSpriteAnimation.h"

#include "CCNode.h"

int main() {
    InitWindow(1024, 768, "raylib [core] example - basic window");
    SetTargetFPS(GetMonitorRefreshRate(0));

    CCController::init();

    auto lb = new CCLabel("yes!");
    auto lb2 = new CCLabel("yes 2!");

    lb->setColor(GREEN);
    lb->setPosition({ 10.f, 70.f });
    lb->setScale(0.33333f);
    lb->setOpacity(1.f);
    
    lb2->setColor(RED);
    lb2->setPosition({ 30.f, 100.f });
    lb2->setScale(2.f);
    lb2->setOpacity(0.5f);

    auto nd = new CCNode();
    nd->addChild(lb);
    // nd->addChild(lb2);
    
    // nd->setOpacity(0.005f);

    nd->setScale(5.f);

    Font fnt = LoadFontEx("Roboto-Bold.ttf", 20, 0, 0);

    lb->setFont(fnt);
    lb2->setFont(fnt);

    auto timeline = CCController::timeline;

    timeline->addToTimeline(nd);

    Image img = GenImagePerlinNoise(128, 128, 10, 10, 10.f);

    CCSprite *spr = new CCSprite(img);

    UnloadImage(img);

    nd->addChild(spr);

    auto key1 = new AKSpriteAnimation(CCController::secondsToFrames(1.f, GetFrameTime()), (Easing)1);

    key1->setFinalPosition({-60, -60});
    key1->setFinalRotation(-60.f);

    spr->runAction(key1);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        timeline->update(GetFrameTime());
        EndDrawing();
    }

    CloseWindow();

    delete nd;

    delete timeline;
    // delete lb;
}