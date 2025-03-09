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
            level1->SetVisible( false );
            return true; 
        }
    }
    return false;
}

int counter = 0 ;
bool PhaseStage1( std::shared_ptr<GameCharacter>* objectArray , const int size ) {
    for ( int i = 1 ; i < size+1 ; ++i ) {
        if ( objectArray[i]->GetClick() ) {
            for ( int j = 0 ; j < 6 ; ++j ) {
                if ( objectArray[i]->GetInformationNeibor()[j] != -1 && objectArray[ objectArray[i]->GetInformationNeibor()[j] ]->GetClick() ){
                    const int next_position = objectArray[i]->GetInformationNeibor()[j];
                    // bool flag = objectArray[next_position]->GetAppearBool();
                    objectArray[i]->SwitchPosition( objectArray[next_position] );
                    
                    std::shared_ptr<GameCharacter> NewObject = objectArray[i];
                    objectArray[i] = objectArray[next_position];
                    objectArray[next_position] = NewObject;
                    // objectArray[i]->SetAppearBool( flag );
                    CheckAppearance( objectArray, size , true );
                    break;
                }
                else if ( counter == 2 && j == 5 ){
                    std::cout << "clear all\n" ;
                    counter = 0;
                    ClearAll( objectArray, size);
                }
            }
        }
        else if ( objectArray[i]->IfClick() ) {
            objectArray[i]->SetClick( true );
            ++counter;
        }
    }
    AppearAll( objectArray , size );
    return true;
}

void DebugPhaseStage1( std::shared_ptr<GameCharacter>* objectArray ) {
    DebugModeOfPosition( objectArray , 0 );
    if ( Util::Input::IsKeyUp(Util::Keycode::R ) ){
        DebugModeCancel( objectArray, 0 );
    }
}