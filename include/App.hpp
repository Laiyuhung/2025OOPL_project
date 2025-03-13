#ifndef APP_HPP
#define APP_HPP

#include <vector>

#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"
#include "Util/Text.hpp"
#include "PhaseResourceManager.hpp"
#include "Character.hpp"
#include "GameCharacter.hpp"
#include "ObjectInformation.hpp"
#include "TaskText.hpp"

// #include "AnimatedCharacter.hpp"

// Declare of Phase Main Action
bool PhaseInitialImage(std::shared_ptr<Character> &chara_obj);
bool PhaseHomePage( std::shared_ptr<Character> &level1);
bool PhaseStage1( std::shared_ptr<GameCharacter>* objectArray , const int size , std::shared_ptr<TaskText> point);
void DebugPhaseStage1( std::shared_ptr<GameCharacter>* objectArray );

// Declare of Check Object
bool CheckAppearance( std::shared_ptr<GameCharacter>* objectArray, int size , int stage);
int  CheckNextAppearance( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int side, int length );

// Declare of Debug Mode
void DebugModeOfPosition( std::shared_ptr<GameCharacter>* objectArray , int option);
void DebugModeCancel( std::shared_ptr<GameCharacter>* objectArray , int option);
void DebugModeOfAppearance( std::shared_ptr<GameCharacter>* objectArray , int size );

// Declare of Disappear
void MakeDisappear( std::shared_ptr<GameCharacter>* objectArray , int size , int stage );
bool DisappearMethodOfOneLine( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length );
int  DisappearMethodOfStripe( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length, int priority );
bool DisappearMethodOfFlower( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length );
bool DisappearMethodOfStarFlower( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length );
bool DisappearMethodOfTriangleFlower( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length );
bool DisappearMethodOfRainbowBall( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int* total_length );
void DisappearBySingleObject ( std::shared_ptr<GameCharacter>* objectArray, std::shared_ptr<GameCharacter>& object, int side, int length_left);

// Declare of Drop
void Dropping( std::shared_ptr<GameCharacter>* objectArray, const int size , int stage);
void Dropping_method( std::shared_ptr<GameCharacter>* objectArray, const int size , const int current_position );

// Declare of Game Main Action
void DisAppearAll( std::shared_ptr<GameCharacter> *objectArray , const int size );
void AppearAll( std::shared_ptr<GameCharacter> *objectArray , const int size );
void ClearAll( std::shared_ptr<GameCharacter> *objectArray , const int size );
bool IsSameColor(int blockType1, int blockType2);
void SetUp( int stage , std::shared_ptr<GameCharacter>* objectArray , const int size , std::shared_ptr<TaskText> point );
void CheckClickSwitch( std::shared_ptr<GameCharacter>* objectArray, int check, int i , std::shared_ptr<TaskText> point , int size);

// Declare of Object Change
void RamdomChangeObject( std::shared_ptr<GameCharacter> &object ); // only change image path not object itself
void InitializeStageCharacter( std::shared_ptr<GameCharacter>* objectArray , int size);
void CheckSpecialObject( std::shared_ptr<GameCharacter>* objectArray, int i, int stage );


// Declare of Point
void PointUpdate( int stage , int point );
int GetPoint( int stage );

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

private:
    void ValidTask();

private:
    enum class Phase {
        INITIAL_IMAGE = 1,
        HOME_PAGE = 2 ,
        STAGE_1 = 3 ,
    };


    State m_CurrentState = State::START;
    Phase m_Phase = Phase::INITIAL_IMAGE;

    Util::Renderer m_Root;

    std::shared_ptr<Character> m_Start_initial;
    std::shared_ptr<Character> m_Stage_Buttom_1;

    std::shared_ptr<GameCharacter> m_Normal_Game_Object[7];

    std::shared_ptr<GameCharacter> m_Stage_1_Object[38];

    // std::shared_ptr<Character> m_Chest;
    // std::vector<std::shared_ptr<Character>> m_Doors;

    // std::shared_ptr<AnimatedCharacter> m_Bee;
    // std::shared_ptr<AnimatedCharacter> m_Ball;
    std::shared_ptr<TaskText> m_Point_Show;

    std::shared_ptr<PhaseResourceManager> m_PRM;

    bool m_EnterDown = false; 
};

#endif