#include "App.hpp"
#include "PhaseResourceManager.hpp"
#include "Global.hpp"
#include "Util/Logger.hpp"

PhaseResourceManager::PhaseResourceManager() {
    // m_TaskText = std::make_shared<TaskText>();
    m_Background = std::make_shared<BackgroundImage>();
}

void PhaseResourceManager::NextPhase(int Phase) {
    if (Phase == 7) return;
    LOG_DEBUG("Passed! Next phase: {}", Phase);
    switch (Phase){
        case PHASE_HOME_PAGE:
            m_Background->NextImage("homePage.png");
            m_Phase = Phase;
            break; 
        case PHASE_STAGE_1:
            m_Background->NextImage("first.png");
            m_Phase = Phase;
            break;
        case PHASE_STAGE_2:
            m_Background->NextImage("second.png");
            m_Phase = Phase;
            break;
        case PHASE_STAGE_3:
            m_Background->NextImage("third.png");
            m_Phase = Phase;
            break;
    }
    // m_TaskText->NextPhase(m_Phase++);
}
