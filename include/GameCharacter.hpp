#ifndef GAME_CHARACTER_HPP
#define GAME_CHARACTER_HPP

#include <string>
#include "Character.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

class GameCharacter : public Character {
public:
    GameCharacter(const std::string& ImagePath) 
        : Character(ImagePath), m_ImagePath(ImagePath) { }

    virtual ~GameCharacter() = default; 

    void Appear() {
        this->SetVisible(true);
    }

    void DisAppear() {
        this->SetVisible(false);
    }
    void Drop(glm::vec2 MoveVector = {0 , 1}, glm::vec2 GoalPosition) {
        while (true) {
            glm::vec2 NextPos = this->GetPosition();
            if (NextPos.y == GoalPosition.y && NextPos.x == GoalPosition.x) {
                return;
            }
            NextPos.x += MoveVector.x;
            NextPos.y += MoveVector.y;
            this->SetPosition(NextPos);
        }
    }
    virtual void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }
    virtual void SetImage(const std::string& ImagePath);

protected:
    void ResetPosition() { 
        m_Transform.translation = {0, 0}; 
    }

    glm::vec2 m_Size = { 50.0f, 100.0f };
    std::string m_ImagePath;
};

#endif // GAME_CHARACTER_HPP
