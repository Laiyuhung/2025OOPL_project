#include "App.hpp"
#include "Global.hpp"

void PhaseInitialImage( std::shared_ptr<Character> & chara_obj , std::shared_ptr<PhaseResourceManager> & RPM){
    if ( chara_obj->GetVisibility() == true ){
        if (chara_obj->IfClick()) { 
            std::cout << "Character clicked!" << std::endl;
            chara_obj->SetVisible( false );
            RPM->NextPhase( PHASE_HOME_PAGE );
        }
    }
}

void PhaseInitialImage( std::shared_ptr<GameCharacter>* objectArray , std::shared_ptr<Character> & chara_obj , std::shared_ptr<PhaseResourceManager> & RPM){
    if ( chara_obj->GetVisibility() == true ){
        if (chara_obj->IfClick()) { 
            std::cout << "Character clicked!" << std::endl;
            chara_obj->SetVisible( false );
            RPM->NextPhase( PHASE_HOME_PAGE );
        }
        DebugModeOfPosition(objectArray, 0 );
    }
}

void PhaseHomePage( std::shared_ptr<GameCharacter>* objectArray , std::shared_ptr<PhaseResourceManager> & RPM){
    DebugModeOfPosition( objectArray , 0 );
}