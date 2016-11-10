#include "../metaprog.hpp"


template<word arguments>
void wmem(Memory& mem, Reg_box& reg, unsigned int& pc){
    const word rj = arguments & 0b000011110000;
    const word ri = arguments & 0b000000001111;
    mem[reg[rj]] = reg[ri];
    pc+=1;
}


template<word arguments>
struct Operand<0x0, arguments>{
    fonction operand(){
        return wmem<arguments>;
    }
};


void createWmem(Operands_table& t){
    CreateTab<0x0000, 0x0FFF>::createTab(t);
}
