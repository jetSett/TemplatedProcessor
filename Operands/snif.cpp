#include "../metaprog.hpp"
#include "../Util.hpp"

template<word condition>
bool cond(word op1, word op2){
    std::cout << "Condition implémentée dans le turfu !" << std::endl;
    return false;
}

template<>
bool cond<0x0>(word op1, word op2){
    return op1 == op2;
}

template<>
bool cond<0x1>(word op1, word op2){
    return op1 != op2;
}

template<>
bool cond<0x2>(word op1, word op2){
    int16_t op1c = conversionNeg4bit(op1), op2c = conversionNeg4bit(op2);
    return op1c > op2c;
}

template<>
bool cond<0x3>(word op1, word op2){
    int16_t op1c = conversionNeg4bit(op1), op2c = conversionNeg4bit(op2);
    return op1c < op2c;
}
template<>
bool cond<0x4>(word op1, word op2){
    return op1 > op2;
}

template<>
bool cond<0x5>(word op1, word op2){
    return op1 >= op2;
}

template<>
bool cond<0x6>(word op1, word op2){
    return op1 < op2;
}

template<>
bool cond<0x7>(word op1, word op2){
    return op1 <= op2;
}


template<word arguments>
void snif(Memory& mem, Reg_box& reg, unsigned int& pc){
    const word condition = (arguments & 0b011100000000) >> 8;
    const bool ilyauneconstante = ((arguments &0b100000000000)>> 11); // on récupère le flag
    if(ilyauneconstante){
        cond<condition>(reg[(arguments&0b000011110000)>>4], (arguments&0b000000001111)>>4)?pc+=2:pc+=1;
    }else{
        cond<condition>(reg[(arguments&0b000011110000)>>4], reg[(arguments&0b000000001111)>>4])?pc+=2:pc+=1;
    }
}


template<word arguments>
struct Operand<0x3, arguments>{
    fonction operand(){
        return snif<arguments>;
    }
};

void createSnif(Operands_table& t){
    CreateTab<0x3000, 0x3FFF>::createTab(t);
}
