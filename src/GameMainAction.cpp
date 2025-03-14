#include "App.hpp"
#include "Global.hpp"
#include "Util/Keycode.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>
#include <thread>
#include <vector>

using namespace std;

void AppearAll( std::shared_ptr<GameCharacter> *objectArray , const int size ) {
    for ( int i = 1 ; i < size+1 ; ++i )  {
        objectArray[i]->Appear();
        objectArray[i]->SetAppearBool( true );
    }
}
void DisAppearAll( std::shared_ptr<GameCharacter> *objectArray , const int size ) {
    for ( int i = 1 ; i < size+1 ; ++i )  {
        objectArray[i]->DisAppear();
        objectArray[i]->SetAppearBool( false );
    }
}


void ClearAll( std::shared_ptr<GameCharacter> *objectArray , const int size ) {
    for ( int i = 1 ; i < size+1 ; ++i ) {
        objectArray[i]->SetClick( false );
    }
}

bool IsSameColor(int blockType1, int blockType2) {
    // cout<<blockType1<<"   "<< blockType2<<endl;
    return (blockType1 % 10) == (blockType2 % 10);

}

void SetUp( int stage , std::shared_ptr<GameCharacter>* objectArray , const int size , std::shared_ptr<TaskText> point ) {
    for ( int i = 1 ; i < size+1 ; ++i ) {
        if ( objectArray[i]->GetAppearBool() )
            objectArray[i]->Appear(); 
    }
    InitializeStageCharacter( objectArray, size);
    CheckAppearance( objectArray , size , 0);
    // objectArray[37]->SetImage( RAINBOWBALL_OBJECT_LINK );
    // objectArray[37]->SetBlockType( NORMAL_OBJECT );
    // objectArray[37]->SetCurrentType( RAINBOWBALL_OBJECT );
    // objectArray[37]->SetAppearBool( true );
    // objectArray[37]->SetGenerate( true );
    // objectArray[36]->SetImage( BLUE_STRIPE_OBJECT );
    // objectArray[36]->SetBlockType( NORMAL_OBJECT );
    // objectArray[36]->SetBlock( BLUE_OBJECT );
    // objectArray[36]->SetCurrentType( STRIPE_OBJECT );
    // objectArray[36]->SetAppearBool( true );
    // objectArray[36]->SetGenerate( true );
    point->SetValue( 0 );
    point->SetVisible( true );
    point->UpdateText();
}

void CheckClickSwitch( std::shared_ptr<GameCharacter>* objectArray, int check, int i , std::shared_ptr<TaskText> point , int size) {
    for ( int j = 0 ; j < 6 ; ++j ) {
        if( objectArray[i]->GetInformationNeibor()[j] == check ) {
            objectArray[i]->SetSwitched(2);
            objectArray[check]->SetSwitched(2);
            std::cout<<"pos: "<<i<<"  "<<check<<std::endl;
            std::cout<<"set SetSwitched to 2"<<std::endl;
            objectArray[i]->SwitchPosition( objectArray[check] );
            std::shared_ptr<GameCharacter> NewObject = objectArray[check];
            objectArray[check] = objectArray[i];
            objectArray[i] = NewObject;
            if ( objectArray[check]->GetType() == RAINBOWBALL_OBJECT ) {
                objectArray[check]->SetBlock( objectArray[i]->GetBlockType() );
            }
            if ( objectArray[i]->GetType() == RAINBOWBALL_OBJECT ) {
                objectArray[i]->SetBlock( objectArray[check]->GetBlockType() );
            }
            if ( !CheckAppearance( objectArray, size, 1) ) {
                objectArray[i]->SwitchPosition( objectArray[check] );
                std::shared_ptr<GameCharacter> NewObject = objectArray[check];
                objectArray[check] = objectArray[i];
                objectArray[i] = NewObject;
            }
            point->SetValue( stage_point_counter[1] );
            point->UpdateText();
            // std::cout << "Point: " << stage_point_counter[1] << std::endl;
            break;
        }
    }
}