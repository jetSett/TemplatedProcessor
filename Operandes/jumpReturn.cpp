#include <string>
#include "../metaprog.hpp"
#include "../Util.hpp"

template<word arguments>
void jump(Memoire& mem, Boite_registres& reg, unsigned int& pc){
    int16_t c = conversionNeg12bit(arguments);
    pc +=  c;
    if(pc < 0){
        throw std::string("Jump en trop loin en arrière");
    }
}


void returnOp(Memoire& mem, Boite_registres& reg, unsigned int& pc){
    pc = reg[15];
}

template<word arguments>
struct Operande<0xB, arguments>{
    fonction operande(){
        return jump<arguments>;
    }
};

template<>
struct Operande<0xB, 1>{
    fonction operande(){
        return returnOp;
    }
};


void creerJumpReturn(table_operandes& t){
    CreerTableau<0xB000, 0xBFFF>::creerTab(t);
}
