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

void Dropping( std::shared_ptr<GameCharacter>* objectArray, const int size , int stage = 0 ) {
    int loop_count = 0;
    for ( int i = 1 ; i < size+1 ; ) {
        if ( loop_count > size || !objectArray[i] || objectArray[i]->GetInformationNeibor()[0] == -1 || objectArray[i]->GetAppearBool() ) {
            ++i;
            loop_count = 0;
            continue;
        }
        if ( !objectArray[i]->GetAppearBool() && objectArray[i]->GetInformationNeibor()[0] != -1 ) 
            Dropping_method( objectArray, size, i);
        ++loop_count ;
    }
    for ( int i = 1 ; i < size+1 ; ++i ) {
        if ( !objectArray[i]->GetAppearBool() ) {
            RamdomChangeObject( objectArray[i] );
        }
        objectArray[i]->SetAppearBool( true );
    }
    if ( stage != 0 ) 
        AppearAll( objectArray , size );
    
    CheckAppearance( objectArray, size , stage);

}

void Dropping_method( std::shared_ptr<GameCharacter>* objectArray, const int size , const int current_position ) {
    if ( !objectArray[current_position] || objectArray[current_position]->GetInformationNeibor()[0] == -1  || !objectArray[objectArray[current_position]->GetInformationNeibor()[0]])
        return;
    if ( current_position < size+1 ) {
        const int next_position = objectArray[current_position]->GetInformationNeibor()[0];
        bool flag = objectArray[next_position]->GetAppearBool();

        objectArray[current_position]->SetSwitched(1);
        // cout<<"pos: "<<current_position<<"  "<<next_position<<endl;
        // cout<<"set SetSwitched to 1"<<endl;
        objectArray[next_position]->SetSwitched(1);
        objectArray[current_position]->SwitchPosition( objectArray[next_position] );

        std::shared_ptr<GameCharacter> NewObject = objectArray[current_position];
        objectArray[current_position] = objectArray[next_position];
        objectArray[next_position] = NewObject;
        objectArray[current_position]->SetAppearBool( flag );

        Dropping_method( objectArray , size , next_position );
    }

    return;
}