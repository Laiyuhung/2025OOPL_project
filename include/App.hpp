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
#include "Item.hpp"
#include <vector>

bool PhaseInitialImage(std::shared_ptr<Character>& chara_obj);
int PhaseHomePage(const std::vector<std::shared_ptr<Character>>& buttoms);
bool PhaseStage(std::shared_ptr<StageObject> StageObject, int size, std::shared_ptr<TaskText> point, int stage , std::vector< std::shared_ptr<Item> > Tools );
// bool PhaseStage2(std::shared_ptr<StageObject> StageObject, int size, std::shared_ptr<TaskText> point);
void DebugPhaseStage1(std::vector<std::shared_ptr<GameCharacter>>& objectArray);

// Declare of Debug Mode
void DebugModeOfPosition(std::vector<std::shared_ptr<GameCharacter>>& objectArray, int option);
void DebugModeCancel(std::vector<std::shared_ptr<GameCharacter>>& objectArray, int option);
void DebugModeOfAppearance(const std::vector<std::shared_ptr<GameCharacter>>& objectArray, int size);
void DebugModeShowMapObject(const std::vector<std::shared_ptr<GameCharacter>>& objectArray, int size);

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
    void End();
    
    void SetUpStage(int stage) {
        // m_Stage_Object.at(stage)->ClearObject();
        m_BGM_Music.at(0)->Playing(GA_RESOURCE_DIR "/Music/rickRoll.mp3");
        int size = 0;
        if (stage == 1) size = 37;
        else if (stage == 2) size = 45;
        else if (stage == 3) size = 47;
        else if (stage == 4) size = 64;
        else if (stage == 5) size = 39;
        else if (stage == 6) size = 72;
        else if (stage == 7) size = 60;
        else if (stage == 8) size = 70;
        else if (stage == 9) size = 43;
        else if (stage == 10) size = 73;
        else if (stage == 11) size = 59;
        else if (stage == 12) size = 69;
        
        if (m_Stage_Object.size() <= static_cast<size_t>(stage)) m_Stage_Object.resize(stage + 1);
        m_Stage_Object.at(stage) = std::make_shared<StageObject>(size);
        m_Stage_Object.at(stage)->SetStage(0);
        auto clickObj = std::make_shared<GameCharacter>(GA_RESOURCE_DIR "/Image/GameObject/click.png");
        clickObj->SetVisible(false);
        clickObj->SetZIndex(9);
        m_Stage_Object[stage]->PushBackObject(clickObj);
        m_Root.AddChild(clickObj);
        
        for (int i = 1; i <= size; ++i) {
            auto obj = std::make_shared<GameCharacter>(BLUE_NORMAL_OBJECT);
            obj->SetVisible(false);
            obj->SetZIndex(10);
            m_Stage_Object.at(stage)->PushBackObject(obj); // 先收集
            m_Root.AddChild(obj);
        }
        
        m_Root.AddChild(m_Stage_Object.at(stage));
        
        auto goalImage = (stage >= 3) ? REACH_IMAGE : BROWN_NORMAL_OBJECT;
        auto stage_goal = std::make_shared<GameCharacter>(goalImage);
        if ( stage == 1 || stage == 2 ) 
            stage_goal->SetImage( BROWN_NORMAL_OBJECT );
        else if ( stage == 3 || stage == 3 )
            stage_goal->SetImage( REACH_IMAGE );
        else if ( stage == 5 || stage == 6 || stage == 7 || stage == 11  )
            stage_goal->SetImage( COOKIE_ONE_IMAGE );
        else if ( stage == 8 )
            stage_goal->SetImage( WHITE_STARFLOWER_OBJECT );
        else if ( stage == 9 || stage == 10 )
            stage_goal->SetImage( WHITE_STRIPE_OBJECT );
        else if ( stage == 12 )
            stage_goal->SetImage( RAINBOWBALL_OBJECT_LINK );

        stage_goal->SetPosition(stage_goal_position[stage]);
        stage_goal->SetVisible(true);
        stage_goal->SetZIndex( 10 );
        m_Root.AddChild(stage_goal);
        m_Stage_Object.at(stage)->SetStageGoalObject( stage_goal );
        
        for (auto& btn : m_Stage_Buttoms) 
            if ( btn )
                btn->SetVisible(false);
        m_Jump_Page->AllDisappear();
        m_Jump_Page->GetPauseButtom()->SetVisible(true);
        m_Text_Point->SetPoint(0);
        m_Text_Point->SetVisible(true);
    }

    void RemoveStage(int stage) {
        for ( int i = 0 ; i < m_Stage_Object.at(stage)->GetSize()+1 ; ++i ){
            m_Root.RemoveChild( m_Stage_Object.at(stage)->GetStageObjectItem(i) );
        }
        m_Stage_Object.at(stage)->ClearAll();
        m_Root.RemoveChild(m_Stage_Object.at(stage)->GetStageGoalObject());
        if (static_cast<size_t>(stage) < m_Stage_Object.size()) {
            m_Root.RemoveChild(m_Stage_Object.at(stage));
        }
    }

    void AppearHomePage() {
        m_BGM_Music.at(0)->Playing(GA_RESOURCE_DIR "/Music/springDayShadow.mp3");
        m_Text_Point->SetVisible(false);
        m_Setting->SetVisible( true );
        for (size_t i = 1; i < m_Stage_Buttoms.size(); ++i) {
            if (ifClear[i]) m_Stage_Buttoms.at(i)->SetImage(ClearStageList[i]);
            else if (ifClear[i - 1]) m_Stage_Buttoms.at(i)->SetImage(CurrentStageList[i]);
            else m_Stage_Buttoms.at(i)->SetImage(LevelStageList[i]);
            m_Stage_Buttoms.at(i)->SetVisible(true);
        }
    }

    void SetStage(int i) { m_stage_pos = i; }
    int GetStage() { return m_stage_pos; }

private:
    void ValidTask();
    void Stage( int stage_pos );

private:
    enum class Phase {
        INITIAL_IMAGE = 1,
        HOME_PAGE = 2,
        STAGE_1 = 3,
        STAGE_2 = 4,
        STAGE_3 = 5,
        STAGE_4 = 6,
        STAGE_5 = 7,
        STAGE_6 = 8,
        STAGE_7 = 9,
        STAGE_8 = 10,
        STAGE_9 = 11,
        STAGE_10 = 12,
        STAGE_11 = 13,
        STAGE_12 = 14,
    };

    State m_CurrentState = State::START;
    Phase m_Phase = Phase::INITIAL_IMAGE;

    Util::Renderer m_Root;
    std::vector<std::shared_ptr<Music>> m_BGM_Music;
    std::shared_ptr<Character> m_Start_initial;
    std::shared_ptr<Character> m_Setting;
    std::vector<std::shared_ptr<Character>> m_Stage_Buttoms;
    std::vector<std::shared_ptr<StageObject>> m_Stage_Object;
    std::vector<std::shared_ptr<Item>> m_Tools;

    std::shared_ptr<JumpPage> m_Jump_Page;
    std::shared_ptr<TaskText> m_Text_Point;
    std::shared_ptr<TaskText> m_End_Point;
    std::shared_ptr<TaskText> m_Show_Text;
    std::shared_ptr<PhaseResourceManager> m_PRM;

    int m_stage_pos = 0;
    bool m_EnterDown = false;
};

#endif
