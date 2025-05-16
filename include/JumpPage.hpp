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

        void AllDisappear() {
            m_Play_Buttom->SetVisible( false );
            m_Cancel_Buttom->SetVisible( false );
            m_Pause_Buttom->SetVisible( false );
            m_Continue_Buttom->SetVisible( false );
            m_Stop_Buttom->SetVisible( false );
            m_info_Buttom->SetVisible( false );
            this->SetVisible( false );
        }

        void InfoPage( int stage ) {
            m_Cancel_Buttom->SetVisible( true );
            if ( stage == 1 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage1Info.png");
            if ( stage == 2 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage2Info.png");
            if ( stage == 3 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage3Info.png");
            if ( stage == 4 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage4Info.png");
            if ( stage == 5 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage5Info.png");
            if ( stage == 6 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage6Info.png");
            if ( stage == 7 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage7Info.png");
            if ( stage == 8 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage8Info.png");
            if ( stage == 9 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage9Info.png");
            if ( stage == 10 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage10Info.png");

            this->SetVisible( true );
            SetStatus( JUMP_INFO );
        }
        void PlayPage( int stage ) {
            AllDisappear();
            m_Play_Buttom->SetVisible( true );
            m_Cancel_Buttom->SetVisible( true );
            m_info_Buttom->SetVisible( true );
            if ( stage == 1 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage1Start.png" );
            else if ( stage == 2 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage2Start.png" );
            else if ( stage == 3 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage3Start.png" );
            else if ( stage == 4 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage4Start.png" );
            else if ( stage == 5 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage5Start.png" );
            else if ( stage == 6 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage6Start.png" );
            else if ( stage == 7 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage7Start.png" );
            else if ( stage == 8 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage8Start.png" );
            else if ( stage == 9 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage9Start.png" );
            else if ( stage == 10 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage10Start.png" );
            
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
            else if ( stage == 3 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage3End.png" );
            else if ( stage == 4 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage4End.png" );
            else if ( stage == 5 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage5End.png" );
            else if ( stage == 6 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage6End.png" );
            else if ( stage == 7 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage7End.png" );
            else if ( stage == 8 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage8End.png" );
            else if ( stage == 9 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage9End.png" );
            else if ( stage == 10 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage10End.png" );
            
            SetStatus( JUMP_END );
            this->SetVisible( true );
        }

        void FailPage( int stage ) {
            AllDisappear();
            m_Cancel_Buttom->SetVisible( true );
            if ( stage == 1 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage1fail.png" );
            else if ( stage == 2 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage2Fail.png" );
            else if ( stage == 3 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage3Fail.png" );
            else if ( stage == 4 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage4Fail.png" );
            else if ( stage == 5 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage5Fail.png" );
            else if ( stage == 6 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage6Fail.png" );
            else if ( stage == 7 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage7Fail.png" );
            else if ( stage == 8 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage8Fail.png" );
            else if ( stage == 9 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage9Fail.png" );
            else if ( stage == 10 )
                this->SetImage( GA_RESOURCE_DIR"/Image/Background/stage10Fail.png" );
            
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
private:
        int m_Status;
        std::string m_ImagePath;
        std::shared_ptr<Character> m_Play_Buttom;
        std::shared_ptr<Character> m_Cancel_Buttom;
        std::shared_ptr<Character> m_Pause_Buttom;
        std::shared_ptr<Character> m_Continue_Buttom;
        std::shared_ptr<Character> m_Stop_Buttom;
        std::shared_ptr<Character> m_info_Buttom;
        inline std::string ImagePath(const std::string& phase) {
            // std::cout<<"hihi"<<phase<<std::endl;
            return (GA_RESOURCE_DIR "/Image/Background/" + phase );

        }
};