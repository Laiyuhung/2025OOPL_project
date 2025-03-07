#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#pragma once
#define PHASE_INITIAL_IMAGE 1
#define PHASE_HOME_PAGE 2
#define PHASE_STAGE_1 3

#define BLUE_NORMAL_OBJECT 0
#define BROWN_NORMAL_OBJECT 1
#define GREEN_NORMAL_OBJECT 2
#define PINK_NORMAL_OBJECT 3
#define ORANGE_NORMAL_OBJECT 4
#define WHITE_NORMAL_OBJECT 5
#define YELLOW_NORMAL_OBJECT 6

#include <glm/vec2.hpp> 
#include "ObjectInformation.hpp"

extern glm::vec2 stage1_postion[38];
extern int stage1_neibor[38][6] = {0};
extern Objectinformation stage1[38];

#endif // GLOBAL_HPP
