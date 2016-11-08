#include "../metaprog.hpp"


template<word arguments>
void letl(Memoire& mem, Boite_registres& reg, unsigned int& pc){
    const word regDestination = (arguments & 0b111100000000) >> 8;
    const word constante = arguments & 0b000011111111;
    const bool constanteNeg = (constante & 0b10000000) >> 7;
    if(constanteNeg){
        reg[regDestination] = 0xFFF & constante;
    }else{
        reg[regDestination] = (reg[regDestination]&0xF000) | constante;
    }
    pc += 1;
}


template<word arguments>
struct Operande<0xC, arguments>{
    fonction operande(){
        return letl<arguments>;
    }
};


void creerLetl(table_operandes& t){
    CreerTableau<0xC000, 0xCFFF>::creerTab(t);
}
