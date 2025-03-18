#include "App.hpp"
#include "Global.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    InitializeStage1();
    // InitializeStage2();
    startTime = std::chrono::steady_clock::now();

    m_Start_initial = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/GameObject/initailStartButton.png");
    m_Start_initial->SetPosition({0, -160.5f});
    m_Start_initial->SetZIndex(10);
    m_Root.AddChild(m_Start_initial);
    
    m_Stage_Buttom_1 = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/GameObject/levelOne.png");
    m_Stage_Buttom_1->SetPosition({0, -160.5f});
    m_Stage_Buttom_1->SetZIndex(10);
    m_Stage_Buttom_1->SetVisible(false);
    m_Root.AddChild( m_Stage_Buttom_1 );

    m_Stage_Buttom_2 = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/GameObject/levelTwo.png");
    m_Stage_Buttom_2->SetPosition({0, -50.5f});
    m_Stage_Buttom_2->SetZIndex(10);
    m_Stage_Buttom_2->SetVisible(false);
    m_Root.AddChild( m_Stage_Buttom_2 );

    for ( int i = 1 ; i < 38 ; ++i ) { 
        m_Stage_1_Object[i] = std::make_shared<GameCharacter>( BLUE_NORMAL_OBJECT );
        m_Stage_1_Object[i]->SetVisible( false );
        m_Root.AddChild( m_Stage_1_Object[i] );
    }
    m_Stage_Object[1] = std::make_shared<StageObject>( 37 , m_Stage_1_Object );
    m_Stage_Object[1]->SetStage( 0 );
    m_Root.AddChild( m_Stage_Object[1] );

    for ( int i = 1 ; i < 46 ; ++i ) { 
        m_Stage_2_Object[i] = std::make_shared<GameCharacter>( BLUE_NORMAL_OBJECT );
        m_Stage_2_Object[i]->SetVisible( false );
        m_Root.AddChild( m_Stage_2_Object[i] );
    }
    m_Stage_Object[2] = std::make_shared<StageObject>( 46 , m_Stage_2_Object );
    m_Stage_Object[2]->SetStage( 0 );
    m_Root.AddChild( m_Stage_Object[2] );

    m_Point_Show = std::make_shared<TaskText>();
    m_Point_Show->SetVisible( false );
    m_Point_Show->SetZIndex(10);
    m_Point_Show->SetPosition( {125, 210} );
    m_Point_Show->SetValue(0);
    m_Root.AddChild( m_Point_Show );

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
                m_Stage_Buttom_2->SetVisible( true );
            }
            break;
        case Phase::HOME_PAGE:
            if (PhaseHomePage(m_Stage_Buttom_1)){
                std::cout << "Level1 Character clicked!" << std::endl;
                m_Stage_Buttom_1->SetVisible( false );
                m_Stage_Buttom_2->SetVisible( false );
                m_PRM->NextPhase(PHASE_STAGE_1);
                m_Stage_Object[1]->SetUp( 1 );
                m_Stage_Object[1]->AppearAll();
                m_Stage_Object[1]->SetStage( 1 );
                m_Point_Show->SetValue( 0 );
                m_Point_Show->SetVisible( true );
                m_Point_Show->UpdateText();
                currentPhase = PHASE_NORMAL;
                m_Phase = Phase::STAGE_1;
            } 
            else if (PhaseHomePage(m_Stage_Buttom_2)){
                std::cout << "Level2 Character clicked!" << std::endl;
                m_Stage_Buttom_1->SetVisible( false );
                m_Stage_Buttom_2->SetVisible( false );
                m_PRM->NextPhase(PHASE_STAGE_2);
                m_Stage_Object[2]->SetUp( 2 );
                m_Stage_Object[2]->AppearAll();
                m_Stage_Object[2]->SetStage( 2 );
                m_Point_Show->SetValue( 0 );
                m_Point_Show->SetVisible( true );
                m_Point_Show->UpdateText();
                currentPhase = PHASE_NORMAL;
                m_Phase = Phase::STAGE_2;
            }
            break;
        case Phase::STAGE_1:
            if (PhaseStage1( m_Stage_Object[1], m_Stage_Object[1]->GetSize() , m_Point_Show )){
                m_PRM->NextPhase(PHASE_HOME_PAGE);
                m_Phase = Phase::HOME_PAGE;
                m_Stage_Buttom_1->SetVisible( true );
                m_Stage_Object[1]->DisAppearAll();
                m_Point_Show->SetVisible( false );
            } 
            else if ( currentPhase == PHASE_PAUSE_FOR_DISAPPEAR ) {
                if ( (std::chrono::steady_clock::now() - startTime) >= std::chrono::seconds(1)) {
                    currentPhase = PHASE_DROPPING;
                }
                m_Root.Update();
            }
            else if ( currentPhase == PHASE_DROPPING ) {
                m_Stage_Object[1]->Dropping();
            }
            break;
        case Phase::STAGE_2:
            if (PhaseStage2( m_Stage_Object[2], m_Stage_Object[2]->GetSize() , m_Point_Show )){
                m_PRM->NextPhase(PHASE_HOME_PAGE);
                m_Phase = Phase::HOME_PAGE;
                m_Stage_Buttom_1->SetVisible( true );
                m_Stage_Buttom_2->SetVisible( true );
                m_Stage_Object[2]->DisAppearAll();
                m_Point_Show->SetVisible( false );
            } 
            else if ( currentPhase == PHASE_PAUSE_FOR_DISAPPEAR ) {
                if ( (std::chrono::steady_clock::now() - startTime) >= std::chrono::seconds(1)) {
                    currentPhase = PHASE_DROPPING;
                }
                m_Root.Update();
            }
            else if ( currentPhase == PHASE_DROPPING ) {
                m_Stage_Object[2]->Dropping();
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
