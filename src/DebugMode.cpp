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

void DebugModeOfAppearance( std::shared_ptr<GameCharacter>* objectArray , int size ) {
    for ( int i = 1 ; i < size+1 ; ++i ) {
        std::cout << "Pos number: " << objectArray[i]->GetInformationPosNumber() << " Appear Bool: " << objectArray[i]->GetAppearBool() << std::endl;
    }
}
void DebugModeOfPosition( std::shared_ptr<GameCharacter>* objectArray , int option) {
    objectArray[option]->Appear();
    objectArray[option]->DebugMode(2.5);
}

void DebugModeCancel( std::shared_ptr<GameCharacter>* objectArray , int option) {
    objectArray[option]->DisAppear();
    std::cout << "x : " << objectArray[option]->GetPosition().x << " y : " << objectArray[option]->GetPosition().y << "\n";
}

void DebugModeShowMapObject(std::shared_ptr<GameCharacter>* objectArray , int size ) {
    for ( int i = 1 ; i < size+1 ; ++i ) {
        cout << "Pos number: " << objectArray[i]->GetInformationPosNumber() << " Appear Bool: " << objectArray[i]->GetAppearBool() << endl;
    }
}