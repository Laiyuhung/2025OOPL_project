#include "App.hpp"

#define PHASE_INITIAL_IMAGE 1
#define PHASE_HOME_PAGE 2

void PhaseInitialImage( std::shared_ptr<Character> & chara_obj , std::shared_ptr<PhaseResourceManager> & RPM){
    if ( chara_obj->GetVisibility() == true ){
        if (chara_obj->IfClick()) { 
            std::cout << "Character clicked!" << std::endl;
            chara_obj->SetVisible( false );
            RPM->NextPhase( PHASE_HOME_PAGE );
        }
    }
}
