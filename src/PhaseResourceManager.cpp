#include "PhaseResourceManager.hpp"

#include "Util/Logger.hpp"

#define PHASE_INITIAL_IMAGE 1
#define PHASE_HOME_PAGE 2


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

    }
    // m_TaskText->NextPhase(m_Phase++);
}
