#include "App.hpp"
#include "Global.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    InitializeStage1();
    InitializeStage2();
    startTime = std::chrono::steady_clock::now();

    m_Start_initial = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/GameObject/initailStartButton.png");
    m_Start_initial->SetPosition({0, -160.5f});
    m_Start_initial->SetZIndex(10);
    m_Root.AddChild(m_Start_initial);
    
    m_Stage_Buttom_1 = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/GameObject/levelOne.png");
    m_Stage_Buttom_1->SetPosition({-64.5, 87.5f});
    m_Stage_Buttom_1->SetZIndex(10);
    m_Stage_Buttom_1->SetVisible(false);
    m_Root.AddChild( m_Stage_Buttom_1 );

    m_Stage_Buttom_2 = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/GameObject/levelTwo.png");
    m_Stage_Buttom_2->SetPosition({0, 87.5f});
    m_Stage_Buttom_2->SetZIndex(10);
    m_Stage_Buttom_2->SetVisible(false);
    m_Root.AddChild( m_Stage_Buttom_2 );

    m_Play_Buttom = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/GameObject/playButtom.png");
    m_Play_Buttom->SetPosition( { 60.5, -120.5f } );
    m_Play_Buttom->SetZIndex( 13 );
    m_Play_Buttom->SetVisible(false);
    m_Root.AddChild( m_Play_Buttom );

    m_Cancel_Buttom = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/GameObject/closeButton.png");
    m_Cancel_Buttom->SetPosition( { 100, 146 } );
    m_Cancel_Buttom->SetZIndex( 13 );
    m_Cancel_Buttom->SetVisible(false);
    m_Root.AddChild( m_Cancel_Buttom );

    m_Pause_Buttom = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/GameObject/pauseButton.png");
    m_Pause_Buttom->SetPosition( { -114.5, -258 } );
    m_Pause_Buttom->SetZIndex( 13 );
    m_Pause_Buttom->SetVisible(false);
    m_Root.AddChild( m_Pause_Buttom );

    m_Pause_Page = std::make_shared<Character>( GA_RESOURCE_DIR"/Image/Background/pausePage.png" );
    m_Pause_Page->SetPosition( {0 , 0} );
    m_Pause_Page->SetZIndex( 13 );
    m_Pause_Page->SetVisible(false);
    m_Root.AddChild( m_Pause_Page );

    m_Continue_Buttom = std::make_shared<Character>( GA_RESOURCE_DIR"/Image/GameObject/continueButtom.png");
    m_Continue_Buttom->SetPosition( {0 , 30} );
    m_Continue_Buttom->SetZIndex( 14 );
    m_Continue_Buttom->SetVisible(false);
    m_Root.AddChild( m_Continue_Buttom );

    m_Stop_Buttom = std::make_shared<Character>( GA_RESOURCE_DIR"/Image/GameObject/stopButtom.png" );
    m_Stop_Buttom->SetPosition( {0 , -30} );
    m_Stop_Buttom->SetZIndex( 14 );
    m_Stop_Buttom->SetVisible(false);
    m_Root.AddChild( m_Stop_Buttom );

    m_Play_Page[1] = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/Background/stage1Start.png");
    m_Play_Page[1]->SetVisible( false );
    m_Play_Page[1]->SetPosition({0, 0});
    m_Play_Page[1]->SetZIndex( 12 );
    m_Play_Page[1]->SetSize( {5, 5} );
    m_Root.AddChild( m_Play_Page[1] );

    m_finish_Page[1] = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/Background/stage1End.png");
    m_finish_Page[1]->SetVisible( false );
    m_finish_Page[1]->SetPosition({0, 0});
    m_finish_Page[1]->SetZIndex( 12 );
    m_finish_Page[1]->SetSize( {5, 5} );
    m_Root.AddChild( m_finish_Page[1] );

    m_Play_Page[2] = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/Background/stage2Start.png");
    m_Play_Page[2]->SetVisible( false );
    m_Play_Page[2]->SetPosition({0, 0});
    m_Play_Page[2]->SetZIndex( 12 );
    m_Play_Page[2]->SetSize( {5, 5} );
    m_Root.AddChild( m_Play_Page[2] );


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
    m_Stage_Object[2] = std::make_shared<StageObject>( 45 , m_Stage_2_Object );
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
            m_Pause_Buttom->SetVisible( false );
            m_Continue_Buttom->SetVisible( false );
            m_Stop_Buttom->SetVisible( false );
            m_Stage_Buttom_1->SetVisible( true );
            m_Stage_Buttom_2->SetVisible( true );
            if (PhaseHomePage(m_Stage_Buttom_1)){
                m_stage_pos = 1;
                m_Play_Page[1]->SetVisible(true);
                m_Play_Buttom->SetVisible( true );
                m_Cancel_Buttom->SetVisible( true );
            } 
            else if (PhaseHomePage(m_Stage_Buttom_2)){
                m_stage_pos = 2;
                m_Play_Page[2]->SetVisible(true);
                m_Play_Buttom->SetVisible( true );
                m_Cancel_Buttom->SetVisible( true );
            }
            if ( m_Play_Buttom->GetVisibility() ) {
                if ( m_Play_Buttom->IfClick() ) {
                    if ( m_stage_pos == 1  ) {
                        std::cout << "Level1 Character clicked!" << std::endl;
                        m_Stage_Buttom_1->SetVisible( false );
                        m_Stage_Buttom_2->SetVisible( false );
                        m_Play_Buttom->SetVisible( false );
                        m_Cancel_Buttom->SetVisible( false );
                        m_Play_Page[1]->SetVisible( false );
                        m_Pause_Buttom->SetVisible( true );
                        m_PRM->NextPhase(PHASE_STAGE_1);
                        m_Stage_Object[1]->SetUp( 1 );
                        m_Stage_Object[1]->AppearAll();
                        m_Stage_Object[1]->SetStage( 1 );
                        m_Point_Show->SetValue( 0 );
                        m_Point_Show->SetVisible( true );
                        m_Point_Show->SetPosition( point_position[1] );
                        m_Point_Show->UpdateText();
                        currentPhase = PHASE_NORMAL;
                        m_Phase = Phase::STAGE_1;
                    }
                    if ( m_stage_pos == 2  ) {
                        std::cout << "Level2 Character clicked!" << std::endl;
                        m_Stage_Buttom_1->SetVisible( false );
                        m_Stage_Buttom_2->SetVisible( false );
                        m_Play_Buttom->SetVisible( false );
                        m_Cancel_Buttom->SetVisible( false );
                        m_Play_Page[2]->SetVisible( false );
                        m_Pause_Buttom->SetVisible( true );
                        m_PRM->NextPhase(PHASE_STAGE_2);
                        m_Stage_Object[2]->SetUp( 2 );
                        m_Stage_Object[2]->AppearAll();
                        m_Stage_Object[2]->SetStage( 2 );
                        m_Point_Show->SetPosition( point_position[2] );
                        m_Point_Show->SetValue( 0 );
                        m_Point_Show->SetVisible( true );
                        m_Point_Show->UpdateText();
                        currentPhase = PHASE_NORMAL;
                        m_Phase = Phase::STAGE_2;
                    }
                }
                if ( m_Cancel_Buttom->IfClick() ) {
                    if ( m_stage_pos == 1 ) {
                        m_stage_pos = 0;
                        m_Play_Page[1]->SetVisible( false );
                        m_Play_Buttom->SetVisible( false );
                        m_Cancel_Buttom->SetVisible( false );
                    }
                    if ( m_stage_pos == 2 ) {
                        m_stage_pos = 0;
                        m_Play_Page[2]->SetVisible( false );
                        m_Play_Buttom->SetVisible( false );
                        m_Cancel_Buttom->SetVisible( false );
                    }
                }
            }
            break;
        case Phase::STAGE_1:
            if ( m_Pause_Buttom->IfClick() ) {
                m_Pause_Page->SetVisible( true );
                m_Continue_Buttom->SetVisible( true );
                m_Stop_Buttom->SetVisible( true );
            }
            if ( m_Pause_Page->GetVisibility() && m_Continue_Buttom->IfClick() ) {
                m_Pause_Page->SetVisible( false );
                m_Continue_Buttom->SetVisible( false );
                m_Stop_Buttom->SetVisible( false );
            }
            if ( m_Pause_Page->GetVisibility() && m_Stop_Buttom->IfClick() ) {
                m_Pause_Page->SetVisible( false );
                m_Continue_Buttom->SetVisible( false );
                m_Stop_Buttom->SetVisible( false );
                m_PRM->NextPhase(PHASE_HOME_PAGE);
                m_Phase = Phase::HOME_PAGE;
                m_Stage_Object[1]->DisAppearAll();
                stage_point_counter[1] = 0;
                m_stage_pos = 0;
                m_Point_Show->SetVisible( false );
            }
            if ( m_finish_Page[1]->GetVisibility() && m_Cancel_Buttom->IfClick() ) {
                m_PRM->NextPhase(PHASE_HOME_PAGE);
                m_Phase = Phase::HOME_PAGE;
                m_Stage_Buttom_1->SetVisible( true );
                m_Stage_Buttom_2->SetVisible( true );
                m_Cancel_Buttom->SetVisible( false );
                m_finish_Page[1]->SetVisible( false );
                stage_point_counter[1] = 0;
                m_stage_pos = 0;
            }
            if (PhaseStage1( m_Stage_Object[1], m_Stage_Object[1]->GetSize() , m_Point_Show )){
                m_Stage_Object[1]->DisAppearAll();
                m_Point_Show->SetVisible( false );
                m_finish_Page[1]->SetVisible( true );
                m_Cancel_Buttom->SetVisible( true );
            } 
            else if ( currentPhase == PHASE_PAUSE_FOR_DISAPPEAR ) {
                if ( (std::chrono::steady_clock::now() - startTime) >= std::chrono::seconds(1)) {
                    currentPhase = PHASE_DROPPING;
                }
                m_Root.Update();
            }
            else if ( currentPhase == PHASE_DROPPING ) {
                m_Stage_Object[1]->Dropping();
                m_Point_Show->SetValue( stage_point_counter[1] );
                m_Point_Show->UpdateText();
            }
            break;
        case Phase::STAGE_2:
            if ( m_Pause_Buttom->IfClick() ) {
                m_Pause_Page->SetVisible( true );
                m_Continue_Buttom->SetVisible( true );
                m_Stop_Buttom->SetVisible( true );
            }
            if ( m_Pause_Page->GetVisibility() && m_Continue_Buttom->IfClick() ) {
                m_Pause_Page->SetVisible( false );
                m_Continue_Buttom->SetVisible( false );
                m_Stop_Buttom->SetVisible( false );
            }
            if ( m_Pause_Page->GetVisibility() && m_Stop_Buttom->IfClick() ) {
                m_Pause_Page->SetVisible( false );
                m_Continue_Buttom->SetVisible( false );
                m_Stop_Buttom->SetVisible( false );
                m_PRM->NextPhase(PHASE_HOME_PAGE);
                m_Phase = Phase::HOME_PAGE;
                stage_point_counter[2] = 0;
                m_Stage_Object[2]->DisAppearAll();
                m_stage_pos = 0;
                m_Point_Show->SetVisible( false );
            }
            if ( m_finish_Page[2]->GetVisibility() && m_Cancel_Buttom->IfClick() ) {
                m_PRM->NextPhase(PHASE_HOME_PAGE);
                m_Phase = Phase::HOME_PAGE;
                stage_point_counter[2] = 0;
                m_Stage_Buttom_1->SetVisible( true );
                m_Stage_Buttom_2->SetVisible( true );
                m_finish_Page[2]->SetVisible( false );
                m_Cancel_Buttom->SetVisible( false );
                m_stage_pos = 0;
            }
            if (PhaseStage2( m_Stage_Object[2], m_Stage_Object[2]->GetSize() , m_Point_Show )){
                m_Stage_Object[2]->DisAppearAll();
                m_Point_Show->SetVisible( false );
                m_finish_Page[2]->SetVisible( true );
                m_Cancel_Buttom->SetVisible( true );
            } 
            else if ( currentPhase == PHASE_PAUSE_FOR_DISAPPEAR ) {
                if ( (std::chrono::steady_clock::now() - startTime) >= std::chrono::seconds(1)) {
                    currentPhase = PHASE_DROPPING;
                }
                m_Root.Update();
            }
            else if ( currentPhase == PHASE_DROPPING ) {
                m_Stage_Object[2]->Dropping();
                m_Point_Show->SetValue( stage_point_counter[2] );
                m_Point_Show->UpdateText();
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
