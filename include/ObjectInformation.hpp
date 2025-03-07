#include <string>
#include <glm/vec2.hpp>

class Objectinformation {
    public:
        Objectinformation( int Stage = 0 )
            : m_Stage(Stage) {
                this->InitialNeiber();
            }
        void InitialNeiber() {
            for ( int i = 0 ; i < 6 ; ++i ) {
                this->m_Neibor[i] = -1;
            }
        }
        void SetPosNumber( int PosNumber ) { 
            this->m_PosNumber = PosNumber;
        }

        void SetNeibor(int *Neibor ) {
            for ( int i = 0 ; i < 6 ; ++i ) {
                this->m_Neibor[i] = Neibor[i];
            }
        }
        void SetNeibor( int Neibor, int Dimension ) {
            this->m_Neibor[Dimension] = Neibor;
        }
    private:
        int m_Stage = 0 ;
        int m_PosNumber = 0 ;
        int m_Neibor[6] = {0};
};