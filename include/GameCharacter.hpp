#ifndef GAME_CHARACTER_HPP
#define GAME_CHARACTER_HPP

#include <string>
#include <iostream>

#include "ObjectInformation.hpp"
#include "Character.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

class GameCharacter : public Character {
public:
    GameCharacter(const std::string& ImagePath);

    virtual ~GameCharacter() = default; 

    void Appear() {
        this->SetVisible(true);
    }

    void DisAppear() {
        this->SetVisible(false);
    }
    void Drop(glm::vec2 MoveVector = {0 , 1}, glm::vec2 GoalPosition = {0, 0}) {
        while (true) {
            glm::vec2 NextPos = this->GetPosition();
            if (NextPos.y == GoalPosition.y && NextPos.x == GoalPosition.x) {
                return;
            }
            NextPos.x += MoveVector.x;
            NextPos.y += MoveVector.y;
            this->SetPosition(NextPos);
        }
    }
    void DebugMode(float Speed) {
        glm::vec2 NextPos = this->GetPosition();
        if (Util::Input::IsKeyDown(Util::Keycode::UP) )
            NextPos.y += Speed;
        if (Util::Input::IsKeyDown(Util::Keycode::DOWN) )
            NextPos.y -= Speed;
        if (Util::Input::IsKeyDown(Util::Keycode::LEFT) )
            NextPos.x -= Speed;
        if (Util::Input::IsKeyDown(Util::Keycode::RIGHT) )
            NextPos.x += Speed;

        this->SetPosition( NextPos ); 
        std::cout << "x : " << NextPos.x << " y : " << NextPos.y << "\n";
    }
    
    Objectinformation GetInformation() { return this->m_information; }
    
    int GetInformationStage() { return (this->m_information).GetStage(); }

    int GetInformationPosNumber() { return (this->m_information).GetPositionNumber(); }

    int* GetInformationNeibor() { return (this->m_information).GetNeibor(); }

    int GetBlockType() { return this->m_Block; }

    bool GetAppearBool() { return this->m_Appear; }
    
    glm::vec2 GetInformationPosition() { return (this->m_information).GetPosition(); }

    void SwitchPosition( std::shared_ptr<GameCharacter>& other ) {
        Objectinformation temp = this->m_information;
        this->m_information = other->m_information;
        other->m_information = temp;
        
        this->SetPosition( this->GetInformationPosition() );
        other->SetPosition( other->GetInformationPosition() );

    }

    void SetInformation( Objectinformation& other ) {
        this->m_information = other;
    }

    void SetInformation( int Stage , int Pos , int* Neibor , const glm::vec2& Position) {
        (this->m_information).SetStage( Stage );
        (this->m_information).SetPosNumber( Pos );
        (this->m_information).SetNeibor( Neibor );
        this->SetPosition( Position );
    }
    virtual void SetPosition(const glm::vec2& Position) { 
        m_Transform.translation = Position; 
        (this->m_information).SetPosition( Position );
    }

    void SetBlock(int block_type){
        this->m_Block = block_type;
    }

    void SetAppearBool( bool flag ) {
        this->m_Appear = flag;
    }
    virtual void SetImage(const std::string& ImagePath);
protected:
    void ResetPosition() { 
        m_Transform.translation = {0, 0}; 
    }

    int m_Block = -1 ;
    glm::vec2 m_Size = { 50.0f, 100.0f };
    std::string m_ImagePath;
    Objectinformation m_information ;
    bool m_Appear = true;
};

#endif // GAME_CHARACTER_HPP
    