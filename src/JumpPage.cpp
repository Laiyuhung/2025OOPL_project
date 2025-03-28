#include "JumpPage.hpp"
#include "Util/Image.hpp"


JumpPage::JumpPage(const std::string& ImagePath)
        : Character(ImagePath), m_ImagePath(ImagePath) {
            m_Play_Buttom = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/GameObject/playButtom.png");
            m_Play_Buttom->SetPosition( { 60.5, -120.5f } );
            m_Play_Buttom->SetZIndex( 13 );
            m_Play_Buttom->SetVisible(false);
            
            m_info_Buttom = std::make_shared<Character>( GA_RESOURCE_DIR"/Image/GameObject/informationButton.png" );
            m_info_Buttom->SetPosition( {-50.5, -120.5f} );
            m_info_Buttom->SetZIndex( 14 );
            m_info_Buttom->SetVisible(false);
            
            m_Cancel_Buttom = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/GameObject/closeButton.png");
            m_Cancel_Buttom->SetPosition( { 100, 146 } );
            m_Cancel_Buttom->SetZIndex( 13 );
            m_Cancel_Buttom->SetVisible(false);
        
            m_Pause_Buttom = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/GameObject/pauseButton.png");
            m_Pause_Buttom->SetPosition( { -114.5, -258 } );
            m_Pause_Buttom->SetZIndex( 13 );
            m_Pause_Buttom->SetVisible(false);
        
            m_Continue_Buttom = std::make_shared<Character>( GA_RESOURCE_DIR"/Image/GameObject/continueButtom.png");
            m_Continue_Buttom->SetPosition( {0 , 30} );
            m_Continue_Buttom->SetZIndex( 14 );
            m_Continue_Buttom->SetVisible(false);
        
            m_Stop_Buttom = std::make_shared<Character>( GA_RESOURCE_DIR"/Image/GameObject/stopButtom.png" );
            m_Stop_Buttom->SetPosition( {0 , -30} );
            m_Stop_Buttom->SetZIndex( 14 );
            m_Stop_Buttom->SetVisible(false);

        }

void JumpPage::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}
        