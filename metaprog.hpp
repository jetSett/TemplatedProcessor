#ifndef METAPROG_HPP_INCLUDED
#define METAPROG_HPP_INCLUDED

#include <iostream>
#include <functional>
#include <unordered_map>
#include <vector>
#include <array>

using word = uint16_t;

using Memory = std::vector<word>;
using Reg_box = std::array<word, 16>;


using fonction =  std::function<void(Memory&, Reg_box&, unsigned int&)>; //arguments : <mémoire> <registres> <pc>
using Operands_table = std::array<fonction, 0x10000>;


void doNothing(Memory&, Reg_box&, unsigned int&);

template<word code, word arguments>
struct Operand{
    fonction operand(){
        return doNothing;
    }
};

template<word opcode>
fonction getFonction(){
        Operand<((opcode & 0xF000) >> 12), (opcode & 0x0FFF)> op;
        return fonction(op.operand());
}

template<word n, word fin>
struct CreateTab{
    static void createTab(Operands_table& tab){
        tab[n] = getFonction<n>();
        CreateTab<n+1, fin>::createTab(tab);
    }
};

template<word n>
struct CreateTab<n, n>{
    static void createTab(Operands_table& tab){
        tab[n] = getFonction<n>();
    }
};

// on appelle createTab<0xFFFF>
#endif // METAPROG_HPP_INCLUDED
