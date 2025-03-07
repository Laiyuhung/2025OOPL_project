#include "App.hpp"
#include "Global.hpp"
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
            level1->SetVisible( false );
            return true; 
        }
    }
    return false;
}

bool PhaseStage1( std::shared_ptr<GameCharacter>* objectArray ) {
    objectArray[0]->Appear();
    return true;
}

void DebugPhaseStage1( std::shared_ptr<GameCharacter>* objectArray ) {
    DebugModeOfPosition( objectArray , 0 );
    if ( Util::Input::IsKeyDown(Util::Keycode::R ) ){
        DebugModeCancel( objectArray, 0 );
    }
}