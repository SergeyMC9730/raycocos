#pragma once

#include  "raylib/src/raylib.h"

typedef struct CCSpriteCacheItem {
	const char* filename;
	Texture2D texture;
} CCSpriteCacheItem;