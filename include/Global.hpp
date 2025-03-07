#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#pragma once
#define PHASE_INITIAL_IMAGE 1
#define PHASE_HOME_PAGE 2
#define PHASE_STAGE_1 3

#define BLUE_NORMAL_OBJECT 1
#define BROWN_NORMAL_OBJECT 2
#define GREEN_NORMAL_OBJECT 3
#define PINK_NORMAL_OBJECT 4
#define ORANGE_NORMAL_OBJECT 5
#define WHITE_NORMAL_OBJECT 6
#define YELLOW_NORMAL_OBJECT 7

#include <glm/vec2.hpp> 
#include "ObjectInformation.hpp"

extern glm::vec2 stage1_position[38];
extern int stage1_neibor[38][6];
extern Objectinformation stage1[38];

void InitializeStage1();

#endif // GLOBAL_HPP
