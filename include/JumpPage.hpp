#include "Character.hpp"
#include "Global.hpp"

class JumpPage : public Character {
    public:
        JumpPage(const std::string& ImagePath);
        virtual void SetImage(const std::string& ImagePath);

        std::shared_ptr<Character> GetPlayButtom() {
            return m_Play_Buttom;
        }
        
        std::shared_ptr<Character> GetCancelButtom() {
            return m_Cancel_Buttom;
        }

        std::shared_ptr<Character> GetPauseButtom() {
            return m_Pause_Buttom;
        }

        std::shared_ptr<Character> GetContinueButtom() {
            return m_Continue_Buttom;
        }

        std::shared_ptr<Character> GetStopButtom() {
            return m_Stop_Buttom;
        }

        std::shared_ptr<Character> GetInfoButtom() {
            return m_info_Buttom;
        }     
        
        std::shared_ptr<Character> GetBGMButtom() {
            return m_BGM_Buttom;
        }   

        // std::shared_ptr<Character> GetPlusButtom1() {
        //     return m_Plus_Buttom_1;
        // }   

        // std::shared_ptr<Character> GetPlusButtom2() {
        //     return m_Plus_Buttom_2;
        // }   

        // std::shared_ptr<Character> GetPlusButtom3() {
        //     return m_Plus_Buttom_3;
        // }   

        void AllDisappear() {
            m_Play_Buttom->SetVisible( false );
            m_Cancel_Buttom->SetVisible( false );
            m_Pause_Buttom->SetVisible( false );
            m_Continue_Buttom->SetVisible( false );
            m_Stop_Buttom->SetVisible( false );
            m_info_Buttom->SetVisible( false );
            // m_Plus_Buttom_1->SetVisible( false );
            // m_Plus_Buttom_2->SetVisible( false );
            // m_Plus_Buttom_3->SetVisible( false );
            m_BGM_Buttom->SetVisible( false );
            this->SetVisible( false );
        }

        void SettingPage() {
            m_Cancel_Buttom->SetVisible( true );
            // m_Plus_Buttom_1->SetVisible( true );
            // m_Plus_Buttom_2->SetVisible( true );
            // m_Plus_Buttom_3->SetVisible( true );
            m_BGM_Buttom->SetVisible( true );
            this->SetImage( GA_RESOURCE_DIR"/Image/Background/setting.png" );
            this->SetVisible( true );
            SetStatus( JUMP_SETTING );
        }

        void InfoPage( int stage ) {
            m_Cancel_Buttom->SetVisible( true );
            std::string path = "stage" + std::to_string( stage ) + "Info.png";
            this->SetImage( GA_RESOURCE_DIR"/Image/Background/" + path );
            this->SetVisible( true );
            SetStatus( JUMP_INFO );
        }
        void PlayPage( int stage ) {
            AllDisappear();
            m_Play_Buttom->SetVisible( true );
            m_Cancel_Buttom->SetVisible( true );
            m_info_Buttom->SetVisible( true );
            std::string path = "stage" + std::to_string( stage ) + "Start.png";
            this->SetImage( GA_RESOURCE_DIR"/Image/Background/" + path );
            this->SetVisible( true );
            SetStatus( JUMP_PLAY );
        }

        void EndPage( int stage ) {
            AllDisappear();
            m_Cancel_Buttom->SetVisible( true );
            std::string path = "stage" + std::to_string( stage ) + "End.png";
            this->SetImage( GA_RESOURCE_DIR"/Image/Background/" + path );
            SetStatus( JUMP_END );
            this->SetVisible( true );
        }

        void FailPage( int stage ) {
            AllDisappear();
            m_Cancel_Buttom->SetVisible( true );
            std::string path = "stage" + std::to_string( stage ) + "fail.png";
            this->SetImage( GA_RESOURCE_DIR"/Image/Background/" + path );
            SetStatus( JUMP_END );
            this->SetVisible( true );
        }

        void PausePage() {
            AllDisappear();
            m_Continue_Buttom->SetVisible( true );
            m_Stop_Buttom->SetVisible( true );
            this->SetImage( GA_RESOURCE_DIR"/Image/Background/pausePage.png" );
            SetStatus( JUMP_PAUSE );
            this->SetVisible( true );
        }

        void SetStatus( int status ) {
            m_Status = status;
        }

        int GetStatus() {
            return m_Status;
        }

        bool ifClickWithPlayButtom() { return m_Play_Buttom->GetVisibility() && m_Play_Buttom->IfClick(); }
        
        bool ifClickWithCancelButtom() { return m_Cancel_Buttom->GetVisibility() && m_Cancel_Buttom->IfClick(); }

        bool ifClickWithPauseButtom() { return m_Pause_Buttom->GetVisibility() && m_Pause_Buttom->IfClick(); }

        bool ifClickWithContinueButtom() { return m_Continue_Buttom->GetVisibility() && m_Continue_Buttom->IfClick(); }

        bool ifClickWithStopButtom() { return m_Stop_Buttom->GetVisibility() && m_Stop_Buttom->IfClick(); }

        bool ifClickWithCancelButtomInEnd() { return m_Cancel_Buttom->GetVisibility() && m_Cancel_Buttom->IfClick() && ( GetStatus() == JUMP_END ); }
        
        bool ifClickWithInfoButtom() { return m_info_Buttom->GetVisibility() && m_info_Buttom->IfClick(); }

        // bool ifClickWithPlus1() { return m_Plus_Buttom_1->GetVisibility() && m_Plus_Buttom_1->IfClick(); }

        // bool ifClickWithPlus2() { return m_Plus_Buttom_2->GetVisibility() && m_Plus_Buttom_2->IfClick(); }
    
        // bool ifClickWithPlus3() { return m_Plus_Buttom_3->GetVisibility() && m_Plus_Buttom_3->IfClick(); }

        
        bool ifClickWithBGM() { return m_BGM_Buttom->GetVisibility() && m_BGM_Buttom->IfClick(); }
private:
        int m_Status;
        std::string m_ImagePath;
        std::shared_ptr<Character> m_Play_Buttom;
        std::shared_ptr<Character> m_Cancel_Buttom;
        std::shared_ptr<Character> m_Pause_Buttom;
        std::shared_ptr<Character> m_Continue_Buttom;
        std::shared_ptr<Character> m_Stop_Buttom;
        std::shared_ptr<Character> m_info_Buttom;
        std::shared_ptr<Character> m_BGM_Buttom;
        // std::shared_ptr<Character> m_Plus_Buttom_1;
        // std::shared_ptr<Character> m_Plus_Buttom_2;
        // std::shared_ptr<Character> m_Plus_Buttom_3;

        inline std::string ImagePath(const std::string& phase) {
            return (GA_RESOURCE_DIR "/Image/Background/" + phase );
        }
};