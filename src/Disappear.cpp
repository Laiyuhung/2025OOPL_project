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
        if ( objectArray[i]->GetVisibility() == false ) {
            continue;
        }
        // cout<<"set "<<i<<" SetSwitched to 0"<<endl;
        if ( !objectArray[i]->GetAppearBool() && ( objectArray[i]->GetCurrentType() == NORMAL_OBJECT || objectArray[i]->GetGenerate() ) ) {
            MakeDisappearWithObject( objectArray , i , size , stage );
            objectArray[i]->SetGenerate( false );
        }
    }

    for ( int i = 1 ; i < size+1 ; ++i ) {
        if ( objectArray[i]->GetType() != NORMAL_OBJECT && !objectArray[i]->GetAppearBool() ) {
            PointUpdate( stage , GetPoint(stage) + 1 );
            objectArray[i]->SetAppearBool(true);
            CheckSpecialObject( objectArray, i, stage );
            objectArray[i]->SetGenerate( true );
            objectArray[i]->SetCurrentType( objectArray[i]->GetType() );
            objectArray[i]->SetBlockType( NORMAL_OBJECT );
        } 
    }

    for ( int i = 1 ; i < size+1 ; ++i ) {
        if ( !objectArray[i]->GetAppearBool() ) {
            PointUpdate( stage , GetPoint(stage) + 1 );
        }
    }
    cout<<"score: "<<GetPoint(stage)<<endl;
}

bool DisappearMethodOfOneLine( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length ) {
    
    bool cont_to_check = false ;

    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( (total_length[i] + total_length[j] ) == 2 ) {

            bool left_check = true ;
            bool right_check = true ;

            //check all side appear
            if (total_length[i] > 0)
                left_check = checkAppearanceOfObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);

            if (total_length[j] > 0)
                right_check = checkAppearanceOfObject( objectArray, objectArray[ object->GetInformationNeibor()[j] ], j, total_length[j]-1);


            //all side appear checked(true)
            if ( object->GetAppearBool() == true && left_check == true && right_check == true )
            {
                object->SetAppearBool( false );
                cout<<"Line"<<endl;
                cont_to_check = true ;
                //all disappear(except switched blocks)
                if (total_length[i] > 0)
                    DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);

                if (total_length[j] > 0)
                    DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[j] ], j, total_length[j]-1);

                return cont_to_check;
            }
            // else //initial(not started)
            // {
            //     object->SetAppearBool( false );
            // }

        }
        else if (total_length[i] + total_length[j]  > 2) // check all lines initial(line stripe rainbowball)
        {
            bool left_check_switch = true ;
            bool right_check_switch = true ;

            //check all side appear
            if (total_length[i] > 0)
                left_check_switch = checkSwitchedAllInfoWithZero( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);

            if (total_length[j] > 0)
                right_check_switch = checkSwitchedAllInfoWithZero( objectArray, objectArray[ object->GetInformationNeibor()[j] ], j, total_length[j]-1);

            if (left_check_switch == true && right_check_switch == true && object->GetAppearBool() == true)
            {
                cont_to_check = true ;
                if (total_length[i] > 0)
                    DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);

                if (total_length[j] > 0)
                    DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[j] ], j, total_length[j]-1);

                return cont_to_check;
            }
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

            bool left_check = true ;
            bool right_check = true ;

            //check all side appear
            if (total_length[i] > 0)
                left_check = checkAppearanceOfObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);

            if (total_length[j] > 0)
                right_check = checkAppearanceOfObject( objectArray, objectArray[ object->GetInformationNeibor()[j] ], j, total_length[j]-1);

            // check initial switch -> find switch side
            if (object->GetSwitchedInfo() == 2 && priority == 2 && object->GetAppearBool() == true  && left_check == true && right_check == true)
            {
                object->SetAppearBool( false );
                //all disappear(except switched blocks)
                if (total_length[i] > 0)
                    DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);
                if (total_length[j] > 0)
                    DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[j] ], j, total_length[j]-1);

                //find initial neighbor side
                for ( int switch_side = 0  ; switch_side < 6 ; ++switch_side )
                {
                    if (objectArray[ object->GetInformationNeibor()[switch_side]]->GetSwitchedInfo() == 2 )
                    {
                        cout << "Stripe" << endl;
                        return switch_side;
                    }
                }
            }
            else if (object->GetSwitchedInfo() == 1 && priority == 1 && object->GetAppearBool() == true  && left_check == true && right_check == true)
            {
                //all disappear
                object->SetAppearBool( false );
                if (total_length[i] > 0)
                    DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);
                if (total_length[j] > 0)
                    DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[j] ], j, total_length[j]-1);

                cout << "Stripe" << endl;
                return 0;
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
            bool checkside_check = true ;
            checkside_check = checkAppearanceOfObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);

            if (checkside_check == true)
            {
                check_side = i ;
                break;
            }

        }
    }

    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( i != check_side && j != check_side && check_side != -1 )
        {
            bool left_check = true ;
            bool right_check = true ;

            //check all side appear
            if (total_length[i] > 0)
                left_check = checkAppearanceOfObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);

            if (total_length[j] > 0)
                right_check = checkAppearanceOfObject( objectArray, objectArray[ object->GetInformationNeibor()[j] ], j, total_length[j]-1);

            if ( total_length[i] >= 1 && total_length[j] >= 1  && object->GetAppearBool() == true  && left_check == true && right_check == true && check_side != -1) {//two side 1
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
            bool left_check = checkAppearanceOfObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);
            bool right_check = checkAppearanceOfObject( objectArray, objectArray[ object->GetInformationNeibor()[j] ], j, total_length[j]-1);

            if (left_check == true && right_check == true )
                check_sides++ ;
        }
    }


    if (check_sides >= 2 && object->GetAppearBool() == true)
    {
        for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j )
        {
            if (total_length[i] > 0)
                DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);
            if (total_length[j] > 0)
                DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[j] ], j, total_length[j]-1);
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
            bool left_check = checkAppearanceOfObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);

            if (left_check == true)
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
            // cout<<i<<" side total length: "<<total_length[i]<<endl;
            if (total_length[i] > 0)
                DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);
        }

    }

    return cont_to_check;

}

bool DisappearMethodOfRainbowBall( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length, int priority ) { 

    bool cont_to_check = false ;
    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( (total_length[i] + total_length[j] ) >= 4 ) {

            bool left_check = checkAppearanceOfObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);
            bool right_check = checkAppearanceOfObject( objectArray, objectArray[ object->GetInformationNeibor()[j] ], j, total_length[j]-1);

            if (object->GetSwitchedInfo() == priority && object->GetAppearBool() == true && left_check == true && right_check == true)
            {
                object->SetAppearBool( false );
                cout<<"Rainbow Ball"<<endl;
                cont_to_check = true ;
                //all disappear(except switched blocks)
                if (total_length[i] > 0)
                    DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[i] ], i, total_length[i]-1);
                if (total_length[j] > 0)
                    DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[j] ], j, total_length[j]-1);
                return cont_to_check;
            }


        }
    }
    return cont_to_check;
}


void DisappearBySingleObject ( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int side, int length_left) {
    object->SetAppearBool( false );
    // cout<<"object disapp."<<endl;

    if( !object  )
        return;

    if ( length_left  >  0 )
    {
        // cout<<"side: "<<side<<" length_left: "<<length_left<<endl;
        DisappearBySingleObject( objectArray, objectArray[ object->GetInformationNeibor()[side] ], side, length_left - 1) ;
    }


}

bool checkAppearanceOfObject ( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int side, int length_left)
{
    bool return_bool = true;

    if( !object  )
        return false;

    if ( object->GetAppearBool() == true )
    {
        if( length_left >  0 )
        {
            return_bool = checkAppearanceOfObject ( objectArray, objectArray[ object->GetInformationNeibor()[side] ], side, length_left - 1);
            return return_bool;
        }
        else
        {
            return object->GetAppearBool();
        }
    }

    else{
        // cout<<"return_bool: false"<<endl;
        return false ;
    }
}

bool checkSwitchedAllInfoWithZero ( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int side, int length_left)
{

    if( !object  )
        return false;

    if ( object->GetSwitchedInfo() == 0 )
    {
        if( length_left >  0 )
            return checkSwitchedAllInfoWithZero ( objectArray, objectArray[ object->GetInformationNeibor()[side] ], side, length_left - 1) ;
        else
            return true;
    }
    else
        return false ;
}

void MakeDisappearWithObject( std::shared_ptr<GameCharacter>* objectArray , int current_pos , const int size , const int stage ) {
    if ( objectArray[current_pos]->GetVisibility() == false ) {
        return;
    }
    switch ( objectArray[current_pos]->GetCurrentType() ) {
        case STRIPE_OBJECT:
            MakeDisappearWithStripe( objectArray , current_pos , size , stage );
            break;
        case STRIPE_LEFT_RIGHT_OBJECT:
            MakeDisappearWithStripeInLeftRight( objectArray , current_pos , size , stage );
            break;
        case STRIPE_RIGHT_LEFT_OBJECT:
            MakeDisappearWithStripeInRightLeft( objectArray , current_pos , size , stage );
            break;
        case RAINBOWBALL_OBJECT:
            MakeDisappearWithRainbow( objectArray,  current_pos , size , stage );
            break;
        case FLOWER_OBJECT:
            MakeDisappearWithFlower( objectArray,  current_pos , size , stage );
            break;
        case TRIANGLEFLOWER_OBJECT:
            MakeDisappearWithTriangleFlower( objectArray,  current_pos , size , stage  );
            break;
        case STARFLOWER_OBJECT:
            MakeDisappearWithStarFlower( objectArray,  current_pos , size , stage  );
            break;
        case NORMAL_OBJECT:
            objectArray[current_pos]->DisAppear();
            objectArray[current_pos]->SetAppearBool( false );
            break;
        default:
            objectArray[current_pos]->DisAppear();
            objectArray[current_pos]->SetAppearBool( false );
            break;
    }
}

void MakeDisappearWithStripe( std::shared_ptr<GameCharacter>* objectArray , int current_pos , const int size , const int stage ) {
    objectArray[current_pos]->DisAppear();
    objectArray[current_pos]->SetAppearBool( false );
    cout << "STRIPE\n";
    for ( int i = current_pos , j = current_pos ; ; ) {
        if ( objectArray[i]->GetInformationNeibor()[0] != -1 ) {
            MakeDisappearWithObject( objectArray , objectArray[i]->GetInformationNeibor()[0] , size , stage );
            i = objectArray[i]->GetInformationNeibor()[0];
        }
        if ( objectArray[j]->GetInformationNeibor()[3] != -1 ) {
            MakeDisappearWithObject( objectArray , objectArray[j]->GetInformationNeibor()[3] , size , stage );
            j = objectArray[j]->GetInformationNeibor()[3];
        }
        if ( objectArray[i]->GetInformationNeibor()[0] == -1 && objectArray[j]->GetInformationNeibor()[3] == -1 )
            break;
    }
}

void MakeDisappearWithStripeInLeftRight( std::shared_ptr<GameCharacter>* objectArray , int current_pos , const int size , const int stage ) {
    objectArray[current_pos]->DisAppear();
    objectArray[current_pos]->SetAppearBool( false );
    cout << "LEFT_RIGHT\n";
    for ( int i = current_pos , j = current_pos ; ; ) {
        if ( objectArray[i]->GetInformationNeibor()[2] != -1 ) {
            MakeDisappearWithObject( objectArray , objectArray[i]->GetInformationNeibor()[2] , size , stage );
            i = objectArray[i]->GetInformationNeibor()[2];
        }
        if ( objectArray[j]->GetInformationNeibor()[5] != -1 ) {
            MakeDisappearWithObject( objectArray , objectArray[j]->GetInformationNeibor()[5] , size , stage );
            j = objectArray[j]->GetInformationNeibor()[5];
        }
        if ( objectArray[i]->GetInformationNeibor()[2] == -1 && objectArray[j]->GetInformationNeibor()[5] == -1 )
            break;
    }
}

void MakeDisappearWithStripeInRightLeft( std::shared_ptr<GameCharacter>* objectArray , int current_pos , const int size , const int stage ) {
    objectArray[current_pos]->DisAppear();
    objectArray[current_pos]->SetAppearBool( false );
    cout << "RIGHT_LEFT\n";
    for ( int i = current_pos , j = current_pos ; ; ) {
        if ( objectArray[i]->GetInformationNeibor()[1] != -1 ) {
            MakeDisappearWithObject( objectArray , objectArray[i]->GetInformationNeibor()[1] , size , stage );
            i = objectArray[i]->GetInformationNeibor()[1];
        }
        if ( objectArray[j]->GetInformationNeibor()[4] != -1 ) {
            MakeDisappearWithObject( objectArray , objectArray[j]->GetInformationNeibor()[4] , size , stage );
            j = objectArray[j]->GetInformationNeibor()[4];
        }
        if ( objectArray[i]->GetInformationNeibor()[1] == -1 && objectArray[j]->GetInformationNeibor()[4] == -1 )
            break;
    }
}

void MakeDisappearWithRainbow( std::shared_ptr<GameCharacter>* objectArray , int current_pos , const int size , const int stage ) {
    objectArray[current_pos]->DisAppear();
    objectArray[current_pos]->SetAppearBool( false );
    if ( objectArray[current_pos]->GetBlockType() == 0 ) {
        objectArray[current_pos]->SetBlock( BLUE_OBJECT );
    }
    cout << "RAINBOW\n";
    for ( int i = 1 ; i < size+1 ; ++i ) {
        if ( i != current_pos && objectArray[current_pos]->GetBlockType() == objectArray[i]->GetBlockType() ) {
            MakeDisappearWithObject( objectArray , i , size , stage );
        }
    }
}

void MakeDisappearWithTriangleFlower( std::shared_ptr<GameCharacter>* objectArray , int current_pos , const int size , const int stage ) {
    objectArray[current_pos]->DisAppear();
    objectArray[current_pos]->SetAppearBool( false );
    cout << "TRIANGLE_FLOWER\n";
    for ( int i = 0 ; i < 6 ; ++i )
    {
        if (objectArray[current_pos]->GetInformationNeibor()[i] != -1)
            MakeDisappearWithObject( objectArray , objectArray[current_pos]->GetInformationNeibor()[i] , size , stage );
    }
    if (objectArray[current_pos]->GetInformationNeibor()[0] != -1 && objectArray[objectArray[current_pos]->GetInformationNeibor()[0] ] ->GetInformationNeibor()[5] != -1)
        MakeDisappearWithObject( objectArray , objectArray[objectArray[current_pos]->GetInformationNeibor()[0] ] ->GetInformationNeibor()[5] , size , stage );

    if (objectArray[current_pos]->GetInformationNeibor()[2] != -1 && objectArray[objectArray[current_pos]->GetInformationNeibor()[2] ] ->GetInformationNeibor()[1] != -1)
        MakeDisappearWithObject( objectArray , objectArray[objectArray[current_pos]->GetInformationNeibor()[2] ] ->GetInformationNeibor()[1] , size , stage );

    if (objectArray[current_pos]->GetInformationNeibor()[4] != -1 && objectArray[objectArray[current_pos]->GetInformationNeibor()[4] ] ->GetInformationNeibor()[3] != -1)
        MakeDisappearWithObject( objectArray , objectArray[objectArray[current_pos]->GetInformationNeibor()[4] ] ->GetInformationNeibor()[3] , size , stage );

}

void MakeDisappearWithFlower( std::shared_ptr<GameCharacter>* objectArray , int current_pos , const int size , const int stage ) {
    objectArray[current_pos]->DisAppear();
    objectArray[current_pos]->SetAppearBool( false );
    cout << "FLOWER\n";
    for ( int i = 0 ; i < 6 ; ++i )
    {
        if (objectArray[current_pos]->GetInformationNeibor()[i] != -1){
            MakeDisappearWithObject( objectArray , objectArray[current_pos]->GetInformationNeibor()[i] , size , stage );
            cout<<i<<" ";
        }

    }
    if (objectArray[current_pos]->GetInformationNeibor()[0] != -1 && objectArray[objectArray[current_pos]->GetInformationNeibor()[0] ] ->GetInformationNeibor()[5] != -1){
        MakeDisappearWithObject( objectArray , objectArray[objectArray[current_pos]->GetInformationNeibor()[0] ] ->GetInformationNeibor()[5] , size , stage );
    }
    if (objectArray[current_pos]->GetInformationNeibor()[0] != -1 && objectArray[objectArray[current_pos]->GetInformationNeibor()[0] ] ->GetInformationNeibor()[1] != -1){
        MakeDisappearWithObject( objectArray , objectArray[objectArray[current_pos]->GetInformationNeibor()[0] ] ->GetInformationNeibor()[1] , size , stage );
    }
    if (objectArray[current_pos]->GetInformationNeibor()[3] != -1 && objectArray[objectArray[current_pos]->GetInformationNeibor()[3] ] ->GetInformationNeibor()[2] != -1){
        MakeDisappearWithObject( objectArray , objectArray[objectArray[current_pos]->GetInformationNeibor()[3] ] ->GetInformationNeibor()[2] , size , stage );
    }
    if (objectArray[current_pos]->GetInformationNeibor()[3] != -1 && objectArray[objectArray[current_pos]->GetInformationNeibor()[3] ] ->GetInformationNeibor()[4] != -1){
        MakeDisappearWithObject( objectArray , objectArray[objectArray[current_pos]->GetInformationNeibor()[3] ] ->GetInformationNeibor()[4] , size , stage );
    }
    if (objectArray[current_pos]->GetInformationNeibor()[1] != -1 && objectArray[objectArray[current_pos]->GetInformationNeibor()[1] ] ->GetInformationNeibor()[2] != -1){
        MakeDisappearWithObject( objectArray , objectArray[objectArray[current_pos]->GetInformationNeibor()[1] ] ->GetInformationNeibor()[2] , size , stage );
    }
    if (objectArray[current_pos]->GetInformationNeibor()[5] != -1 && objectArray[objectArray[current_pos]->GetInformationNeibor()[5] ] ->GetInformationNeibor()[4] != -1){
        MakeDisappearWithObject( objectArray , objectArray[objectArray[current_pos]->GetInformationNeibor()[5] ] ->GetInformationNeibor()[4] , size , stage );
    }
}

void MakeDisappearWithStarFlower( std::shared_ptr<GameCharacter>* objectArray , int current_pos , const int size , const int stage ) {
    objectArray[current_pos]->DisAppear();
    objectArray[current_pos]->SetAppearBool( false );
    cout << "STAR_FLOWER\n";
    for ( int i = 0 ; i < 6 ; ++i )
    {
        if (objectArray[current_pos]->GetInformationNeibor()[i] != -1){
            MakeDisappearWithObject( objectArray , objectArray[current_pos]->GetInformationNeibor()[i] , size , stage );
        
            if (objectArray[objectArray[current_pos]->GetInformationNeibor()[i]] ->GetInformationNeibor()[i] != -1)  
                MakeDisappearWithObject( objectArray , objectArray[objectArray[current_pos]->GetInformationNeibor()[i]] ->GetInformationNeibor()[i] , size , stage );

        }
    }

}