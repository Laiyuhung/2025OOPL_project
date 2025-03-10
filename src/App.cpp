#include "App.hpp"
#include "Global.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    InitializeStage1();

    m_Start_initial = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/GameObject/initailStartButton.png");
    m_Start_initial->SetPosition({0, -160.5f});
    m_Start_initial->SetZIndex(10);
    m_Root.AddChild(m_Start_initial);
    
    m_Stage_Buttom_1 = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/GameObject/levelOne.png");
    m_Stage_Buttom_1->SetPosition({0, -160.5f});
    m_Stage_Buttom_1->SetZIndex(10);
    m_Stage_Buttom_1->SetVisible(false);
    m_Root.AddChild( m_Stage_Buttom_1 );

    InitializeStageCharacter( m_Stage_1_Object, 37);
    for ( int i = 1 ; i < 38 ; ++i )
        m_Root.AddChild( m_Stage_1_Object[i] );
    CheckAppearance( m_Stage_1_Object , 37 , false);

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

                // m_Stage_1_Object[1]->SwitchPosition( m_Stage_1_Object[2] );
                // std::shared_ptr<GameCharacter> temp = m_Stage_1_Object[1];
                // m_Stage_1_Object[1] = m_Stage_1_Object[2];
                // m_Stage_1_Object[2] = temp;

                // std::cout << "wqd "<< m_Stage_1_Object[1]->GetBlockType() << " " << m_Stage_1_Object[2]->GetBlockType() << std::endl;
            }
            break;
        case Phase::HOME_PAGE:
            if (PhaseHomePage(m_Stage_Buttom_1)){
                m_PRM->NextPhase(PHASE_STAGE_1);
                for ( int i = 1 ; i < 38 ; ++i ) {
                    // std::cout << "i : " << i << " " << m_Stage_1_Object[i]->GetPosition().x << " " <<  m_Stage_1_Object[i]->GetPosition().y<< std::endl;
                    if ( m_Stage_1_Object[i]->GetAppearBool() )
                        m_Stage_1_Object[i]->Appear();  
                }
                m_Phase = Phase::STAGE_1;
            }
            break;
        case Phase::STAGE_1:
            if (PhaseStage1(m_Stage_1_Object, 37)){
                m_PRM->NextPhase(PHASE_HOME_PAGE);
                m_Phase = Phase::HOME_PAGE;
                m_Stage_Buttom_1->SetVisible( true );
                DisAppearAll( m_Stage_1_Object , 37 );
            }
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
