#include "../metaprog.hpp"

template<word arguments>
void lsl(Memoire& mem, Boite_registres& reg, unsigned int& pc){
    const bool ilyauneconstante = ((arguments &0b100000000000)>> 11); // on récupère le flag
    if(ilyauneconstante){
        reg[(arguments & 0b011100000000)>>8] = reg[(arguments & 0b000011110000)>>4] << (arguments & 0b000000001111);
    }else{
        reg[(arguments & 0b011100000000)>>8] = reg[(arguments & 0b000011110000)>>4] << reg[(arguments & 0b000000001111)];
    }
    pc += 1;
}


template<word arguments>
struct Operande<0x7, arguments>{
    fonction operande(){
        return lsl<arguments>;
    }
};


void creerLsl(table_operandes& t){
    CreerTableau<0x7000, 0x7FFF>::creerTab(t);
}
