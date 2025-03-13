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
    std::vector<std::vector<int>> total_length(size + 1, std::vector<int>(6, 0));
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
        if ( DisappearMethodOfRainbowBall(objectArray, objectArray[i] , total_length[i].data() ) ) {
            objectArray[i]->SetBlockType( RAINBOWBALL_OBJECT );
        }
    }
    for ( int i = 1 ; i < size+1 ; ++i )
    {
        if ( DisappearMethodOfFlower(objectArray, objectArray[i] , total_length[i].data() ) ) {
            objectArray[i]->SetBlockType( FLOWER_OBJECT );

        }
    }
    for ( int i = 1 ; i < size+1 ; ++i )
    {
        if ( DisappearMethodOfTriangleFlower(objectArray, objectArray[i] , total_length[i].data() ) ) {
            objectArray[i]->SetBlockType( TRIANGLEFLOWER_OBJECT );
        }
    }
    for ( int i = 1 ; i < size+1 ; ++i )
    {
        if ( DisappearMethodOfStarFlower(objectArray, objectArray[i] , total_length[i].data() ) ) {
            objectArray[i]->SetBlockType( STARFLOWER_OBJECT );
        }
    }
    for ( int i = 1 ; i < size+1 ; ++i )
    {
        if ( (stripe_side = DisappearMethodOfStripe(objectArray, objectArray[i] , total_length[i].data(), 2 )) != -1 ) {

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
        if ( (DisappearMethodOfStripe(objectArray, objectArray[i] , total_length[i].data(), 1 )) != -1 ) {
            objectArray[i]->SetBlockType( STRIPE_OBJECT );
        }
    }
    for ( int i = 1 ; i < size+1 ; ++i )
    {
        // cout<<"no  "<<i<<"length1  "<<total_length[i].data()[0]<<endl;
        if ( DisappearMethodOfOneLine(objectArray, objectArray[i] , total_length[i].data() ) ) {
            objectArray[i]->SetBlockType( NORMAL_OBJECT);
        }
        // else {
        //     objectArray[i]->SetBlockType( NORMAL_OBJECT );
        //     }
    }
    // for ( int i = 1 ; i < size+1 ; ++i )
    // {
    //
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
