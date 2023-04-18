#include  "raylib/src/raylib.h"

#include "CCController.h"
#include "AKSpriteAnimation.h"
#include "AKOpacityChange.h"
#include "AKTimer.h"
#include "AKInterval.h"

#include "CCSprite.h"
#include "CCLabel.h"
#include "CCColors.h"

#include "CCMessageBox.h"

using namespace std;

void create_hieffect() {
    auto timeline = CCController::timeline;

    auto sometext = new CCLabel(".");

    auto key1 = new AKSpriteAnimation(GetMonitorRefreshRate(0), (Easing)GetRandomValue(0, 30));

    key1->setFinalScale(2.f);
    key1->setFinalRotation(GetRandomValue(-90, 90));

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

    InitWindow(1024, 768, "raylib [core] example - basic window");
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
        if (!stop_hieffect) {
            int i = 0;
            int m = 144.f / (float)GetFPS();
            if (m == 0) m == 1;
            while (i < m) {
                create_hieffect();
                i++;
            }
        }
        CCColors::rainbow_color_tick();
    }, 1);
    auto iv2 = new AKInterval([&](AKInterval*) {
        auto timeline = CCController::timeline;

        snprintf(labeldata, 128, "OBJECTS: %d", timeline->getSize());
        snprintf(labeldata2, 128, "FPS: %d", GetFPS());

        if (IsKeyPressed(KEY_S)) {
            stop_hieffect = !stop_hieffect;
            if (stop_hieffect) {
                // create_message("Screen saver is disabled.");
                timeline->addToTimeline(new CCMessageBox("Screensaver is disabled."));
            }
            else {
                timeline->addToTimeline(new CCMessageBox("Screensaver is enabled."));
            }
        }
        if (IsKeyPressed(KEY_F)) {
            infullscreen = !infullscreen;

            if (infullscreen) {
                timeline->addToTimeline(new CCMessageBox("Fullscreen is enabled."));
                SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
                ToggleFullscreen();
                int i = 0;
                while (i < hide_list.size()) {
                    hide_list[i]->setOpacity(0.f);
                    auto op = new AKOpacityChange(1.f, 0.f, GetMonitorRefreshRate(0) / 3     + 1);
                    hide_list[i]->runAction(op);
                    i++;
                }
            }
            else {
                ToggleFullscreen();
                SetWindowSize(1024, 768);
                timeline->addToTimeline(new CCMessageBox("Fullscreen is disabled."));
                int i = 0;
                while (i < hide_list.size()) {
                    hide_list[i]->setOpacity(0.f);
                    auto op = new AKOpacityChange(0.f, 1.f, GetMonitorRefreshRate(0) / 3 + 1);
                    hide_list[i]->runAction(op);
                    i++;
                }
            }
        }
        if (IsKeyPressed(KEY_T)) {
            int i = 0;
            while (i < 64) {
                auto tmm = new AKTimer([&](AKTimer* self) {
                    auto timeline = CCController::timeline;
                    timeline->addToTimeline(new CCMessageBox("Test T!"));
                    self->destroy();
                }, i);
                timeline->addToTimeline(tmm);
                i++;
            }
        }
        if (IsKeyPressed(KEY_Y)) {
            timeline->addToTimeline(new CCMessageBox("Test Y!"));
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
        BeginDrawing();
        ClearBackground(BLACK);
        timeline->update(GetFrameTime());
        EndDrawing();
    }

    CloseWindow();

    delete timeline;
    delete iv;
    delete lb;

	return 0;
}
