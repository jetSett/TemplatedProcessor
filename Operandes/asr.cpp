#include "../metaprog.hpp"

///TODO : LE CODER


void asrn(Memoire& mem, Boite_registres& reg, word registre, word n, bool rajouter){
    if(n==0){
        return;
    }
    reg[registre] = (reg[registre] >> 1) | (rajouter?0b100000000000000:0);
    asrn(mem, reg, registre, n-1, rajouter);
}

template<word arguments>
void asr(Memoire& mem, Boite_registres& reg, unsigned int& pc){
    const bool ilyauneconstante = ((arguments &0x800)>> 15); // on récupère le flag
    if(ilyauneconstante){
        reg[(arguments & 0b011100000000)>>8] = reg[(arguments & 0b000011110000)>>4];
        asrn(mem, reg, (arguments & 0b011100000000)>>8, (arguments & 0b000000001111), (reg[(arguments & 0b000011110000)>>4] & 0b1000000000000000)>>15);
    }else{
        reg[(arguments & 0b011100000000)>>8] = reg[(arguments & 0b000011110000)>>4];
        asrn(mem, reg, (arguments & 0b011100000000)>>8, reg[(arguments & 0b000000001111)], (reg[(arguments & 0b000011110000)>>4] & 0b1000000000000000)>>15);
    }
    pc += 1;
}

template<word arguments>
struct Operande<0x9, arguments>{
    fonction operande(){
        return asr<arguments>;
    }
};


void creerAsr(table_operandes& t){
    CreerTableau<0x9000, 0x9FFF>::creerTab(t);
}
