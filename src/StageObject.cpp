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
#include <chrono>
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

void StageObject::InitializeStageCharacter( int s ) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(1, 7);
    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if ( m_Stage !=  0 ) {
            if ( m_Stage_Object[i] -> GetType() != NORMAL_OBJECT ) {
                continue;
            }
        }
        RandomChangeObject( i );
        if ( s == 1 ) {
            m_Stage_Object[i]->SetInformation( stage1[i] );
            m_Stage_Object[i]->SetPosition( stage1_position[i] );
            m_Stage_Object[i]->SetZIndex(10);
            m_Stage_Object[i]->SetSize( {20, 25} );
            m_Stage_Object[i]->DisAppear();
            m_Stage_Object[i]->SetAppearBool( true );
            m_Stage_Object[i]->SetBlockType( NORMAL_OBJECT );
            m_Stage_Object[i]->SetCurrentType( NORMAL_OBJECT );
        } 
        else if ( s == 2 ) {
            m_Stage_Object[i]->SetInformation( stage2[i] );
            m_Stage_Object[i]->SetPosition( stage2_position[i] );
            m_Stage_Object[i]->SetZIndex(10);
            m_Stage_Object[i]->SetSize( {20, 25} );
            m_Stage_Object[i]->DisAppear();
            m_Stage_Object[i]->SetAppearBool( true );
            m_Stage_Object[i]->SetBlockType( NORMAL_OBJECT );
            m_Stage_Object[i]->SetCurrentType( NORMAL_OBJECT );
        }
        else if ( s == 3 ) {
            m_Stage_Object[i]->SetInformation( stage3[i] );
            m_Stage_Object[i]->SetPosition( stage3_position[i] );
            m_Stage_Object[i]->SetZIndex(10);
            m_Stage_Object[i]->SetSize( {20, 25} );
            m_Stage_Object[i]->DisAppear();
            m_Stage_Object[i]->SetAppearBool( true );
            m_Stage_Object[i]->SetBlockType( NORMAL_OBJECT );
            m_Stage_Object[i]->SetCurrentType( NORMAL_OBJECT );
        }
    }
}

bool StageObject::CheckAppearance( int s ) {
    if ( s != 0 && currentPhase != PHASE_NORMAL ) {
        return false;
    }
    bool cont_to_check = false;
    bool flag = false;
    int stripe_side;

    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if( !m_Stage_Object[i] ) continue;
        m_Stage_Object[i]->SetAppearBool( true );
    }

    std::vector<std::vector<int>> total_length(m_Size + 1, std::vector<int>(6, 0));
    for ( int i = 1 ; i < m_Size+1 ; ++i )
    {
        // cout<<"no. "<<i<<" type: "<<m_Stage_Object[i]->GetCurrentType()<<" had switch:"<<m_Stage_Object[i]->GetSwitchedInfo()<<endl;
        if( !m_Stage_Object[i] )
            continue;
        int *neighbors = m_Stage_Object[i]->GetInformationNeibor();//GET NEIGHBOR
        m_Stage_Object[i]->GetBlockType() ;

        // hand switch rainbowBall + FLOWER_COMBINED + FLOWER_STRIPE + STRIPE_COMBINED
        if ( (m_Stage_Object[i]->GetCurrentType() == RAINBOWBALL_OBJECT  ) && m_Stage_Object[i]->GetSwitchedInfo() == MOVE_BY_SWITCH ) {
            m_Stage_Object[i]->SetAppearBool( false );
            MakeDisappear();
            for ( int j = 1 ; j < m_Size+1 ; ++j ) {
                m_Stage_Object[j]->SetSwitched( NO_MOVE );
            }
            // Dropping();
            return true;
        }
        if ( ( m_Stage_Object[i]->GetCurrentType() == FLOWER_COMBINED_OBJECT ||  m_Stage_Object[i]->GetCurrentType() == FLOWER_STRIPE_OBJECT || m_Stage_Object[i]->GetCurrentType() == STRIPE_COMBINED_OBJECT) && m_Stage_Object[i]->GetSwitchedInfo() == MOVE_BY_SWITCH ) {
            m_Stage_Object[i]->SetAppearBool( false );
            // MakeDisappear();
            // cout<<"I'm in"<<endl;
            // Dropping();
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
            cout << "Rainbow information for generating\n";
            cout << m_Stage_Object[i]->GetCurrentType() << endl;
            cout << m_Stage_Object[i]->GetType() << endl;
            cout << m_Stage_Object[i]->GetBlockType() << endl;
            cout << m_Stage_Object[i]->GetGenerate() << endl;
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
        m_Stage_Object[i]->SetSwitched( NO_MOVE );
    }

    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if( !m_Stage_Object[i] ) continue;
        if( !m_Stage_Object[i]->GetAppearBool() ) 
            flag = true;
    }

    CheckObstaclesDisappear();

    if ( flag ) {
        // DebugModeOfAppearance( m_Stage_Object , size);
        MakeDisappear();
        if ( s == 0 )
            Dropping();
    }

    //check need shuffle or not
    else
    {
        for ( int i = 1 ; i < m_Size+1 ; ++i )
            m_Stage_Object[i]->SetSwitched(0);

        std::pair<int, int> result = CheckShuffleDemands();
        if (result.first == -1 && result.second == -1) {
            InitializeStageCharacter(m_Stage);
        } else {
            std::cout << "Swap between " << result.first << " and " << result.second << std::endl;
        }
    }                                                                                                                                                
    return flag;
}

void StageObject::CheckSpecialObject( int i ){
    switch ( m_Stage_Object[i]->GetBlockType() )
    {
        case ONE_LAYER_COOKIE_OBJECT:

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
    if ( m_Stage != 0 && currentPhase != PHASE_NORMAL )
        return;
    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        // m_Stage_Object[i]->SetSwitched(0);
        if ( m_Stage_Object[i]->GetVisibility() == false ) {
            continue;
        }

        if ( !m_Stage_Object[i]->GetAppearBool() && ( m_Stage_Object[i]->GetCurrentType() == NORMAL_OBJECT || m_Stage_Object[i]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT || m_Stage_Object[i]->GetGenerate() ) ) {
            MakeDisappearWithObject( i );
            m_Stage_Object[i]->SetGenerate( false );
        }
    }

    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if ((m_Stage_Object[i]->GetType() == NORMAL_OBJECT || m_Stage_Object[i]->GetType() == ONE_LAYER_COOKIE_OBJECT || m_Stage_Object[i]->GetType() == TWO_LAYER_COOKIE_OBJECT ) && !m_Stage_Object[i]->GetAppearBool()) {
            // PointUpdate( GetPoint() + 1 );
            m_Stage_Object[i]->SetCurrentType( m_Stage_Object[i]->GetType() ); //current == now, blockType = next(finished)
            m_Stage_Object[i]->SetBlockType( NORMAL_OBJECT );
                
        }
        else if ( m_Stage_Object[i]->GetType() != NORMAL_OBJECT && !m_Stage_Object[i]->GetAppearBool() ) {
            PointUpdate( GetPoint() + 1 );
            GoalUpdate( i );
            m_Stage_Object[i]->SetAppearBool(true);
            CheckSpecialObject( i );
            m_Stage_Object[i]->SetGenerate( true );
            m_Stage_Object[i]->SetCurrentType( m_Stage_Object[i]->GetType() ); //current == now, blockType = next(finished)
            m_Stage_Object[i]->SetBlockType( NORMAL_OBJECT );
        }
    }

    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if ( !m_Stage_Object[i]->GetAppearBool() ) {
            PointUpdate( GetPoint() + 1 );
            GoalUpdate( i );
        }
    }
    cout<<"score: "<< GetPoint() <<endl;

    currentPhase = PHASE_PAUSE_FOR_DISAPPEAR;
    startTime = std::chrono::steady_clock::now();
}

void StageObject::Dropping() {
    if ( m_Stage != 0 && currentPhase != PHASE_DROPPING ) {
        return;
    }
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
        if ( !m_Stage_Object[i]->GetAppearBool() && m_Stage_Object[i]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT ) {
            m_Stage_Object[i]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/cookie1.png" );
            m_Stage_Object[i]->SetBlock( ONE_LAYER_COOKIE_OBJECT );
            m_Stage_Object[i]->SetBlockType( NORMAL_OBJECT );
        }
        else if ( !m_Stage_Object[i]->GetAppearBool() ) {
            RandomChangeObject( i );
            m_Stage_Object[i]->SetBlockType( NORMAL_OBJECT );
        }
        m_Stage_Object[i]->SetAppearBool( true );
    }
    if ( m_Stage != 0 )
        AppearAll();
    currentPhase = PHASE_NORMAL;
    CheckAppearance( m_Stage );
}

void StageObject::MakeObstaclesDisappear(int position) {

    //Add here if more obstacles
    switch ( m_Stage_Object[position]->GetCurrentType() ) {
        case ONE_LAYER_COOKIE_OBJECT:
            m_Stage_Object[position]->SetAppearBool(false);
        break;
        case TWO_LAYER_COOKIE_OBJECT:
            m_Stage_Object[position]->SetAppearBool(false);
        break;
    }
}

void StageObject::CheckObstaclesDisappear() {

    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if(m_Stage_Object[i]->GetCurrentType() >= ONE_LAYER_COOKIE_OBJECT && m_Stage_Object[i]->GetCurrentType() <= 50) {

            //check if neighbor disap.
            for ( int j = 0 ; j < 6 ; ++j ) {
                if (m_Stage_Object[i]->GetInformationNeibor()[j] != -1 && !m_Stage_Object[m_Stage_Object[i]->GetInformationNeibor()[j]]->GetAppearBool() ) {
                    MakeObstaclesDisappear(i);
                    break;
                }
            }
        }
    }
}


void StageObject::PointUpdate(int point ) {
    stage_point_counter[m_Stage] = point;
}

void StageObject::GoalUpdate( int i ) {
    switch ( m_Stage ) {
        case 1:
            if ( m_Stage_Object[i]->GetBlockType() == BROWN_OBJECT ) {
                stage_goal_counter[1]--;
            }
            break;
        case 2:
            if ( m_Stage_Object[i]->GetBlockType() == BROWN_OBJECT ) {
                stage_goal_counter[2]--;
            }
            break;
        case 3:
            if ( m_Stage_Object[i]->GetBlockType() == BROWN_OBJECT ) {
                stage_goal_counter[3]--;
            }
            break;
        default:
            break;
    }
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
        case FLOWER_COMBINED_OBJECT:
            MakeDisappearWithFlowerCombined( current_pos );
        break;
        case FLOWER_STRIPE_OBJECT:
            MakeDisappearWithStripeFlower( current_pos );
        break;
        case STRIPE_COMBINED_OBJECT:
            MakeDisappearWithStripeCombined( current_pos );
        break;
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
        case ONE_LAYER_COOKIE_OBJECT:
            m_Stage_Object[current_pos]->DisAppear();
            m_Stage_Object[current_pos]->SetAppearBool( false );
            m_Stage_Object[current_pos]->SetCurrentType( NORMAL_OBJECT );
            break;
        case TWO_LAYER_COOKIE_OBJECT:
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
void StageObject::MakeDisappearWithFlowerCombined( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );

    cout << "FLOWER_COMBINED\n";

    for ( int i = 0 ; i < 6 ; ++i )
    {
        if (m_Stage_Object[current_pos]->GetInformationNeibor()[i] != -1)
        {
            MakeDisappearWithObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]  );

            for ( int j = 0 ; j < 6 ; ++j ) {
                if (m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[i] ] ->GetInformationNeibor()[j] != -1)
                {
                    MakeDisappearWithObject( m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[i] ] ->GetInformationNeibor()[j]  );

                }
            }
        }
    }
}

void StageObject::MakeDisappearWithStripeFlower( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    cout << "STRIPE_FLOWER\n";

    // m_Stage_Object[current_pos]->GetCurrentType();
    int extend_side[2] = {-1} ;
    int side = -1 ;
    if (m_Stage_Object[current_pos]->GetType() == STRIPE_OBJECT )
    {
        if (m_Stage_Object[current_pos]->GetInformationNeibor()[1] != -1)
            extend_side[0] = 1 ;
        else if (m_Stage_Object[current_pos]->GetInformationNeibor()[2] != -1)
            extend_side[0] = 2 ;

        if (m_Stage_Object[current_pos]->GetInformationNeibor()[4] != -1)
            extend_side[1] = 4 ;
        else if (m_Stage_Object[current_pos]->GetInformationNeibor()[5] != -1)
            extend_side[1] = 5 ;

        side = 0 ;

    }
    else if (m_Stage_Object[current_pos]->GetType() == STRIPE_LEFT_RIGHT_OBJECT )
    {
        if (m_Stage_Object[current_pos]->GetInformationNeibor()[0] != -1)
            extend_side[0] = 0 ;
        else if (m_Stage_Object[current_pos]->GetInformationNeibor()[1] != -1)
            extend_side[0] = 1 ;

        if (m_Stage_Object[current_pos]->GetInformationNeibor()[3] != -1)
            extend_side[1] = 3 ;
        else if (m_Stage_Object[current_pos]->GetInformationNeibor()[4] != -1)
            extend_side[1] = 4 ;

        side = 2 ;
    }
    else if (m_Stage_Object[current_pos]->GetType() == STRIPE_RIGHT_LEFT_OBJECT )
    {
        if (m_Stage_Object[current_pos]->GetInformationNeibor()[0] != -1)
            extend_side[0] = 0 ;
        else if (m_Stage_Object[current_pos]->GetInformationNeibor()[2] != -1)
            extend_side[0] = 2 ;

        if (m_Stage_Object[current_pos]->GetInformationNeibor()[3] != -1)
            extend_side[1] = 3 ;
        else if (m_Stage_Object[current_pos]->GetInformationNeibor()[5] != -1)
            extend_side[1] = 5 ;

        side = 1 ;
    }
    m_Stage_Object[current_pos]->SetBlockType(NORMAL_OBJECT);
    // cout<<"extend_side: "<<extend_side[0]<<"   "<<extend_side[1]<<endl;

    for ( int i = current_pos , j = current_pos ; ; ) {
        if ( m_Stage_Object[i]->GetInformationNeibor()[side] != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[side] );
            i = m_Stage_Object[i]->GetInformationNeibor()[side];
        }
        if ( m_Stage_Object[j]->GetInformationNeibor()[side+3] != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[side+3] );
            j = m_Stage_Object[j]->GetInformationNeibor()[side+3];
        }
        if ( m_Stage_Object[i]->GetInformationNeibor()[side] == -1 && m_Stage_Object[j]->GetInformationNeibor()[side+3] == -1 )
            break;
    }

    if (extend_side[0] != -1) {
        m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[extend_side[0]] ]->DisAppear();
        m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[extend_side[0]] ]->SetAppearBool( false );

        for ( int i = m_Stage_Object[current_pos]->GetInformationNeibor()[extend_side[0]] , j = m_Stage_Object[current_pos]->GetInformationNeibor()[extend_side[0]] ; ; ) {
            if ( m_Stage_Object[i]->GetInformationNeibor()[side] != -1 ) {
                MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[side] );
                i = m_Stage_Object[i]->GetInformationNeibor()[side];
            }
            if ( m_Stage_Object[j]->GetInformationNeibor()[side + 3] != -1 ) {
                MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[side + 3] );
                j = m_Stage_Object[j]->GetInformationNeibor()[side + 3];
            }
            if ( m_Stage_Object[i]->GetInformationNeibor()[side] == -1 && m_Stage_Object[j]->GetInformationNeibor()[side + 3] == -1 )
                break;
        }
    }

    if (extend_side[1] != -1) {
        m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[extend_side[1]] ]->DisAppear();
        m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[extend_side[1]] ]->SetAppearBool( false );

        for ( int i = m_Stage_Object[current_pos]->GetInformationNeibor()[extend_side[1]] , j = m_Stage_Object[current_pos]->GetInformationNeibor()[extend_side[1]] ; ; ) {
            if ( m_Stage_Object[i]->GetInformationNeibor()[side] != -1 ) {
                MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[side] );
                i = m_Stage_Object[i]->GetInformationNeibor()[side];
            }
            if ( m_Stage_Object[j]->GetInformationNeibor()[side + 3] != -1 ) {
                MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[side + 3] );
                j = m_Stage_Object[j]->GetInformationNeibor()[side + 3];
            }
            if ( m_Stage_Object[i]->GetInformationNeibor()[side] == -1 && m_Stage_Object[j]->GetInformationNeibor()[side + 3] == -1 )
                break;
        }
    }


}

void StageObject::MakeDisappearWithStripeCombined( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    cout << "STRIPE_COMBINED"<<endl;

    int side = -1 ;
    if (m_Stage_Object[current_pos]->GetType() == STRIPE_OBJECT )
    {
        side = 0 ;

    }
    else if (m_Stage_Object[current_pos]->GetType() == STRIPE_LEFT_RIGHT_OBJECT )
    {
        side = 2 ;
    }
    else if (m_Stage_Object[current_pos]->GetType() == STRIPE_RIGHT_LEFT_OBJECT )
    {
        side = 1 ;
    }
    m_Stage_Object[current_pos]->SetBlockType(NORMAL_OBJECT);

    for ( int i = current_pos , j = current_pos ; ; ) {
        if ( m_Stage_Object[i]->GetInformationNeibor()[side] != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[side] );
            i = m_Stage_Object[i]->GetInformationNeibor()[side];
        }
        if ( m_Stage_Object[j]->GetInformationNeibor()[side+3] != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[side+3] );
            j = m_Stage_Object[j]->GetInformationNeibor()[side+3];
        }
        if ( m_Stage_Object[i]->GetInformationNeibor()[side] == -1 && m_Stage_Object[j]->GetInformationNeibor()[side+3] == -1 )
            break;
    }


}

void StageObject::MakeDisappearWithStripeInLeftRight( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    cout << "STRIPE_LEFT_RIGHT\n";
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
    cout << "STRIPE_RIGHT_LEFT\n";
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

void StageObject::MakeDisappearWithRainbow( int current_pos ) { //get type: next move
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );

    if ( m_Stage_Object[current_pos]->GetBlockType() == 0 ) { // no color
        m_Stage_Object[current_pos]->SetBlock( BLUE_OBJECT );
    }

    cout << "RAINBOW BALL\n";

    if (m_Stage_Object[current_pos]->GetType() == RAINBOWBALL_OBJECT) {
        for ( int i = 1 ; i < m_Size+1 ; ++i ) {
                MakeDisappearWithObject( i );
        }
        return ;
    }

    if (m_Stage_Object[current_pos]->GetType() != 0) {
        // change same color to special type
        for ( int i = 1 ; i < m_Size+1 ; ++i ) {
            if ( i != current_pos && m_Stage_Object[current_pos]->GetBlockType() == m_Stage_Object[i]->GetBlockType() ) {
                //random

                if (m_Stage_Object[current_pos]->GetType() >=2 && m_Stage_Object[current_pos]->GetType() <=4) {
                    std::random_device rd;  // 硬體隨機數產生器
                    std::mt19937 gen(rd()); // Mersenne Twister 亂數引擎
                    std::uniform_int_distribution<int> dist(2, 4); // 產生 2 到 4 之間的整數

                    int random_number = dist(gen);

                    m_Stage_Object[i]->SetCurrentType( random_number );
                }
                    m_Stage_Object[i]->SetCurrentType( m_Stage_Object[current_pos]->GetType() );
            }
        }
    }

    m_Stage_Object[current_pos]->SetBlockType(NORMAL_OBJECT);

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

                    if ( m_Stage_Object[current_pos]->GetInformationNeibor()[switch_side] != -1) {
                        if (m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[switch_side] ]->GetSwitchedInfo() == 2 )
                        {
                            cout << "Stripe" << endl;
                            return switch_side;
                        }
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
            if (total_length[i] > 0)
                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i], i, total_length[i]-1);
        }

    }

    return cont_to_check;
}

bool StageObject::DisappearMethodOfRainbowBall(  int current_pos, int* total_length, int priority ) {
    bool cont_to_check = false ;
    bool left_check;
    bool right_check;
    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( (total_length[i] + total_length[j] ) >= 4 ) {

            if ( total_length[i] > 0 )
                left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i], i, total_length[i]-1);
            if ( total_length[j] > 0 )
                right_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j], j, total_length[j]-1);

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

    if( !m_Stage_Object[current_pos]  )
        return;

    if ( length_left  >  0 )
    {
        DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[side], side, length_left - 1) ;
    }
}

void StageObject::Dropping_method( const int current_position ) {
    if ( !m_Stage_Object[current_position] || m_Stage_Object[current_position]->GetInformationNeibor()[0] == -1  || !m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[0]])
        return;
    if ( current_position < m_Size+1 ) {
        int next_position; 
        if ( m_Stage_Object[current_position]->GetInformationNeibor()[0] != -1 && ( m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[0]]->GetCurrentType() != ONE_LAYER_COOKIE_OBJECT && m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[0]]->GetCurrentType() != TWO_LAYER_COOKIE_OBJECT ) )
            next_position = m_Stage_Object[current_position]->GetInformationNeibor()[0];
        else if ( m_Stage_Object[current_position]->GetInformationNeibor()[5] != -1 && ( m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[5]]->GetCurrentType() != ONE_LAYER_COOKIE_OBJECT && m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[5]]->GetCurrentType() != TWO_LAYER_COOKIE_OBJECT ) )
            next_position = m_Stage_Object[current_position]->GetInformationNeibor()[5];
        else if ( m_Stage_Object[current_position]->GetInformationNeibor()[1] != -1 && ( m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[1]]->GetCurrentType() != ONE_LAYER_COOKIE_OBJECT && m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[1]]->GetCurrentType() != TWO_LAYER_COOKIE_OBJECT ) )
            next_position = m_Stage_Object[current_position]->GetInformationNeibor()[1];
        else
            return;
        bool flag = m_Stage_Object[next_position]->GetAppearBool();

        m_Stage_Object[current_position]->SetSwitched(1);
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

void StageObject::SetUp( int stage ) {
    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if ( m_Stage_Object[i]->GetAppearBool() )
            m_Stage_Object[i]->Appear();
    }
    InitializeStageCharacter( stage );
    CheckAppearance( 0 );
    // m_Stage_Object[37]->SetImage( RAINBOWBALL_OBJECT_LINK );
    // m_Stage_Object[37]->SetBlockType( NORMAL_OBJECT );
    // m_Stage_Object[37]->SetCurrentType( RAINBOWBALL_OBJECT);
    // m_Stage_Object[37]->SetBlock( 0 );
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

            if ( m_Stage_Object[check]->GetCurrentType() == RAINBOWBALL_OBJECT ) {
                m_Stage_Object[check]->SetBlock( m_Stage_Object[i]->GetBlockType() );
                m_Stage_Object[check]->SetBlockType( m_Stage_Object[i]->GetCurrentType() );
                cout<<"find rainbow ball"<<endl;
            }
            if ( m_Stage_Object[i]->GetCurrentType() == RAINBOWBALL_OBJECT ) {
                m_Stage_Object[i]->SetBlock( m_Stage_Object[check]->GetBlockType() ); //color
                m_Stage_Object[i]->SetBlockType( m_Stage_Object[check]->GetCurrentType() );
                cout<<"find rainbow ball"<<endl;
            }

            // flower + flower
            if ( m_Stage_Object[check]->GetCurrentType() >= FLOWER_OBJECT && m_Stage_Object[check]->GetCurrentType() <= TRIANGLEFLOWER_OBJECT && m_Stage_Object[i]->GetCurrentType() >= FLOWER_OBJECT && m_Stage_Object[i]->GetCurrentType() <= TRIANGLEFLOWER_OBJECT ) {
                m_Stage_Object[i]->SetCurrentType( FLOWER_COMBINED_OBJECT );
                m_Stage_Object[check]->SetCurrentType( FLOWER_COMBINED_OBJECT );
                cout<<"find flower combined"<<endl;
            }

            //to be opt.
            // flower + stripe 1
            if ( m_Stage_Object[check]->GetCurrentType() >= STRIPE_OBJECT && m_Stage_Object[check]->GetCurrentType() <= STRIPE_RIGHT_LEFT_OBJECT &&  m_Stage_Object[i]->GetCurrentType() >= FLOWER_OBJECT && m_Stage_Object[i]->GetCurrentType() <= TRIANGLEFLOWER_OBJECT  ) {
                m_Stage_Object[i]->SetBlockType( NORMAL_OBJECT);
                m_Stage_Object[check]->SetBlockType( m_Stage_Object[check]->GetCurrentType());
                m_Stage_Object[check]->SetCurrentType( FLOWER_STRIPE_OBJECT );
                m_Stage_Object[i]->SetCurrentType( NORMAL_OBJECT );
                cout<<"find flower stripe"<<endl;
            }

            //to be opt.
            // flower + stripe 2
            if ( m_Stage_Object[check]->GetCurrentType() >= FLOWER_OBJECT && m_Stage_Object[check]->GetCurrentType() <= TRIANGLEFLOWER_OBJECT &&  m_Stage_Object[i]->GetCurrentType() >= STRIPE_OBJECT && m_Stage_Object[i]->GetCurrentType() <= STRIPE_RIGHT_LEFT_OBJECT   ) {
                m_Stage_Object[i]->SetBlockType( m_Stage_Object[i]->GetCurrentType());
                m_Stage_Object[check]->SetBlockType( NORMAL_OBJECT);
                m_Stage_Object[i]->SetCurrentType( FLOWER_STRIPE_OBJECT );
                m_Stage_Object[check]->SetCurrentType( NORMAL_OBJECT );
                cout<<"find flower stripe"<<endl;
            }

            //to be opt.
            // stripe + stripe
            if ( m_Stage_Object[check]->GetCurrentType() >= STRIPE_OBJECT && m_Stage_Object[check]->GetCurrentType() <= STRIPE_RIGHT_LEFT_OBJECT &&  m_Stage_Object[i]->GetCurrentType() >= STRIPE_OBJECT && m_Stage_Object[i]->GetCurrentType() <= STRIPE_RIGHT_LEFT_OBJECT   ) {
                m_Stage_Object[i]->SetBlockType( m_Stage_Object[i]->GetCurrentType());
                m_Stage_Object[check]->SetBlockType( m_Stage_Object[check]->GetCurrentType());
                m_Stage_Object[check]->SetCurrentType( STRIPE_COMBINED_OBJECT );
                m_Stage_Object[i]->SetCurrentType( STRIPE_COMBINED_OBJECT );
                cout<<"find stripe combined"<<endl;
            }

            //can't disappear
            if ( !CheckAppearance( 1 ) ) {
                m_Stage_Object[i]->SwitchPosition( m_Stage_Object[check] );
                std::shared_ptr<GameCharacter> NewObject = m_Stage_Object[check];
                m_Stage_Object[check] = m_Stage_Object[i];
                m_Stage_Object[i] = NewObject;
            } 
            else {
                point->SetMove( point->GetMove() - 1 );
            }
            point->SetPoint( stage_point_counter[m_Stage] );
            point->UpdateText();
            // std::cout<<"moves left: "<<GetMovesLeft()<<std::endl;
            break;
        }
    }
}

std::pair<int, int> StageObject::CheckShuffleDemands() {

    for ( int i = 1 ; i < m_Size +1 ; ++i) {
        //center
        for ( int j = 0 ; j < 6 ; ++j) {
            //switched side
            const int neighbor_no = m_Stage_Object[i]->GetInformationNeibor()[j];

            if (neighbor_no != -1) {
                m_Stage_Object[i]->SwitchPosition(  m_Stage_Object[neighbor_no] );
                std::shared_ptr<GameCharacter> NewObject = m_Stage_Object[neighbor_no];
                m_Stage_Object[neighbor_no] = m_Stage_Object[i];
                m_Stage_Object[i] = NewObject;

                std::pair<int, int> result = CheckRainbowUsing();
                if (result.first != -1 || result.second != -1)
                {
                    m_Stage_Object[i]->SwitchPosition(  m_Stage_Object[neighbor_no] );
                    NewObject = m_Stage_Object[neighbor_no];
                    m_Stage_Object[neighbor_no] = m_Stage_Object[i];
                    m_Stage_Object[i] = NewObject;

                    return {result.first, result.second};
                }


                m_Stage_Object[i]->SwitchPosition(  m_Stage_Object[neighbor_no] );
                NewObject = m_Stage_Object[neighbor_no];
                m_Stage_Object[neighbor_no] = m_Stage_Object[i];
                m_Stage_Object[i] = NewObject;
            }
        }
    }

    for ( int i = 1 ; i < m_Size +1 ; ++i) {
        //center
        for ( int j = 0 ; j < 6 ; ++j) {
            //switched side

            const int neighbor_no = m_Stage_Object[i]->GetInformationNeibor()[j];

            if (neighbor_no != -1) {
                m_Stage_Object[i]->SwitchPosition(  m_Stage_Object[neighbor_no] );
                std::shared_ptr<GameCharacter> NewObject = m_Stage_Object[neighbor_no];
                m_Stage_Object[neighbor_no] = m_Stage_Object[i];
                m_Stage_Object[i] = NewObject;

                std::pair<int, int> result = CheckSpecialBlocksNeighbor();
                if (result.first != -1 || result.second != -1)
                {
                    m_Stage_Object[i]->SwitchPosition(  m_Stage_Object[neighbor_no] );
                    NewObject = m_Stage_Object[neighbor_no];
                    m_Stage_Object[neighbor_no] = m_Stage_Object[i];
                    m_Stage_Object[i] = NewObject;

                    return {result.first, result.second};
                }

                m_Stage_Object[i]->SwitchPosition(  m_Stage_Object[neighbor_no] );
                NewObject = m_Stage_Object[neighbor_no];
                m_Stage_Object[neighbor_no] = m_Stage_Object[i];
                m_Stage_Object[i] = NewObject;
            }
        }
    }
    for ( int i = 1 ; i < m_Size +1 ; ++i) {
        //center
        for ( int j = 0 ; j < 6 ; ++j) {
            //switched side

            const int neighbor_no = m_Stage_Object[i]->GetInformationNeibor()[j];

            if (neighbor_no != -1) {
                m_Stage_Object[i]->SwitchPosition(  m_Stage_Object[neighbor_no] );
                std::shared_ptr<GameCharacter> NewObject = m_Stage_Object[neighbor_no];
                m_Stage_Object[neighbor_no] = m_Stage_Object[i];
                m_Stage_Object[i] = NewObject;

                if (CheckLineMaking())
                {
                    m_Stage_Object[i]->SwitchPosition(  m_Stage_Object[neighbor_no] );
                    NewObject = m_Stage_Object[neighbor_no];
                    m_Stage_Object[neighbor_no] = m_Stage_Object[i];
                    m_Stage_Object[i] = NewObject;

                    return {i, neighbor_no};

                }
                m_Stage_Object[i]->SwitchPosition(  m_Stage_Object[neighbor_no] );
                NewObject = m_Stage_Object[neighbor_no];
                m_Stage_Object[neighbor_no] = m_Stage_Object[i];
                m_Stage_Object[i] = NewObject;
            }
        }
    }
    return {-1, -1};
}

bool StageObject::CheckLineMaking() {

    for ( int current_pos = 1 ; current_pos < m_Size +1 ; ++current_pos) {//center
        for ( int check_side = 0 ; check_side < 3 ; ++check_side) {
            //check_side

            int length = 1 ;

            if (m_Stage_Object[current_pos]->GetInformationNeibor()[check_side] != -1 ){

                if ( IsSameColor(m_Stage_Object[current_pos]->GetBlockType() ,  m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[check_side] ]->GetBlockType())){
                    length += CheckNextAppearance(  m_Stage_Object[current_pos]->GetInformationNeibor()[check_side] , check_side, 1 ) ;
                }
            }

            if (m_Stage_Object[current_pos]->GetInformationNeibor()[check_side+3] != -1 ){

                if ( IsSameColor(m_Stage_Object[current_pos]->GetBlockType() ,  m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[check_side+3] ]->GetBlockType())){
                    length += CheckNextAppearance(  m_Stage_Object[current_pos]->GetInformationNeibor()[check_side+3] , check_side+3, 1 ) ;
                }
            }

            if (length >= 3)
                return true;

        }
    }

    return false;
}

std::pair<int, int> StageObject::CheckRainbowUsing() {
    for ( int current_pos = 1 ; current_pos < m_Size +1 ; ++current_pos) {
        //check if has neighbor
        if (m_Stage_Object[current_pos]->GetCurrentType() == RAINBOWBALL_OBJECT) {

            for ( int j = 0 ; j < 6 ; ++j) {
                if (m_Stage_Object[current_pos]->GetInformationNeibor()[j] != -1)
                    return {current_pos, m_Stage_Object[current_pos]->GetInformationNeibor()[j]};
            }
        }
    }
    return {-1, -1};

}

std::pair<int, int> StageObject::CheckSpecialBlocksNeighbor() {
    for ( int current_pos = 1 ; current_pos < m_Size +1 ; ++current_pos) {

        if (m_Stage_Object[current_pos]->GetCurrentType() >= STRIPE_OBJECT && m_Stage_Object[current_pos]->GetCurrentType() <= TRIANGLEFLOWER_OBJECT) {
            //check if neighbor is special block
            for ( int j = 0 ; j < 6 ; ++j) {
                if (m_Stage_Object[current_pos]->GetInformationNeibor()[j] != -1) {

                    if ( m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[j] ]->GetCurrentType() >= STRIPE_OBJECT && m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[j] ]->GetCurrentType() <= TRIANGLEFLOWER_OBJECT) {
                        return {current_pos, m_Stage_Object[current_pos]->GetInformationNeibor()[j]};
                    }
                }

            }
        }
    }
    return {-1, -1};

}

