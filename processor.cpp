#include <fstream>
#include <sstream>
#include "processor.hpp"

const unsigned memSize = 1000000;

Processor::Processor(const std::string& file) : _mem(memSize, 0)
{

    //reading the file
    std::ifstream stream(file);

    if(not stream)
        throw std::string("Unable to open file : ") + file;

    std::string s_word;
    while(stream >> s_word){
        std::stringstream ss;
        ss << std::hex << s_word;
        word w;
        ss >> w;
        _instructions.push_back(w);
    }

    _reg.fill(0);
    createWmem(_operands); // 0
    createAdd(_operands); // 1
    createSub(_operands); // 2
    createSnif(_operands); // 3
    createAnd(_operands); // 4
    createOr(_operands); // 5
    createXor(_operands); // 6
    createLsl(_operands); // 7
    createLsr(_operands); // 8
    createAsr(_operands); // 9
    createCall(_operands); // A
    createJumpReturn(_operands); // B
    createLetl(_operands); // C
    createLeth(_operands); // D

    createRmemCopy(_operands); // F
}

void Processor::printState(){
    using namespace std;
    if(_instructions.size() == 0)
        throw string("No instruction loaded");

    cout << "Pc : " << _pc << " | Instr : " << hex << _instructions[_pc] << dec << " | ";
    unsigned i = 0;
    for(auto r : _reg){
        cout << "R" << i << " : " << hex << r << dec << " | ";
        i++;
    }
    cout << endl;
}

void Processor::run(bool interactive){
    while(_pc < _instructions.size()){
        word inst = _instructions[_pc];
        _operands[inst](_mem, _reg, _pc);
    }
}