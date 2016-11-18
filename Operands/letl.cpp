#include "../metaprog.hpp"


template<word arguments>
void letl(Memory&, Reg_box& reg, unsigned int& pc){
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
struct Operand<0xC, arguments>{
    fonction operand(){
        return letl<arguments>;
    }
};


void createLetl(Operands_table& t){
    CreateTab<0xC000, 0xCFFF>::createTab(t);
}
