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
    for ( int i = 1 ; i < size+1 ; ++i ) {
        int random_number = std::rand() % 7 + 1;
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
        
        objectArray[i]->SetBlock( random_number );
        objectArray[i]->SetInformation( stage1[i] );
        objectArray[i]->SetPosition( stage1_position[i] );
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

void CheckAppearance( std::shared_ptr<GameCharacter>* objectArray, int size ) {
    for ( int i = 1 ; i < size+1 ; ++i ) {
        int *neighbors = objectArray[i]->GetInformationNeibor() ;//GET NEIGHBOR
        objectArray[i]->GetBlockType() ;
        int length = 0 ;
        int total_length[6] = { 0 } ;
        for ( int j = 0 ; j < 6 ; ++j ) { 
            if ( objectArray[ neighbors[j] ]->GetBlockType() == objectArray[i]->GetBlockType() ) {       
                total_length[j] = CheckNextAppearance( objectArray, objectArray[ neighbors[j] ], j, length ) ;
            }
        }
        for ( int j = 0 ; j < 6 ; ++j ) 
            DisappaerMethodOfOneLine(objectArray, objectArray[ neighbors[j]] , total_length );
    }
}

int CheckNextAppearance( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int side, int length ) {
    if ( object->GetBlockType() == objectArray[ object->GetInformationNeibor()[side] ]->GetBlockType() ){
        length++ ;
        return CheckNextAppearance( objectArray, objectArray[ object->GetInformationNeibor()[side] ], side, length ) ;
    }
    else
        return length ;
}

void DisappaerMethodOfOneLine( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length ) {
    if ( (total_length[0] + total_length[3] + 1 ) >=3 ) {
        object->DisAppear();
        DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[0] ], 0, total_length[0]);
        DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[3] ], 3, total_length[3]);
    }
    else if ( (total_length[1] + total_length[4] + 1 ) >=3 ) {
        object->DisAppear();
        DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[1] ], 1, total_length[1]);
        DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[4] ], 4, total_length[4]);
    }
    else if ( (total_length[2] + total_length[5] + 1 ) >=3 ) {
        object->DisAppear();        
        DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[2] ], 2, total_length[2]);
        DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[5] ], 5, total_length[5]);
    }
    else 
        return;

}

void DisappearBySingleObject ( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int side, int length_left) {
    object->DisAppear();
    if ( length_left - 1 > 0 ) {
        DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[side] ], side, length_left - 1) ;
    } else
        return;
}


void DebugModeOfPosition( std::shared_ptr<GameCharacter>* objectArray , int option) {
    objectArray[option]->Appear();
    objectArray[option]->DebugMode(10);
}

void DebugModeCancel( std::shared_ptr<GameCharacter>* objectArray , int option) {
    objectArray[option]->DisAppear();
    std::cout << "x : " << objectArray[option]->GetPosition().x << " y : " << objectArray[option]->GetPosition().y << "\n";
}