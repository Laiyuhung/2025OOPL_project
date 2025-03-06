#include "App.hpp"
#include "Global.hpp"
#include "Util/Keycode.hpp"

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