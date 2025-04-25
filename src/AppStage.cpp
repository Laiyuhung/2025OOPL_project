#include "App.hpp"
#include "Global.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Stage( int stage_pos ) {
    m_Jump_Page->GetPauseButtom()->SetVisible( true );
    if (stage_goal_counter[stage_pos] <= 0 || PhaseStage( m_Stage_Object[stage_pos], m_Stage_Object[stage_pos]->GetSize() , m_Text_Point , stage_pos , m_Tools )){
        m_Stage_Object[stage_pos]->DisAppearAll();
        m_Text_Point->SetVisible( false );
        ifClear[stage_pos] = true;
        m_Jump_Page->EndPage( stage_pos );
        m_Jump_Page->SetStatus( JUMP_END );
    }
    else if ( currentPhase == PHASE_ITEM_USED ) {
        for ( int i = 0 ; i < 3 ; ++i ) {
            if ( m_Tools.at(i)->Click() ) {
                if ( i == HAMMER ) {
                    m_Stage_Object.at(stage_pos)->UseHammer( m_Tools.at( HAMMER ));
                }
                // else if ( i == MAGIC_STICK ) {
                //     m_Stage_Object.at(stage_pos)->UseMagicStick( m_Tools.at( MAGIC_STICK ) );
                // }
                // else if ( i == GLOVES ) {
                //     m_Stage_Object.at(stage_pos)->UseMagicGlove( m_Tools.at( GLOVES ) );
                // }
            }
        }
    }
    else if ( (m_Text_Point->GetMove() <= 0 && stage_goal_counter[stage_pos] > 0) && currentPhase == PHASE_NORMAL ) {
        m_Stage_Object[stage_pos]->DisAppearAll();
        m_Text_Point->SetVisible( false );
        ifClear[stage_pos] = false;
        m_Jump_Page->FailPage( stage_pos );
    }
    else if ( currentPhase == PHASE_PAUSE_FOR_DISAPPEAR ) {
        if ( (std::chrono::steady_clock::now() - startTime) >= std::chrono::seconds(1)) {
            currentPhase = PHASE_DROPPING;
        }
        m_Root.Update();
    }
    else if ( currentPhase == PHASE_DROPPING ) {
        m_Stage_Object[stage_pos]->Dropping( stage_pos , stage_pos , false );
        m_Text_Point->SetPoint( stage_point_counter[stage_pos] );
        m_Text_Point->SetGoal( stage_goal_counter[stage_pos] );
        if ( stage_pos != 3 && stage_pos != 4 )
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
        RemoveStage( stage_pos );
        m_Phase = Phase::HOME_PAGE;
        AppearHomePage();
        m_Stage_Object[stage_pos]->DisAppearAll();
        stage_point_counter[stage_pos] = 0;
        m_stage_pos = 0;
        m_Text_Point->SetVisible( false );
    }
    if ( m_Jump_Page->ifClickWithCancelButtomInEnd() ) {
        m_Jump_Page->AllDisappear();
        m_PRM->NextPhase(PHASE_HOME_PAGE);
        RemoveStage( stage_pos );
        m_Phase = Phase::HOME_PAGE;
        AppearHomePage();
        stage_point_counter[stage_pos] = 0;
        m_stage_pos = 0;
    }
}