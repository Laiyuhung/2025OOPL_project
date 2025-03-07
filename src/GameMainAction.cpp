#include "App.hpp"
#include "Global.hpp"
#include "Util/Keycode.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

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
void InitializeStageCharacter(std::shared_ptr<GameCharacter>* objectArray, int size) {
    std::srand( std::time( NULL ));
    for ( int i = 0 ; i < size ; ++i ) {
        int random_number = std::rand() % 7;
        if ( random_number == BLUE_NORMAL_OBJECT ) {
            objectArray[i] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/blueNormal.png" );
            
        } 
        else if ( random_number == BROWN_NORMAL_OBJECT ) {
            objectArray[i] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/brownNormal.png" );
        } 

        else if ( random_number == GREEN_NORMAL_OBJECT ) {
            objectArray[i] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/greenNormal.png" );
        } 

        else if ( random_number == PINK_NORMAL_OBJECT ) {
            objectArray[i] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/pinkNormal.png" );
        } 

        else if ( random_number == ORANGE_NORMAL_OBJECT ) {
            objectArray[i] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/orangeNormal.png" );
        } 

        else if ( random_number == WHITE_NORMAL_OBJECT ) {
            objectArray[i] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/whiteNormal.png" );
        } 

        else if ( random_number == YELLOW_NORMAL_OBJECT ) {
            objectArray[i] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/yellowNormal.png" );
        } 

        objectArray[i]->SetPosition( stage1_postion[i] );
        objectArray[i]->SetZIndex(10);
        objectArray[i]->DisAppear();
    }
    
    // objectArray[BLUE_NORMAL_OBJECT] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/blueNormal.png" );
    // objectArray[BROWN_NORMAL_OBJECT] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/brownNormal.png" );
    // objectArray[GREEN_NORMAL_OBJECT] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/greenNormal.png" );
    // objectArray[PINK_NORMAL_OBJECT] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/pinkNormal.png" );
    // objectArray[ORANGE_NORMAL_OBJECT] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/orangeNormal.png" );
    // objectArray[WHITE_NORMAL_OBJECT] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/whiteNormal.png" );
    // objectArray[YELLOW_NORMAL_OBJECT] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/yellowNormal.png" );

    // for ( int i = 0 ; i < 7 ; ++i ) {
    //     objectArray[i]->SetPosition( {0, -160.5f} );
    //     objectArray[i]->SetZIndex(10);
    //     objectArray[i]->DisAppear();
    // }
}

void DebugModeOfPosition( std::shared_ptr<GameCharacter>* objectArray , int option) {
    objectArray[option]->Appear();
    objectArray[option]->DebugMode(10);
}

void DebugModeCancel( std::shared_ptr<GameCharacter>* objectArray , int option) {
    objectArray[option]->DisAppear();
    std::cout << "x : " << objectArray[option]->GetPosition().x << " y : " << objectArray[option]->GetPosition().y << "\n";
}