#include "CCColors.h"

Color CCColors::rainbow;
float CCColors::ticks = 0;

void CCColors::rainbow_color_tick() {
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;
    double h = (float)ticks / (double)GetFPS() * 3;
    int i = (int)(h * 6);
    float f = h * 6.0 - i;
    float q = 1 - f;

    switch (i % 6) {
        case 0: {
            r = 1;
            g = f;
            b = 0;
            break;
        }
        case 1: {
            r = q;
            g = 1;
            b = 0;
            break;
        }
        case 2: {
            r = 0;
            g = 1;
            b = f;
            break;
        }
        case 3: {
            r = 0;
            g = q;
            b = 1;
            break;
        }
        case 4: {
            r = f;
            g = 0;
            b = 1;
            break;
        }
        case 5: {
            r = 1;
            g = 0;
            b = q;
            break;
        }
    }
    Color c;
    c.a = 255;
    c.r = (int)(r * 256);
    c.g = (int)(g * 256);
    c.b = (int)(b * 256);
    rainbow = c;
    ticks += 0.1f;
}