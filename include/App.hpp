#ifndef APP_HPP
#define APP_HPP
#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"
#include "Util/Text.hpp"
#include "PhaseResourceManager.hpp"
#include "Character.hpp"
#include "GameCharacter.hpp"
#include "ObjectInformation.hpp"
#include "TaskText.hpp"
#include "StageObject.hpp"
#include "JumpPage.hpp"
#include "Music.hpp"

// #include "AnimatedCharacter.hpp"

// Declare of Phase Main Action
bool PhaseInitialImage(std::shared_ptr<Character> &chara_obj);
int  PhaseHomePage( std::shared_ptr<Character>* buttoms );
bool PhaseStage(std::shared_ptr<StageObject> StageObject, const int size, std::shared_ptr<TaskText> point, const int stage);
// bool PhaseStage2( std::shared_ptr<StageObject> StageObject , const int size , std::shared_ptr<TaskText> point);
void DebugPhaseStage1( std::shared_ptr<GameCharacter>* objectArray );

// Declare of Debug Mode
void DebugModeOfPosition( std::shared_ptr<GameCharacter>* objectArray , int option);
void DebugModeCancel( std::shared_ptr<GameCharacter>* objectArray , int option);
void DebugModeOfAppearance( std::shared_ptr<GameCharacter>* objectArray , int size );
void DebugModeShowMapObject(std::shared_ptr<GameCharacter>* objectArray , int size );


class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }
    
    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

    void SetUpStage( int stage ) {
        m_BGM_Music[0]->Playing( GA_RESOURCE_DIR"/Music/rickRoll.mp3");
        if ( stage == 1 ) {
            m_Stage_Object_GameCharacter[0] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/click.png" );
            m_Stage_Object_GameCharacter[0]->SetVisible( false );
            m_Stage_Object_GameCharacter[0]->SetZIndex( 9 );
            m_Root.AddChild( m_Stage_Object_GameCharacter[0] );
            for ( int i = 1 ; i < 38 ; ++i ) { 
                m_Stage_Object_GameCharacter[i] = std::make_shared<GameCharacter>( BLUE_NORMAL_OBJECT );
                m_Stage_Object_GameCharacter[i]->SetVisible( false );
                m_Stage_Object_GameCharacter[i]->SetZIndex( 10 );
                m_Root.AddChild( m_Stage_Object_GameCharacter[i] );
            }
            m_Stage_Object[1] = std::make_shared<StageObject>( 37 , m_Stage_Object_GameCharacter );
            m_Stage_Object[1]->SetStage( 0 );
            m_Root.AddChild( m_Stage_Object[1] );
            m_Stage_Goal_Object_Show = std::make_shared<GameCharacter>( BROWN_NORMAL_OBJECT );
            m_Stage_Goal_Object_Show->SetPosition( stage_goal_position[1] );
            m_Stage_Goal_Object_Show->SetVisible( true );
            m_Root.AddChild( m_Stage_Goal_Object_Show );
        }
        else if ( stage == 2 ) {
            m_Stage_Object_GameCharacter[0] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/click.png" );
            m_Stage_Object_GameCharacter[0]->SetVisible( false );
            m_Stage_Object_GameCharacter[0]->SetZIndex( 9 );
            m_Root.AddChild( m_Stage_Object_GameCharacter[0] );
            for ( int i = 1 ; i < 46 ; ++i ) { 
                m_Stage_Object_GameCharacter[i] = std::make_shared<GameCharacter>( BLUE_NORMAL_OBJECT );
                m_Stage_Object_GameCharacter[i]->SetVisible( false );
                m_Stage_Object_GameCharacter[i]->SetZIndex( 10 );
                m_Root.AddChild( m_Stage_Object_GameCharacter[i] );
            }
            m_Stage_Object[2] = std::make_shared<StageObject>( 45 , m_Stage_Object_GameCharacter );
            m_Stage_Object[2]->SetStage( 0 );
            m_Root.AddChild( m_Stage_Object[2] );
            m_Stage_Goal_Object_Show = std::make_shared<GameCharacter>( BROWN_NORMAL_OBJECT );
            m_Stage_Goal_Object_Show->SetPosition( stage_goal_position[2] );
            m_Stage_Goal_Object_Show->SetVisible( true );
            m_Root.AddChild( m_Stage_Goal_Object_Show );
        }
        else if ( stage == 3 ) {
            m_Stage_Object_GameCharacter[0] = std::make_shared<GameCharacter>( GA_RESOURCE_DIR"/Image/GameObject/click.png" );
            m_Stage_Object_GameCharacter[0]->SetVisible( false );
            m_Stage_Object_GameCharacter[0]->SetZIndex( 9 );
            m_Root.AddChild( m_Stage_Object_GameCharacter[0] );
            for ( int i = 1 ; i < 48 ; ++i ) { 
                m_Stage_Object_GameCharacter[i] = std::make_shared<GameCharacter>( BLUE_NORMAL_OBJECT );
                m_Stage_Object_GameCharacter[i]->SetVisible( false );
                m_Stage_Object_GameCharacter[i]->SetZIndex( 10 );
                m_Root.AddChild( m_Stage_Object_GameCharacter[i] );
            }
            m_Stage_Object[3] = std::make_shared<StageObject>( 47 , m_Stage_Object_GameCharacter );
            m_Stage_Object[3]->SetStage( 0 );
            m_Root.AddChild( m_Stage_Object[3] );
            m_Stage_Goal_Object_Show = std::make_shared<GameCharacter>( REACH_IMAGE );
            m_Stage_Goal_Object_Show->SetPosition( stage_goal_position[3] );
            m_Stage_Goal_Object_Show->SetVisible( true );
            m_Root.AddChild( m_Stage_Goal_Object_Show );
        }
        for ( int i = 1 ; i < 13 ; ++i ) {
            m_Stage_Buttoms[i]->SetVisible( false );
        }
        m_Jump_Page->AllDisappear();
        m_Jump_Page->m_Pause_Buttom->SetVisible( true );
        m_Text_Point->SetPoint( 0 );
        m_Text_Point->SetVisible( true );
    }

    void RemoveStage( int stage ) {
        if ( stage == 1 ) {
            for ( int i = 0 ; i < 38 ; ++i ) { 
                m_Root.RemoveChild( m_Stage_Object_GameCharacter[i] );
            }
            m_Root.RemoveChild( m_Stage_Goal_Object_Show );
            m_Root.RemoveChild( m_Stage_Object[1] );
        }
        else if ( stage == 2 ) {
            for ( int i = 0 ; i < 46 ; ++i ) { 
                m_Root.RemoveChild( m_Stage_Object_GameCharacter[i] );
            }
            m_Root.RemoveChild( m_Stage_Goal_Object_Show );
            m_Root.RemoveChild( m_Stage_Object[2] );
        }
        else if ( stage == 3 ) {
            for ( int i = 0 ; i < 48 ; ++i ) { 
                m_Root.RemoveChild( m_Stage_Object_GameCharacter[i] );
            }
            m_Root.RemoveChild( m_Stage_Goal_Object_Show );
            m_Root.RemoveChild( m_Stage_Object[3] );
        }
    }

    void AppearHomePage() {
        m_BGM_Music[0]->Playing( GA_RESOURCE_DIR"/Music/springDayShadow.mp3");
        m_Text_Point->SetVisible( false );
        for ( int i = 1 ; i < 13 ; ++i ) {
            if ( ifClear[i] ) {
                m_Stage_Buttoms[i]->SetImage( ClearStageList[i] );
            }
            else if ( ifClear[i-1] ) {
                m_Stage_Buttoms[i]->SetImage( CurrentStageList[i] );
            }
            else {
                m_Stage_Buttoms[i]->SetImage( LevelStageList[i] );
            }
            m_Stage_Buttoms[i]->SetVisible( true );
        }
    }

    void SetStage( int i ) {
        m_stage_pos = i;
    }

    int GetStage() {
        return m_stage_pos;
    }
private:
    void ValidTask();

private:
    enum class Phase {
        INITIAL_IMAGE = 1,
        HOME_PAGE = 2 ,
        STAGE_1 = 3 ,
        STAGE_2 = 4 ,
        STAGE_3 = 5, 
    };


    // const int m_GameCharacterSize = 51;
    State m_CurrentState = State::START;
    Phase m_Phase = Phase::INITIAL_IMAGE;

    Util::Renderer m_Root;

    std::shared_ptr<Music> m_BGM_Music[40];

    std::shared_ptr<Character> m_Start_initial;
    std::shared_ptr<Character> m_Stage_Buttoms[13];
    

    // std::shared_ptr<GameCharacter> m_Normal_Game_Object[13];
    
    std::shared_ptr<GameCharacter> m_Stage_Object_GameCharacter[90];
    // std::shared_ptr<GameCharacter> m_Stage_Object_GameCharacter[46];
    // std::shared_ptr<GameCharacter> m_Stage_Object_GameCharacter[48];

    std::shared_ptr<GameCharacter> m_Stage_Goal_Object_Show;

    std::shared_ptr<StageObject> m_Stage_Object[13];

    std::shared_ptr<JumpPage> m_Jump_Page;
    
    // std::shared_ptr<Character> m_Chest;
    // std::vector<std::shared_ptr<Character>> m_Doors;

    // std::shared_ptr<AnimatedCharacter> m_Bee;
    // std::shared_ptr<AnimatedCharacter> m_Ball;
    std::shared_ptr<TaskText> m_Text_Point;
    
    
    std::shared_ptr<PhaseResourceManager> m_PRM;
    int m_stage_pos = 0;
    bool m_EnterDown = false; 
};

#endif