#include <string>
#include "../metaprog.hpp"
#include "../Util.hpp"

template<word arguments>
void jump(Memory& mem, Reg_box& reg, unsigned int& pc){
    int16_t c = conversionNeg12bit(arguments);
    pc +=  c;
    if(pc < 0){
        throw std::string("Jump en trop loin en arrière");
    }
}


void returnOp(Memory& mem, Reg_box& reg, unsigned int& pc){
    pc = reg[15];
}

template<word arguments>
struct Operand<0xB, arguments>{
    fonction operand(){
        return jump<arguments>;
    }
};

template<>
struct Operand<0xB, 1>{
    fonction operand(){
        return returnOp;
    }
};


void createJumpReturn(Operands_table& t){
    CreateTab<0xB000, 0xBFFF>::createTab(t);
}
