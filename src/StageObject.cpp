#include "StageObject.hpp"
#include "App.hpp"
#include "Global.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>
#include <thread>
#include <vector>
using namespace std;
void StageObject::RandomChangeObject( int current_pos ) {
    static std::random_device rd;
    static std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> distrib(1, 7); 
    
    int ramdom_number = distrib(gen);

    switch ( ramdom_number )
    {
        case BLUE_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/blueNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( BLUE_OBJECT );
            break;
        case BROWN_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/brownNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( BROWN_OBJECT );
            break;
        case GREEN_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/greenNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( GREEN_OBJECT );
            break;
        case PINK_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/pinkNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( PINK_OBJECT );
            break;
        case ORANGE_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/orangeNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( ORANGE_OBJECT );
            break;
        case WHITE_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/whiteNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( WHITE_OBJECT );
            break;
        case YELLOW_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/yellowNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( YELLOW_OBJECT );
            break;
        default:
            break;
    }
}

void StageObject::InitializeStageCharacter() {
    static std::random_device rd;
    static std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> distrib(1, 7); 
    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        RandomChangeObject( i );
        m_Stage_Object[i]->SetInformation( stage1[i] );
        m_Stage_Object[i]->SetPosition( stage1_position[i] );
        m_Stage_Object[i]->SetZIndex(10);
        m_Stage_Object[i]->SetSize( {20, 25} );
        m_Stage_Object[i]->DisAppear();
        m_Stage_Object[i]->SetAppearBool( true );
        m_Stage_Object[i]->SetBlockType( NORMAL_OBJECT );
        m_Stage_Object[i]->SetCurrentType( NORMAL_OBJECT );
    }
}

bool StageObject::CheckAppearance( int s ) {
    bool cont_to_check = false;
    bool flag = false;
    int stripe_side;

    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if( !m_Stage_Object[i] ) continue;
        m_Stage_Object[i]->SetAppearBool( true );
    }

    // cout<<"mid of checking Appearance"<<endl;
    std::vector<std::vector<int>> total_length(m_Size + 1, std::vector<int>(6, 0));
    for ( int i = 1 ; i < m_Size+1 ; ++i )
    {
        if( !m_Stage_Object[i] )
            continue;
        int *neighbors = m_Stage_Object[i]->GetInformationNeibor();//GET NEIGHBOR
        m_Stage_Object[i]->GetBlockType() ;
        if ( m_Stage_Object[i]->GetType() == RAINBOWBALL_OBJECT && m_Stage_Object[i]->GetSwitchedInfo() == MOVE_BY_SWITCH ) {
            m_Stage_Object[i]->SetAppearBool( false );
            MakeDisappear();
            Dropping();
            return true;
        }

        for ( int j = 0 ; j < 6 ; ++j ) { 
            if ( neighbors[j] == -1 ) 
                continue;
            if ( IsSameColor(m_Stage_Object[ neighbors[j] ]->GetBlockType() , m_Stage_Object[i]->GetBlockType()) )
            {
                total_length[i][j] = CheckNextAppearance( neighbors[j] , j , 1) ;
            }
        }
    }

    for ( int i = 1 ; i < m_Size+1 ; ++i )
    {
        if ( DisappearMethodOfRainbowBall(i , total_length[i].data(), 2 ) ) {
            m_Stage_Object[i]->SetBlockType( RAINBOWBALL_OBJECT );
        }
    }

    for ( int i = 1 ; i < m_Size+1 ; ++i )
    {
        if ( DisappearMethodOfRainbowBall(i , total_length[i].data(), 1 ) ) {
            m_Stage_Object[i]->SetBlockType( RAINBOWBALL_OBJECT );
        }
    }
    for ( int i = 1 ; i < m_Size+1 ; ++i )
    {
        if ( DisappearMethodOfFlower( i , total_length[i].data() ) ) {
            m_Stage_Object[i]->SetBlockType( FLOWER_OBJECT );
        }
    }
    for ( int i = 1 ; i < m_Size+1 ; ++i )
    {
        if ( DisappearMethodOfTriangleFlower(i  , total_length[i].data() ) ) {
            m_Stage_Object[i]->SetBlockType( TRIANGLEFLOWER_OBJECT );
        }
    }
    for ( int i = 1 ; i < m_Size+1 ; ++i )
    {
        if ( DisappearMethodOfStarFlower(i , total_length[i].data() ) ) {
            m_Stage_Object[i]->SetBlockType( STARFLOWER_OBJECT );
        }
    }
    for ( int i = 1 ; i < m_Size+1 ; ++i )
    {
        stripe_side = DisappearMethodOfStripe(i , total_length[i].data(), 2 );
        // cout << stripe_side << endl;
        if ( stripe_side != -1 ) {
            if ( stripe_side == 0 || stripe_side == 3)
            {
                m_Stage_Object[i]->SetBlockType( STRIPE_OBJECT );
            }
            else if ( stripe_side == 1 || stripe_side == 4)
            {
                m_Stage_Object[i]->SetBlockType( STRIPE_RIGHT_LEFT_OBJECT );
            }
            else if ( stripe_side == 2 || stripe_side == 5)
            {
                m_Stage_Object[i]->SetBlockType( STRIPE_LEFT_RIGHT_OBJECT );
            }

        }
    }
    for ( int i = 1 ; i < m_Size+1 ; ++i )
    {
        if ( (DisappearMethodOfStripe(i  , total_length[i].data(), 1 )) != -1 ) {
            m_Stage_Object[i]->SetBlockType( STRIPE_OBJECT );
        }
    }
    for ( int i = 1 ; i < m_Size+1 ; ++i )
    {
        if ( DisappearMethodOfOneLine(i , total_length[i].data() ) ) {
            m_Stage_Object[i]->SetBlockType( NORMAL_OBJECT);
        }
    }

    for ( int i = 1 ; i < m_Size+1 ; ++i )
    {
        if ( s == 0 )
            m_Stage_Object[i]->SetBlockType( NORMAL_OBJECT );
    }


    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if( !m_Stage_Object[i] ) continue;
        if( !m_Stage_Object[i]->GetAppearBool() ) flag = true;
    }

    // cout<<"end checking Appearance"<<endl;

    if ( flag ) {
        // DebugModeOfAppearance( m_Stage_Object , size);
        MakeDisappear();
        Dropping();
    }
    return flag;
}

void StageObject::CheckSpecialObject( int i ){
    switch ( m_Stage_Object[i]->GetBlockType() )
    {
        case BLUE_OBJECT:
            if ( m_Stage_Object[i]->GetType() == STRIPE_OBJECT ) {
                m_Stage_Object[i]->SetImage( BLUE_STRIPE_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == STRIPE_LEFT_RIGHT_OBJECT ) {
                m_Stage_Object[i]->SetImage( BLUE_STRIPE_LEFT_RIGHT_OBJECT);
            }
            else if ( m_Stage_Object[i]->GetType() == STRIPE_RIGHT_LEFT_OBJECT ) {
                m_Stage_Object[i]->SetImage( BLUE_STRIPE_RIGHT_LEFT_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == FLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( BLUE_FLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == STARFLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( BLUE_STARFLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == TRIANGLEFLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( BLUE_TRIANGLEFLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == RAINBOWBALL_OBJECT ) {
                m_Stage_Object[i]->SetImage( RAINBOWBALL_OBJECT_LINK );
                m_Stage_Object[i]->SetBlock( 0 );
            }
            break;
        case BROWN_OBJECT:
            if ( m_Stage_Object[i]->GetType() == STRIPE_OBJECT ) {
                m_Stage_Object[i]->SetImage( BROWN_STRIPE_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == STRIPE_LEFT_RIGHT_OBJECT ) {
                m_Stage_Object[i]->SetImage( BROWN_STRIPE_LEFT_RIGHT_OBJECT);
            }
            else if ( m_Stage_Object[i]->GetType() == STRIPE_RIGHT_LEFT_OBJECT ) {
                m_Stage_Object[i]->SetImage( BROWN_STRIPE_RIGHT_LEFT_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == FLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( BROWN_FLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == STARFLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( BROWN_STARFLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == TRIANGLEFLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( BROWN_TRIANGLEFLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == RAINBOWBALL_OBJECT ) {
                m_Stage_Object[i]->SetImage( RAINBOWBALL_OBJECT_LINK );
                m_Stage_Object[i]->SetBlock( 0 );
            }
            break;
        case GREEN_OBJECT:
            if ( m_Stage_Object[i]->GetType() == STRIPE_OBJECT ) {
                m_Stage_Object[i]->SetImage( GREEN_STRIPE_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == STRIPE_LEFT_RIGHT_OBJECT ) {
                m_Stage_Object[i]->SetImage( GREEN_STRIPE_LEFT_RIGHT_OBJECT);
            }
            else if ( m_Stage_Object[i]->GetType() == STRIPE_RIGHT_LEFT_OBJECT ) {
                m_Stage_Object[i]->SetImage( GREEN_STRIPE_RIGHT_LEFT_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == FLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( GREEN_FLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == STARFLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( GREEN_STARFLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == TRIANGLEFLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( GREEN_TRIANGLEFLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == RAINBOWBALL_OBJECT ) {
                m_Stage_Object[i]->SetImage( RAINBOWBALL_OBJECT_LINK );
                m_Stage_Object[i]->SetBlock( 0 );
            }
            break;
        case PINK_OBJECT:
            if ( m_Stage_Object[i]->GetType() == STRIPE_OBJECT ) {
                m_Stage_Object[i]->SetImage( PINK_STRIPE_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == STRIPE_LEFT_RIGHT_OBJECT ) {
                m_Stage_Object[i]->SetImage( PINK_STRIPE_LEFT_RIGHT_OBJECT);
            }
            else if ( m_Stage_Object[i]->GetType() == STRIPE_RIGHT_LEFT_OBJECT ) {
                m_Stage_Object[i]->SetImage( PINK_STRIPE_RIGHT_LEFT_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == FLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( PINK_FLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == STARFLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( PINK_STARFLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == TRIANGLEFLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( PINK_TRIANGLEFLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == RAINBOWBALL_OBJECT ) {
                m_Stage_Object[i]->SetImage( RAINBOWBALL_OBJECT_LINK );
                m_Stage_Object[i]->SetBlock( 0 );
            }
            break;
        case ORANGE_OBJECT:
            if ( m_Stage_Object[i]->GetType() == STRIPE_OBJECT ) {
                m_Stage_Object[i]->SetImage( ORANGE_STRIPE_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == STRIPE_LEFT_RIGHT_OBJECT ) {
                m_Stage_Object[i]->SetImage( ORANGE_STRIPE_LEFT_RIGHT_OBJECT);
            }
            else if ( m_Stage_Object[i]->GetType() == STRIPE_RIGHT_LEFT_OBJECT ) {
                m_Stage_Object[i]->SetImage( ORANGE_STRIPE_RIGHT_LEFT_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == FLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( ORANGE_FLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == STARFLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( ORANGE_STARFLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == TRIANGLEFLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( ORANGE_TRIANGLEFLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == RAINBOWBALL_OBJECT ) {
                m_Stage_Object[i]->SetImage( RAINBOWBALL_OBJECT_LINK );
                m_Stage_Object[i]->SetBlock( 0 );
            }
            break;
        case WHITE_OBJECT:
            if ( m_Stage_Object[i]->GetType() == STRIPE_OBJECT ) {
                m_Stage_Object[i]->SetImage( WHITE_STRIPE_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == STRIPE_LEFT_RIGHT_OBJECT ) {
                m_Stage_Object[i]->SetImage( WHITE_STRIPE_LEFT_RIGHT_OBJECT);
            }
            else if ( m_Stage_Object[i]->GetType() == STRIPE_RIGHT_LEFT_OBJECT ) {
                m_Stage_Object[i]->SetImage( WHITE_STRIPE_RIGHT_LEFT_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == FLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( WHITE_FLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == STARFLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( WHITE_STARFLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == TRIANGLEFLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( WHITE_TRIANGLEFLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == RAINBOWBALL_OBJECT ) {
                m_Stage_Object[i]->SetImage( RAINBOWBALL_OBJECT_LINK );
                m_Stage_Object[i]->SetBlock( 0 );
            }
            break;
        case YELLOW_OBJECT:
            if ( m_Stage_Object[i]->GetType() == STRIPE_OBJECT ) {
                m_Stage_Object[i]->SetImage( YELLOW_STRIPE_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == STRIPE_LEFT_RIGHT_OBJECT ) {
                m_Stage_Object[i]->SetImage( YELLOW_STRIPE_LEFT_RIGHT_OBJECT);
            }
            else if ( m_Stage_Object[i]->GetType() == STRIPE_RIGHT_LEFT_OBJECT ) {
                m_Stage_Object[i]->SetImage( YELLOW_STRIPE_RIGHT_LEFT_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == FLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( YELLOW_FLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == STARFLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( YELLOW_STARFLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == TRIANGLEFLOWER_OBJECT ) {
                m_Stage_Object[i]->SetImage( YELLOW_TRIANGLEFLOWER_OBJECT );
            }
            else if ( m_Stage_Object[i]->GetType() == RAINBOWBALL_OBJECT ) {
                m_Stage_Object[i]->SetImage( RAINBOWBALL_OBJECT_LINK );
                m_Stage_Object[i]->SetBlock( 0 );
            }
            break;
        default:
            break;
    }
}

void StageObject::MakeDisappear() {
    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        m_Stage_Object[i]->SetSwitched(0);
        if ( m_Stage_Object[i]->GetVisibility() == false ) {
            continue;
        }
        // cout<<"set "<<i<<" SetSwitched to 0"<<endl;
        if ( !m_Stage_Object[i]->GetAppearBool() && ( m_Stage_Object[i]->GetCurrentType() == NORMAL_OBJECT || m_Stage_Object[i]->GetGenerate() ) ) {
            MakeDisappearWithObject( i );
            m_Stage_Object[i]->SetGenerate( false );
        }
    }

    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if ( m_Stage_Object[i]->GetType() != NORMAL_OBJECT && !m_Stage_Object[i]->GetAppearBool() ) {
            PointUpdate( GetPoint() + 1 );
            m_Stage_Object[i]->SetAppearBool(true);
            CheckSpecialObject( i );
            m_Stage_Object[i]->SetGenerate( true );
            m_Stage_Object[i]->SetCurrentType( m_Stage_Object[i]->GetType() );
            m_Stage_Object[i]->SetBlockType( NORMAL_OBJECT );
        } 
    }

    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if ( !m_Stage_Object[i]->GetAppearBool() ) {
            PointUpdate( GetPoint() + 1 );;
        }
    }
    cout<<"score: "<< GetPoint() <<endl;
}

void StageObject::Dropping() {
    int loop_count = 0;
    for ( int i = 1 ; i < m_Size+1 ; ) {
        if ( loop_count > m_Size || !m_Stage_Object[i] ||  m_Stage_Object[i]->GetInformationNeibor()[0] == -1 || m_Stage_Object[i]->GetAppearBool() ) {
            ++i;
            loop_count = 0;
            continue;
        }
        if ( !m_Stage_Object[i]->GetAppearBool() && m_Stage_Object[i]->GetInformationNeibor()[0] != -1 ) 
            Dropping_method( i );
        ++loop_count ;
    }
    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if ( !m_Stage_Object[i]->GetAppearBool() ) {
            RandomChangeObject( i );
            m_Stage_Object[i]->SetBlockType( NORMAL_OBJECT );
        }
        m_Stage_Object[i]->SetAppearBool( true );
    }
    if ( m_Stage != 0 ) 
        AppearAll();
    
    CheckAppearance( m_Stage );
}

void StageObject::PointUpdate(int point ) {
    stage_point_counter[m_Stage] = point;
}

int StageObject::GetPoint() {
    return stage_point_counter[m_Stage];
}

void StageObject::AppearAll() {
    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if( !m_Stage_Object[i] ) continue;
        m_Stage_Object[i]->SetAppearBool( true );
        m_Stage_Object[i]->Appear();
    }
}

void StageObject::DisAppearAll() {
    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if( !m_Stage_Object[i] ) continue;
        m_Stage_Object[i]->SetAppearBool( false );
        m_Stage_Object[i]->DisAppear();
    }
}

void StageObject::ClearAllClick() {
    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        m_Stage_Object[i]->SetClick( false );
    }
}

void StageObject::MakeDisappearWithObject( int current_pos ) {
    if ( m_Stage_Object[current_pos]->GetVisibility() == false ) {
        return;
    }
    switch ( m_Stage_Object[current_pos]->GetCurrentType() ) {
        case STRIPE_OBJECT:
            MakeDisappearWithStripe( current_pos );
            break;
        case STRIPE_LEFT_RIGHT_OBJECT:
            MakeDisappearWithStripeInLeftRight( current_pos );
            break;
        case STRIPE_RIGHT_LEFT_OBJECT:
            MakeDisappearWithStripeInRightLeft( current_pos );
            break;
        case RAINBOWBALL_OBJECT:
            MakeDisappearWithRainbow( current_pos );
            break;
        case FLOWER_OBJECT:
            MakeDisappearWithFlower( current_pos );
            break;
        case TRIANGLEFLOWER_OBJECT:
            MakeDisappearWithTriangleFlower( current_pos );
            break;
        case STARFLOWER_OBJECT:
            MakeDisappearWithStarFlower( current_pos );
            break;
        case NORMAL_OBJECT:
            m_Stage_Object[current_pos]->DisAppear();
            m_Stage_Object[current_pos]->SetAppearBool( false );
            break;
        default:
            m_Stage_Object[current_pos]->DisAppear();
            m_Stage_Object[current_pos]->SetAppearBool( false );
            break;
    }
}

void StageObject::MakeDisappearWithStripe( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    cout << "STRIPE\n";
    for ( int i = current_pos , j = current_pos ; ; ) {
        if ( m_Stage_Object[i]->GetInformationNeibor()[0] != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[0] );
            i = m_Stage_Object[i]->GetInformationNeibor()[0];
        }
        if ( m_Stage_Object[j]->GetInformationNeibor()[3] != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[3] );
            j = m_Stage_Object[j]->GetInformationNeibor()[3];
        }
        if ( m_Stage_Object[i]->GetInformationNeibor()[0] == -1 && m_Stage_Object[j]->GetInformationNeibor()[3] == -1 )
            break;
    }
}

void StageObject::MakeDisappearWithStripeInLeftRight( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    cout << "LEFT_RIGHT\n";
    for ( int i = current_pos , j = current_pos ; ; ) {
        if ( m_Stage_Object[i]->GetInformationNeibor()[2] != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[2] );
            i = m_Stage_Object[i]->GetInformationNeibor()[2];
        }
        if ( m_Stage_Object[j]->GetInformationNeibor()[5] != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[5]  );
            j = m_Stage_Object[j]->GetInformationNeibor()[5];
        }
        if ( m_Stage_Object[i]->GetInformationNeibor()[2] == -1 && m_Stage_Object[j]->GetInformationNeibor()[5] == -1 )
            break;
    }
}

void StageObject::MakeDisappearWithStripeInRightLeft( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    cout << "RIGHT_LEFT\n";
    for ( int i = current_pos , j = current_pos ; ; ) {
        if ( m_Stage_Object[i]->GetInformationNeibor()[1] != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[1] );
            i = m_Stage_Object[i]->GetInformationNeibor()[1];
        }
        if ( m_Stage_Object[j]->GetInformationNeibor()[4] != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[4] );
            j = m_Stage_Object[j]->GetInformationNeibor()[4];
        }
        if ( m_Stage_Object[i]->GetInformationNeibor()[1] == -1 && m_Stage_Object[j]->GetInformationNeibor()[4] == -1 )
            break;
    }
}

void StageObject::MakeDisappearWithRainbow( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    if ( m_Stage_Object[current_pos]->GetBlockType() == 0 ) {
        m_Stage_Object[current_pos]->SetBlock( BLUE_OBJECT );
    }
    cout << "RAINBOW\n";
    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if ( i != current_pos && m_Stage_Object[current_pos]->GetBlockType() == m_Stage_Object[i]->GetBlockType() ) {
            MakeDisappearWithObject( i );
        }
    }
}

void StageObject::MakeDisappearWithTriangleFlower( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    cout << "TRIANGLE_FLOWER\n";
    for ( int i = 0 ; i < 6 ; ++i )
    {
        if (m_Stage_Object[current_pos]->GetInformationNeibor()[i] != -1)
            MakeDisappearWithObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]  );
    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[0] != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[0] ] ->GetInformationNeibor()[5] != -1)
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[0] ] ->GetInformationNeibor()[5] );

    if (m_Stage_Object[current_pos]->GetInformationNeibor()[2] != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[2] ] ->GetInformationNeibor()[1] != -1)
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[2] ] ->GetInformationNeibor()[1] );

    if (m_Stage_Object[current_pos]->GetInformationNeibor()[4] != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[4] ] ->GetInformationNeibor()[3] != -1)
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[4] ] ->GetInformationNeibor()[3] );

}

void StageObject::MakeDisappearWithFlower( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    cout << "FLOWER\n";
    for ( int i = 0 ; i < 6 ; ++i )
    {
        if (m_Stage_Object[current_pos]->GetInformationNeibor()[i] != -1){
            MakeDisappearWithObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i] );
            cout<<i<<" ";
        }

    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[0] != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[0] ] ->GetInformationNeibor()[5] != -1){
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[0] ] ->GetInformationNeibor()[5]  );
    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[0] != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[0] ] ->GetInformationNeibor()[1] != -1){
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[0] ] ->GetInformationNeibor()[1] );
    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[3] != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[3] ] ->GetInformationNeibor()[2] != -1){
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[3] ] ->GetInformationNeibor()[2]  );
    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[3] != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[3] ] ->GetInformationNeibor()[4] != -1){
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[3] ] ->GetInformationNeibor()[4] );
    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[1] != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[1] ] ->GetInformationNeibor()[2] != -1){
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[1] ] ->GetInformationNeibor()[2] );
    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[5] != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[5] ] ->GetInformationNeibor()[4] != -1){
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[5] ] ->GetInformationNeibor()[4] );
    }
}

void StageObject::MakeDisappearWithStarFlower( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    cout << "STAR_FLOWER\n";
    for ( int i = 0 ; i < 6 ; ++i )
    {
        if (m_Stage_Object[current_pos]->GetInformationNeibor()[i] != -1){
            MakeDisappearWithObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]  );
        
            if (m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[i]] ->GetInformationNeibor()[i] != -1)  
                MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[i]] ->GetInformationNeibor()[i] );

        }
    }
}

bool StageObject::DisappearMethodOfOneLine( int current_pos , int *total_length ) {

    bool cont_to_check = false ;

    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( (total_length[i] + total_length[j] ) == 2 ) {

            bool left_check = true ;
            bool right_check = true ;

            //check all side appear
            if (total_length[i] > 0)
                left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i] , i, total_length[i]-1);

            if (total_length[j] > 0)
                right_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j] , j, total_length[j]-1);


            //all side appear checked(true)
            if ( m_Stage_Object[current_pos]->GetAppearBool() == true && left_check == true && right_check == true )
            {
                m_Stage_Object[current_pos]->SetAppearBool( false );
                cout<<"Line"<<endl;
                cont_to_check = true ;
                //all disappear(except switched blocks)
                if (total_length[i] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i] , i, total_length[i]-1);

                if (total_length[j] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j] , j, total_length[j]-1);

                return cont_to_check;
            }

        }
        else if (total_length[i] + total_length[j]  > 2) // check all lines initial(line stripe rainbowball)
        {
            bool left_check_switch = true ;
            bool right_check_switch = true ;

            //check all side appear
            if (total_length[i] > 0)
                left_check_switch = checkSwitchedAllInfoWithZero( m_Stage_Object[current_pos]->GetInformationNeibor()[i] , i, total_length[i]-1);

            if (total_length[j] > 0)
                right_check_switch = checkSwitchedAllInfoWithZero( m_Stage_Object[current_pos]->GetInformationNeibor()[j] , j, total_length[j]-1);

            if (left_check_switch == true && right_check_switch == true && m_Stage_Object[current_pos]->GetAppearBool() == true)
            {
                cont_to_check = true ;
                if (total_length[i] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i], i, total_length[i]-1);

                if (total_length[j] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j], j, total_length[j]-1);

                return cont_to_check;
            }
        }
    }
    return cont_to_check;

}

int StageObject::DisappearMethodOfStripe( int current_pos, int* total_length, int priority ) {
    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        // do not make true if it was checked
        if ( (total_length[i] + total_length[j] ) == 3 ) {
            bool left_check = true ;
            bool right_check = true ;
    
            //check all side appear
            if (total_length[i] > 0)
                left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i], i, total_length[i]-1);
    
            if (total_length[j] > 0)
                right_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j] , j, total_length[j]-1);
    
            // check initial switch -> find switch side
            if (m_Stage_Object[current_pos]->GetSwitchedInfo() == 2 && priority == 2 && m_Stage_Object[current_pos]->GetAppearBool() == true  && left_check == true && right_check == true)
            {
                m_Stage_Object[current_pos]->SetAppearBool( false );
                //all disappear(except switched blocks)
                if (total_length[i] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i] , i, total_length[i]-1);
                if (total_length[j] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j] , j, total_length[j]-1);
    
                //find initial neighbor side
                for ( int switch_side = 0  ; switch_side < 6 ; ++switch_side )
                {
                    if (m_Stage_Object[current_pos]->GetInformationNeibor()[switch_side] != -1 && m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[switch_side] ]->GetSwitchedInfo() == 2 )
                    {
                        cout << "Stripe" << endl;
                        return switch_side;
                    }
                }
            }
            else if (m_Stage_Object[current_pos]->GetSwitchedInfo() == 1 && priority == 1 && m_Stage_Object[current_pos]->GetAppearBool() == true  && left_check == true && right_check == true)
            {
                //all disappear
                m_Stage_Object[current_pos]->SetAppearBool( false );
                if (total_length[i] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i], i, total_length[i]-1);
                if (total_length[j] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j], j, total_length[j]-1);
    
                cout << "Stripe" << endl;
                return 0;
            }
    
        }
    }
    return -1;
}

bool StageObject::DisappearMethodOfFlower( int current_pos, int* total_length ) {

    bool cont_to_check = false ; //two side 1 + another 2
    int check_side = -1;

    for ( int i = 0  ; i < 6 ; ++i ) //another 2
    {
        if ( total_length[i] >= 2 )
        {
            bool checkside_check = true ;
            checkside_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i], i, total_length[i]-1);

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
                left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i] , i, total_length[i]-1);

            if (total_length[j] > 0)
                right_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j] , j, total_length[j]-1);

            if ( total_length[i] >= 1 && total_length[j] >= 1  && m_Stage_Object[current_pos]->GetAppearBool() == true  && left_check == true && right_check == true && check_side != -1) {//two side 1
                cont_to_check = true ;
                m_Stage_Object[current_pos]->SetAppearBool( false );
                cout<<"Flower"<<endl;

                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[check_side] , check_side, total_length[check_side]-1);
                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i] , i, total_length[i]-1);
                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j] , j, total_length[j]-1);
                break;
            }


        }
    }

    return cont_to_check;
}

bool StageObject::DisappearMethodOfStarFlower(  int current_pos, int* total_length ) {
 
    bool cont_to_check = false ; //two side 2
    int check_sides = 0;


    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( total_length[i] >= 1 && total_length[j] >= 1)
        {
            bool left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i], i, total_length[i]-1);
            bool right_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j], j, total_length[j]-1);

            if (left_check == true && right_check == true )
                check_sides++ ;
        }
    }


    if (check_sides >= 2 && m_Stage_Object[current_pos]->GetAppearBool() == true)
    {
        for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j )
        {
            if (total_length[i] > 0)
                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i], i, total_length[i]-1);
            if (total_length[j] > 0)
                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j], j, total_length[j]-1);
        }
        m_Stage_Object[current_pos]->SetAppearBool( false );
        cout<<"Star Flower"<<endl;
        cont_to_check = true ;
    }

    return cont_to_check;
}

bool StageObject::DisappearMethodOfTriangleFlower( int current_pos , int* total_length ) {
    bool cont_to_check = false ; //two side >=2
    int check = 0;
    // two side >= 2
    for ( int i = 0  ; i < 6 ; ++i ) {
        if ( total_length[i] >= 2 ) {
            bool left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i], i, total_length[i]-1);

            if (left_check == true)
                check ++ ;
        }
    }

    if (check >= 2 && m_Stage_Object[current_pos]->GetAppearBool() == true)
    {
        m_Stage_Object[current_pos]->SetBlockType( TRIANGLEFLOWER_OBJECT );
        m_Stage_Object[current_pos]->SetAppearBool( false );
        cout<<"Triangle Flower"<<endl;
        cont_to_check = true ;
        for ( int i = 0  ; i < 6 ; ++i )
        {
            // cout<<i<<" side total length: "<<total_length[i]<<endl;
            if (total_length[i] > 0)
                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i], i, total_length[i]-1);
        }

    }

    return cont_to_check;
}

bool StageObject::DisappearMethodOfRainbowBall(  int current_pos, int* total_length, int priority ) {
    bool cont_to_check = false ;
    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( (total_length[i] + total_length[j] ) >= 4 ) {

            bool left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i], i, total_length[i]-1);
            bool right_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j], j, total_length[j]-1);

            if (m_Stage_Object[current_pos]->GetSwitchedInfo() == priority && m_Stage_Object[current_pos]->GetAppearBool() == true && left_check == true && right_check == true)
            {
                m_Stage_Object[current_pos]->SetAppearBool( false );
                cout<<"Rainbow Ball"<<endl;
                cont_to_check = true ;
                //all disappear(except switched blocks)
                if (total_length[i] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i], i, total_length[i]-1);
                if (total_length[j] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j], j, total_length[j]-1);
                return cont_to_check;
            }


        }
    }
    return cont_to_check;
}

void StageObject::DisappearBySingleObject( int current_pos, int side, int length_left) {
    m_Stage_Object[current_pos]->SetAppearBool( false );
    // cout<<"object disapp."<<endl;

    if( !m_Stage_Object[current_pos]  )
        return;

    if ( length_left  >  0 )
    {
        // cout<<"side: "<<side<<" length_left: "<<length_left<<endl;
        DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[side], side, length_left - 1) ;
    }
}

void StageObject::Dropping_method( const int current_position ) {
    if ( !m_Stage_Object[current_position] || m_Stage_Object[current_position]->GetInformationNeibor()[0] == -1  || !m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[0]])
        return;
    if ( current_position < m_Size+1 ) {
        const int next_position = m_Stage_Object[current_position]->GetInformationNeibor()[0];
        bool flag = m_Stage_Object[next_position]->GetAppearBool();

        m_Stage_Object[current_position]->SetSwitched(1);
        // cout<<"pos: "<<current_position<<"  "<<next_position<<endl;
        // cout<<"set SetSwitched to 1"<<endl;
        m_Stage_Object[next_position]->SetSwitched(1);
        m_Stage_Object[current_position]->SwitchPosition( m_Stage_Object[next_position] );

        std::shared_ptr<GameCharacter> NewObject = m_Stage_Object[current_position];
        m_Stage_Object[current_position] = m_Stage_Object[next_position];
        m_Stage_Object[next_position] = NewObject;
        m_Stage_Object[current_position]->SetAppearBool( flag );

        Dropping_method( next_position );
    }

    return;
}

bool StageObject::checkAppearanceOfObject ( int i, int side, int length_left) {
    bool return_bool = true;

    if( !m_Stage_Object[i]  )
        return false;

    if ( m_Stage_Object[i]->GetAppearBool() == true )
    {
        if( length_left >  0 )
        {
            return_bool = checkAppearanceOfObject (  m_Stage_Object[i]->GetInformationNeibor()[side] , side, length_left - 1);
            return return_bool;
        }
        else
        {
            return m_Stage_Object[i]->GetAppearBool();
        }
    }

    else{
        // cout<<"return_bool: false"<<endl;
        return false ;
    }
}

bool StageObject::checkSwitchedAllInfoWithZero ( int i, int side, int length_left) {
    if( !m_Stage_Object[i]  )
        return false;

    if ( m_Stage_Object[i]->GetSwitchedInfo() == 0 )
    {
        if( length_left >  0 )
            return checkSwitchedAllInfoWithZero ( m_Stage_Object[i]->GetInformationNeibor()[side], side, length_left - 1) ;
        else
            return true;
    }
    else
        return false ;
}

int StageObject::CheckNextAppearance( int i, int side, int length ) {
    if (!m_Stage_Object[i] || m_Stage_Object[i]->GetInformationNeibor()[side] == -1 || !m_Stage_Object[ m_Stage_Object[i]->GetInformationNeibor()[side] ] )
        return length;
    
    if ( IsSameColor(m_Stage_Object[i]->GetBlockType() ,  m_Stage_Object[ m_Stage_Object[i]->GetInformationNeibor()[side] ]->GetBlockType()) &&  m_Stage_Object[i]->GetInformationNeibor()[side] != -1 ){
        return CheckNextAppearance(  m_Stage_Object[i]->GetInformationNeibor()[side] , side, length + 1 ) ;
    }
    else
        return length ;
}

bool StageObject::IsSameColor(int blockType1, int blockType2) {
    return (blockType1 % 10) == (blockType2 % 10);
}

void StageObject::SetUp() {
    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if ( m_Stage_Object[i]->GetAppearBool() )
        m_Stage_Object[i]->Appear(); 
    }
    InitializeStageCharacter();
    CheckAppearance( 0 );
    // m_Stage_Object[37]->SetImage( ORANGE_STARFLOWER_OBJECT );
    // m_Stage_Object[37]->SetBlockType( NORMAL_OBJECT );
    // m_Stage_Object[37]->SetCurrentType( STARFLOWER_OBJECT);
    // m_Stage_Object[37]->SetBlock( ORANGE_OBJECT );
    // m_Stage_Object[37]->SetAppearBool( true );
    // m_Stage_Object[37]->SetGenerate( true );
}

void StageObject::CheckClickSwitch( int check , int i , std::shared_ptr<TaskText> point ) {
    for ( int j = 0 ; j < 6 ; ++j ) {
        if( m_Stage_Object[i]->GetInformationNeibor()[j] == check ) {
            m_Stage_Object[i]->SetSwitched(2);
            m_Stage_Object[check]->SetSwitched(2);
            std::cout<<"pos: "<<i<<"  "<<check<<std::endl;
            std::cout<<"set SetSwitched to 2"<<std::endl;
            m_Stage_Object[i]->SwitchPosition( m_Stage_Object[check] );
            std::shared_ptr<GameCharacter> NewObject = m_Stage_Object[check];
            m_Stage_Object[check] = m_Stage_Object[i];
            m_Stage_Object[i] = NewObject;
            if ( m_Stage_Object[check]->GetType() == RAINBOWBALL_OBJECT ) {
                m_Stage_Object[check]->SetBlock( m_Stage_Object[i]->GetBlockType() );
            }
            if ( m_Stage_Object[i]->GetType() == RAINBOWBALL_OBJECT ) {
                m_Stage_Object[i]->SetBlock( m_Stage_Object[check]->GetBlockType() );
            }
            if ( !CheckAppearance( 1 ) ) {
                m_Stage_Object[i]->SwitchPosition( m_Stage_Object[check] );
                std::shared_ptr<GameCharacter> NewObject = m_Stage_Object[check];
                m_Stage_Object[check] = m_Stage_Object[i];
                m_Stage_Object[i] = NewObject;
            }
            point->SetValue( stage_point_counter[1] );
            point->UpdateText();
            // std::cout << "Point: " << stage_point_counter[1] << std::endl;
            break;
        }
    }
}