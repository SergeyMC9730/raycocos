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
			//printf("destroyed keyframe %X\n", keys[i]);
			switch (keys[i]->getType()) {
			default:
			case ATSCHEDULABLE: {
				delete keys[i];
				break;
			}
			case ATTIMER: {
				auto ttt = static_cast<AKTimer*>(keys[i]);
				delete ttt;
				break;
			}
			case ATINTERVAL: {
				auto ttt = static_cast<AKInterval*>(keys[i]);
				delete ttt;
				break;
			}
			case ATOPACITYCHANGE: {
				auto ttt = static_cast<AKOpacityChange*>(keys[i]);
				delete ttt;
				break;
			}
			case ATSPRITEANIMATION: {
				auto ttt = static_cast<AKSpriteAnimation*>(keys[i]);
				delete ttt;
				break;
			}
			case ATNODE: {
				auto ttt = static_cast<CCNode*>(keys[i]);
				delete ttt;
				break;
			}
			case ATSPRITE: {
				auto ttt = static_cast<CCSprite*>(keys[i]);
				delete ttt;
				break;
			}
			case ATLABEL: {
				auto ttt = static_cast<CCLabel*>(keys[i]);
				delete ttt;
				break;
			}
			case ATBOX: {
				auto ttt = static_cast<CCBox*>(keys[i]);
				delete ttt;
				break;
			}
			}
			keys.erase(keys.begin() + i);
		}
		i++;
	}
}

int AnimationTimeline::getSize() {
	return keys.size();
}