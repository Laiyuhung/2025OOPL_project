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

bool IsSameColor(int blockType1, int blockType2) {
    // cout<<blockType1<<"   "<< blockType2<<endl;
    return (blockType1 % 10) == (blockType2 % 10);

}

bool CheckAppearance( std::shared_ptr<GameCharacter>* objectArray, const int size , int stage )
{
    cout<<"checking Appearance"<<endl;
    bool cont_to_check = false;
    bool flag = false;
    int stripe_side;

    for ( int i = 1 ; i < size+1 ; ++i ) {
        if( !objectArray[i] ) continue;
        objectArray[i]->SetAppearBool( true );
    }

    cout<<"mid of checking Appearance"<<endl;
    int total_length[size+1][6] = { 0 } ;
    for ( int i = 1 ; i < size+1 ; ++i )
    {
        if( !objectArray[i] )
            continue;
        int *neighbors = objectArray[i]->GetInformationNeibor() ;//GET NEIGHBOR
        objectArray[i]->GetBlockType() ;

        for ( int j = 0 ; j < 6 ; ++j ) { 
            if ( neighbors[j] == -1 ) 
                continue;
            if ( IsSameColor(objectArray[ neighbors[j] ]->GetBlockType() , objectArray[i]->GetBlockType()) )
            {
                total_length[i][j] = CheckNextAppearance( objectArray, objectArray[ neighbors[j] ], j, 1 ) ;
            }
        }
    }

    for ( int i = 1 ; i < size+1 ; ++i )
    {
        if ( DisappearMethodOfRainbowBall(objectArray, objectArray[i] , total_length[i] ) ) {
            objectArray[i]->SetBlockType( RAINBOWBALL_OBJECT );
        }
    }
    for ( int i = 1 ; i < size+1 ; ++i )
    {
        if ( DisappearMethodOfFlower(objectArray, objectArray[i] , total_length[i] ) ) {
            objectArray[i]->SetBlockType( FLOWER_OBJECT );

        }
    }
    for ( int i = 1 ; i < size+1 ; ++i )
    {
        if ( DisappearMethodOfTriangleFlower(objectArray, objectArray[i] , total_length[i] ) ) {
            objectArray[i]->SetBlockType( TRIANGLEFLOWER_OBJECT );
        }
    }
    for ( int i = 1 ; i < size+1 ; ++i )
    {
        if ( DisappearMethodOfStarFlower(objectArray, objectArray[i] , total_length[i] ) ) {
            objectArray[i]->SetBlockType( STARFLOWER_OBJECT );
        }
    }
    for ( int i = 1 ; i < size+1 ; ++i )
    {
        if ( (stripe_side = DisappearMethodOfStripe(objectArray, objectArray[i] , total_length[i], 2 )) != -1 ) {

            // int stripe_side = DisappearMethodOfStripe(objectArray, objectArray[i] , total_length );
            // cout<<"side: "<<stripe_side<<endl;
            if ( stripe_side == 0 || stripe_side == 3)
            {
                cout<<"aaa"<<endl;
                objectArray[i]->SetBlockType( STRIPE_OBJECT );
            }
            else if ( stripe_side == 1 || stripe_side == 4)
            {
                cout<<"bbb"<<endl;
                objectArray[i]->SetBlockType( STRIPE_RIGHT_LEFT_OBJECT );
            }
            else if ( stripe_side == 2 || stripe_side == 5)
            {
                cout<<"ccc"<<endl;
                objectArray[i]->SetBlockType( STRIPE_LEFT_RIGHT_OBJECT );
            }

        }
    }
    for ( int i = 1 ; i < size+1 ; ++i )
    {
        if ( (stripe_side = DisappearMethodOfStripe(objectArray, objectArray[i] , total_length[i], 1 )) != -1 ) {
            objectArray[i]->SetBlockType( STRIPE_OBJECT );
        }
    }
    for ( int i = 1 ; i < size+1 ; ++i )
    {
        if ( DisappearMethodOfOneLine(objectArray, objectArray[i] , total_length[i] ) ) {
            objectArray[i]->SetBlockType( NORMAL_OBJECT);
        }
    }
    // for ( int i = 1 ; i < size+1 ; ++i )
    // {
    //     else {
    //         objectArray[i]->SetBlockType( NORMAL_OBJECT );
    //     }
    // }
    for ( int i = 1 ; i < size+1 ; ++i )
    {
        if ( stage == 0 )
            objectArray[i]->SetBlockType( NORMAL_OBJECT );
    }


    for ( int i = 1 ; i < size+1 ; ++i ) {
        if( !objectArray[i] ) continue;
        if( !objectArray[i]->GetAppearBool() ) flag = true;
        // objectArray[i]->SetSwitched(0);
    }

    cout<<"end checking Appearance"<<endl;

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
        // if ( (total_length[i] + total_length[j] ) == 2  && object->GetAppearBool() == true) {
        //
        //
        //
        // }
        if ( total_length[i] ==1 && total_length[j] == 1 && object->GetAppearBool() == true)//mid
        {
            cont_to_check = true ;
            object->SetAppearBool( false );
            DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, 0);
            DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], j, 0);
            cout << "Line" << endl;
        }
    }

    return cont_to_check;

}

// int CheckSwitchedInfo( std::shared_ptr<GameCharacter>& object )
// {
//     return object->GetSwitchedInfo();
// }

int DisappearMethodOfStripe( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length, int priority ) { //total_length = 6 side's consec.


    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        // do not make true if it was checked
        if ( (total_length[i] + total_length[j] ) == 3 ) {



            // check initial switch -> find switch side
            if (object->GetSwitchedInfo() == 2 && priority == 2 && object->GetAppearBool() == true)
            {
                object->SetAppearBool( false );
                //all disappear(except switched blocks)
                DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);
                DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[j] ], j, total_length[j]-1);

                //find initial neighbor side
                for ( int switch_side = 0  ; switch_side < 6 ; ++switch_side )
                {
                    if (objectArray[ object->GetInformationNeibor()[switch_side]]->GetSwitchedInfo() == 2 )
                    {
                        cout<<object->GetInformationPosNumber()<<" GetSwitchedInfo(): "<<object->GetSwitchedInfo()<<endl;
                        cout << "Stripe" << endl;
                        cout<<"return: "<<switch_side<<endl;
                        return switch_side;
                    }
                }
            }
            else if (object->GetSwitchedInfo() == 1 && priority == 1 && object->GetAppearBool() == true)
            {
                object->SetAppearBool( false );
                //all disappear(except switched blocks)
                cout<<"test"<<endl;
                DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);
                DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[j] ], j, total_length[j]-1);

                cout<<object->GetInformationPosNumber()<<" GetSwitchedInfo(): "<<object->GetSwitchedInfo()<<endl;
                cout << "Stripe" << endl;
                cout<<"return: "<<0<<endl;
                return 0;
            }

            else //initial(not started)
            {

                object->SetAppearBool( false );
            }


        }
    }
    return -1;
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

            if ( total_length[i] >= 1 && total_length[j] >= 1  && object->GetAppearBool() == true) {//two side 1
                cont_to_check = true ;
                object->SetAppearBool( false );
                cout<<"Flower"<<endl;

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

    if (check_sides >= 2 && object->GetAppearBool() == true)
    {
        for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j )
        {
            DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);
            DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[j]-1);
        }
        object->SetAppearBool( false );
        cout<<"Star Flower"<<endl;
        cont_to_check = true ;
    }

    return cont_to_check;

}

bool DisappearMethodOfTriangleFlower( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length ) { //total_length = 6 side's consec.

    bool cont_to_check = false ; //two side >=2
    int check = 0;
    // two side >= 2
    for ( int i = 0  ; i < 6 ; ++i ) {
        if ( total_length[i] >= 2 ) {
            check ++ ;
        }
    }

    if (check >= 2 && object->GetAppearBool() == true)
    {
        object->SetBlockType( TRIANGLEFLOWER_OBJECT );
        object->SetAppearBool( false );
        cout<<"Triangle Flower"<<endl;
        cont_to_check = true ;
        for ( int i = 0  ; i < 6 ; ++i )
        {
            cout<<i<<" side total length: "<<total_length[i]<<endl;
            if (total_length[i] > 0)
                DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);
        }

    }

    return cont_to_check;

}

bool DisappearMethodOfRainbowBall( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length ) { //total_length = 6 side's consec.

    bool cont_to_check = false ;
    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( (total_length[i] + total_length[j] ) >= 4 ) {


            // if( !(total_length[i] > 0 && total_length[j] == 0) ) {
            //     //self disappear
            //     object->SetAppearBool( false );
            // }
            if (object->GetSwitchedInfo() > 0 && object->GetAppearBool() == true )
            {
                object->SetAppearBool( false );
                cout<<"Rainbow Ball"<<endl;
                cont_to_check = true ;
                //all disappear(except switched blocks)
                DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);
                DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[j] ], j, total_length[j]-1);
                return cont_to_check;
            }
            else //initial(not started)
            {
                object->SetAppearBool( false );
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
        objectArray[i]->SetSwitched(0);
        // cout<<"set "<<i<<" SetSwitched to 0"<<endl;
        // if ( !objectArray[i] ) continue; 
        if ( !objectArray[i]->GetAppearBool() && objectArray[i]->GetType() == NORMAL_OBJECT ) {
            objectArray[i]->DisAppear();
            ++stage_point_counter[stage];

        }
        else {
            if ( objectArray[i]->GetType() != NORMAL_OBJECT && !objectArray[i]->GetAppearBool() ) {
                objectArray[i]->SetAppearBool(true);
                ++stage_point_counter[stage];
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
                            objectArray[i]->SetBlockType( 0 );
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
                            objectArray[i]->SetBlockType( 0 );
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
                            objectArray[i]->SetBlockType( 0 );
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
                            objectArray[i]->SetBlockType( 0 );
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
                            objectArray[i]->SetBlockType( 0 );
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
                            objectArray[i]->SetBlockType( 0 );
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
                            objectArray[i]->SetBlockType( 0 );
                        }

                        break;
                    default:
                        break;
                }
            }
        }

    }
    cout<<"score: "<<stage_point_counter[stage]<<endl;
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