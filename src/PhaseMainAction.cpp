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
// bool PhaseHomePage( std::shared_ptr<GameCharacter>* objectArray ){
//     if ( chara_obj->GetVisibility() == true ){
//         if (chara_obj->IfClick()) { 
//             std::cout << "Character clicked!" << std::endl;
//             chara_obj->SetVisible( false );
//             return true; 
//         }
//     }
//     return false;
// }

// void PhaseStage1( std::shared_ptr<GameCharacter>* objectArray ) {
//     DebugModeOfPosition( objectArray , 0 );
//     if ( Util::Input::IsKeyDown(Util::Keycode::R ) ){
//         DebugModeCancel( objectArray, 0 );
//     }
// }