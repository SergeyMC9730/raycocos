cmake_minimum_required (VERSION 3.8)

project ("CMakeProject1")

add_subdirectory(raylib)

add_executable (CMakeProject1 "main.cpp" "AnimationTimeline.h" "AKSpriteAnimation.cpp"    "AnimationTimeline.cpp"   "EasingSet.cpp"        "AKSchedulable.h" "AKSchedulable.cpp" "AKTimer.h" "AKTimer.cpp" "Easing.h" "AKSpriteAnimation.h" "AKInterval.h" "AKInterval.cpp" "CCNode.h" "CCController.h" "CCController.cpp"  "CCNode.cpp" "CCSprite.h" "AKType.h" "CCSprite.cpp" "CCSpriteCacheItem.h" "CCSpriteCache.h" "CCSpriteCache.cpp" "CCLabel.h" "CCLabel.cpp"   "AKOpacityChange.h" "AKOpacityChange.cpp" "CCBox.h" "CCBox.cpp" "CCColorParameter.h" "CCColorParameter.cpp"  "CCColors.h" "CCColors.cpp" "CCMessageBox.h" "CCMessageBox.cpp")

target_link_libraries(CMakeProject1 raylib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProject1 PROPERTY CXX_STANDARD 20)
endif()
