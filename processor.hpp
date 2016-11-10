#ifndef PROCESSEUR_H
#define PROCESSEUR_H

#include "metaprog.hpp"


void createWmem(Operands_table&); // 0
void createAdd(Operands_table&); // 1
void createSub(Operands_table&); // 2
void createSnif(Operands_table&); // 3
void createAnd(Operands_table&); // 4
void createOr(Operands_table&); // 5
void createXor(Operands_table&); // 6
void createLsl(Operands_table&); // 7
void createLsr(Operands_table&); // 8
void createAsr(Operands_table&); // 9
void createCall(Operands_table&); // A
void createJumpReturn(Operands_table&); // B
void createLetl(Operands_table&); // C
void createLeth(Operands_table&); // D
// implémentée dans le turfu !
void createRmemCopy(Operands_table&); // F

class Processor
{
    public:
        Processor(const std::string& file);
        void run(bool interactive);
        void printState();
    private:
        Operands_table _operands;

        Memory _mem;
        Reg_box _reg;
        unsigned _pc;

        std::vector<word> _instructions;
};

#endif // PROCESSEUR_H
