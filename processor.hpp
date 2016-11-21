#ifndef PROCESSEUR_H
#define PROCESSEUR_H

#include <QObject>
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

class Processor : public QObject
{
    Q_OBJECT
    public:
        Processor();
        ~Processor();
        std::string printState();
        void loadFile(const std::string& file);

        Memory& getMemory(){ // WARNING ! we are returning a reference
            return _mem;
        }

        Reg_box& getRegbox(){ // IDEM
            return _reg;
        }

        unsigned& getPc(){ //IDEM
            return _pc;
        }

        bool loaded(){
            return _nbOpe != 0;
        }

        bool ended(){
            return _pc >=_nbOpe;
        }

    public slots:
        void step();

    signals:
        void fileLoaded();
        void stepBegin();
        void stepEnd();
    private:
        Operands_table _operands;

        Memory _mem;
        Reg_box _reg;
        unsigned _pc;
        unsigned _nbOpe;
};

#endif // PROCESSEUR_H
