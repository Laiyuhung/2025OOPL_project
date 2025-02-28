#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

#include "Util/GameObject.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

class Character : public Util::GameObject {
public:
    explicit Character(const std::string& ImagePath);

    Character(const Character&) = delete;

    Character(Character&&) = delete;

    Character& operator=(const Character&) = delete;

    Character& operator=(Character&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    glm::vec2 GetSize() { return this->m_Size; }

    void SetSize( glm::vec2 size ) { this->m_Size = size; }

    // TODO: Implement the collision detection
    [[nodiscard]] bool IfCollides(const std::shared_ptr<Character>& other) const {
        if (!other) return false;  
        glm::vec2 posA = GetPosition();
        glm::vec2 sizeA = this -> m_Size;
    
        glm::vec2 posB = other->GetPosition();
        glm::vec2 sizeB = this -> m_Size;
    
        bool collisionX = (posA.x < posB.x + sizeB.x) && (posA.x + sizeA.x > posB.x);
        bool collisionY = (posA.y < posB.y + sizeB.y) && (posA.y + sizeA.y > posB.y);
    
        return collisionX && collisionY;
    }
    
    [[nodiscard]] bool IfClick() {
        glm::vec2 mousePos = Util::Input::GetCursorPosition();
    
        glm::vec2 pos = GetPosition();
        glm::vec2 size = this -> m_Size; 
        bool insideX = (mousePos.x >= pos.x && mousePos.x <= pos.x + size.x);
        bool insideY = (mousePos.y >= pos.y && mousePos.y <= pos.y + size.y);
        bool isClicked = Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB);
    
        return insideX && insideY && isClicked;
    }
    

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    glm::vec2 m_Size = { 50.0f, 100.0f };
    std::string m_ImagePath;
};


#endif //CHARACTER_HPP
