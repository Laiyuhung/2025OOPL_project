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
    
    m_Stage_Buttoms[1] = std::make_shared<Character>( LEVEL_ONE_IMAGE );
    m_Stage_Buttoms[2] = std::make_shared<Character>( LEVEL_TWO_IMAGE );
    m_Stage_Buttoms[3] = std::make_shared<Character>( LEVEL_THREE_IMAGE );
    m_Stage_Buttoms[4] = std::make_shared<Character>( LEVEL_FOUR_IMAGE );
    m_Stage_Buttoms[5] = std::make_shared<Character>( LEVEL_FIVE_IMAGE );
    m_Stage_Buttoms[6] = std::make_shared<Character>( LEVEL_SIX_IMAGE );
    m_Stage_Buttoms[7] = std::make_shared<Character>( LEVEL_SEVEN_IMAGE );
    m_Stage_Buttoms[8] = std::make_shared<Character>( LEVEL_EIGHT_IMAGE );
    m_Stage_Buttoms[9] = std::make_shared<Character>( LEVEL_NINE_IMAGE );
    m_Stage_Buttoms[10] = std::make_shared<Character>( LEVEL_TEN_IMAGE );
    m_Stage_Buttoms[11] = std::make_shared<Character>( LEVEL_ELEVEN_IMAGE );
    m_Stage_Buttoms[12] = std::make_shared<Character>( LEVEL_TWELVE_IMAGE );
        
    for ( int i = 1 ; i < 13 ; ++i ) {
        m_Stage_Buttoms[i]->SetPosition( stage_position[i] );
        m_Stage_Buttoms[i]->SetZIndex(10);
        m_Stage_Buttoms[i]->SetVisible(false);
        m_Root.AddChild( m_Stage_Buttoms[i] );
    }
    
    m_Jump_Page = std::make_shared<JumpPage>(GA_RESOURCE_DIR"/Image/Background/stage1Start.png");
    m_Jump_Page->SetVisible( false );
    m_Jump_Page->SetPosition({0, 0});
    m_Jump_Page->SetZIndex( 12 );
    m_Jump_Page->SetSize( {5, 5} );
    m_Root.AddChild( m_Jump_Page );

    m_Root.AddChild( m_Jump_Page->m_Play_Buttom );
    m_Root.AddChild( m_Jump_Page->m_Cancel_Buttom );
    m_Root.AddChild( m_Jump_Page->m_Pause_Buttom );
    m_Root.AddChild( m_Jump_Page->m_Stop_Buttom );
    m_Root.AddChild( m_Jump_Page->m_Continue_Buttom );

    m_Text_Point = std::make_shared<TaskText>();
    m_Text_Point->SetPosition({-125, 210});
    m_Text_Point->Initial( 0 );
    m_Text_Point->UpdateText();
    m_Text_Point->SetVisible(false);
    m_Root.AddChild(m_Text_Point);
    
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
                AppearHomePage();
                m_Jump_Page->AllDisappear();
            }
            break;
        case Phase::HOME_PAGE:
            {
                AppearHomePage();
                int get_stage = PhaseHomePage(m_Stage_Buttoms);
                if ( get_stage != 0 ){
                    m_stage_pos = get_stage;
                    m_Jump_Page->PlayPage( m_stage_pos );
                } 
                if ( m_Jump_Page->ifClickWithPlayButtom() ) {
                    SetUpStage( m_stage_pos );
                    if ( m_stage_pos == 1  ) {
                        std::cout << "Level1 Character clicked!" << std::endl;
                        m_Jump_Page->AllDisappear();
                        m_PRM->NextPhase(PHASE_STAGE_1);
                        m_Stage_Object[1]->SetUp( 1 );
                        m_Stage_Object[1]->AppearAll();
                        m_Stage_Object[1]->SetStage( 1 );
                        m_Text_Point->Initial( 1 );
                        currentPhase = PHASE_NORMAL;
                        m_Phase = Phase::STAGE_1;
                    }
                    else if ( m_stage_pos == 2 ) {
                        std::cout << "Level2 Character clicked!" << std::endl;
                        m_Jump_Page->AllDisappear();
                        m_PRM->NextPhase(PHASE_STAGE_2);
                        m_Stage_Object[2]->SetUp( 2 );
                        m_Stage_Object[2]->AppearAll();
                        m_Stage_Object[2]->SetStage( 2 );
                        m_Text_Point->Initial( 2 );
                        currentPhase = PHASE_NORMAL;
                        m_Phase = Phase::STAGE_2;
                    }   
                }
                if ( m_Jump_Page->ifClickWithCancelButtom() ) {
                    m_stage_pos = 0;
                    m_Jump_Page->AllDisappear();
                }
            }
            break;
        case Phase::STAGE_1:
            m_Jump_Page->m_Pause_Buttom->SetVisible( true );
            if (PhaseStage( m_Stage_Object[1], m_Stage_Object[1]->GetSize() , m_Text_Point , 1 )){
                m_Stage_Object[1]->DisAppearAll();
                m_Text_Point->SetVisible( false );
                ifClear[1] = true;
                m_Jump_Page->EndPage( 1 );
            }
            else if ( m_Text_Point->GetMove() <= 0 ) {
                m_Stage_Object[1]->DisAppearAll();
                m_Text_Point->SetVisible( false );
                ifClear[1] = true;
                m_Jump_Page->EndPage( 1 );
            }
            else if ( currentPhase == PHASE_PAUSE_FOR_DISAPPEAR ) {
                if ( (std::chrono::steady_clock::now() - startTime) >= std::chrono::seconds(1)) {
                    currentPhase = PHASE_DROPPING;
                }
                m_Root.Update();
            }
            else if ( currentPhase == PHASE_DROPPING ) {
                m_Stage_Object[1]->Dropping();
                m_Text_Point->SetPoint( stage_point_counter[1] );
                m_Text_Point->SetGoal( stage_goal_counter[1] );
                m_Text_Point->UpdateText();
            }
            if ( m_Jump_Page->ifClickWithPauseButtom() ) {
                m_Jump_Page->PausePage();
            }
            if ( m_Jump_Page->ifClickWithContinueButtom() ) {
                m_Jump_Page->AllDisappear();
            }
            if ( m_Jump_Page->ifClickWithStopButtom() ) {
                m_Jump_Page->AllDisappear();
                m_PRM->NextPhase(PHASE_HOME_PAGE);
                RemoveStage( 1 );
                m_Phase = Phase::HOME_PAGE;
                m_Stage_Object[1]->DisAppearAll();
                stage_point_counter[1] = 0;
                m_stage_pos = 0;
                m_Text_Point->SetVisible( false );
            }
            if ( m_Jump_Page->ifClickWithCancelButtomInEnd() ) {
                m_Jump_Page->AllDisappear();
                m_PRM->NextPhase(PHASE_HOME_PAGE);
                RemoveStage( 1 );
                m_Phase = Phase::HOME_PAGE;
                AppearHomePage();
                stage_point_counter[1] = 0;
                m_stage_pos = 0;
            }
            break;
        case Phase::STAGE_2:
            m_Jump_Page->m_Pause_Buttom->SetVisible( true );
            if (PhaseStage( m_Stage_Object[2], m_Stage_Object[2]->GetSize() , m_Text_Point , 2)){
                m_Stage_Object[2]->DisAppearAll();
                m_Text_Point->SetVisible( false );
                ifClear[2] = true;
                m_Jump_Page->EndPage( 1 );
            } 
            else if ( m_Text_Point->GetMove() <= 0 ) {
                m_Stage_Object[2]->DisAppearAll();
                m_Text_Point->SetVisible( false );
                ifClear[2] = true;
                m_Jump_Page->EndPage( 1 );
            }
            else if ( currentPhase == PHASE_PAUSE_FOR_DISAPPEAR ) {
                if ( (std::chrono::steady_clock::now() - startTime) >= std::chrono::seconds(1)) {
                    currentPhase = PHASE_DROPPING;
                }
                m_Root.Update();
            }
            else if ( currentPhase == PHASE_DROPPING ) {
                m_Stage_Object[2]->Dropping();
                m_Text_Point->SetPoint( stage_point_counter[2] );
                m_Text_Point->SetGoal( stage_goal_counter[2] );
                m_Text_Point->UpdateText();
            }
            if ( m_Jump_Page->ifClickWithPauseButtom() ) {
                m_Jump_Page->PausePage();
            }
            if ( m_Jump_Page->ifClickWithContinueButtom() ) {
                m_Jump_Page->AllDisappear();
            }
            if ( m_Jump_Page->ifClickWithStopButtom() ) {
                m_Jump_Page->AllDisappear();
                m_PRM->NextPhase(PHASE_HOME_PAGE);
                RemoveStage( 2 );
                m_Phase = Phase::HOME_PAGE;
                m_Stage_Object[2]->DisAppearAll();
                stage_point_counter[2] = 0;
                m_stage_pos = 0;
                m_Text_Point->SetVisible( false );
            }
            if ( m_Jump_Page->ifClickWithCancelButtomInEnd() ) {
                m_Jump_Page->AllDisappear();
                m_PRM->NextPhase(PHASE_HOME_PAGE);
                RemoveStage( 2 );
                m_Phase = Phase::HOME_PAGE;
                AppearHomePage();
                stage_point_counter[2] = 0;
                m_stage_pos = 0;
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