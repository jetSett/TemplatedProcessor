#include <fstream>
#include <sstream>
#include "processor.hpp"

const unsigned memSize = 0x10000; // indexée de 0 à 0xFFFF

Processor::Processor() : _mem(memSize, 0), _pc(0), _nbOpe(0)
{
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

void Processor::loadFile(const std::string &file){
    _nbOpe = 0;
    std::fill(_mem.begin(), _mem.end(), 0);
    _reg.fill(0);
    _pc = 0;
    //reading the file
    std::ifstream stream(file);

    if(not stream)
        throw std::string("Unable to open file : ") + file;
    unsigned i = 0;
    std::string s_word;
    while(stream >> s_word){
        _nbOpe ++;
        std::stringstream ss;
        ss << std::hex << s_word;
        word w;
        ss >> w;
        _mem[i] = w;
        i++;
    }
    emit fileLoaded();
}

std::string Processor::printState(){
    using namespace std;
    std::ostringstream oss;
    oss << "Pc : " << _pc << " | Instr : " << hex << _mem[_pc] << dec << " | ";
    unsigned i = 0;
    for(auto r : _reg){
        oss << "R" << i << " : " << hex << r << dec << " | ";
        i++;
    }
    oss << "\n";
    return oss.str();
}

void Processor::resetState(){
    std::fill(_mem.begin()+_nbOpe, _mem.end(), 0);
    _reg.fill(0);
    _pc = 0;
}

Processor::~Processor(){

}

void Processor::step(){
    emit stepBegin();
    word instruction = _mem[_pc];
    _operands[instruction](_mem, _reg, _pc);
    if(_pc >= _nbOpe){
        emit finished();
    }
    emit stepEnd();
}
