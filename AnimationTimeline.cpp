#include "AnimationTimeline.h"

#include "AKSpriteAnimation.h"
#include "AKOpacityChange.h"
#include "AKTimer.h"
#include "AKInterval.h"
#include "CCSprite.h"
#include "CCLabel.h"
#include "CCBox.h"

void AnimationTimeline::addToTimeline(AKSchedulable *key) {
	keys.push_back(key);
}

void AnimationTimeline::update(float delta) {
	int i = 0;
	while (i < keys.size()) {
		auto key = keys[i];
		if (!key->isPaused() && !key->isDestroyed()) key->update(delta);
		i++;
	}

	i = 0;
	while (i < keys.size()) {
		if (keys[i]->isDestroyed()) {
			// printf("destroyed keyframe %X\n", keys[i]);
			delete keys[i];
			keys.erase(keys.begin() + i);
		}
		i++;
	}
}

int AnimationTimeline::getSize() {
	return keys.size();
}