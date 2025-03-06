#include "GameCharacter.hpp"
#include "Util/Image.hpp"


GameCharacter::GameCharacter(const std::string& ImagePath) {
    SetImage(ImagePath);
    ResetPosition();
}

void GameCharacter::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}
