#include "PhaseResourceManager.hpp"

#include "Util/Logger.hpp"

PhaseResourceManager::PhaseResourceManager() {
    // m_TaskText = std::make_shared<TaskText>();
    m_Background = std::make_shared<BackgroundImage>();
}

void PhaseResourceManager::NextPhase(int m_Phase) {
    if (m_Phase == 7) return;
    LOG_DEBUG("Passed! Next phase: {}", m_Phase);
    // m_Background->NextPhase(m_Phase);
    // m_TaskText->NextPhase(m_Phase++);
}
