#include "GameCharacter.hpp"
#include "ObjectInformation.hpp"
#include "TaskText.hpp"
#include "Util/GameObject.hpp"
#include <condition_variable>
#include <mutex>
#pragma once

class StageObject : public Util::GameObject {
    public:
        StageObject(  int Size , std::shared_ptr<GameCharacter>* objectArray ) 
            :  m_Size(Size), m_Stage_Object(objectArray)
        {
        }
        std::shared_ptr<GameCharacter>* GetStageObject() {
            return m_Stage_Object;
        }
        int GetStage() {
            return m_Stage;
        }
        int GetSize() {
            return m_Size;
        }

        void SetStage( int stage ) {
            m_Stage = stage;
        }

        virtual ~StageObject() = default;
        void SetUp();
        void InitializeStageCharacter();
        bool CheckAppearance( int s );
        void CheckSpecialObject( int i );
        void MakeDisappear();
        void Dropping();
        void PointUpdate( int point );
        int  GetPoint();
        void AppearAll();
        void DisAppearAll();
        void ClearAllClick();
        bool IsSameColor(int blockType1, int blockType2);
        void CheckClickSwitch(int check, int i , std::shared_ptr<TaskText> point);
    protected:
        int m_Stage;
        int m_Size;
        std::shared_ptr<GameCharacter> *m_Stage_Object;

        void RandomChangeObject( int current_pos );

        void MakeDisappearWithObject( int current_pos );
        void MakeDisappearWithStripe( int current_pos );
        void MakeDisappearWithRainbow( int current_pos );
        void MakeDisappearWithFlower( int current_pos );
        void MakeDisappearWithStarFlower( int current_pos );
        void MakeDisappearWithTriangleFlower( int current_pos );
        void MakeDisappearWithStripeInLeftRight( int current_pos );
        void MakeDisappearWithStripeInRightLeft( int current_pos );
        void MakeDisappearWithFlowerCombined( int current_pos );
        void MakeDisappearWithStripeFlower( int current_pos );
        void MakeDisappearWithStripeCombined( int current_pos );

        bool DisappearMethodOfOneLine( int current_pos, int* total_length );
        int  DisappearMethodOfStripe(  int current_pos, int* total_length, int priority );
        bool DisappearMethodOfFlower(  int current_pos, int* total_length );
        bool DisappearMethodOfStarFlower(  int current_pos, int* total_length );
        bool DisappearMethodOfTriangleFlower(  int current_pos, int* total_length );
        bool DisappearMethodOfRainbowBall(  int current_pos, int* total_length, int priority );
        void DisappearBySingleObject ( int current_pos, int side, int length_left);

        bool CheckShuffleDemands();
        bool CheckLineMaking();
        bool CheckRainbowUsing();
        bool CheckSpecialBlocksNeighbor();

        void Dropping_method( const int current_position );
        bool checkAppearanceOfObject ( int i, int side, int length_left);
        bool checkSwitchedAllInfoWithZero ( int i, int side, int length_left);
        int  CheckNextAppearance( int i, int side, int length );
};