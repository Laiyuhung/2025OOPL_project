#ifndef BACKGROUND_IMAGE_HPP
#define BACKGROUND_IMAGE_HPP

#include <filesystem>
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class BackgroundImage : public Util::GameObject {
public:
    BackgroundImage() : GameObject(
            std::make_unique<Util::Image>(GA_RESOURCE_DIR "/Image/Background/InitialImage.png"), -1) {
            SetPivot(glm::vec2(0.1f, 0.5f));
    }

    void NextImage(const std::string phase) {
        auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
        if (temp) {
            temp->SetImage(ImagePath(phase));
        }
    }
    void Draw(const Core::Matrices &data) {
        Core::Matrices modifiedData = data;
        modifiedData.m_Model = ComputeScaleMatrix() * modifiedData.m_Model;  

        auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
        if (temp) {
            temp->Draw(modifiedData);
        }
    }

private:
    glm::vec2 GetScreenSize() {
        int width = 1920, height = 1080;
        SDL_Window* window = SDL_GL_GetCurrentWindow();
        if (window) {
            SDL_GetWindowSize(window, &width, &height);
        }
        return glm::vec2(width, height);
    }
    glm::mat4 ComputeScaleMatrix() {
        glm::vec2 screenSize = GetScreenSize();
        auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
        if (!temp) return glm::mat4(1.0f);

        glm::vec2 imageSize = temp->GetSize();

        float scaleX = screenSize.x / imageSize.x;
        float scaleY = screenSize.y / imageSize.y;
        float finalScale = std::min(scaleX, scaleY); 

        return glm::scale(glm::mat4(1.0f), glm::vec3(finalScale, finalScale, 1.0f));
    }
    inline std::string ImagePath(const std::string phase) {
        return (GA_RESOURCE_DIR "/Image/Background/" + phase + ".png" );
    }
};

#endif // BACKGROUND_IMAGE_HPP