#include "../metaprog.hpp"


template<word arguments>
void rMemCopy(Memoire& mem, Boite_registres& reg, unsigned int& pc){
    const bool copie = (arguments & 0b000000010000) >> 4;
    const word destination = (arguments & 0b111100000000) >> 8;
    const word source = (arguments & 0b000000001111);
    if(copie){
        reg[destination] = reg[source];
    }else{
        mem[reg[destination]] = reg[source];
    }
    pc += 1;
}


template<word arguments>
struct Operande<0xF, arguments>{
    fonction operande(){
        return rMemCopy<arguments>;
    }
};


void creerRmemCopy(table_operandes& t){
    CreerTableau<0xF000, 0xFFFF>::creerTab(t);
}
