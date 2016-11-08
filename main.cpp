#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "metaprog.hpp"

/// \warning Ceci va être impossible à comprendre


void creerWmem(table_operandes&); // 0
void creerAdd(table_operandes&); // 1
void creerSub(table_operandes&); // 2
void creerSnif(table_operandes&); // 3
void creerAnd(table_operandes&); // 4
void creerOr(table_operandes&); // 5
void creerXor(table_operandes&); // 6
void creerLsl(table_operandes&); // 7
void creerLsr(table_operandes&); // 8
void creerAsr(table_operandes&); // 9
void creerCall(table_operandes&); // A
void creerJumpReturn(table_operandes&); // B
void creerLetl(table_operandes&); // C
void creerLeth(table_operandes&); // D
// implémentée dans le turfu !
void creerRmemCopy(table_operandes&); // F

using namespace std;


void afficherEtat(const Boite_registres& reg, unsigned& pc){
    unsigned i = 0;
    for(auto r : reg){
        cout << "r" << i << " : " << hex << r << dec <<" | ";i++;
    }
    cout << "pc : "<< pc << endl;
}


int main(int argc, char** argv)
{
    table_operandes table;
    creerWmem(table); // 0
    creerAdd(table); // 1
    creerSub(table); // 2
    creerSnif(table); // 3
    creerAnd(table); // 4
    creerOr(table); // 5
    creerXor(table); // 6
    creerLsl(table); // 7
    creerLsr(table); // 8
    creerAsr(table); // 9
    creerCall(table); // A
    creerJumpReturn(table); // B
    creerLetl(table); // C
    creerLeth(table); // D

    creerRmemCopy(table); // F

    ifstream stream(argv[1]);
    vector<word> instructions;
    string mot;
    while(stream >> mot){
        word x;
        stringstream ss;
        ss << std::hex << mot;
        ss >> x;
        instructions.push_back(x);
    }


    cout << "Fin de lecture du fichier" << endl << "Debut de l'interpretation" << endl << endl;


    unsigned pc = 0;

    Memoire mem(5000, 0);
    Boite_registres reg;
    reg.fill(0);

    while(pc < instructions.size()){
        afficherEtat(reg, pc);
        table[instructions[pc]](mem, reg, pc);
    }
    afficherEtat(reg, pc);

    return 0;
}
