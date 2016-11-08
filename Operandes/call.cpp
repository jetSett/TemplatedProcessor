#include "../metaprog.hpp"


template<word arguments>
void call(Memoire& mem, Boite_registres& reg, unsigned int& pc){
    reg[15] = pc + 1;
    pc = 16*arguments;
}


template<word arguments>
struct Operande<0xA, arguments>{
    fonction operande(){
        return call<arguments>;
    }
};


void creerCall(table_operandes& t){
    CreerTableau<0xA000, 0xAFFF>::creerTab(t);
}
