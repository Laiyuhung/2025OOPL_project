#ifndef GAME_CHARACTER_HPP
#define GAME_CHARACTER_HPP

#include <string>
#include <iostream>

#include "Character.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

class GameCharacter : public Character {
public:
    GameCharacter(const std::string& ImagePath);

    virtual ~GameCharacter() = default; 

    void Appear() {
        this->SetVisible(true);
    }

    void DisAppear() {
        this->SetVisible(false);
    }
    void Drop(glm::vec2 MoveVector = {0 , 1}, glm::vec2 GoalPosition = {0, 0}) {
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
    void DebugMode(int Speed) {
        glm::vec2 NextPos = this->GetPosition();
        if (Util::Input::IsKeyDown(Util::Keycode::UP) )
            NextPos.y += Speed;
        if (Util::Input::IsKeyDown(Util::Keycode::DOWN) )
            NextPos.y -= Speed;
        if (Util::Input::IsKeyDown(Util::Keycode::LEFT) )
            NextPos.x -= Speed;
        if (Util::Input::IsKeyDown(Util::Keycode::RIGHT) )
            NextPos.x += Speed;

        this->SetPosition( NextPos ); 
        std::cout << "x : " << NextPos.x << " y : " << NextPos.y << "\n";
    }
    void SwitchPosition( std::shared_ptr<Character>& other ) {
        glm::vec2 temp = this->GetPosition();
        this->SetPosition( other->GetPosition() );
        other->SetPosition( temp );
    }

    std::shared_ptr<Character> Clone() const override {
        return std::make_shared<GameCharacter>(*this);
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
