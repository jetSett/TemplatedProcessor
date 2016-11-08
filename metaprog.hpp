#ifndef METAPROG_HPP_INCLUDED
#define METAPROG_HPP_INCLUDED

#include <iostream>
#include <functional>
#include <unordered_map>
#include <vector>
#include <array>

using word = uint16_t;

using Memoire = std::vector<word>;
using Boite_registres = std::array<word, 16>;


using fonction =  std::function<void(Memoire&, Boite_registres&, unsigned int&)>; //arguments : <mémoire> <registres> <pc>
using table_operandes = std::array<fonction, 0x10000>;


void doNothing(Memoire&, Boite_registres&, unsigned int&);

template<word code, word arguments>
struct Operande{
    fonction operande(){
        return doNothing;
    }
};

template<word opcode>
fonction getFonction(){
        Operande<((opcode & 0xF000) >> 12), (opcode & 0x0FFF)> op;
        return fonction(op.operande());
}

template<word n, word fin>
struct CreerTableau{
    static void creerTab(table_operandes& tableau){
        tableau[n] = getFonction<n>();
        CreerTableau<n+1, fin>::creerTab(tableau);
    }
};

template<word n>
struct CreerTableau<n, n>{
    static void creerTab(table_operandes& tableau){
        tableau[n] = getFonction<n>();
    }
};

// on appelle creerTableau<0xFFFF>
#endif // METAPROG_HPP_INCLUDED
