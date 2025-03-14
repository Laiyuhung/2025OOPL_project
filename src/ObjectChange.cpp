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

void RamdomChangeObject( std::shared_ptr<GameCharacter> &object ) {
    static std::random_device rd;
    static std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> distrib(1, 7); 
    
    int ramdom_number = distrib(gen);

    switch ( ramdom_number )
    {
        case BLUE_OBJECT:
            object->SetImage( GA_RESOURCE_DIR"/Image/GameObject/blueNormal.png" );
            object->SetBlock( BLUE_OBJECT );
            break;
        case BROWN_OBJECT:
            object->SetImage( GA_RESOURCE_DIR"/Image/GameObject/brownNormal.png" );
            object->SetBlock( BROWN_OBJECT );
            break;
        case GREEN_OBJECT:
            object->SetImage( GA_RESOURCE_DIR"/Image/GameObject/greenNormal.png" );
            object->SetBlock( GREEN_OBJECT );
            break;
        case PINK_OBJECT:
            object->SetImage( GA_RESOURCE_DIR"/Image/GameObject/pinkNormal.png" );
            object->SetBlock( PINK_OBJECT );
            break;
        case ORANGE_OBJECT:
            object->SetImage( GA_RESOURCE_DIR"/Image/GameObject/orangeNormal.png" );
            object->SetBlock( ORANGE_OBJECT );
            break;
        case WHITE_OBJECT:
            object->SetImage( GA_RESOURCE_DIR"/Image/GameObject/whiteNormal.png" );
            object->SetBlock( WHITE_OBJECT );
            break;
        case YELLOW_OBJECT:
            object->SetImage( GA_RESOURCE_DIR"/Image/GameObject/yellowNormal.png" );
            object->SetBlock( YELLOW_OBJECT );
            break;
        default:
            break;
    }
}
void InitializeStageCharacter(std::shared_ptr<GameCharacter>* objectArray, int size) {
    static std::random_device rd;
    static std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> distrib(1, 7); 
    for ( int i = 1 ; i < size+1 ; ++i ) {
        RamdomChangeObject( objectArray[i] );
        objectArray[i]->SetInformation( stage1[i] );
        objectArray[i]->SetPosition( stage1_position[i] );
        objectArray[i]->SetZIndex(10);
        objectArray[i]->SetSize( {20, 25} );
        objectArray[i]->DisAppear();
        objectArray[i]->SetAppearBool( true );
        objectArray[i]->SetBlockType( NORMAL_OBJECT );
        objectArray[i]->SetCurrentType( NORMAL_OBJECT );
    }
}

void CheckSpecialObject( std::shared_ptr<GameCharacter>* objectArray, int i, int stage ) {
    switch ( objectArray[i]->GetBlockType() )
    {
        case BLUE_OBJECT:
            if ( objectArray[i]->GetType() == STRIPE_OBJECT ) {
                objectArray[i]->SetImage( BLUE_STRIPE_OBJECT );
            }
            else if ( objectArray[i]->GetType() == STRIPE_LEFT_RIGHT_OBJECT ) {
                objectArray[i]->SetImage( BLUE_STRIPE_LEFT_RIGHT_OBJECT);
            }
            else if ( objectArray[i]->GetType() == STRIPE_RIGHT_LEFT_OBJECT ) {
                objectArray[i]->SetImage( BLUE_STRIPE_RIGHT_LEFT_OBJECT );
            }
            else if ( objectArray[i]->GetType() == FLOWER_OBJECT ) {
                objectArray[i]->SetImage( BLUE_FLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == STARFLOWER_OBJECT ) {
                objectArray[i]->SetImage( BLUE_STARFLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == TRIANGLEFLOWER_OBJECT ) {
                objectArray[i]->SetImage( BLUE_TRIANGLEFLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == RAINBOWBALL_OBJECT ) {
                objectArray[i]->SetImage( RAINBOWBALL_OBJECT_LINK );
                objectArray[i]->SetBlock( 0 );
            }
            break;
        case BROWN_OBJECT:
            if ( objectArray[i]->GetType() == STRIPE_OBJECT ) {
                objectArray[i]->SetImage( BROWN_STRIPE_OBJECT );
            }
            else if ( objectArray[i]->GetType() == STRIPE_LEFT_RIGHT_OBJECT ) {
                objectArray[i]->SetImage( BROWN_STRIPE_LEFT_RIGHT_OBJECT);
            }
            else if ( objectArray[i]->GetType() == STRIPE_RIGHT_LEFT_OBJECT ) {
                objectArray[i]->SetImage( BROWN_STRIPE_RIGHT_LEFT_OBJECT );
            }
            else if ( objectArray[i]->GetType() == FLOWER_OBJECT ) {
                objectArray[i]->SetImage( BROWN_FLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == STARFLOWER_OBJECT ) {
                objectArray[i]->SetImage( BROWN_STARFLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == TRIANGLEFLOWER_OBJECT ) {
                objectArray[i]->SetImage( BROWN_TRIANGLEFLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == RAINBOWBALL_OBJECT ) {
                objectArray[i]->SetImage( RAINBOWBALL_OBJECT_LINK );
                objectArray[i]->SetBlock( 0 );
            }
            break;
        case GREEN_OBJECT:
            if ( objectArray[i]->GetType() == STRIPE_OBJECT ) {
                objectArray[i]->SetImage( GREEN_STRIPE_OBJECT );
            }
            else if ( objectArray[i]->GetType() == STRIPE_LEFT_RIGHT_OBJECT ) {
                objectArray[i]->SetImage( GREEN_STRIPE_LEFT_RIGHT_OBJECT);
            }
            else if ( objectArray[i]->GetType() == STRIPE_RIGHT_LEFT_OBJECT ) {
                objectArray[i]->SetImage( GREEN_STRIPE_RIGHT_LEFT_OBJECT );
            }
            else if ( objectArray[i]->GetType() == FLOWER_OBJECT ) {
                objectArray[i]->SetImage( GREEN_FLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == STARFLOWER_OBJECT ) {
                objectArray[i]->SetImage( GREEN_STARFLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == TRIANGLEFLOWER_OBJECT ) {
                objectArray[i]->SetImage( GREEN_TRIANGLEFLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == RAINBOWBALL_OBJECT ) {
                objectArray[i]->SetImage( RAINBOWBALL_OBJECT_LINK );
                objectArray[i]->SetBlock( 0 );
            }
            break;
        case PINK_OBJECT:
            if ( objectArray[i]->GetType() == STRIPE_OBJECT ) {
                objectArray[i]->SetImage( PINK_STRIPE_OBJECT );
            }
            else if ( objectArray[i]->GetType() == STRIPE_LEFT_RIGHT_OBJECT ) {
                objectArray[i]->SetImage( PINK_STRIPE_LEFT_RIGHT_OBJECT);
            }
            else if ( objectArray[i]->GetType() == STRIPE_RIGHT_LEFT_OBJECT ) {
                objectArray[i]->SetImage( PINK_STRIPE_RIGHT_LEFT_OBJECT );
            }
            else if ( objectArray[i]->GetType() == FLOWER_OBJECT ) {
                objectArray[i]->SetImage( PINK_FLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == STARFLOWER_OBJECT ) {
                objectArray[i]->SetImage( PINK_STARFLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == TRIANGLEFLOWER_OBJECT ) {
                objectArray[i]->SetImage( PINK_TRIANGLEFLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == RAINBOWBALL_OBJECT ) {
                objectArray[i]->SetImage( RAINBOWBALL_OBJECT_LINK );
                objectArray[i]->SetBlock( 0 );
            }
            break;
        case ORANGE_OBJECT:
            if ( objectArray[i]->GetType() == STRIPE_OBJECT ) {
                objectArray[i]->SetImage( ORANGE_STRIPE_OBJECT );
            }
            else if ( objectArray[i]->GetType() == STRIPE_LEFT_RIGHT_OBJECT ) {
                objectArray[i]->SetImage( ORANGE_STRIPE_LEFT_RIGHT_OBJECT);
            }
            else if ( objectArray[i]->GetType() == STRIPE_RIGHT_LEFT_OBJECT ) {
                objectArray[i]->SetImage( ORANGE_STRIPE_RIGHT_LEFT_OBJECT );
            }
            else if ( objectArray[i]->GetType() == FLOWER_OBJECT ) {
                objectArray[i]->SetImage( ORANGE_FLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == STARFLOWER_OBJECT ) {
                objectArray[i]->SetImage( ORANGE_STARFLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == TRIANGLEFLOWER_OBJECT ) {
                objectArray[i]->SetImage( ORANGE_TRIANGLEFLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == RAINBOWBALL_OBJECT ) {
                objectArray[i]->SetImage( RAINBOWBALL_OBJECT_LINK );
                objectArray[i]->SetBlock( 0 );
            }
            break;
        case WHITE_OBJECT:
            if ( objectArray[i]->GetType() == STRIPE_OBJECT ) {
                objectArray[i]->SetImage( WHITE_STRIPE_OBJECT );
            }
            else if ( objectArray[i]->GetType() == STRIPE_LEFT_RIGHT_OBJECT ) {
                objectArray[i]->SetImage( WHITE_STRIPE_LEFT_RIGHT_OBJECT);
            }
            else if ( objectArray[i]->GetType() == STRIPE_RIGHT_LEFT_OBJECT ) {
                objectArray[i]->SetImage( WHITE_STRIPE_RIGHT_LEFT_OBJECT );
            }
            else if ( objectArray[i]->GetType() == FLOWER_OBJECT ) {
                objectArray[i]->SetImage( WHITE_FLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == STARFLOWER_OBJECT ) {
                objectArray[i]->SetImage( WHITE_STARFLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == TRIANGLEFLOWER_OBJECT ) {
                objectArray[i]->SetImage( WHITE_TRIANGLEFLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == RAINBOWBALL_OBJECT ) {
                objectArray[i]->SetImage( RAINBOWBALL_OBJECT_LINK );
                objectArray[i]->SetBlock( 0 );
            }
            break;
        case YELLOW_OBJECT:
            if ( objectArray[i]->GetType() == STRIPE_OBJECT ) {
                objectArray[i]->SetImage( YELLOW_STRIPE_OBJECT );
            }
            else if ( objectArray[i]->GetType() == STRIPE_LEFT_RIGHT_OBJECT ) {
                objectArray[i]->SetImage( YELLOW_STRIPE_LEFT_RIGHT_OBJECT);
            }
            else if ( objectArray[i]->GetType() == STRIPE_RIGHT_LEFT_OBJECT ) {
                objectArray[i]->SetImage( YELLOW_STRIPE_RIGHT_LEFT_OBJECT );
            }
            else if ( objectArray[i]->GetType() == FLOWER_OBJECT ) {
                objectArray[i]->SetImage( YELLOW_FLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == STARFLOWER_OBJECT ) {
                objectArray[i]->SetImage( YELLOW_STARFLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == TRIANGLEFLOWER_OBJECT ) {
                objectArray[i]->SetImage( YELLOW_TRIANGLEFLOWER_OBJECT );
            }
            else if ( objectArray[i]->GetType() == RAINBOWBALL_OBJECT ) {
                objectArray[i]->SetImage( RAINBOWBALL_OBJECT_LINK );
                objectArray[i]->SetBlock( 0 );
            }

            break;
        default:
            break;
    }
}