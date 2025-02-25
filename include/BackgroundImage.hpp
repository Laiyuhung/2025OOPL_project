#ifndef BACKGROUND_IMAGE_HPP
#define BACKGROUND_IMAGE_HPP

#include <filesystem>
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class BackgroundImage : public Util::GameObject {
public:
    BackgroundImage() : GameObject(
            std::make_unique<Util::Image>(GA_RESOURCE_DIR "/Image/Background/InitialImage.png"), -1) {
        AdjustSize();  // 初始化時調整大小
    }

    void NextPhase(const int phase) {
        auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
        if (temp) {
            temp->SetImage(ImagePath(phase));
            AdjustSize();  // 切換圖片時自動調整大小
        }
    }

private:
    void AdjustSize() {
        // 直接指定 scale，避免黑邊或變形
        this->GetTransform().scale = glm::vec2(0.5, 1.0);  // 放大 1.5 倍
    }

    inline std::string ImagePath(const int phase) {
        return GA_RESOURCE_DIR "/Image/Background/" + std::to_string(phase) + ".png";
    }
};

#endif // BACKGROUND_IMAGE_HPP
