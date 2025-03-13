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

void MakeDisappear( std::shared_ptr<GameCharacter>* objectArray , const int size , int stage) {
    for ( int i = 1 ; i < size+1 ; ++i ) {
        objectArray[i]->SetSwitched(0);
        // cout<<"set "<<i<<" SetSwitched to 0"<<endl;
        // if ( !objectArray[i] ) continue; 
        if ( !objectArray[i]->GetAppearBool() && objectArray[i]->GetType() == NORMAL_OBJECT ) {
            objectArray[i]->DisAppear();
            PointUpdate( stage , GetPoint(stage) + 1 );
        }
        else {
            if ( objectArray[i]->GetType() != NORMAL_OBJECT && !objectArray[i]->GetAppearBool() ) {
                objectArray[i]->SetAppearBool(true);
                PointUpdate( stage , GetPoint(stage) + 1 );
                CheckSpecialObject( objectArray, i, stage );
            }
        }

    }
    cout<<"score: "<<GetPoint(stage)<<endl;
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
