#include "Character.hpp"
#include "Global.hpp"

class JumpPage : public Character {
    public:
        JumpPage(const std::string& ImagePath);
        virtual void SetImage(const std::string& ImagePath);

        void AllDisappear() {
            m_Play_Buttom->SetVisible( false );
            m_Cancel_Buttom->SetVisible( false );
            m_Pause_Buttom->SetVisible( false );
            m_Continue_Buttom->SetVisible( false );
            m_Stop_Buttom->SetVisible( false );
            this->SetVisible( false );
        }
        void PlayPage( int stage ) {
            AllDisappear();
            m_Play_Buttom->SetVisible( true );
            m_Cancel_Buttom->SetVisible( true );
            if ( stage == 1 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage1Start.png" );
            else if ( stage == 2 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage2Start.png" );
            this->SetVisible( true );
            SetStatus( JUMP_PLAY );
        }

        void EndPage( int stage ) {
            AllDisappear();
            m_Cancel_Buttom->SetVisible( true );
            if ( stage == 1 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage1End.png" );
            else if ( stage == 2 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage2End.png" );
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
        int m_Status;
        std::string m_ImagePath;
        std::shared_ptr<Character> m_Play_Buttom;
        std::shared_ptr<Character> m_Cancel_Buttom;
        std::shared_ptr<Character> m_Pause_Buttom;
        std::shared_ptr<Character> m_Continue_Buttom;
        std::shared_ptr<Character> m_Stop_Buttom;
        inline std::string ImagePath(const std::string& phase) {
            return (GA_RESOURCE_DIR "/Image/Background/" + phase );
        }
};