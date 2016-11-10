#include "../metaprog.hpp"

template<word arguments>
void orOp(Memory& mem, Reg_box& reg, unsigned int& pc){
    const bool ilyauneconstante = ((arguments &0b100000000000)>> 11); // on récupère le flag
    if(ilyauneconstante){
        reg[(arguments & 0b011100000000)>>8] = reg[(arguments & 0b000011110000)>>4]|(arguments & 0b000000001111);
    }else{
        reg[(arguments & 0b011100000000)>>8] = reg[(arguments & 0b000011110000)>>4]|reg[(arguments & 0b000000001111)];
    }
    pc+= 1;
}


template<word arguments>
struct Operand<0x5, arguments>{
    fonction operand(){
        return orOp<arguments>;
    }
};

void createOr(Operands_table& t){
    CreateTab<0x5000, 0x5FFF>::createTab(t);
}
