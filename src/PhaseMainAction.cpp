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

bool PhaseStage1( std::shared_ptr<GameCharacter>* objectArray , const int size , std::shared_ptr<TaskText> point) {
    for ( int i = 1 ; i < size+1 ; ++i ) {
        if ( objectArray[i]->IfClick() ) {
            std::cout << "which click: " << objectArray[i]->GetInformationPosNumber() << std::endl;
            if ( is_click == 0  ) {
                is_click = i;
            }
            else {
                std::cout << "test_else\n";
                if ( is_click == i ) {
                    is_click = 0;
                    break;
                }
                int check = is_click;
                is_click = 0;
                for ( int j = 0 ; j < 6 ; ++j ) {
                    if( objectArray[i]->GetInformationNeibor()[j] == check ) {
                        objectArray[i]->SwitchPosition( objectArray[check] );
                        std::shared_ptr<GameCharacter> NewObject = objectArray[check];
                        objectArray[check] = objectArray[i];
                        objectArray[i] = NewObject;

                        if ( !CheckAppearance( objectArray, size, 1 ) ) {
                            objectArray[i]->SwitchPosition( objectArray[check] );
                            std::shared_ptr<GameCharacter> NewObject = objectArray[check];
                            objectArray[check] = objectArray[i];
                            objectArray[i] = NewObject;
                        }
                        point->SetValue( stage_point_counter[1] );
                        point->UpdateText();
                        // std::cout << "Point: " << stage_point_counter[1] << std::endl;
                        break;
                    }
                }
            }
        }
    }
    AppearAll( objectArray , size );
    if ( stage_point_counter[1] >= stage_point_goal[1] ) 
        return true;
    return false;
}

void DebugPhaseStage1( std::shared_ptr<GameCharacter>* objectArray ) {
    DebugModeOfPosition( objectArray , 0 );
    if ( Util::Input::IsKeyUp(Util::Keycode::R ) ){
        DebugModeCancel( objectArray, 0 );
    }
}