#include "../metaprog.hpp"


template<word arguments>
void leth(Memory&, Reg_box& reg, unsigned int& pc){
    const word regDestination = (arguments & 0b111100000000) >> 8;
    const word constante = arguments & 0b000011111111;
    reg[regDestination] = (reg[regDestination] & 0b000000001111) | (constante << 4);
    pc += 1;
}


template<word arguments>
struct Operand<0xD, arguments>{
    fonction operand(){
        return leth<arguments>;
    }
};


void createLeth(Operands_table& t){
    CreateTab<0xD000, 0xDFFF>::createTab(t);
}
