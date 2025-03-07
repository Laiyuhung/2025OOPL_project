#include "App.hpp"
#include "Global.hpp"
#include "Util/Keycode.hpp"
#include <iostream>

void InitializeGameCharacter( std::shared_ptr<GameCharacter>* objectArray ){
    objectArray[BLUE_NORMAL_OBJECT] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/blueNormal.png" );
    objectArray[BROWN_NORMAL_OBJECT] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/brownNormal.png" );
    objectArray[GREEN_NORMAL_OBJECT] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/greenNormal.png" );
    objectArray[PINK_NORMAL_OBJECT] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/pinkNormal.png" );
    objectArray[ORANGE_NORMAL_OBJECT] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/orangeNormal.png" );
    objectArray[WHITE_NORMAL_OBJECT] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/whiteNormal.png" );
    objectArray[YELLOW_NORMAL_OBJECT] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/yellowNormal.png" );

    for ( int i = 0 ; i < 7 ; ++i ) {
        objectArray[i]->SetPosition( {0, -160.5f} );
        objectArray[i]->SetZIndex(10);
        objectArray[i]->DisAppear();
    }
}

void InitializeStageCharacter(std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>* object) {
    
    if (object[0]) {
        objectArray[0] = std::dynamic_pointer_cast<GameCharacter>(object[0]->Clone());    
    }
}

void DebugModeOfPosition( std::shared_ptr<GameCharacter>* objectArray , int option) {
    objectArray[option]->Appear();
    objectArray[option]->DebugMode(10);
}

void DebugModeCancel( std::shared_ptr<GameCharacter>* objectArray , int option) {
    objectArray[option]->DisAppear();
    std::cout << "x : " << objectArray[option]->GetPosition().x << " y : " << objectArray[option]->GetPosition().y << "\n";
}