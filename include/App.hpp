#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"
#include "Util/Text.hpp"
#include "PhaseResourceManager.hpp"
#include "Character.hpp"
#include "GameCharacter.hpp"

// #include "AnimatedCharacter.hpp"

// Declare of Phase Main Action
bool PhaseInitialImage(std::shared_ptr<Character> &chara_obj);
bool PhaseHomePage( std::shared_ptr<Character> &level1);
bool PhaseStage1( std::shared_ptr<GameCharacter>* objectArray );
void DebugPhaseStage1( std::shared_ptr<GameCharacter>* objectArray );

// Declare of Game Main Character
void InitializeGameCharacter( std::shared_ptr<GameCharacter>* objectArray );
void DebugModeOfPosition( std::shared_ptr<GameCharacter>* objectArray , int option);
void DebugModeCancel( std::shared_ptr<GameCharacter>* objectArray , int option);

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

    // std::shared_ptr<Character> m_Chest;
    // std::vector<std::shared_ptr<Character>> m_Doors;

    // std::shared_ptr<AnimatedCharacter> m_Bee;
    // std::shared_ptr<AnimatedCharacter> m_Ball;

    std::shared_ptr<PhaseResourceManager> m_PRM;

    bool m_EnterDown = false; 
};

#endif