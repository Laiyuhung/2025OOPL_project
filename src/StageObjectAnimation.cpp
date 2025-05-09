#include "StageObject.hpp"
#include "Global.hpp"
#include "Util/Time.hpp"
#include <iostream>
#include <algorithm>

void StageObject::PrepareDropAnimation(int sourcePos, int targetPos) {
    // Create a new animation entry
    DroppingAnimation anim;
    anim.sourcePos = sourcePos;
    anim.targetPos = targetPos;
    anim.startPosition = m_Stage_Object[sourcePos]->GetPosition();
    anim.targetPosition = m_Stage_Object[targetPos]->GetPosition();
    anim.progress = 0.0f;

    // Add to active animations
    m_ActiveAnimations.push_back(anim);
    
    // Mark that we have animations in progress
    m_AnimationsComplete = false;
}

void StageObject::UpdateDropAnimations() {
    if (m_ActiveAnimations.empty()) {
        return;
    }

    // Calculate delta time for smooth animation
    const float deltaTime = static_cast<float>(Util::Time::GetDeltaTimeMs()) / 1000.0f;
    const float stepAmount = m_AnimationSpeed * deltaTime * 10.0f; // Adjust for desired speed
    
    bool allComplete = true;
    
    // Update all active animations
    for (auto& anim : m_ActiveAnimations) {
        // Update progress
        anim.progress += stepAmount;
        
        if (anim.progress >= 1.0f) {
            // Animation complete
            anim.progress = 1.0f;
        } else {
            allComplete = false;
        }
        
        // Calculate interpolated position
        glm::vec2 currentPos = anim.startPosition + (anim.targetPosition - anim.startPosition) * anim.progress;
        
        // Update object visual position (without changing logical position yet)
        m_Stage_Object[anim.sourcePos]->SetPosition(currentPos);
    }
    
    // Check if all animations are complete
    if (allComplete) {
        // Process all completed animations
        for (const auto& anim : m_ActiveAnimations) {
            CompleteDropAnimation(anim);
        }
        
        // Clear the animations list
        m_ActiveAnimations.clear();
        m_AnimationsComplete = true;
        
        // Continue with normal game flow
        currentPhase = PHASE_NORMAL;
    }
}

void StageObject::CompleteDropAnimation(const DroppingAnimation& anim) {
    int sourcePos = anim.sourcePos;
    int targetPos = anim.targetPos;
    
    // Complete the logical swap that was prepared in Dropping_method
    bool flag = m_Stage_Object[targetPos]->GetAppearBool();
    
    // Exchange information between objects
    m_Stage_Object[sourcePos]->SwitchPosition(m_Stage_Object[targetPos]);
    
    // Swap the objects
    std::shared_ptr<GameCharacter> NewObject = m_Stage_Object[sourcePos];
    m_Stage_Object[sourcePos] = m_Stage_Object[targetPos];
    m_Stage_Object[targetPos] = NewObject;
    
    // Update appearance state
    m_Stage_Object[sourcePos]->SetAppearBool(flag);
}
