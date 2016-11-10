#include <bitset>
#include "Util.hpp"

int16_t conversionNeg4bit(word mot){
    if(((mot & 0b1000) >> 3) == 0){
        return mot;
    }else{
        return - ( ((mot)^0b111111111111) + 1 );
    }
}

int16_t conversionNeg12bit(word mot){
    if(((mot & 0b100000000000) >> 11) == 0){
        return mot;
    }else{
        return - ( ((mot)^0b111111111111) + 1 );
    }
}
