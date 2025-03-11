#ifndef TASKTEXT_HPP
#define TASKTEXT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include "Util/Color.hpp"
#include <string>

class TaskText : public Util::GameObject {
public:
    TaskText() : GameObject(
            std::make_unique<Util::Text>(GA_RESOURCE_DIR "/Font/Inkfree.ttf", 50,
                                         append_string_views("0", ""),
                                         Util::Color::FromName(Util::Colors::WHITE)),
            100) {
        m_Transform.translation = {0.0F, -270.F};
    }

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    void SetValue(int value) {
        this->m_value = value;
    }

    void UpdateText() {  
        auto* temp = dynamic_cast<Util::Text*>(m_Drawable.get());
        if (temp) {
            temp->SetText(show_string(this->m_value));
        }
    }

private:
    inline static std::string append_string_views(const std::string& sv1, const std::string& sv2) {
        return sv1 + "\n" + sv2;
    }

    inline static std::string show_string(int s) {
        return std::to_string(s) + "\n";
    }

    int m_value = 0;
};

#endif // TASKTEXT_HPP
