#include "App.hpp"
#include "Global.hpp"
#include "Util/Keycode.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>
#include <thread>
#include <vector>

using namespace std;

void PointUpdate( int stage , int point ) {
    stage_point_counter[stage] = point;
}

int GetPoint( int stage ) {
   return stage_point_counter[stage]; 
}