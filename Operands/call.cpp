#include "../metaprog.hpp"


template<word arguments>
void call(Memory& mem, Reg_box& reg, unsigned int& pc){
    reg[15] = pc + 1;
    pc = 16*arguments;
}


template<word arguments>
struct Operand<0xA, arguments>{
    fonction operand(){
        return call<arguments>;
    }
};


void createCall(Operands_table& t){
   	CreateTab<0xA000, 0xAFFF>::createTab(t);
}
