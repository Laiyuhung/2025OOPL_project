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
            m_Cancel_Buttom->SetSize( {100, 100} );
            m_Cancel_Buttom->SetVisible(false);
        
            m_Pause_Buttom = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/GameObject/pauseButton.png");
            m_Pause_Buttom->SetPosition( { -114.5, -258 } );
            m_Pause_Buttom->SetZIndex( 13 );
            m_Pause_Buttom->SetVisible(false);
        
            m_Continue_Buttom = std::make_shared<Character>( GA_RESOURCE_DIR"/Image/GameObject/continueButtom.png");
            m_Continue_Buttom->SetPosition( {0 , 30} );
            m_Continue_Buttom->SetZIndex( 14 );
            m_Continue_Buttom->SetVisible(false);
        
            m_BGM_Buttom = std::make_shared<Character>( GA_RESOURCE_DIR"/Image/GameObject/on.png" );
            m_BGM_Buttom->SetPosition( {0 , 0} );
            m_BGM_Buttom->SetZIndex( 14 );
            m_BGM_Buttom->SetVisible(false);

            // m_Plus_Buttom_1 = std::make_shared<Character>( GA_RESOURCE_DIR"/Image/GameObject/plus.png" );
            // m_Plus_Buttom_1->SetPosition( {0 , -30} );
            // m_Plus_Buttom_1->SetZIndex( 14 );
            // m_Plus_Buttom_1->SetVisible(false);

            // m_Plus_Buttom_2 = std::make_shared<Character>( GA_RESOURCE_DIR"/Image/GameObject/plus.png" );
            // m_Plus_Buttom_2->SetPosition( {0 , -30} );
            // m_Plus_Buttom_2->SetZIndex( 14 );
            // m_Plus_Buttom_2->SetVisible(false);

            // m_Plus_Buttom_3 = std::make_shared<Character>( GA_RESOURCE_DIR"/Image/GameObject/plus.png" );
            // m_Plus_Buttom_3->SetPosition( {0 , -30} );
            // m_Plus_Buttom_3->SetZIndex( 14 );
            // m_Plus_Buttom_3->SetVisible(false);
        }

void JumpPage::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}
        