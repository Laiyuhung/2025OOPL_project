#include "StageObject.hpp"
#include "App.hpp"
#include "Global.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>
#include <thread>
#include <vector>
#include <chrono>
using namespace std;

void StageObject::RandomChangeObject( int current_pos ) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(1, 7);

    int ramdom_number = distrib(gen);

    switch ( ramdom_number )
    {
        case BLUE_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/blueNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( BLUE_OBJECT );
            break;
        case BROWN_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/brownNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( BROWN_OBJECT );
            break;
        case GREEN_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/greenNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( GREEN_OBJECT );
            break;
        case PINK_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/pinkNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( PINK_OBJECT );
            break;
        case ORANGE_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/orangeNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( ORANGE_OBJECT );
            break;
        case WHITE_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/whiteNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( WHITE_OBJECT );
            break;
        case YELLOW_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/yellowNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( YELLOW_OBJECT );
            break;
        default:
            break;
    }
}
void StageObject::ShuffleStageCharacter( int s ) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(1, 7);

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        auto& obj = m_Stage_Object[i];
        if (!obj) continue;

        if (m_Stage != 0) {
            auto type = obj->GetCurrentType();
            if (type != NORMAL_OBJECT && type != ONE_LAYER_COOKIE_OBJECT && type != TWO_LAYER_COOKIE_OBJECT) {
                continue;
            }
        }

        if (s == 5 && i < 27 && obj->GetCurrentType() != NORMAL_OBJECT ) {
            obj->SetImage(COOKIE_ONE_IMAGE);
            obj->SetBlock(NO_COLOR);
            obj->SetInformation(stage5[i]);
            obj->SetPosition(stage5_position[i]);
            obj->SetZIndex(10);
            obj->SetSize({20, 25});
            obj->DisAppear();
            obj->SetAppearBool(true);
            obj->SetBlockType(NORMAL_OBJECT);
            obj->SetCurrentType(ONE_LAYER_COOKIE_OBJECT);
            continue;
        } 
        if (s == 6 && m_Size - i <= 35 && obj->GetCurrentType() != NORMAL_OBJECT) {
            if ( obj->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT ) {
                obj->SetImage(COOKIE_ONE_IMAGE);
                obj->SetBlock(NO_COLOR);
                obj->SetInformation(stage6[i]);
                obj->SetPosition(stage6_position[i]);
                obj->SetZIndex(10);
                obj->SetSize({20, 25});
                obj->DisAppear();
                obj->SetAppearBool(true);
                obj->SetBlockType(NORMAL_OBJECT);
                obj->SetCurrentType(ONE_LAYER_COOKIE_OBJECT);
            } 
            else if ( obj->GetCurrentType() == TWO_LAYER_COOKIE_OBJECT ) {
                obj->SetImage(COOKIE_TWO_IMAGE);
                obj->SetBlock(NO_COLOR);
                obj->SetInformation(stage6[i]);
                obj->SetPosition(stage6_position[i]);
                obj->SetZIndex(10);
                obj->SetSize({20, 25});
                obj->DisAppear();
                obj->SetAppearBool(true);
                obj->SetBlockType(ONE_LAYER_COOKIE_OBJECT);
                obj->SetCurrentType(TWO_LAYER_COOKIE_OBJECT);
            }
            continue;
        } 
        if ( s == 7 && obj->GetCurrentType() != NORMAL_OBJECT) {
            if ( one_layer_7.find(i) != one_layer_7.end() ) {
                obj->SetImage(COOKIE_ONE_IMAGE);
                obj->SetBlock(NO_COLOR);
                obj->SetInformation(stage7[i]);
                obj->SetPosition(stage7_position[i]);
                obj->SetZIndex(10);
                obj->SetSize({20, 25});
                obj->DisAppear();
                obj->SetAppearBool(true);
                obj->SetBlockType(NORMAL_OBJECT);
                obj->SetCurrentType(ONE_LAYER_COOKIE_OBJECT);
                continue;
            }
            else if ( two_layer_7.find(i) != two_layer_7.end() ) {
                obj->SetImage(COOKIE_TWO_IMAGE);
                obj->SetBlock(NO_COLOR);
                obj->SetInformation(stage7[i]);
                obj->SetPosition(stage7_position[i]);
                obj->SetZIndex(10);
                obj->SetSize({20, 25});
                obj->DisAppear();
                obj->SetAppearBool(true);
                obj->SetBlockType(ONE_LAYER_COOKIE_OBJECT);
                obj->SetCurrentType(TWO_LAYER_COOKIE_OBJECT);
                continue;
            }
        } 
        RandomChangeObject(i);

        obj->SetZIndex(10);
        obj->SetSize({20, 25});
        obj->DisAppear();
        obj->SetAppearBool(true);
        obj->SetBlockType(NORMAL_OBJECT);
        obj->SetCurrentType(NORMAL_OBJECT);

        switch (s) {
            case 1:
                obj->SetInformation(stage1[i]);
                obj->SetPosition(stage1_position[i]);
                break;
            case 2:
                obj->SetInformation(stage2[i]);
                obj->SetPosition(stage2_position[i]);
                break;
            case 3:
                obj->SetInformation(stage3[i]);
                obj->SetPosition(stage3_position[i]);
                break;
            case 4:
                obj->SetInformation(stage4[i]);
                obj->SetPosition(stage4_position[i]);
                break;
            case 5:
                obj->SetInformation(stage5[i]);
                obj->SetPosition(stage5_position[i]);
                break;
            case 6:
                obj->SetInformation(stage6[i]);
                obj->SetPosition(stage6_position[i]);
                break;
            case 7:
                obj->SetInformation(stage7[i]);
                obj->SetPosition(stage7_position[i]);
                break;
            default:
                break;
        }
    }
}


void StageObject::InitializeStageCharacter(int s) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(1, 7);

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        auto& obj = m_Stage_Object[i];
        if (!obj) continue;

        if (m_Stage != 0) {
            auto type = obj->GetCurrentType();
            if (type != NORMAL_OBJECT && type != ONE_LAYER_COOKIE_OBJECT && type != TWO_LAYER_COOKIE_OBJECT) {
                continue;
            }
        }

        if (s == 5 && i < 27) {
            obj->SetImage(COOKIE_ONE_IMAGE);
            obj->SetBlock(NO_COLOR);
            obj->SetInformation(stage5[i]);
            obj->SetPosition(stage5_position[i]);
            obj->SetZIndex(10);
            obj->SetSize({20, 25});
            obj->DisAppear();
            obj->SetAppearBool(true);
            obj->SetBlockType(NORMAL_OBJECT);
            obj->SetCurrentType(ONE_LAYER_COOKIE_OBJECT);
            continue;
        } 
        if (s == 6 && m_Size - i <= 35) {
            obj->SetImage(COOKIE_TWO_IMAGE);
            obj->SetBlock(NO_COLOR);
            obj->SetInformation(stage6[i]);
            obj->SetPosition(stage6_position[i]);
            obj->SetZIndex(10);
            obj->SetSize({20, 25});
            obj->DisAppear();
            obj->SetAppearBool(true);
            obj->SetBlockType(ONE_LAYER_COOKIE_OBJECT);
            obj->SetCurrentType(TWO_LAYER_COOKIE_OBJECT);
            continue;
        }
        if ( s == 7 ) {
            if ( one_layer_7.find(i) != one_layer_7.end() ) {
                obj->SetImage(COOKIE_ONE_IMAGE);
                obj->SetBlock(NO_COLOR);
                obj->SetInformation(stage7[i]);
                obj->SetPosition(stage7_position[i]);
                obj->SetZIndex(10);
                obj->SetSize({20, 25});
                obj->DisAppear();
                obj->SetAppearBool(true);
                obj->SetBlockType(NORMAL_OBJECT);
                obj->SetCurrentType(ONE_LAYER_COOKIE_OBJECT);
                continue;
            }
            else if ( two_layer_7.find(i) != two_layer_7.end() ) {
                obj->SetImage(COOKIE_TWO_IMAGE);
                obj->SetBlock(NO_COLOR);
                obj->SetInformation(stage7[i]);
                obj->SetPosition(stage7_position[i]);
                obj->SetZIndex(10);
                obj->SetSize({20, 25});
                obj->DisAppear();
                obj->SetAppearBool(true);
                obj->SetBlockType(ONE_LAYER_COOKIE_OBJECT);
                obj->SetCurrentType(TWO_LAYER_COOKIE_OBJECT);
                continue;
            }
        } 
        RandomChangeObject(i);
        

        obj->SetZIndex(10);
        obj->SetSize({20, 25});
        obj->DisAppear();
        obj->SetAppearBool(true);
        obj->SetBlockType(NORMAL_OBJECT);
        obj->SetCurrentType(NORMAL_OBJECT);

        switch (s) {
            case 1:
                obj->SetInformation(stage1[i]);
                obj->SetPosition(stage1_position[i]);
                break;
            case 2:
                obj->SetInformation(stage2[i]);
                obj->SetPosition(stage2_position[i]);
                break;
            case 3:
                obj->SetInformation(stage3[i]);
                obj->SetPosition(stage3_position[i]);
                break;
            case 4:
                obj->SetInformation(stage4[i]);
                obj->SetPosition(stage4_position[i]);
                break;
            case 5:
                obj->SetInformation(stage5[i]);
                obj->SetPosition(stage5_position[i]);
                break;
            case 6:
                obj->SetInformation(stage6[i]);
                obj->SetPosition(stage6_position[i]);
                break;
            case 7:
                obj->SetInformation(stage7[i]);
                obj->SetPosition(stage7_position[i]);
                break;
            default:
                break;
        }
    }
}

bool StageObject::CheckAppearance(int s, int now_stage, bool ifShuffle) {
    if (s != 0 && currentPhase != PHASE_NORMAL && currentPhase != PHASE_ITEM_USED )
        return false;

    bool flag = false;
    int stripe_side;
    // std::cout << "now stage " << now_stage << std::endl;

    if ( currentPhase == PHASE_NORMAL )
        for (auto& obj : m_Stage_Object) {
            if (obj) obj->SetAppearBool(true);
        }

    std::vector<std::vector<int>> total_length(m_Stage_Object.size(), std::vector<int>(6, 0));

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        auto& obj = m_Stage_Object[i];
        if (!obj) continue;

        int* neighbors = obj->GetInformationNeibor();
        obj->GetBlockType();

        

        if (obj->GetCurrentType() == RAINBOWBALL_OBJECT && obj->GetSwitchedInfo() == MOVE_BY_SWITCH) {
            obj->SetAppearBool(false);
            // MakeDisappear();
            // for (auto& o : m_Stage_Object) if (o) o->SetSwitched(NO_MOVE);
            // return true;
        }

        if ((obj->GetCurrentType() == FLOWER_COMBINED_OBJECT || obj->GetCurrentType() == FLOWER_STRIPE_OBJECT || obj->GetCurrentType() == STRIPE_COMBINED_OBJECT) && obj->GetSwitchedInfo() == MOVE_BY_SWITCH) {
            obj->SetAppearBool(false);
        }

        for (int j = 0; j < 6; ++j) {
            int neighbor = neighbors[j]%(m_Size+1);
            if (neighbor == -1) continue;
            auto& neighbor_obj = m_Stage_Object[neighbor];
            if (!neighbor_obj) continue;

            if (IsSameColor(neighbor_obj->GetBlockType(), obj->GetBlockType()) &&
                neighbor_obj->GetCurrentType() != ONE_LAYER_COOKIE_OBJECT &&
                neighbor_obj->GetCurrentType() != TWO_LAYER_COOKIE_OBJECT &&
                obj->GetCurrentType() != ONE_LAYER_COOKIE_OBJECT &&
                obj->GetCurrentType() != TWO_LAYER_COOKIE_OBJECT) {
                total_length[i][j] = CheckNextAppearance(neighbor, j, 1);
            }
        }
    }

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (DisappearMethodOfRainbowBall(i, total_length[i].data(), 2)) {
            m_Stage_Object[i]->SetBlockType(RAINBOWBALL_OBJECT);
        }
    }
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (DisappearMethodOfRainbowBall(i, total_length[i].data(), 1)) {
            m_Stage_Object[i]->SetBlockType(RAINBOWBALL_OBJECT);
        }
    }
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (DisappearMethodOfFlower(i, total_length[i].data())) {
            m_Stage_Object[i]->SetBlockType(FLOWER_OBJECT);
        }
    }
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (DisappearMethodOfTriangleFlower(i, total_length[i].data())) {
            m_Stage_Object[i]->SetBlockType(TRIANGLEFLOWER_OBJECT);
        }
    }
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (DisappearMethodOfStarFlower(i, total_length[i].data())) {
            m_Stage_Object[i]->SetBlockType(STARFLOWER_OBJECT);
        }
    }
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        stripe_side = DisappearMethodOfStripe(i, total_length[i].data(), 2);
        if (stripe_side != -1) {
            if (stripe_side == 0 || stripe_side == 3)
                m_Stage_Object[i]->SetBlockType(STRIPE_OBJECT);
            else if (stripe_side == 1 || stripe_side == 4)
                m_Stage_Object[i]->SetBlockType(STRIPE_RIGHT_LEFT_OBJECT);
            else if (stripe_side == 2 || stripe_side == 5)
                m_Stage_Object[i]->SetBlockType(STRIPE_LEFT_RIGHT_OBJECT);
        }
    }
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (DisappearMethodOfStripe(i, total_length[i].data(), 1) != -1) {
            m_Stage_Object[i]->SetBlockType(STRIPE_OBJECT);
        }
    }

    // for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
    //     printf( "current type %d , next %d\n" , m_Stage_Object[i]->GetCurrentType() , m_Stage_Object[i]->GetType() );
    // }

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (DisappearMethodOfOneLine(i, total_length[i].data())) {
            m_Stage_Object[i]->SetBlockType(NORMAL_OBJECT);
        }
    }
    
    
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (s == 0 && m_Stage_Object[i]->GetCurrentType() != TWO_LAYER_COOKIE_OBJECT )
            m_Stage_Object[i]->SetBlockType(NORMAL_OBJECT);
    }


    for (auto& obj : m_Stage_Object) if (obj) obj->SetSwitched(NO_MOVE);

    for (auto& obj : m_Stage_Object) {
        if (obj && !obj->GetAppearBool()) flag = true;
    }

    

    CheckObstaclesDisappear(ifShuffle);
    // cout<<"flag: "<<flag<<endl;

    if (flag || currentPhase == PHASE_ITEM_USED ) {
        MakeDisappear();
        if (s == 0 || ifShuffle)
            Dropping(s, now_stage, ifShuffle);
    } else {
        for (auto& obj : m_Stage_Object) if (obj) obj->SetSwitched(0);
        auto result = CheckShuffleDemands();
        if (result.first == -1 && result.second == -1) {
            std::cout << "SHUFFLE\n";
            ShuffleStageCharacter(now_stage);
            CheckAppearance(s, now_stage, true);
            AppearAll();
        } else {
            std::cout << "Swap between " << result.first << " and " << result.second << std::endl;
        }
    }

    return flag;
}

void StageObject::CheckSpecialObject(int i) {
    static const std::unordered_map<int, std::unordered_map<int, std::string>> imageMap = {
        {BLUE_OBJECT, {
            {STRIPE_OBJECT, BLUE_STRIPE_OBJECT},
            {STRIPE_LEFT_RIGHT_OBJECT, BLUE_STRIPE_LEFT_RIGHT_OBJECT},
            {STRIPE_RIGHT_LEFT_OBJECT, BLUE_STRIPE_RIGHT_LEFT_OBJECT},
            {FLOWER_OBJECT, BLUE_FLOWER_OBJECT},
            {STARFLOWER_OBJECT, BLUE_STARFLOWER_OBJECT},
            {TRIANGLEFLOWER_OBJECT, BLUE_TRIANGLEFLOWER_OBJECT}
        }},
        {BROWN_OBJECT, {
            {STRIPE_OBJECT, BROWN_STRIPE_OBJECT},
            {STRIPE_LEFT_RIGHT_OBJECT, BROWN_STRIPE_LEFT_RIGHT_OBJECT},
            {STRIPE_RIGHT_LEFT_OBJECT, BROWN_STRIPE_RIGHT_LEFT_OBJECT},
            {FLOWER_OBJECT, BROWN_FLOWER_OBJECT},
            {STARFLOWER_OBJECT, BROWN_STARFLOWER_OBJECT},
            {TRIANGLEFLOWER_OBJECT, BROWN_TRIANGLEFLOWER_OBJECT}
        }},
        {GREEN_OBJECT, {
            {STRIPE_OBJECT, GREEN_STRIPE_OBJECT},
            {STRIPE_LEFT_RIGHT_OBJECT, GREEN_STRIPE_LEFT_RIGHT_OBJECT},
            {STRIPE_RIGHT_LEFT_OBJECT, GREEN_STRIPE_RIGHT_LEFT_OBJECT},
            {FLOWER_OBJECT, GREEN_FLOWER_OBJECT},
            {STARFLOWER_OBJECT, GREEN_STARFLOWER_OBJECT},
            {TRIANGLEFLOWER_OBJECT, GREEN_TRIANGLEFLOWER_OBJECT}
        }},
        {PINK_OBJECT, {
            {STRIPE_OBJECT, PINK_STRIPE_OBJECT},
            {STRIPE_LEFT_RIGHT_OBJECT, PINK_STRIPE_LEFT_RIGHT_OBJECT},
            {STRIPE_RIGHT_LEFT_OBJECT, PINK_STRIPE_RIGHT_LEFT_OBJECT},
            {FLOWER_OBJECT, PINK_FLOWER_OBJECT},
            {STARFLOWER_OBJECT, PINK_STARFLOWER_OBJECT},
            {TRIANGLEFLOWER_OBJECT, PINK_TRIANGLEFLOWER_OBJECT}
        }},
        {ORANGE_OBJECT, {
            {STRIPE_OBJECT, ORANGE_STRIPE_OBJECT},
            {STRIPE_LEFT_RIGHT_OBJECT, ORANGE_STRIPE_LEFT_RIGHT_OBJECT},
            {STRIPE_RIGHT_LEFT_OBJECT, ORANGE_STRIPE_RIGHT_LEFT_OBJECT},
            {FLOWER_OBJECT, ORANGE_FLOWER_OBJECT},
            {STARFLOWER_OBJECT, ORANGE_STARFLOWER_OBJECT},
            {TRIANGLEFLOWER_OBJECT, ORANGE_TRIANGLEFLOWER_OBJECT}
        }},
        {WHITE_OBJECT, {
            {STRIPE_OBJECT, WHITE_STRIPE_OBJECT},
            {STRIPE_LEFT_RIGHT_OBJECT, WHITE_STRIPE_LEFT_RIGHT_OBJECT},
            {STRIPE_RIGHT_LEFT_OBJECT, WHITE_STRIPE_RIGHT_LEFT_OBJECT},
            {FLOWER_OBJECT, WHITE_FLOWER_OBJECT},
            {STARFLOWER_OBJECT, WHITE_STARFLOWER_OBJECT},
            {TRIANGLEFLOWER_OBJECT, WHITE_TRIANGLEFLOWER_OBJECT}
        }},
        {YELLOW_OBJECT, {
            {STRIPE_OBJECT, YELLOW_STRIPE_OBJECT},
            {STRIPE_LEFT_RIGHT_OBJECT, YELLOW_STRIPE_LEFT_RIGHT_OBJECT},
            {STRIPE_RIGHT_LEFT_OBJECT, YELLOW_STRIPE_RIGHT_LEFT_OBJECT},
            {FLOWER_OBJECT, YELLOW_FLOWER_OBJECT},
            {STARFLOWER_OBJECT, YELLOW_STARFLOWER_OBJECT},
            {TRIANGLEFLOWER_OBJECT, YELLOW_TRIANGLEFLOWER_OBJECT}
        }}
    };

    auto color = m_Stage_Object[i]->GetBlockType();
    auto type = m_Stage_Object[i]->GetType();

    if (type == RAINBOWBALL_OBJECT) {
        m_Stage_Object[i]->SetImage(RAINBOWBALL_OBJECT_LINK);
        m_Stage_Object[i]->SetBlock(0);
        return;
    }

    auto colorIt = imageMap.find(color);
    if (colorIt != imageMap.end()) {
        const auto& typeMap = colorIt->second;
        auto typeIt = typeMap.find(type);
        if (typeIt != typeMap.end()) {
            m_Stage_Object[i]->SetImage(typeIt->second);
        }
    }
}

void StageObject::MakeDisappear() {
    if (m_Stage != 0 && currentPhase != PHASE_NORMAL && currentPhase != PHASE_ITEM_USED)
        return;
    
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (!m_Stage_Object[i]->GetVisibility()) continue;
        
        if (!m_Stage_Object[i]->GetAppearBool() &&
        (m_Stage_Object[i]->GetCurrentType() == NORMAL_OBJECT ||
        m_Stage_Object[i]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT ||
        m_Stage_Object[i]->GetCurrentType() == TWO_LAYER_COOKIE_OBJECT ||
        m_Stage_Object[i]->GetGenerate())) {
            
            MakeDisappearWithObject(static_cast<int>(i));
            m_Stage_Object[i]->SetGenerate(false);
        }
    }

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if ((m_Stage_Object[i]->GetType() == NORMAL_OBJECT ||
             m_Stage_Object[i]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT) &&
             !m_Stage_Object[i]->GetAppearBool()) {
            GoalUpdate(static_cast<int>(i));
            // printf( "current type %d , next %d\n" , m_Stage_Object[i]->GetCurrentType() , m_Stage_Object[i]->GetType() );
            m_Stage_Object[i]->SetCurrentType(m_Stage_Object[i]->GetType());
            m_Stage_Object[i]->SetBlockType(NORMAL_OBJECT);
        }
        else if ( !m_Stage_Object[i]->GetAppearBool() &&
            m_Stage_Object[i]->GetCurrentType() == TWO_LAYER_COOKIE_OBJECT ) {
            m_Stage_Object[i]->SetCurrentType(ONE_LAYER_COOKIE_OBJECT);
            m_Stage_Object[i]->SetBlockType(NORMAL_OBJECT);
            m_Stage_Object[i]->SetAppearBool( true );
            m_Stage_Object[i]->SetImage(COOKIE_ONE_IMAGE);
            m_Stage_Object[i]->SetBlock(NO_COLOR);
        } 
        else if (m_Stage_Object[i]->GetType() != NORMAL_OBJECT &&
                   !m_Stage_Object[i]->GetAppearBool()) {
            PointUpdate(GetPoint() + 1);
            GoalUpdate(static_cast<int>(i));
            m_Stage_Object[i]->SetAppearBool(true);
            CheckSpecialObject(static_cast<int>(i));
            m_Stage_Object[i]->SetGenerate(true);
            m_Stage_Object[i]->SetCurrentType(m_Stage_Object[i]->GetType());
            m_Stage_Object[i]->SetBlockType(NORMAL_OBJECT);
        }
    }

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (!m_Stage_Object[i]->GetAppearBool()) {
            PointUpdate(GetPoint() + 1);
            GoalUpdate(static_cast<int>(i));
        }
    }

    std::cout << "score: " << GetPoint() << std::endl;

    currentPhase = PHASE_PAUSE_FOR_DISAPPEAR;
    startTime = std::chrono::steady_clock::now();
}

void StageObject::Dropping(int s, int now_stage, bool ifShuffle) {
    if (m_Stage != 0 && currentPhase != PHASE_DROPPING ) return;

    // is_click = 0;
    size_t loop_count = 0;
    for (size_t i = 1; i < m_Stage_Object.size();) {
        if (loop_count > m_Stage_Object.size() || !m_Stage_Object[i] || m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1) == -1 || m_Stage_Object[i]->GetAppearBool()) {
            ++i;
            loop_count = 0;
            continue;
        }
        if (!m_Stage_Object[i]->GetAppearBool() && m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1) != -1)
            Dropping_method(static_cast<int>(i));
        ++loop_count;
    }

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (!m_Stage_Object[i]->GetAppearBool() && m_Stage_Object[i]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT) {
            std::cout << "testing\n";
            m_Stage_Object[i]->SetImage(COOKIE_ONE_IMAGE);
            m_Stage_Object[i]->SetBlock(NO_COLOR);
            m_Stage_Object[i]->SetBlockType(NORMAL_OBJECT);
        }
        else if (!m_Stage_Object[i]->GetAppearBool()) {
            RandomChangeObject(static_cast<int>(i));
            m_Stage_Object[i]->SetBlockType(NORMAL_OBJECT);
        }
        m_Stage_Object[i]->SetAppearBool(true);
    }

    if (m_Stage != 0 ) AppearAll();
    // else if ( ifShuffle == true ) AppearAll();
    currentPhase = PHASE_NORMAL;
    CheckAppearance(s, now_stage, ifShuffle);
}


void StageObject::MakeObstaclesDisappear(int position) {

    //Add here if more obstacles
    switch ( m_Stage_Object[position]->GetCurrentType() ) {
        case ONE_LAYER_COOKIE_OBJECT:
            m_Stage_Object[position]->SetAppearBool(false);
        break;
        case TWO_LAYER_COOKIE_OBJECT:
            m_Stage_Object[position]->SetAppearBool(false);
        break;
    }
}

void StageObject::CheckObstaclesDisappear(bool ifShuffle) {

    cout<<"shuffle? "<<ifShuffle<<endl;
    if ( ifShuffle )
        return;
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        auto& obj = m_Stage_Object[i];
        if (!obj) continue;

        if (obj->GetCurrentType() >= ONE_LAYER_COOKIE_OBJECT && obj->GetCurrentType() <= 50) {
            int* neighbors = obj->GetInformationNeibor();
            for (int j = 0; j < 6; ++j) {
                int neighborIdx = neighbors[j]%(m_Size+1);
                if (neighborIdx != -1 && neighborIdx < static_cast<int>(m_Stage_Object.size())) {
                    auto& neighbor = m_Stage_Object[neighborIdx];
                    if (neighbor && !neighbor->GetAppearBool() && neighbor->GetCurrentType() <= STRIPE_COMBINED_OBJECT) {
                        MakeObstaclesDisappear(static_cast<int>(i));
                        break;
                    }
                }
            }
        }
    }
}


void StageObject::PointUpdate(int point ) {
    stage_point_counter[m_Stage] = point;
}

void StageObject::GoalUpdate( int i ) {
    switch ( m_Stage ) {
        case 1:
            if ( m_Stage_Object[i]->GetBlockType() == BROWN_OBJECT ) {
                stage_goal_counter[1]--;
            }
            break;
        case 2:
            if ( m_Stage_Object[i]->GetBlockType() == BROWN_OBJECT ) {
                stage_goal_counter[2]--;
            }
            break;
        case 3:
            stage_goal_counter[3] = stage_point_goal[3] - stage_point_counter[3];
            break;
        case 4:
            stage_goal_counter[4] = stage_point_goal[4] - stage_point_counter[4];
            break;
        case 5:
            if ( m_Stage_Object[i]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT ) {
                stage_goal_counter[5]--;
            }
            break;
        case 6:
            if ( m_Stage_Object[i]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT  && m_Stage_Object[i]->GetType() == NORMAL_OBJECT ) {
                stage_goal_counter[6]--;
            }
            break;
        case 7:
            if ( m_Stage_Object[i]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT  && m_Stage_Object[i]->GetType() == NORMAL_OBJECT ) {
                stage_goal_counter[7]--;
            }
            break;
        default:
            break;
    }
}

int StageObject::GetPoint() {
    return stage_point_counter[m_Stage];
}

void StageObject::AppearAll() {
    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        m_Stage_Object.at(i)->SetVisible( true );
        m_Stage_Object.at(i)->SetAppearBool( true );
    }
    
}

void StageObject::DisAppearAll() {
    for (auto& obj : m_Stage_Object) {
        if (obj) {
            obj->SetAppearBool(false);
            obj->DisAppear();
        }
    }
    this->GetStageGoalObject()->DisAppear();
}

void StageObject::ClearAllClick() {
    for (auto& obj : m_Stage_Object) {
        if (obj) obj->SetClick(false);
    }
}

void StageObject::MakeDisappearWithObject( int current_pos ) {
    if ( m_Stage_Object[current_pos]->GetVisibility() == false ) {
        return;
    }

    switch ( m_Stage_Object[current_pos]->GetCurrentType() ) {
        case FLOWER_COMBINED_OBJECT:
            MakeDisappearWithFlowerCombined( current_pos );
        break;
        case FLOWER_STRIPE_OBJECT:
            MakeDisappearWithStripeFlower( current_pos );
        break;
        case STRIPE_COMBINED_OBJECT:
            MakeDisappearWithStripeCombined( current_pos );
        break;
        case STRIPE_OBJECT:
            MakeDisappearWithStripe( current_pos );
            break;
        case STRIPE_LEFT_RIGHT_OBJECT:
            MakeDisappearWithStripeInLeftRight( current_pos );
            break;
        case STRIPE_RIGHT_LEFT_OBJECT:
            MakeDisappearWithStripeInRightLeft( current_pos );
            break;
        case RAINBOWBALL_OBJECT:
            MakeDisappearWithRainbow( current_pos );
            break;
        case FLOWER_OBJECT:
            MakeDisappearWithFlower( current_pos );
            break;
        case TRIANGLEFLOWER_OBJECT:
            MakeDisappearWithTriangleFlower( current_pos );
            break;
        case STARFLOWER_OBJECT:
            MakeDisappearWithStarFlower( current_pos );
            break;
        case NORMAL_OBJECT:
            m_Stage_Object[current_pos]->DisAppear();
            m_Stage_Object[current_pos]->SetAppearBool( false );
            break;
        case ONE_LAYER_COOKIE_OBJECT:
            // m_Stage_Object[current_pos]->DisAppear();
            m_Stage_Object[current_pos]->SetAppearBool( false );
            // m_Stage_Object[current_pos]->SetCurrentType( NORMAL_OBJECT );
            break;
        case TWO_LAYER_COOKIE_OBJECT:
            // m_Stage_Object[current_pos]->DisAppear();
            m_Stage_Object[current_pos]->SetAppearBool( false );
            break;
        default:
            m_Stage_Object[current_pos]->DisAppear();
            m_Stage_Object[current_pos]->SetAppearBool( false );
            break;
    }
}

void StageObject::MakeDisappearWithStripe( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    cout << "STRIPE\n";
    for ( int i = current_pos , j = current_pos ; ; ) {
        if ( m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1) != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1) );
            i = m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1);
        }
        if ( m_Stage_Object[j]->GetInformationNeibor()[3]%(m_Size+1) != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[3]%(m_Size+1) );
            j = m_Stage_Object[j]->GetInformationNeibor()[3]%(m_Size+1);
        }
        if ( m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1) == -1 && m_Stage_Object[j]->GetInformationNeibor()[3]%(m_Size+1) == -1 )
            break;
    }
}
void StageObject::MakeDisappearWithFlowerCombined( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );

    cout << "FLOWER_COMBINED\n";

    for ( int i = 0 ; i < 6 ; ++i )
    {
        if (m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) != -1)
        {
            MakeDisappearWithObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1)  );

            for ( int j = 0 ; j < 6 ; ++j ) {
                if (m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) ] ->GetInformationNeibor()[j]%(m_Size+1) != -1)
                {
                    MakeDisappearWithObject( m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) ] ->GetInformationNeibor()[j]%(m_Size+1)  );

                }
            }
        }
    }
}

void StageObject::MakeDisappearWithStripeFlower( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    cout << "STRIPE_FLOWER\n";

    // m_Stage_Object[current_pos]->GetCurrentType();
    int extend_side[2] = {-1} ;
    int side = -1 ;
    if (m_Stage_Object[current_pos]->GetType() == STRIPE_OBJECT )
    {
        if (m_Stage_Object[current_pos]->GetInformationNeibor()[1]%(m_Size+1) != -1)
            extend_side[0] = 1 ;
        else if (m_Stage_Object[current_pos]->GetInformationNeibor()[2]%(m_Size+1) != -1)
            extend_side[0] = 2 ;

        if (m_Stage_Object[current_pos]->GetInformationNeibor()[4]%(m_Size+1) != -1)
            extend_side[1] = 4 ;
        else if (m_Stage_Object[current_pos]->GetInformationNeibor()[5]%(m_Size+1) != -1)
            extend_side[1] = 5 ;

        side = 0 ;

    }
    else if (m_Stage_Object[current_pos]->GetType() == STRIPE_LEFT_RIGHT_OBJECT )
    {
        if (m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) != -1)
            extend_side[0] = 0 ;
        else if (m_Stage_Object[current_pos]->GetInformationNeibor()[1]%(m_Size+1) != -1)
            extend_side[0] = 1 ;

        if (m_Stage_Object[current_pos]->GetInformationNeibor()[3]%(m_Size+1) != -1)
            extend_side[1] = 3 ;
        else if (m_Stage_Object[current_pos]->GetInformationNeibor()[4]%(m_Size+1) != -1)
            extend_side[1] = 4 ;

        side = 2 ;
    }
    else if (m_Stage_Object[current_pos]->GetType() == STRIPE_RIGHT_LEFT_OBJECT )
    {
        if (m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) != -1)
            extend_side[0] = 0 ;
        else if (m_Stage_Object[current_pos]->GetInformationNeibor()[2]%(m_Size+1) != -1)
            extend_side[0] = 2 ;

        if (m_Stage_Object[current_pos]->GetInformationNeibor()[3]%(m_Size+1) != -1)
            extend_side[1] = 3 ;
        else if (m_Stage_Object[current_pos]->GetInformationNeibor()[5]%(m_Size+1) != -1)
            extend_side[1] = 5 ;

        side = 1 ;
    }
    m_Stage_Object[current_pos]->SetBlockType(NORMAL_OBJECT);
    // cout<<"extend_side: "<<extend_side[0]<<"   "<<extend_side[1]<<endl;

    for ( int i = current_pos , j = current_pos ; ; ) {
        if ( m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) );
            i = m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1);
        }
        if ( m_Stage_Object[j]->GetInformationNeibor()[side+3]%(m_Size+1) != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[side+3]%(m_Size+1) );
            j = m_Stage_Object[j]->GetInformationNeibor()[side+3]%(m_Size+1);
        }
        if ( m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) == -1 && m_Stage_Object[j]->GetInformationNeibor()[side+3]%(m_Size+1) == -1 )
            break;
    }

    if (extend_side[0] != -1) {
        m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[extend_side[0]]%(m_Size+1) ]->DisAppear();
        m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[extend_side[0]]%(m_Size+1) ]->SetAppearBool( false );

        for ( int i = m_Stage_Object[current_pos]->GetInformationNeibor()[extend_side[0]]%(m_Size+1) , j = m_Stage_Object[current_pos]->GetInformationNeibor()[extend_side[0]]%(m_Size+1) ; ; ) {
            if ( m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) != -1 ) {
                MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) );
                i = m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1);
            }
            if ( m_Stage_Object[j]->GetInformationNeibor()[side + 3]%(m_Size+1) != -1 ) {
                MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[side + 3]%(m_Size+1) );
                j = m_Stage_Object[j]->GetInformationNeibor()[side + 3]%(m_Size+1);
            }
            if ( m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) == -1 && m_Stage_Object[j]->GetInformationNeibor()[side + 3]%(m_Size+1) == -1 )
                break;
        }
    }

    if (extend_side[1] != -1) {
        m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[extend_side[1]]%(m_Size+1) ]->DisAppear();
        m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[extend_side[1]]%(m_Size+1) ]->SetAppearBool( false );

        for ( int i = m_Stage_Object[current_pos]->GetInformationNeibor()[extend_side[1]]%(m_Size+1) , j = m_Stage_Object[current_pos]->GetInformationNeibor()[extend_side[1]]%(m_Size+1) ; ; ) {
            if ( m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) != -1 ) {
                MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) );
                i = m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1);
            }
            if ( m_Stage_Object[j]->GetInformationNeibor()[side + 3]%(m_Size+1) != -1 ) {
                MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[side + 3]%(m_Size+1) );
                j = m_Stage_Object[j]->GetInformationNeibor()[side + 3]%(m_Size+1);
            }
            if ( m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) == -1 && m_Stage_Object[j]->GetInformationNeibor()[side + 3]%(m_Size+1) == -1 )
                break;
        }
    }


}

void StageObject::MakeDisappearWithStripeCombined( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    cout << "STRIPE_COMBINED"<<endl;

    int side = -1 ;
    if (m_Stage_Object[current_pos]->GetType() == STRIPE_OBJECT )
    {
        side = 0 ;

    }
    else if (m_Stage_Object[current_pos]->GetType() == STRIPE_LEFT_RIGHT_OBJECT )
    {
        side = 2 ;
    }
    else if (m_Stage_Object[current_pos]->GetType() == STRIPE_RIGHT_LEFT_OBJECT )
    {
        side = 1 ;
    }
    m_Stage_Object[current_pos]->SetBlockType(NORMAL_OBJECT);

    for ( int i = current_pos , j = current_pos ; ; ) {
        if ( m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) );
            i = m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1);
        }
        if ( m_Stage_Object[j]->GetInformationNeibor()[side+3]%(m_Size+1) != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[side+3]%(m_Size+1) );
            j = m_Stage_Object[j]->GetInformationNeibor()[side+3]%(m_Size+1);
        }
        if ( m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) == -1 && m_Stage_Object[j]->GetInformationNeibor()[side+3]%(m_Size+1) == -1 )
            break;
    }


}

void StageObject::MakeDisappearWithStripeInLeftRight( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    cout << "STRIPE_LEFT_RIGHT\n";
    for ( int i = current_pos , j = current_pos ; ; ) {
        if ( m_Stage_Object[i]->GetInformationNeibor()[2]%(m_Size+1) != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[2]%(m_Size+1) );
            i = m_Stage_Object[i]->GetInformationNeibor()[2]%(m_Size+1);
        }
        if ( m_Stage_Object[j]->GetInformationNeibor()[5]%(m_Size+1) != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[5]%(m_Size+1)  );
            j = m_Stage_Object[j]->GetInformationNeibor()[5]%(m_Size+1);
        }
        if ( m_Stage_Object[i]->GetInformationNeibor()[2]%(m_Size+1) == -1 && m_Stage_Object[j]->GetInformationNeibor()[5]%(m_Size+1) == -1 )
            break;
    }
}

void StageObject::MakeDisappearWithStripeInRightLeft( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    cout << "STRIPE_RIGHT_LEFT\n";
    for ( int i = current_pos , j = current_pos ; ; ) {
        if ( m_Stage_Object[i]->GetInformationNeibor()[1]%(m_Size+1) != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[1]%(m_Size+1) );
            i = m_Stage_Object[i]->GetInformationNeibor()[1]%(m_Size+1);
        }
        if ( m_Stage_Object[j]->GetInformationNeibor()[4]%(m_Size+1) != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[4]%(m_Size+1) );
            j = m_Stage_Object[j]->GetInformationNeibor()[4]%(m_Size+1);
        }
        if ( m_Stage_Object[i]->GetInformationNeibor()[1]%(m_Size+1) == -1 && m_Stage_Object[j]->GetInformationNeibor()[4]%(m_Size+1) == -1 )
            break;
    }
}

void StageObject::MakeDisappearWithRainbow( int current_pos ) { //get type: next move
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );

    if ( m_Stage_Object[current_pos]->GetBlockType() == 0 ) { // no color
        m_Stage_Object[current_pos]->SetBlock( BLUE_OBJECT );
    }

    cout << "RAINBOW BALL\n";

    if (m_Stage_Object[current_pos]->GetType() == RAINBOWBALL_OBJECT) {
        for ( int i = 1 ; i < m_Size+1 ; ++i ) {
                MakeDisappearWithObject( i );
        }
        return ;
    }

    if (m_Stage_Object[current_pos]->GetType() != 0) {
        // change same color to special type
        for ( int i = 1 ; i < m_Size+1 ; ++i ) {
            if ( i != current_pos && m_Stage_Object[current_pos]->GetBlockType() == m_Stage_Object[i]->GetBlockType() ) {
                //random

                if (m_Stage_Object[current_pos]->GetType() >=2 && m_Stage_Object[current_pos]->GetType() <=4) {
                    std::random_device rd;  // 硬體隨機數產生器
                    std::mt19937 gen(rd()); // Mersenne Twister 亂數引擎
                    std::uniform_int_distribution<int> dist(2, 4); // 產生 2 到 4 之間的整數

                    int random_number = dist(gen);

                    m_Stage_Object[i]->SetCurrentType( random_number );
                }
                    m_Stage_Object[i]->SetCurrentType( m_Stage_Object[current_pos]->GetType() );
            }
        }
    }

    m_Stage_Object[current_pos]->SetBlockType(NORMAL_OBJECT);

    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if ( i != current_pos && m_Stage_Object[current_pos]->GetBlockType() == m_Stage_Object[i]->GetBlockType() ) {

            MakeDisappearWithObject( i );
            for ( int j = 0 ; j < 6 ; ++j ) {
                if (m_Stage_Object[i]->GetInformationNeibor()[j]%(m_Size+1) != -1 && m_Stage_Object[i]->GetCurrentType() == NORMAL_OBJECT){

                    if (  m_Stage_Object[m_Stage_Object[i]->GetInformationNeibor()[j]%(m_Size+1)]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT || m_Stage_Object[m_Stage_Object[i]->GetInformationNeibor()[j]%(m_Size+1)]->GetCurrentType() == TWO_LAYER_COOKIE_OBJECT)  {
                        MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[j]%(m_Size+1) );
                    }
                }
            }
        }
    }
}

void StageObject::MakeDisappearWithTriangleFlower( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    cout << "TRIANGLE_FLOWER\n";
    for ( int i = 0 ; i < 6 ; ++i )
    {
        if (m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) != -1)
            MakeDisappearWithObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1)  );
    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) ] ->GetInformationNeibor()[5]%(m_Size+1) != -1)
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) ] ->GetInformationNeibor()[5]%(m_Size+1) );

    if (m_Stage_Object[current_pos]->GetInformationNeibor()[2]%(m_Size+1) != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[2]%(m_Size+1) ] ->GetInformationNeibor()[1]%(m_Size+1) != -1)
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[2]%(m_Size+1) ] ->GetInformationNeibor()[1]%(m_Size+1) );

    if (m_Stage_Object[current_pos]->GetInformationNeibor()[4]%(m_Size+1) != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[4]%(m_Size+1) ] ->GetInformationNeibor()[3]%(m_Size+1) != -1)
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[4]%(m_Size+1) ] ->GetInformationNeibor()[3]%(m_Size+1) );

}

void StageObject::MakeDisappearWithFlower( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    cout << "FLOWER\n";
    for ( int i = 0 ; i < 6 ; ++i )
    {
        if (m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) != -1){
            MakeDisappearWithObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) );
        }

    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) ] ->GetInformationNeibor()[5]%(m_Size+1) != -1){
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) ] ->GetInformationNeibor()[5]%(m_Size+1)  );
    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) ] ->GetInformationNeibor()[1]%(m_Size+1) != -1){
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) ] ->GetInformationNeibor()[1]%(m_Size+1) );
    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[3]%(m_Size+1) != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[3]%(m_Size+1) ] ->GetInformationNeibor()[2]%(m_Size+1) != -1){
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[3]%(m_Size+1) ] ->GetInformationNeibor()[2]%(m_Size+1)  );
    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[3]%(m_Size+1) != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[3]%(m_Size+1) ] ->GetInformationNeibor()[4]%(m_Size+1) != -1){
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[3]%(m_Size+1) ] ->GetInformationNeibor()[4]%(m_Size+1) );
    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[1]%(m_Size+1) != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[1]%(m_Size+1) ] ->GetInformationNeibor()[2]%(m_Size+1) != -1){
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[1]%(m_Size+1) ] ->GetInformationNeibor()[2]%(m_Size+1) );
    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[5]%(m_Size+1) != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[5]%(m_Size+1) ] ->GetInformationNeibor()[4]%(m_Size+1) != -1){
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[5]%(m_Size+1) ] ->GetInformationNeibor()[4]%(m_Size+1) );
    }
}

void StageObject::MakeDisappearWithStarFlower( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    cout << "STAR_FLOWER\n";
    for ( int i = 0 ; i < 6 ; ++i )
    {
        if (m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) != -1){
            MakeDisappearWithObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1)  );

            if (m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1)] ->GetInformationNeibor()[i]%(m_Size+1) != -1)
                MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1)] ->GetInformationNeibor()[i]%(m_Size+1) );

        }
    }
}

bool StageObject::DisappearMethodOfOneLine( int current_pos , int *total_length ) {

    bool cont_to_check = false ;

    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( (total_length[i] + total_length[j] ) == 2 ) {

            bool left_check = true ;
            bool right_check = true ;

            //check all side appear
            if (total_length[i] > 0)
                left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) , i, total_length[i]-1);

            if (total_length[j] > 0)
                right_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1) , j, total_length[j]-1);


            //all side appear checked(true)
            if ( m_Stage_Object[current_pos]->GetAppearBool() == true && left_check == true && right_check == true )
            {
                m_Stage_Object[current_pos]->SetAppearBool( false );
                cout<<"Line"<<endl;
                cont_to_check = true ;
                //all disappear(except switched blocks)
                if (total_length[i] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) , i, total_length[i]-1);

                if (total_length[j] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1) , j, total_length[j]-1);

                return cont_to_check;
            }

        }
        else if (total_length[i] + total_length[j]  > 2) // check all lines initial(line stripe rainbowball)
        {
            bool left_check_switch = true ;
            bool right_check_switch = true ;

            //check all side appear
            if (total_length[i] > 0)
                left_check_switch = checkSwitchedAllInfoWithZero( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) , i, total_length[i]-1);

            if (total_length[j] > 0)
                right_check_switch = checkSwitchedAllInfoWithZero( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1) , j, total_length[j]-1);

            if (left_check_switch == true && right_check_switch == true && m_Stage_Object[current_pos]->GetAppearBool() == true)
            {
                cont_to_check = true ;
                if (total_length[i] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);

                if (total_length[j] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1), j, total_length[j]-1);

                return cont_to_check;
            }
        }
    }
    return cont_to_check;

}

int StageObject::DisappearMethodOfStripe( int current_pos, int* total_length, int priority ) {
    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        // do not make true if it was checked
        if ( (total_length[i] + total_length[j] ) == 3 ) {
            bool left_check = true ;
            bool right_check = true ;

            //check all side appear
            if (total_length[i] > 0)
                left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);

            if (total_length[j] > 0)
                right_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1) , j, total_length[j]-1);

            // check initial switch -> find switch side
            if (m_Stage_Object[current_pos]->GetSwitchedInfo() == 2 && priority == 2 && m_Stage_Object[current_pos]->GetAppearBool() == true  && left_check == true && right_check == true)
            {
                m_Stage_Object[current_pos]->SetAppearBool( false );
                //all disappear(except switched blocks)
                if (total_length[i] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) , i, total_length[i]-1);
                if (total_length[j] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1) , j, total_length[j]-1);

                //find initial neighbor side
                for ( int switch_side = 0  ; switch_side < 6 ; ++switch_side )
                {

                    if ( m_Stage_Object[current_pos]->GetInformationNeibor()[switch_side]%(m_Size+1) != -1) {
                        if (m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[switch_side]%(m_Size+1) ]->GetSwitchedInfo() == 2 )
                        {
                            cout << "Stripe" << endl;
                            return switch_side;
                        }
                    }
                }
            }
            else if (m_Stage_Object[current_pos]->GetSwitchedInfo() == 1 && priority == 1 && m_Stage_Object[current_pos]->GetAppearBool() == true  && left_check == true && right_check == true)
            {
                //all disappear
                m_Stage_Object[current_pos]->SetAppearBool( false );
                if (total_length[i] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);
                if (total_length[j] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1), j, total_length[j]-1);

                cout << "Stripe" << endl;
                return 0;
            }

        }
    }
    return -1;
}

bool StageObject::DisappearMethodOfFlower( int current_pos, int* total_length ) {

    bool cont_to_check = false ; //two side 1 + another 2
    int check_side = -1;

    for ( int i = 0  ; i < 6 ; ++i ) //another 2
    {
        if ( total_length[i] >= 2 )
        {
            bool checkside_check = true ;
            checkside_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);

            if (checkside_check == true)
            {
                check_side = i ;
                break;
            }

        }
    }

    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( i != check_side && j != check_side && check_side != -1 )
        {
            bool left_check = true ;
            bool right_check = true ;

            //check all side appear
            if (total_length[i] > 0)
                left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) , i, total_length[i]-1);

            if (total_length[j] > 0)
                right_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1) , j, total_length[j]-1);

            if ( total_length[i] >= 1 && total_length[j] >= 1  && m_Stage_Object[current_pos]->GetAppearBool() == true  && left_check == true && right_check == true && check_side != -1) {//two side 1
                cont_to_check = true ;
                m_Stage_Object[current_pos]->SetAppearBool( false );
                cout<<"Flower"<<endl;

                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[check_side]%(m_Size+1) , check_side, total_length[check_side]-1);
                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);
                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1) , j, total_length[j]-1);
                break;
            }


        }
    }

    return cont_to_check;
}

bool StageObject::DisappearMethodOfStarFlower(  int current_pos, int* total_length ) {

    bool cont_to_check = false ; //two side 2
    int check_sides = 0;


    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( total_length[i] >= 1 && total_length[j] >= 1)
        {
            bool left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);
            bool right_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1), j, total_length[j]-1);

            if (left_check == true && right_check == true )
                check_sides++ ;
        }
    }


    if (check_sides >= 2 && m_Stage_Object[current_pos]->GetAppearBool() == true)
    {
        for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j )
        {
            if (total_length[i] > 0)
                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);
            if (total_length[j] > 0)
                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1), j, total_length[j]-1);
        }
        m_Stage_Object[current_pos]->SetAppearBool( false );
        cout<<"Star Flower"<<endl;
        cont_to_check = true ;
    }

    return cont_to_check;
}

bool StageObject::DisappearMethodOfTriangleFlower( int current_pos , int* total_length ) {
    bool cont_to_check = false ; //two side >=2
    int check = 0;
    // two side >= 2
    for ( int i = 0  ; i < 6 ; ++i ) {
        if ( total_length[i] >= 2 ) {
            bool left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);

            if (left_check == true)
                check ++ ;
        }
    }

    if (check >= 2 && m_Stage_Object[current_pos]->GetAppearBool() == true)
    {
        m_Stage_Object[current_pos]->SetBlockType( TRIANGLEFLOWER_OBJECT );
        m_Stage_Object[current_pos]->SetAppearBool( false );
        cout<<"Triangle Flower"<<endl;
        cont_to_check = true ;
        for ( int i = 0  ; i < 6 ; ++i )
        {
            if (total_length[i] > 0)
                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);
        }

    }

    return cont_to_check;
}

bool StageObject::DisappearMethodOfRainbowBall(  int current_pos, int* total_length, int priority ) {
    bool cont_to_check = false ;
    bool left_check = false;
    bool right_check = false;
    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( (total_length[i] + total_length[j] ) >= 4 ) {

            if ( total_length[i] > 0 )
                left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);
            if ( total_length[j] > 0 )
                right_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1), j, total_length[j]-1);

            if (m_Stage_Object[current_pos]->GetSwitchedInfo() == priority && m_Stage_Object[current_pos]->GetAppearBool() == true && left_check == true && right_check == true)
            {
                m_Stage_Object[current_pos]->SetAppearBool( false );
                cout<<"Rainbow Ball"<<endl;
                cont_to_check = true ;
                //all disappear(except switched blocks)
                if (total_length[i] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);
                if (total_length[j] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1), j, total_length[j]-1);
                return cont_to_check;
            }


        }
    }
    return cont_to_check;
}

void StageObject::DisappearBySingleObject( int current_pos, int side, int length_left) {
    m_Stage_Object[current_pos]->SetAppearBool( false );

    if( !m_Stage_Object[current_pos]  )
        return;

    if ( length_left  >  0 )
    {
        DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[side]%(m_Size+1), side, length_left - 1) ;
    }
}

void StageObject::Dropping_method( const int current_position ) {
    if ( !m_Stage_Object[current_position] || m_Stage_Object[current_position]->GetInformationNeibor()[0]%(m_Size+1) == -1  || !m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[0]%(m_Size+1)] || m_Stage_Object[current_position]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT || m_Stage_Object[current_position]->GetCurrentType() == TWO_LAYER_COOKIE_OBJECT )
        return;
    if ( current_position < m_Size+1 ) {
        int next_position; 
        if ( m_Stage_Object[current_position]->GetInformationNeibor()[0]%(m_Size+1) != -1 && ( m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[0]%(m_Size+1)]->GetCurrentType() != ONE_LAYER_COOKIE_OBJECT && m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[0]%(m_Size+1)]->GetCurrentType() != TWO_LAYER_COOKIE_OBJECT ) )
            next_position = m_Stage_Object[current_position]->GetInformationNeibor()[0]%(m_Size+1);
        else if ( m_Stage_Object[current_position]->GetInformationNeibor()[5]%(m_Size+1) != -1 && ( m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[5]%(m_Size+1)]->GetCurrentType() != ONE_LAYER_COOKIE_OBJECT && m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[5]%(m_Size+1)]->GetCurrentType() != TWO_LAYER_COOKIE_OBJECT ) )
            next_position = m_Stage_Object[current_position]->GetInformationNeibor()[5]%(m_Size+1);
        else if ( m_Stage_Object[current_position]->GetInformationNeibor()[1]%(m_Size+1) != -1 && ( m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[1]%(m_Size+1)]->GetCurrentType() != ONE_LAYER_COOKIE_OBJECT && m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[1]%(m_Size+1)]->GetCurrentType() != TWO_LAYER_COOKIE_OBJECT ) )
            next_position = m_Stage_Object[current_position]->GetInformationNeibor()[1]%(m_Size+1);
        else
            return;
        bool flag = m_Stage_Object[next_position]->GetAppearBool();

        m_Stage_Object[current_position]->SetSwitched(1);
        m_Stage_Object[next_position]->SetSwitched(1);
        m_Stage_Object[current_position]->SwitchPosition( m_Stage_Object[next_position] );

        std::shared_ptr<GameCharacter> NewObject = m_Stage_Object[current_position];
        m_Stage_Object[current_position] = m_Stage_Object[next_position];
        m_Stage_Object[next_position] = NewObject;
        m_Stage_Object[current_position]->SetAppearBool( flag );

        Dropping_method( next_position );
    }

    return;
}

bool StageObject::checkAppearanceOfObject ( int i, int side, int length_left) {
    bool return_bool = true;

    if( !m_Stage_Object[i]  )
        return false;

    if ( m_Stage_Object[i]->GetAppearBool() == true )
    {
        if( length_left >  0 )
        {
            return_bool = checkAppearanceOfObject (  m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) , side, length_left - 1);
            return return_bool;
        }
        else
        {
            return m_Stage_Object[i]->GetAppearBool();
        }
    }

    else{
        return false ;
    }
}

bool StageObject::checkSwitchedAllInfoWithZero ( int i, int side, int length_left) {
    if( !m_Stage_Object[i]  )
        return false;

    if ( m_Stage_Object[i]->GetSwitchedInfo() == 0 )
    {
        if( length_left >  0 )
            return checkSwitchedAllInfoWithZero ( m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1), side, length_left - 1) ;
        else
            return true;
    }
    else
        return false ;
}

int StageObject::CheckNextAppearance( int i, int side, int length ) {
    if (!m_Stage_Object[i] || m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) == -1 || !m_Stage_Object[ m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) ] )
        return length;

    if ( IsSameColor(m_Stage_Object[i]->GetBlockType() ,  m_Stage_Object[ m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) ]->GetBlockType()) &&  m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) != -1 ){
        return CheckNextAppearance(  m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) , side, length + 1 ) ;
    }
    else
        return length ;
}

bool StageObject::IsSameColor(int blockType1, int blockType2) {
    return ((blockType1 % 10) == (blockType2 % 10) 
    && blockType1 != NO_COLOR && blockType2 != NO_COLOR);
}

void StageObject::SetUp(int stage) {
    for (auto& obj : m_Stage_Object) {
        if (obj && obj->GetAppearBool()) {
            obj->Appear();
        }
    }
    m_Stage_Object.at(0)->DisAppear();
    this->GetStageGoalObject()->Appear();
    InitializeStageCharacter(stage);
    CheckAppearance(0, stage, true);
}


void StageObject::CheckClickSwitch( int check , int i , std::shared_ptr<TaskText> point ) {
    for ( int j = 0 ; j < 6 ; ++j ) {
        if( m_Stage_Object[i]->GetInformationNeibor()[j]%(m_Size+1) == check && m_Stage_Object[i]->GetInformationNeibor()[j] <= m_Size && m_Stage_Object[check]->GetInformationNeibor()[j] <= m_Size) {
            m_Stage_Object[i]->SetSwitched(2);
            m_Stage_Object[check]->SetSwitched(2);
            std::cout<<"pos: "<<i<<"  "<<check<<std::endl;
            std::cout<<"set SetSwitched to 2"<<std::endl;
            m_Stage_Object[i]->SwitchPosition( m_Stage_Object[check] );
            std::shared_ptr<GameCharacter> NewObject = m_Stage_Object[check];
            m_Stage_Object[check] = m_Stage_Object[i];
            m_Stage_Object[i] = NewObject;

            if ( m_Stage_Object[check]->GetCurrentType() == RAINBOWBALL_OBJECT ) {
                m_Stage_Object[check]->SetBlock( m_Stage_Object[i]->GetBlockType() );
                m_Stage_Object[check]->SetBlockType( m_Stage_Object[i]->GetCurrentType() );
                cout<<"find rainbow ball"<<endl;
            }
            if ( m_Stage_Object[i]->GetCurrentType() == RAINBOWBALL_OBJECT ) {
                m_Stage_Object[i]->SetBlock( m_Stage_Object[check]->GetBlockType() ); //color
                m_Stage_Object[i]->SetBlockType( m_Stage_Object[check]->GetCurrentType() );
                cout<<"find rainbow ball"<<endl;
            }

            // flower + flower
            if ( m_Stage_Object[check]->GetCurrentType() >= FLOWER_OBJECT && m_Stage_Object[check]->GetCurrentType() <= TRIANGLEFLOWER_OBJECT && m_Stage_Object[i]->GetCurrentType() >= FLOWER_OBJECT && m_Stage_Object[i]->GetCurrentType() <= TRIANGLEFLOWER_OBJECT ) {
                m_Stage_Object[i]->SetCurrentType( FLOWER_COMBINED_OBJECT );
                m_Stage_Object[check]->SetCurrentType( FLOWER_COMBINED_OBJECT );
                cout<<"find flower combined"<<endl;
            }

            //to be opt.
            // flower + stripe 1
            if ( m_Stage_Object[check]->GetCurrentType() >= STRIPE_OBJECT && m_Stage_Object[check]->GetCurrentType() <= STRIPE_RIGHT_LEFT_OBJECT &&  m_Stage_Object[i]->GetCurrentType() >= FLOWER_OBJECT && m_Stage_Object[i]->GetCurrentType() <= TRIANGLEFLOWER_OBJECT  ) {
                m_Stage_Object[i]->SetBlockType( NORMAL_OBJECT);
                m_Stage_Object[check]->SetBlockType( m_Stage_Object[check]->GetCurrentType());
                m_Stage_Object[check]->SetCurrentType( FLOWER_STRIPE_OBJECT );
                m_Stage_Object[i]->SetCurrentType( NORMAL_OBJECT );
                cout<<"find flower stripe"<<endl;
            }

            //to be opt.
            // flower + stripe 2
            if ( m_Stage_Object[check]->GetCurrentType() >= FLOWER_OBJECT && m_Stage_Object[check]->GetCurrentType() <= TRIANGLEFLOWER_OBJECT &&  m_Stage_Object[i]->GetCurrentType() >= STRIPE_OBJECT && m_Stage_Object[i]->GetCurrentType() <= STRIPE_RIGHT_LEFT_OBJECT   ) {
                m_Stage_Object[i]->SetBlockType( m_Stage_Object[i]->GetCurrentType());
                m_Stage_Object[check]->SetBlockType( NORMAL_OBJECT);
                m_Stage_Object[i]->SetCurrentType( FLOWER_STRIPE_OBJECT );
                m_Stage_Object[check]->SetCurrentType( NORMAL_OBJECT );
                cout<<"find flower stripe"<<endl;
            }

            //to be opt.
            // stripe + stripe
            if ( m_Stage_Object[check]->GetCurrentType() >= STRIPE_OBJECT && m_Stage_Object[check]->GetCurrentType() <= STRIPE_RIGHT_LEFT_OBJECT &&  m_Stage_Object[i]->GetCurrentType() >= STRIPE_OBJECT && m_Stage_Object[i]->GetCurrentType() <= STRIPE_RIGHT_LEFT_OBJECT   ) {
                m_Stage_Object[i]->SetBlockType( m_Stage_Object[i]->GetCurrentType());
                m_Stage_Object[check]->SetBlockType( m_Stage_Object[check]->GetCurrentType());
                m_Stage_Object[check]->SetCurrentType( STRIPE_COMBINED_OBJECT );
                m_Stage_Object[i]->SetCurrentType( STRIPE_COMBINED_OBJECT );
                cout<<"find stripe combined"<<endl;
            }

            //all check but no disappear
            if ( !CheckAppearance( 1 , m_Stage , false ) ) {
                m_Stage_Object[i]->SwitchPosition( m_Stage_Object[check] );
                std::shared_ptr<GameCharacter> NewObject = m_Stage_Object[check];
                m_Stage_Object[check] = m_Stage_Object[i];
                m_Stage_Object[i] = NewObject;
            } 
            else {
                point->SetMove( point->GetMove() - 1 );
            }
            point->SetPoint( stage_point_counter[m_Stage] );
            point->UpdateText();
            // std::cout<<"moves left: "<<GetMovesLeft()<<std::endl;
            break;
        }
    }
}
std::pair<int, int> StageObject::CheckShuffleDemands() {
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        for (int j = 0; j < 6; ++j) {
            const int neighbor_no = m_Stage_Object[i]->GetInformationNeibor()[j]%(m_Size+1);
            if (neighbor_no != -1 && neighbor_no < static_cast<int>(m_Stage_Object.size()) &&
                m_Stage_Object[i]->GetCurrentType() <= STRIPE_COMBINED_OBJECT &&
                m_Stage_Object[neighbor_no]->GetCurrentType() <= STRIPE_COMBINED_OBJECT) {
                m_Stage_Object[i]->SwitchPosition(m_Stage_Object[neighbor_no]);
                std::swap(m_Stage_Object[i], m_Stage_Object[neighbor_no]);

                auto result = CheckRainbowUsing();
                if (result.first != -1 || result.second != -1) {
                    m_Stage_Object[i]->SwitchPosition(m_Stage_Object[neighbor_no]);
                    std::swap(m_Stage_Object[i], m_Stage_Object[neighbor_no]);
                    return {result.first, result.second};
                }

                m_Stage_Object[i]->SwitchPosition(m_Stage_Object[neighbor_no]);
                std::swap(m_Stage_Object[i], m_Stage_Object[neighbor_no]);
            }
        }
    }

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        for (int j = 0; j < 6; ++j) {
            const int neighbor_no = m_Stage_Object[i]->GetInformationNeibor()[j]%(m_Size+1);
            if (neighbor_no != -1 && neighbor_no < static_cast<int>(m_Stage_Object.size()) &&
                m_Stage_Object[i]->GetCurrentType() <= STRIPE_COMBINED_OBJECT &&
                m_Stage_Object[neighbor_no]->GetCurrentType() <= STRIPE_COMBINED_OBJECT) {
                m_Stage_Object[i]->SwitchPosition(m_Stage_Object[neighbor_no]);
                std::swap(m_Stage_Object[i], m_Stage_Object[neighbor_no]);

                auto result = CheckSpecialBlocksNeighbor();
                if (result.first != -1 || result.second != -1) {
                    m_Stage_Object[i]->SwitchPosition(m_Stage_Object[neighbor_no]);
                    std::swap(m_Stage_Object[i], m_Stage_Object[neighbor_no]);
                    return {result.first, result.second};
                }

                m_Stage_Object[i]->SwitchPosition(m_Stage_Object[neighbor_no]);
                std::swap(m_Stage_Object[i], m_Stage_Object[neighbor_no]);
            }
        }
    }

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        for (int j = 0; j < 6; ++j) {
            const int neighbor_no = m_Stage_Object[i]->GetInformationNeibor()[j]%(m_Size+1);
            if (neighbor_no != -1 && neighbor_no < static_cast<int>(m_Stage_Object.size()) &&
                m_Stage_Object[i]->GetCurrentType() <= STRIPE_COMBINED_OBJECT &&
                m_Stage_Object[neighbor_no]->GetCurrentType() <= STRIPE_COMBINED_OBJECT) {
                m_Stage_Object[i]->SwitchPosition(m_Stage_Object[neighbor_no]);
                std::swap(m_Stage_Object[i], m_Stage_Object[neighbor_no]);

                if (CheckLineMaking()) {
                    m_Stage_Object[i]->SwitchPosition(m_Stage_Object[neighbor_no]);
                    std::swap(m_Stage_Object[i], m_Stage_Object[neighbor_no]);
                    return {static_cast<int>(i), neighbor_no};
                }

                m_Stage_Object[i]->SwitchPosition(m_Stage_Object[neighbor_no]);
                std::swap(m_Stage_Object[i], m_Stage_Object[neighbor_no]);
            }
        }
    }

    return {-1, -1};
}

bool StageObject::CheckLineMaking() {
    for (size_t current_pos = 1; current_pos < m_Stage_Object.size(); ++current_pos) {
        for (int check_side = 0; check_side < 3; ++check_side) {
            int length = 1;

            if (m_Stage_Object[current_pos]->GetInformationNeibor()[check_side]%(m_Size+1) != -1 &&
                IsSameColor(m_Stage_Object[current_pos]->GetBlockType(), m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[check_side]%(m_Size+1)]->GetBlockType())) {
                length += CheckNextAppearance(m_Stage_Object[current_pos]->GetInformationNeibor()[check_side]%(m_Size+1), check_side, 1);
            }

            if (m_Stage_Object[current_pos]->GetInformationNeibor()[check_side + 3]%(m_Size+1) != -1 &&
                IsSameColor(m_Stage_Object[current_pos]->GetBlockType(), m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[check_side + 3]%(m_Size+1)]->GetBlockType())) {
                length += CheckNextAppearance(m_Stage_Object[current_pos]->GetInformationNeibor()[check_side + 3]%(m_Size+1), check_side + 3, 1);
            }

            if (length >= 3) return true;
        }
    }
    return false;
}

std::pair<int, int> StageObject::CheckRainbowUsing() {
    for (size_t current_pos = 1; current_pos < m_Stage_Object.size(); ++current_pos) {
        if (m_Stage_Object[current_pos]->GetCurrentType() == RAINBOWBALL_OBJECT) {
            for (int j = 0; j < 6; ++j) {
                if (m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1) != -1)
                    return {static_cast<int>(current_pos), m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1)};
            }
        }
    }
    return {-1, -1};
}

std::pair<int, int> StageObject::CheckSpecialBlocksNeighbor() {
    for (size_t current_pos = 1; current_pos < m_Stage_Object.size(); ++current_pos) {
        if (m_Stage_Object[current_pos]->GetCurrentType() >= STRIPE_OBJECT && m_Stage_Object[current_pos]->GetCurrentType() <= TRIANGLEFLOWER_OBJECT) {
            for (int j = 0; j < 6; ++j) {
                int neighbor = m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1);
                if (neighbor != -1 && neighbor < static_cast<int>(m_Stage_Object.size()) &&
                    m_Stage_Object[neighbor]->GetCurrentType() >= STRIPE_OBJECT && m_Stage_Object[neighbor]->GetCurrentType() <= TRIANGLEFLOWER_OBJECT) {
                    return {static_cast<int>(current_pos), neighbor};
                }
            }
        }
    }
    return {-1, -1};
}

void StageObject::UseHammer( std::shared_ptr<Item> Tool ) {

    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if ( m_Stage_Object.at(i)->IfClick() ) {
            printf( "HAMMER\n");
            m_Stage_Object.at(i)->SetAppearBool(false);
            CheckAppearance( 1 , m_Stage , false );
            Tool->Update();
        }
    }

}

void StageObject::UseMagicStick (std::shared_ptr<Item> Tool) {

    
    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if ( m_Stage_Object.at(i)->IfClick() ) {
            cout<<"UseMagicStick"<<endl;
            std::random_device rd;  // 硬體隨機數產生器
            std::mt19937 gen(rd()); // Mersenne Twister 亂數引擎
            std::uniform_int_distribution<int> dist(5, 7); // 產生 5 到 7 之間的整數

            int random_number = dist(gen);

            m_Stage_Object.at(i)->SetCurrentType(random_number);
            m_Stage_Object.at(i)->SetBlockType(random_number);
            CheckSpecialObject(static_cast<int>(i));
            m_Stage_Object.at(i)->SetBlockType(NORMAL_OBJECT);
            
            m_Stage_Object[i]->SetGenerate(true);
            MakeDisappear();
            Tool->Update();
            break;
        }
    }

}

void StageObject::UseMagicGlove(std::shared_ptr<Item> Tool) {

    auto objectArray = this->GetStageObject();
    
    if ( !objectArray.at(0)->GetVisibility() ) {
        is_click = 0;
    }
    for (int i = 1; i < m_Size + 1; ++i) {
        if (objectArray.at(i)->IfClick()) {
            if (objectArray.at(i)->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT ||
                objectArray.at(i)->GetCurrentType() == TWO_LAYER_COOKIE_OBJECT)
                continue;

            if (is_click == 0) {
                objectArray.at(0)->SetPosition(objectArray.at(i)->GetInformationPosition());
                objectArray.at(0)->SetVisible(true);
                is_click = i;
            } else {
                std::cout << "test_else\n";
                objectArray.at(0)->SetVisible(false);
                if (is_click == i) {
                    is_click = 0;
                    break;
                }
                int check = is_click;
                m_Stage_Object[i]->SwitchPosition( m_Stage_Object[check] );
                std::shared_ptr<GameCharacter> NewObject = m_Stage_Object[check];
                m_Stage_Object[check] = m_Stage_Object[i];
                m_Stage_Object[i] = NewObject;
                m_Stage_Object[i]->SetSwitched( MOVE_BY_SWITCH );
                m_Stage_Object[check]->SetSwitched( MOVE_BY_SWITCH );
                is_click = 0;
                CheckAppearance( 1 , m_Stage , false );
                Tool->Update();
            }
        }
    }
}
