#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#pragma once
#define PHASE_INITIAL_IMAGE 1
#define PHASE_HOME_PAGE 2
#define PHASE_STAGE_1 3
#define PHASE_STAGE_2 4

#define NO_MOVE 0
#define MOVE_BY_DROP 1
#define MOVE_BY_SWITCH 2

#define BLUE_OBJECT 1
#define BROWN_OBJECT 2
#define GREEN_OBJECT 3
#define PINK_OBJECT 4
#define ORANGE_OBJECT 5
#define WHITE_OBJECT 6
#define YELLOW_OBJECT 7

#define NORMAL_OBJECT 1
#define STRIPE_OBJECT 2
#define STRIPE_LEFT_RIGHT_OBJECT 3
#define STRIPE_RIGHT_LEFT_OBJECT 4
#define FLOWER_OBJECT 5
#define STARFLOWER_OBJECT 6
#define TRIANGLEFLOWER_OBJECT 7
#define RAINBOWBALL_OBJECT 8
#define FLOWER_COMBINED_OBJECT 9
#define FLOWER_STRIPE_OBJECT 10
#define STRIPE_COMBINED_OBJECT 11

#define EMPTY_OBJECT GA_RESOURCE_DIR"/Image/GameObject/emptyObject.png"

#define BLUE_NORMAL_OBJECT GA_RESOURCE_DIR"/Image/GameObject/blueNormal.png"
#define BROWN_NORMAL_OBJECT GA_RESOURCE_DIR"/Image/GameObject/brownNormal.png"
#define GREEN_NORMAL_OBJECT GA_RESOURCE_DIR"/Image/GameObject/greenNormal.png" 
#define PINK_NORMAL_OBJECT GA_RESOURCE_DIR"/Image/GameObject/pinkNormal.png"
#define ORANGE_NORMAL_OBJECT GA_RESOURCE_DIR"/Image/GameObject/orangeNormal.png"
#define WHITE_NORMAL_OBJECT GA_RESOURCE_DIR"/Image/GameObject/whiteNormal.png"
#define YELLOW_NORMAL_OBJECT GA_RESOURCE_DIR"/Image/GameObject/yellowNormal.png"

#define BLUE_STRIPE_OBJECT GA_RESOURCE_DIR"/Image/GameObject/blueLine.png"
#define BROWN_STRIPE_OBJECT GA_RESOURCE_DIR"/Image/GameObject/brownLine.png"
#define GREEN_STRIPE_OBJECT GA_RESOURCE_DIR"/Image/GameObject/greenLine.png"
#define PINK_STRIPE_OBJECT GA_RESOURCE_DIR"/Image/GameObject/pinkLine.png"
#define ORANGE_STRIPE_OBJECT GA_RESOURCE_DIR"/Image/GameObject/orangeLine.png"
#define WHITE_STRIPE_OBJECT GA_RESOURCE_DIR"/Image/GameObject/whiteLine.png"
#define YELLOW_STRIPE_OBJECT GA_RESOURCE_DIR"/Image/GameObject/yellowLine.png"

#define BLUE_STRIPE_LEFT_RIGHT_OBJECT GA_RESOURCE_DIR"/Image/GameObject/blueLineLeftRight.png"
#define BROWN_STRIPE_LEFT_RIGHT_OBJECT GA_RESOURCE_DIR"/Image/GameObject/brownLineLeftRight.png"
#define GREEN_STRIPE_LEFT_RIGHT_OBJECT GA_RESOURCE_DIR"/Image/GameObject/greenLineLeftRight.png"
#define PINK_STRIPE_LEFT_RIGHT_OBJECT GA_RESOURCE_DIR"/Image/GameObject/pinkLineLeftRight.png"
#define ORANGE_STRIPE_LEFT_RIGHT_OBJECT GA_RESOURCE_DIR"/Image/GameObject/orangeLineLeftRight.png"
#define WHITE_STRIPE_LEFT_RIGHT_OBJECT GA_RESOURCE_DIR"/Image/GameObject/whiteLineLeftRight.png"
#define YELLOW_STRIPE_LEFT_RIGHT_OBJECT GA_RESOURCE_DIR"/Image/GameObject/yellowLineLeftRight.png"

#define BLUE_STRIPE_RIGHT_LEFT_OBJECT GA_RESOURCE_DIR"/Image/GameObject/blueLineRightLeft.png"
#define BROWN_STRIPE_RIGHT_LEFT_OBJECT GA_RESOURCE_DIR"/Image/GameObject/brownLineRightLeft.png"
#define GREEN_STRIPE_RIGHT_LEFT_OBJECT GA_RESOURCE_DIR"/Image/GameObject/greenLineRightLeft.png"
#define PINK_STRIPE_RIGHT_LEFT_OBJECT GA_RESOURCE_DIR"/Image/GameObject/pinkLineRightLeft.png"
#define ORANGE_STRIPE_RIGHT_LEFT_OBJECT GA_RESOURCE_DIR"/Image/GameObject/orangeLineRightLeft.png"
#define WHITE_STRIPE_RIGHT_LEFT_OBJECT GA_RESOURCE_DIR"/Image/GameObject/whiteLineRightLeft.png"
#define YELLOW_STRIPE_RIGHT_LEFT_OBJECT GA_RESOURCE_DIR"/Image/GameObject/yellowLineRightLeft.png"

#define BLUE_FLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/blueFlower.png"
#define BROWN_FLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/brownFlower.png"
#define GREEN_FLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/greenFlower.png"
#define PINK_FLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/pinkFlower.png"
#define ORANGE_FLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/orangeFlower.png"
#define WHITE_FLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/whiteFlower.png"
#define YELLOW_FLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/yellowFlower.png"

#define BLUE_STARFLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/blueStarFlower.png"
#define BROWN_STARFLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/brownStarFlower.png"
#define GREEN_STARFLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/greenStarFlower.png"
#define PINK_STARFLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/pinkStarFlower.png"
#define ORANGE_STARFLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/orangeStarFlower.png"
#define WHITE_STARFLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/whiteStarFlower.png"
#define YELLOW_STARFLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/yellowStarFlower.png"

#define BLUE_TRIANGLEFLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/blueTriangleFlower.png"
#define BROWN_TRIANGLEFLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/brownTriangleFlower.png"
#define GREEN_TRIANGLEFLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/greenTriangleFlower.png"
#define PINK_TRIANGLEFLOWER_OBJECT  GA_RESOURCE_DIR"/Image/GameObject/pinkTriangleFlower.png"
#define ORANGE_TRIANGLEFLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/orangeTriangleFlower.png"
#define WHITE_TRIANGLEFLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/whiteTriangleFlower.png"
#define YELLOW_TRIANGLEFLOWER_OBJECT GA_RESOURCE_DIR"/Image/GameObject/yellowTriangleFlower.png"

#define RAINBOWBALL_OBJECT_LINK GA_RESOURCE_DIR"/Image/GameObject/rainbowBall.png"


#include <glm/vec2.hpp> 
#include <stack>
#include <memory>
#include "ObjectInformation.hpp"

extern glm::vec2 stage1_position[38];
extern int stage1_neibor[38][6];
extern Objectinformation stage1[38];

extern glm::vec2 stage2_position[46];
extern int stage2_neibor[46][6];
extern Objectinformation stage2[46];



extern int is_click;
extern int stage_point_goal[13];
extern int stage_point_counter[13];

void InitializeStage1();
void InitializeStage2();

enum GamePhase {
    PHASE_NORMAL,
    PHASE_PAUSE_FOR_DISAPPEAR,
    PHASE_DROPPING
};

extern GamePhase currentPhase;

#include <chrono>
extern std::chrono::steady_clock::time_point startTime;

#endif // GLOBAL_HPP
