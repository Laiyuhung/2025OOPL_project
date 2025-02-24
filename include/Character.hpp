#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

#include "Util/GameObject.hpp"

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

    // TODO: Implement the collision detection
    [[nodiscard]] bool IfCollides(const std::shared_ptr<Character>& other) const {
        if (!other) return false;  
        glm::vec2 posA = GetPosition();
        glm::vec2 sizeA = {50.0f, 100.0f};
    
        glm::vec2 posB = other->GetPosition();
        glm::vec2 sizeB = {50.0f, 100.0f};
    
        bool collisionX = (posA.x < posB.x + sizeB.x) && (posA.x + sizeA.x > posB.x);
        bool collisionY = (posA.y < posB.y + sizeB.y) && (posA.y + sizeA.y > posB.y);
    
        return collisionX && collisionY;
    }
    

    // TODO: Add and implement more methods and properties as needed to finish Giraffe Adventure.

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;
};


#endif //CHARACTER_HPP
