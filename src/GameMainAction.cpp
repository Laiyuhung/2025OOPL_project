#include "App.hpp"
#include "Global.hpp"
#include "Util/Keycode.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>
#include <thread>

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

void RamdomChangeObject( std::shared_ptr<GameCharacter> object ) {
    static std::random_device rd;
    static std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> distrib(1, 7); 
    
    int ramdom_number = distrib(gen);

    switch ( ramdom_number )
    {
        case BLUE_NORMAL_OBJECT:
            object->SetImage( GA_RESOURCE_DIR"/Image/GameObject/blueNormal.png" );
            object->SetBlock( BLUE_NORMAL_OBJECT );
            break;
        case BROWN_NORMAL_OBJECT:
            object->SetImage( GA_RESOURCE_DIR"/Image/GameObject/brownNormal.png" );
            object->SetBlock( BROWN_NORMAL_OBJECT );
            break;
        case GREEN_NORMAL_OBJECT:
            object->SetImage( GA_RESOURCE_DIR"/Image/GameObject/greenNormal.png" );
            object->SetBlock( GREEN_NORMAL_OBJECT );
            break;
        case PINK_NORMAL_OBJECT:
            object->SetImage( GA_RESOURCE_DIR"/Image/GameObject/pinkNormal.png" );
            object->SetBlock( PINK_NORMAL_OBJECT );
            break;
        case ORANGE_NORMAL_OBJECT:
            object->SetImage( GA_RESOURCE_DIR"/Image/GameObject/orangeNormal.png" );
            object->SetBlock( ORANGE_NORMAL_OBJECT );
            break;
        case WHITE_NORMAL_OBJECT:
            object->SetImage( GA_RESOURCE_DIR"/Image/GameObject/whiteNormal.png" );
            object->SetBlock( WHITE_NORMAL_OBJECT );
            break;
        case YELLOW_NORMAL_OBJECT:
            object->SetImage( GA_RESOURCE_DIR"/Image/GameObject/yellowNormal.png" );
            object->SetBlock( YELLOW_NORMAL_OBJECT );
            break;
        default:
            break;
    }
}
void InitializeStageCharacter(std::shared_ptr<GameCharacter>* objectArray, int size) {
    static std::random_device rd;
    static std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> distrib(1, 7); 
    
    int ramdom_number = distrib(gen);
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
        objectArray[i]->SetSize( {20, 25} );
        objectArray[i]->DisAppear();
        objectArray[i]->SetAppearBool( true );
    }
}

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
        objectArray[current_position]->SwitchPosition( objectArray[next_position] );

        std::shared_ptr<GameCharacter> NewObject = objectArray[current_position];
        objectArray[current_position] = objectArray[next_position];
        objectArray[next_position] = NewObject;
        objectArray[current_position]->SetAppearBool( flag );

        Dropping_method( objectArray , size , next_position );
    }

    return;
}

bool IsSameColor(int blockType1, int blockType2) {
    // cout<<blockType1<<"   "<< blockType2<<endl;
    return (blockType1 % 10) == (blockType2 % 10);

}

bool CheckAppearance( std::shared_ptr<GameCharacter>* objectArray, const int size , int stage ) {

    bool cont_to_check = false;
    bool flag = false;
    
    // std::cout<< "(initial) cont_to_check: "<< cont_to_check << std::endl;

    for ( int i = 1 ; i < size+1 ; ++i ) {
        if( !objectArray[i] ) continue;
        objectArray[i]->SetAppearBool( true );
    }

    for ( int i = 1 ; i < size+1 ; ++i ) {
        
        if( !objectArray[i] )
            continue;
        int *neighbors = objectArray[i]->GetInformationNeibor() ;//GET NEIGHBOR
        objectArray[i]->GetBlockType() ;
        int total_length[6] = { 0 } ;
        for ( int j = 0 ; j < 6 ; ++j ) { 
            if ( neighbors[j] == -1 ) 
                continue;
            if ( IsSameColor(objectArray[ neighbors[j] ]->GetBlockType() , objectArray[i]->GetBlockType()) ) {
                // std::cout<< "i: "<< i << " type: "<< objectArray[i]->GetBlockType() << " j: "<< objectArray[ neighbors[j] ]->GetInformationPosNumber() << " type: "<< objectArray[ neighbors[j] ]->GetBlockType() << std::endl;
                total_length[j] = CheckNextAppearance( objectArray, objectArray[ neighbors[j] ], j, 1 ) ;
            }
        }

        cont_to_check = DisappearMethodOfOneLine(objectArray, objectArray[i] , total_length ) || cont_to_check;
        cont_to_check = DisappearMethodOfFlower(objectArray, objectArray[i] , total_length ) || cont_to_check;
        cont_to_check = DisappearMethodOfStarFlower(objectArray, objectArray[i] , total_length ) || cont_to_check; //4
        cont_to_check = DisappearMethodOfTriangleFlower(objectArray, objectArray[i] , total_length ) || cont_to_check; //3
        cont_to_check = DisappearMethodOfStripe(objectArray, objectArray[i] , total_length ) || cont_to_check; //2
        cont_to_check = DisappearMethodOfRainbowBall(objectArray, objectArray[i] , total_length ) || cont_to_check; //1

    }


    for ( int i = 1 ; i < size+1 ; ++i ) {
        if( !objectArray[i] ) continue;
        if( !objectArray[i]->GetAppearBool() ) flag = true;
    }

    if ( flag ) {
        // DebugModeOfAppearance( objectArray , size);
        MakeDisappear( objectArray , size , stage);
        Dropping( objectArray, size , stage );
    
    }
    return flag;

}

int CheckNextAppearance( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int side, int length ) {


    if (!object || object->GetInformationNeibor()[side] == -1 || !objectArray[ object->GetInformationNeibor()[side] ] )
        return length;
    
    if ( IsSameColor(object->GetBlockType() , objectArray[ object->GetInformationNeibor()[side] ]->GetBlockType()) && object->GetInformationNeibor()[side] != -1 ){
        return CheckNextAppearance( objectArray, objectArray[ object->GetInformationNeibor()[side] ], side, length + 1 ) ;
    }
    else
        return length ;

}

bool DisappearMethodOfOneLine( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length ) {
    
    bool cont_to_check = false ;
    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( (total_length[i] + total_length[j] ) == 2 ) {
            cont_to_check = true ;
            object->SetAppearBool( false );

        }
        if ( total_length[i] > 0 && total_length[j] == 0 && (total_length[i] + total_length[j] ) == 2 )//side
        {
            cout<<"Line"<<endl;
        }
    }

    return cont_to_check;

}

bool DisappearMethodOfStripe( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length ) { //total_length = 6 side's consec.

    bool cont_to_check = false ;
    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( (total_length[i] + total_length[j] ) == 3 ) {
            cont_to_check = true ;


            if( !(total_length[i] > 0 && total_length[j] == 0) )//if [NOT] j side ->> MID OR I ->disappear
            {

                object->SetAppearBool( false ); //self disappear

            }
            else if ( total_length[i] > 0 && total_length[j] == 0 ) //side
            {

                int currentType = object->GetBlockType();

                // 使用 IsSameColor() 來匹配顏色
                if (IsSameColor(currentType, BLUE_NORMAL_OBJECT)) {
                    object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/blueLine.png");
                    object->SetBlock(BLUE_STRIPE_OBJECT);
                }
                else if (IsSameColor(currentType, BROWN_NORMAL_OBJECT)) {
                    object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/brownLine.png");
                    object->SetBlock(BROWN_STRIPE_OBJECT);
                }
                else if (IsSameColor(currentType, GREEN_NORMAL_OBJECT)) {
                    object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/greenLine.png");
                    object->SetBlock(GREEN_STRIPE_OBJECT);
                }
                else if (IsSameColor(currentType, PINK_NORMAL_OBJECT)) {
                    object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/pinkLine.png");
                    object->SetBlock(PINK_STRIPE_OBJECT);
                }
                else if (IsSameColor(currentType, ORANGE_NORMAL_OBJECT)) {
                    object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/orangeLine.png");
                    object->SetBlock(ORANGE_STRIPE_OBJECT);
                }
                else if (IsSameColor(currentType, WHITE_NORMAL_OBJECT)) {
                    object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/whiteLine.png");
                    object->SetBlock(WHITE_STRIPE_OBJECT);
                }
                else if (IsSameColor(currentType, YELLOW_NORMAL_OBJECT)) {
                    object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/yellowLine.png");
                    object->SetBlock(YELLOW_STRIPE_OBJECT);
                }

                cout<<"Stripe"<<endl;
            }

        }


    }

    return cont_to_check;

}

bool DisappearMethodOfFlower( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length ) { //total_length = 6 side's consec.

    bool cont_to_check = false ; //two side 1 + another 2
    int check_side = -1;

    for ( int i = 0  ; i < 6 ; ++i ) //another 2
    {
        if ( total_length[i] >= 2 )
        {
            check_side = i ;
            // cout<<"check_side: "<<check_side<<" check_side_length: "<<total_length[i]<<endl;
            break;
        }
    }

    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( i != check_side && j != check_side && check_side != -1 )
        {

            if ( total_length[i] >= 1 && total_length[j] >= 1 ) {//two side 1
                cont_to_check = true ;
                cout<<"Flower"<<endl;

                int currentType = object->GetBlockType();

                // 使用 IsSameColor() 來匹配顏色
                if (IsSameColor(currentType, BLUE_NORMAL_OBJECT)) {
                    object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/blueFlower.png");
                    object->SetBlock(BLUE_FLOWER_OBJECT);
                }
                else if (IsSameColor(currentType, BROWN_NORMAL_OBJECT)) {
                    object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/brownFlower.png");
                    object->SetBlock(BROWN_FLOWER_OBJECT);
                }
                else if (IsSameColor(currentType, GREEN_NORMAL_OBJECT)) {
                    object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/greenFlower.png");
                    object->SetBlock(GREEN_FLOWER_OBJECT);
                }
                else if (IsSameColor(currentType, PINK_NORMAL_OBJECT)) {
                    object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/pinkFlower.png");
                    object->SetBlock(PINK_FLOWER_OBJECT);
                }
                else if (IsSameColor(currentType, ORANGE_NORMAL_OBJECT)) {
                    object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/orangeFlower.png");
                    object->SetBlock(ORANGE_FLOWER_OBJECT);
                }
                else if (IsSameColor(currentType, WHITE_NORMAL_OBJECT)) {
                    object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/whiteFlower.png");
                    object->SetBlock(WHITE_FLOWER_OBJECT);
                }
                else if (IsSameColor(currentType, YELLOW_NORMAL_OBJECT)) {
                    object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/yellowFlower.png");
                    object->SetBlock(YELLOW_FLOWER_OBJECT);
                }

                DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[check_side] ], check_side, total_length[check_side]-1);
                DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);
                DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[j] ], j, total_length[j]-1);
                break;
            }
        }
    }

    return cont_to_check;

}

bool DisappearMethodOfStarFlower( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length ) { //total_length = 6 side's consec.

    bool cont_to_check = false ; //two side 2
    int check_sides = 0;


    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( total_length[i] >= 1 && total_length[j] >= 1)
        {
            check_sides++ ;
        }
    }

    if (check_sides >= 2)
    {
        for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j )
        {
            DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);
            DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[j]-1);
        }

        int currentType = object->GetBlockType();

        // 使用 IsSameColor() 來匹配顏色
        if (IsSameColor(currentType, BLUE_NORMAL_OBJECT)) {
            object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/blueStarFlower.png");
            object->SetBlock(BLUE_STARFLOWER_OBJECT);
        }
        else if (IsSameColor(currentType, BROWN_NORMAL_OBJECT)) {
            object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/brownStarFlower.png");
            object->SetBlock(BROWN_STARFLOWER_OBJECT);
        }
        else if (IsSameColor(currentType, GREEN_NORMAL_OBJECT)) {
            object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/greenStarFlower.png");
            object->SetBlock(GREEN_STARFLOWER_OBJECT);
        }
        else if (IsSameColor(currentType, PINK_NORMAL_OBJECT)) {
            object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/pinkStarFlower.png");
            object->SetBlock(PINK_STARFLOWER_OBJECT);
        }
        else if (IsSameColor(currentType, ORANGE_NORMAL_OBJECT)) {
            object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/orangeStarFlower.png");
            object->SetBlock(ORANGE_STARFLOWER_OBJECT);
        }
        else if (IsSameColor(currentType, WHITE_NORMAL_OBJECT)) {
            object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/whiteStarFlower.png");
            object->SetBlock(WHITE_STARFLOWER_OBJECT);
        }
        else if (IsSameColor(currentType, YELLOW_NORMAL_OBJECT)) {
            object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/yellowStarFlower.png");
            object->SetBlock(YELLOW_STARFLOWER_OBJECT);
        }

        cout<<"Star Flower"<<endl;
        cont_to_check = true ;
    }

    return cont_to_check;

}

bool DisappearMethodOfTriangleFlower( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length ) { //total_length = 6 side's consec.

    bool cont_to_check = false ; //two side >=2
    int check = 0;

    for ( int i = 0  ; i < 6 ; ++i ) //two side >=2
    {
        if ( total_length[i] >= 2 )
        {
            check ++ ;
        }
    }

    if (check >= 2) // ex. side 1 + side 4 both >=2 -- rainbow(first
    {
        int currentType = object->GetBlockType();

        // 使用 IsSameColor() 來匹配顏色
        if (IsSameColor(currentType, BLUE_NORMAL_OBJECT)) {
            object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/blueTriangleFlower.png");
            object->SetBlock(BLUE_TRIANGLEFLOWER_OBJECT);
        }
        else if (IsSameColor(currentType, BROWN_NORMAL_OBJECT)) {
            object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/brownTriangleFlower.png");
            object->SetBlock(BROWN_TRIANGLEFLOWER_OBJECT);
        }
        else if (IsSameColor(currentType, GREEN_NORMAL_OBJECT)) {
            object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/greenTriangleFlower.png");
            object->SetBlock(GREEN_TRIANGLEFLOWER_OBJECT);
        }
        else if (IsSameColor(currentType, PINK_NORMAL_OBJECT)) {
            object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/pinkTriangleFlower.png");
            object->SetBlock(PINK_TRIANGLEFLOWER_OBJECT);
        }
        else if (IsSameColor(currentType, ORANGE_NORMAL_OBJECT)) {
            object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/orangeTriangleFlower.png");
            object->SetBlock(ORANGE_TRIANGLEFLOWER_OBJECT);
        }
        else if (IsSameColor(currentType, WHITE_NORMAL_OBJECT)) {
            object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/whiteTriangleFlower.png");
            object->SetBlock(WHITE_TRIANGLEFLOWER_OBJECT);
        }
        else if (IsSameColor(currentType, YELLOW_NORMAL_OBJECT)) {
            object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/yellowTriangleFlower.png");
            object->SetBlock(YELLOW_TRIANGLEFLOWER_OBJECT);
        }

        cout<<"Triangle Flower"<<endl;
        cont_to_check = true ;
        for ( int i = 0  ; i < 6 ; ++i )
        {
            DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);
        }

    }

    return cont_to_check;

}

bool DisappearMethodOfRainbowBall( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length ) { //total_length = 6 side's consec.

    bool cont_to_check = false ;
    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( (total_length[i] + total_length[j] ) >= 4 ) {
            cont_to_check = true ;


            cout<<"Rainbow Ball"<<endl;

            if( !(total_length[i] > 0 && total_length[j] == 0) )//if [NOT] j side ->> MID OR I ->disappear
            {
                object->SetAppearBool( false ); //self disappear
            }
            else
            {
                cout<<"Rainbow Ball"<<endl;
                // object->SetImage(GA_RESOURCE_DIR "/Image/GameObject/RainbowBall.png");
                object->SetBlock(RAINBOWBALL_OBJECT);
            }

        }


    }

    return cont_to_check;

}


void DisappearBySingleObject ( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int side, int length_left) {
    object->SetAppearBool( false );
    if( !object || object->GetInformationNeibor()[side] == -1 ) 
        return;

    if ( length_left  >  0 )
        DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[side] ], side, length_left - 1) ;
    else
        return;
}

void MakeDisappear( std::shared_ptr<GameCharacter>* objectArray , const int size , int stage) {
    for ( int i = 1 ; i < size+1 ; ++i ) {
        // if ( !objectArray[i] ) continue; 
        if ( !objectArray[i]->GetAppearBool() ) {
            objectArray[i]->DisAppear();
            ++stage_point_counter[stage];
        }
    }
    // std::this_thread::sleep_for(std::chrono::seconds(1));  
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