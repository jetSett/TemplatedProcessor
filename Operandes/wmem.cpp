#include "../metaprog.hpp"


template<word arguments>
void wmem(Memoire& mem, Boite_registres& reg, unsigned int& pc){
    const word rj = arguments & 0b000011110000;
    const word ri = arguments & 0b000000001111;
    mem[reg[rj]] = reg[ri];
    pc+=1;
}


template<word arguments>
struct Operande<0x0, arguments>{
    fonction operande(){
        return wmem<arguments>;
    }
};


void creerWmem(table_operandes& t){
    CreerTableau<0x0000, 0x0FFF>::creerTab(t);
}
