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
    InitializeStage3();
    InitializeStage4();
    InitializeStage5();
    InitializeStage6();
    InitializeStage7();

    startTime = std::chrono::steady_clock::now();
    m_Stage_Object.resize( 13 );

    m_BGM_Music.resize(1);
    m_BGM_Music.at(0) = std::make_shared<Music>(GA_RESOURCE_DIR "/Music/springDayShadow.mp3");
    m_BGM_Music.at(0)->Pause();
    m_BGM_Music.at(0)->SetVolume(30);

    m_Start_initial = std::make_shared<Character>(GA_RESOURCE_DIR "/Image/GameObject/initailStartButton.png");
    m_Start_initial->SetPosition({0, -160.5f});
    m_Start_initial->SetZIndex(10);
    m_Root.AddChild(m_Start_initial);

    m_Stage_Buttoms.resize(13);
    const std::vector<std::string> levelImages = {
        "", LEVEL_ONE_IMAGE, LEVEL_TWO_IMAGE, LEVEL_THREE_IMAGE, LEVEL_FOUR_IMAGE,
        LEVEL_FIVE_IMAGE, LEVEL_SIX_IMAGE, LEVEL_SEVEN_IMAGE, LEVEL_EIGHT_IMAGE,
        LEVEL_NINE_IMAGE, LEVEL_TEN_IMAGE, LEVEL_ELEVEN_IMAGE, LEVEL_TWELVE_IMAGE
    };
    for (int i = 1; i < 13; ++i) {
        m_Stage_Buttoms.at(i) = std::make_shared<Character>(levelImages.at(i));
        m_Stage_Buttoms.at(i)->SetPosition(stage_position[i]);
        m_Stage_Buttoms.at(i)->SetZIndex(10);
        m_Stage_Buttoms.at(i)->SetVisible(false);
        m_Root.AddChild(m_Stage_Buttoms.at(i));
    }

    m_Jump_Page = std::make_shared<JumpPage>(GA_RESOURCE_DIR "/Image/Background/stage1Start.png");
    m_Jump_Page->SetVisible(false);
    m_Jump_Page->SetPosition({0, 0});
    m_Jump_Page->SetZIndex(12);
    m_Jump_Page->SetSize({5, 5});
    m_Root.AddChild(m_Jump_Page);

    m_Root.AddChild(m_Jump_Page->GetPlayButtom());
    m_Root.AddChild(m_Jump_Page->GetCancelButtom());
    m_Root.AddChild(m_Jump_Page->GetPauseButtom());
    m_Root.AddChild(m_Jump_Page->GetStopButtom());
    m_Root.AddChild(m_Jump_Page->GetContinueButtom());
    m_Root.AddChild(m_Jump_Page->GetInfoButtom());

    m_Text_Point = std::make_shared<TaskText>();
    m_Text_Point->SetPosition({-125, 210});
    m_Text_Point->Initial(0);
    m_Text_Point->UpdateText();
    m_Text_Point->SetVisible(false);
    m_Root.AddChild(m_Text_Point);

    m_Tools.resize(3);
    m_Tools.at( HAMMER ) = std::make_shared<Item>( HAMMER_IMAGE );
    m_Tools.at( MAGIC_STICK ) = std::make_shared<Item>( MAGIC_STICK_IMAGE );
    m_Tools.at( GLOVES ) = std::make_shared<Item>( GLOVES_IMAGE );
    
    for ( int i = 0 ; i < 3 ; ++i ) {
        m_Tools.at(i)->SetUp( i );
        m_Root.AddChild( m_Tools.at(i)->GetText() );
        m_Root.AddChild( m_Tools.at(i) );
    }
    

    m_PRM = std::make_shared<PhaseResourceManager>();
    m_Root.AddChildren(m_PRM->GetChildren());

    m_CurrentState = State::UPDATE;
    m_BGM_Music.at(0)->Playing(GA_RESOURCE_DIR "/Music/aveMujica.mp3");

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
                m_Tools[0]->Disappear();
                m_Tools[1]->Disappear();
                m_Tools[2]->Disappear();

                int get_stage = PhaseHomePage(m_Stage_Buttoms);
                if ( get_stage != 0 ){
                    m_stage_pos = get_stage;
                    m_Jump_Page->PlayPage( m_stage_pos );
                    m_Jump_Page->SetStatus( JUMP_PLAY );
                } 
                if ( m_Jump_Page->ifClickWithPlayButtom() ) {
                    SetUpStage( m_stage_pos );
                    if ( m_stage_pos >= 1 && m_stage_pos <= 7 ) { 
                        m_Stage_Object[m_stage_pos]->SetUp( m_stage_pos );
                        m_Stage_Object[m_stage_pos]->AppearAll();
                        m_Stage_Object[m_stage_pos]->SetStage( m_stage_pos );
                        m_Text_Point->Initial( m_stage_pos );
                        m_Jump_Page->AllDisappear();
                        currentPhase = PHASE_NORMAL;
                        if ( m_stage_pos == 1  ) {
                            std::cout << "Level1 Character clicked!" << std::endl;
                            m_PRM->NextPhase(PHASE_STAGE_1);
                            m_Tools[0]->Appear();
                            m_Tools[1]->Appear();
                            m_Tools[2]->Appear();
                            m_Phase = Phase::STAGE_1;
                        }
                        else if ( m_stage_pos == 2 ) {
                            std::cout << "Level2 Character clicked!" << std::endl;
                            m_PRM->NextPhase(PHASE_STAGE_2);
                            m_Phase = Phase::STAGE_2;
                        }
                        else if ( m_stage_pos == 3 ) {
                            std::cout << "Level3 Character clicked!" << std::endl;
                            m_PRM->NextPhase(PHASE_STAGE_3);
                            m_Phase = Phase::STAGE_3;
                        }
                        else if ( m_stage_pos == 4 ) {
                            std::cout << "Level4 Character clicked!" << std::endl;
                            m_PRM->NextPhase(PHASE_STAGE_4);
                            m_Phase = Phase::STAGE_4;
                        }
                        else if ( m_stage_pos == 5 ) {
                            std::cout << "Level5 Character clicked!" << std::endl;
                            m_PRM->NextPhase(PHASE_STAGE_5);
                            // m_Stage_Object[5]->GetStageObject()[37]->SetImage( RAINBOWBALL_OBJECT_LINK );
                            // m_Stage_Object[5]->GetStageObject()[37]->SetBlockType( NORMAL_OBJECT );
                            // m_Stage_Object[5]->GetStageObject()[37]->SetCurrentType( RAINBOWBALL_OBJECT );
                            // m_Stage_Object[5]->GetStageObject()[37]->SetBlock( NO_COLOR );
                            // m_Stage_Object[5]->GetStageObject()[37]->SetAppearBool( true );
                            // m_Stage_Object[5]->GetStageObject()[37]->SetGenerate( true );
                            m_Phase = Phase::STAGE_5;
                        }
                        else if ( m_stage_pos == 6 ) {
                            std::cout << "Level6 Character clicked!" << std::endl;
                            m_PRM->NextPhase(PHASE_STAGE_6);
                            m_Phase = Phase::STAGE_6;
                        }
                        else if ( m_stage_pos == 7 ) {
                            std::cout << "Level7 Character clicked!" << std::endl;
                            m_PRM->NextPhase(PHASE_STAGE_7);
                            m_Phase = Phase::STAGE_7;
                        }
                    }
                }
                if ( m_Jump_Page->ifClickWithInfoButtom() ) {
                    m_Jump_Page->AllDisappear();
                    m_Jump_Page->InfoPage( m_stage_pos );
                }
                if ( m_Jump_Page->ifClickWithCancelButtom() && m_Jump_Page->GetStatus() == JUMP_INFO ) {
                    m_Jump_Page->AllDisappear();
                    m_Jump_Page->PlayPage( m_stage_pos );
                    m_Jump_Page->SetStatus( JUMP_PLAY );
                }
                else if (m_Jump_Page->ifClickWithCancelButtom() && m_Jump_Page->GetStatus() == JUMP_PLAY ) {
                    m_Jump_Page->AllDisappear();
                    m_Jump_Page->SetStatus( JUMP_NORMAL );
                    m_stage_pos = 0;
                }
            }
            break;

        case Phase::STAGE_1:
            Stage( 1 );
            break;

        case Phase::STAGE_2:
            Stage( 2 );
            break;

        case Phase::STAGE_3:
            Stage( 3 );
            break;

        case Phase::STAGE_4:
            Stage( 4 );
            break;

        case Phase::STAGE_5:
            Stage( 5 );
            break;

        case Phase::STAGE_6:
            Stage( 6 );
            break;
        
        case Phase::STAGE_7:
            Stage( 7 );
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