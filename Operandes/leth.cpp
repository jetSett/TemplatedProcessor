#include "../metaprog.hpp"


template<word arguments>
void leth(Memoire& mem, Boite_registres& reg, unsigned int& pc){
    const word regDestination = (arguments & 0b111100000000) >> 8;
    const word constante = arguments & 0b000011111111;
    reg[regDestination] = (reg[regDestination] & 0b000000001111) | (constante << 4);
    pc += 1;
}


template<word arguments>
struct Operande<0xD, arguments>{
    fonction operande(){
        return leth<arguments>;
    }
};


void creerLeth(table_operandes& t){
    CreerTableau<0xD000, 0xDFFF>::creerTab(t);
}
