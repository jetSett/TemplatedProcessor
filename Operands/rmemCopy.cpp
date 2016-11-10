#include "../metaprog.hpp"


template<word arguments>
void rMemCopy(Memory& mem, Reg_box& reg, unsigned int& pc){
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
struct Operand<0xF, arguments>{
    fonction operand(){
        return rMemCopy<arguments>;
    }
};


void createRmemCopy(Operands_table& t){
    CreateTab<0xF000, 0xFFFF>::createTab(t);
}
