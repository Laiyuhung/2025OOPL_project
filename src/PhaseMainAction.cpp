#include "App.hpp"
#include "Global.hpp"

#include <thread>

#include "Util/Keycode.hpp"

bool PhaseInitialImage( std::shared_ptr<Character> & chara_obj ){
    if ( chara_obj->GetVisibility() == true ){
        if (chara_obj->IfClick()) { 
            std::cout << "Character clicked!" << std::endl;
            chara_obj->SetVisible( false );
            return true; 
        }
    }
    return false;
}
bool PhaseHomePage( std::shared_ptr<Character> &level1){
    if ( level1->GetVisibility() == true ){
        if (level1->IfClick()) { 
            std::cout << "Level1 Character clicked!" << std::endl;
            stage_point_counter[1] = 0;
            level1->SetVisible( false );
            return true; 
        }
    }
    return false;
}

bool PhaseStage1( std::shared_ptr<StageObject> StageObject , const int size , std::shared_ptr<TaskText> point) {
    std::shared_ptr<GameCharacter>* objectArray = StageObject->GetStageObject();
    for ( int i = 1 ; i < size+1 ; ++i ) {
        if ( objectArray[i]->IfClick() ) {
            std::cout << "which click: " << objectArray[i]->GetInformationPosNumber() << std::endl;
            if ( is_click == 0  ) {
                is_click = i; // 1st clicked
            }
            else {
                std::cout << "test_else\n";
                if ( is_click == i ) {
                    is_click = 0;
                    break;
                }
                int check = is_click;
                is_click = 0;
                StageObject->CheckClickSwitch( check, i , point );
                // CheckClickSwitch( objectArray, check, i , point , size);
            }
        }
    }
    // StageObject->AppearAll();
    return stage_point_counter[1] >= stage_point_goal[1];
}

void DebugPhaseStage1( std::shared_ptr<GameCharacter>* objectArray ) {
    DebugModeOfPosition( objectArray , 0 );
    if ( Util::Input::IsKeyUp(Util::Keycode::R ) ){
        DebugModeCancel( objectArray, 0 );
    }
}