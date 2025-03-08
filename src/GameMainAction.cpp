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
        objectArray[i]->SetAppearBool( true );
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

void Dropping( std::shared_ptr<GameCharacter>* objectArray, const int size ){
    int loop_count = 0;
    for ( int i = 1 ; i < size+1 ; ) {
        if ( loop_count > size/2 || !objectArray[i] || objectArray[i]->GetInformationNeibor()[0] == -1 || objectArray[i]->GetAppearBool() ) {
            ++i;
            loop_count = 0;
            continue;
        }
        if ( !objectArray[i]->GetAppearBool() && objectArray[i]->GetInformationNeibor()[0] != -1 ) 
            Dropping_method( objectArray, size, i);
        ++loop_count ;
    }
}

void Dropping_method( std::shared_ptr<GameCharacter>* objectArray, const int size , const int current_position ) {
    if ( !objectArray[current_position] || objectArray[current_position]->GetInformationNeibor()[0] == -1  || !objectArray[objectArray[current_position]->GetInformationNeibor()[0]])
        return;
    if ( current_position < size+1 ) {
        const int next_position = objectArray[current_position]->GetInformationNeibor()[0];
        bool flag = objectArray[next_position]->GetAppearBool();
        objectArray[current_position]->SwitchPosition( objectArray[next_position] );

        std::shared_ptr<GameCharacter> NewObject = objectArray[current_position];
        objectArray[current_position] = objectArray[next_position];
        objectArray[next_position] = NewObject;
        objectArray[current_position]->SetAppearBool( flag );
        
        Dropping_method( objectArray , size , next_position );
    }

    return;
}

void CheckAppearance( std::shared_ptr<GameCharacter>* objectArray, const int size ) {
    for ( int i = 1 ; i < size+1 ; ++i ) {
        if( !objectArray[i] )
            continue;
        int *neighbors = objectArray[i]->GetInformationNeibor() ;//GET NEIGHBOR
        objectArray[i]->GetBlockType() ;
        int total_length[6] = { 0 } ;
        for ( int j = 0 ; j < 6 ; ++j ) { 
            if ( neighbors[j] == -1 || !objectArray[ neighbors[j] ]) 
                continue;
            if ( objectArray[ neighbors[j] ]->GetBlockType() == objectArray[i]->GetBlockType() ) {      
                total_length[j] = CheckNextAppearance( objectArray, objectArray[ neighbors[j] ], j, 1 ) ;
            }
        }
        for ( int j = 0 ; j < 6 ; ++j ) 
            DisappaerMethodOfOneLine(objectArray, objectArray[ neighbors[j]] , total_length );
    }
    // DebugModeOfAppearance( objectArray , size);
    MakeDisappear( objectArray , size );
    Dropping( objectArray, size );
}

int CheckNextAppearance( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int side, int length ) {
    if (!object || object->GetInformationNeibor()[side] == -1 || !objectArray[ object->GetInformationNeibor()[side] ] )
        return length;
    
    if ( object->GetBlockType() == objectArray[ object->GetInformationNeibor()[side] ]->GetBlockType() && object->GetInformationNeibor()[side] != -1 ){
        return CheckNextAppearance( objectArray, objectArray[ object->GetInformationNeibor()[side] ], side, length + 1 ) ;
    }
    else
        return length ;

}

void DisappaerMethodOfOneLine( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length ) {
    if( !object )
        return;
    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( (total_length[i] + total_length[j] + 1 ) >= 3 ) {
            if ( !objectArray[ object->GetInformationNeibor()[i] ] || !objectArray[ object->GetInformationNeibor()[j] ])
                return;
            object->SetAppearBool( false );
            if( total_length[i] > 0 )
                DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]);
            if( total_length[j] > 0 )
                DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[j] ], j, total_length[j]);
        }
    }
    return;

}

void DisappearBySingleObject ( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int side, int length_left) {
    if( !object || object->GetInformationNeibor()[side] == -1 || !objectArray[ object->GetInformationNeibor()[side] ] ) 
        return;
    object->SetAppearBool( false );
    if ( length_left - 1 > 0 )
        DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[side] ], side, length_left - 1) ;
    else
        return;
}

void MakeDisappear( std::shared_ptr<GameCharacter>* objectArray , const int size ) {
    for ( int i = 1 ; i < size+1 ; ++i ) {
        if ( !objectArray[i] ){
            // std::cout << "Error: objectArray[" << i << "] is nullptr!" << std::endl;
            continue; 
        }
        // std::cout << objectArray[i]->GetAppearBool() << std::endl;
        if ( !objectArray[i]->GetAppearBool() ){
            // printf( "%d\n" , i );
            objectArray[i]->DisAppear();
        }
    }
}



void DebugModeOfAppearance( std::shared_ptr<GameCharacter>* objectArray , int size ) {
    for ( int i = 1 ; i < size+1 ; ++i ) {
        std::cout << "Pos number: " << objectArray[i]->GetInformationPosNumber() << " Appear Bool: " << objectArray[i]->GetAppearBool() << std::endl;
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