#include "AppUtil.hpp"
#include "App.hpp"

#include "Util/Logger.hpp"

/**
 * @brief The function to validate the tasks.
 * @warning Do not modify this function.
 * @note See README.md for the task details.
 */
void App::ValidTask() {
    bool isBeeLooping;
    bool isBeePlaying;
    LOG_DEBUG("Validating the task {}", static_cast<int>(m_Phase));
    switch (m_Phase) {
        case Phase::INITIAL_IMAGE:
            if ( true ) {
                LOG_DEBUG("Congratulations! You have completed Giraffe Adventure!");
                m_CurrentState = State::END;
            } else{
                LOG_DEBUG("The ball animation is not ended");
            }
            break;
    }
}
