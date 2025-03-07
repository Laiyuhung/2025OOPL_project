#include "App.hpp"
#include "Global.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    m_Start_initial = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/GameObject/initailStartButton.png");
    m_Start_initial->SetPosition({0, -160.5f});
    m_Start_initial->SetZIndex(10);
    m_Root.AddChild(m_Start_initial);

    InitializeGameCharacter( m_Normal_Game_Object );
    m_Root.AddChild(m_Normal_Game_Object[BLUE_NORMAL_OBJECT]);
    m_Root.AddChild(m_Normal_Game_Object[BROWN_NORMAL_OBJECT]);
    m_Root.AddChild(m_Normal_Game_Object[GREEN_NORMAL_OBJECT]);
    m_Root.AddChild(m_Normal_Game_Object[PINK_NORMAL_OBJECT]);
    m_Root.AddChild(m_Normal_Game_Object[ORANGE_NORMAL_OBJECT]);
    m_Root.AddChild(m_Normal_Game_Object[WHITE_NORMAL_OBJECT]);
    m_Root.AddChild(m_Normal_Game_Object[YELLOW_NORMAL_OBJECT]);

    m_Stage_Buttom_1 = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/GameObject/levelOne.png");
    m_Stage_Buttom_1->SetPosition({0, -160.5f});
    m_Stage_Buttom_1->SetZIndex(10);
    m_Stage_Buttom_1->SetVisible(false);
    m_Root.AddChild( m_Stage_Buttom_1 );

    m_PRM = std::make_shared<PhaseResourceManager>();
    m_Root.AddChildren(m_PRM->GetChildren());
    m_CurrentState = State::UPDATE;
}

void App::Update() {
    switch (m_Phase) {
        case Phase::INITIAL_IMAGE:
            if (PhaseInitialImage(m_Start_initial)){
                m_PRM->NextPhase(PHASE_HOME_PAGE);
                m_Phase = Phase::HOME_PAGE;
                m_Stage_Buttom_1->SetVisible( true );
            }
            break;
        case Phase::HOME_PAGE:
            if (PhaseHomePage(m_Stage_Buttom_1)){
                m_PRM->NextPhase(PHASE_STAGE_1);
                m_Phase = Phase::STAGE_1;
            }
            break;
        case Phase::STAGE_1:
            break;
    }
    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
