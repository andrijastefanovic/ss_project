#include <string>
#include <iostream>
#include <stdio.h>
#include <list>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>

#include <cstring>

extern int yyparse();
class Symbol
{
public:
  int value;
  std::string name;
  std::string sectionName;
  std::string type;
  bool global;
  bool defined;
  Symbol(int value, std::string name, std::string sectionName, std::string type, bool global, bool defined)
  {
    this->value = value;
    this->name = name;
    this->sectionName = sectionName;
    this->type = type;
    this->global = global;
    this->defined = defined;
  }
};
class Relocation
{
  public:
  std::string sectionName;
  std::string symbolSectionName;
  bool word;
  int addend;
  int offset;
  std::string symbolName;
  Relocation(std::string sectionName, std::string name, int addend, int offset, std::string symbol)
  {
    this->sectionName = sectionName;
    this->symbolSectionName = name;
    this->addend = addend;
    this->offset = offset;
    this->symbolName = symbol;
    this->word = false;
  }
  Relocation(std::string sectionName, std::string name, int addend, int offset, std::string symbol, bool word)
  {
    this->sectionName = sectionName;
    this->symbolSectionName = name;
    this->addend = addend;
    this->offset = offset;
    this->symbolName = symbol;
    this->word = word;
  }
};
class Section
{
public:
  std::vector<char> code;
  std::string name;
  Section(std::string name)
  {
    this->name = name;
  }
};
class Backpatch
{
public:
  std::string symbol;
  std::string section;
  int offset;
  bool word;
  Backpatch(std::string symbol, std::string section, int offset, bool word = false)
  {
    this->symbol = symbol;
    this->section = section;
    this->offset = offset;
    this->word = word;
  }
};
class Asembler
{
public:
  static std::list<Symbol> symbolTable;
  static std::list<Relocation> relocationTable;
  static std::string sectionName;
  static int offset;
  static std::list<Section> code;
  static std::list<Backpatch> backpatch;
  Asembler()
  {
  }
  static void global(std::string symbolList);
  static void externSymbols(std::string symbolList);
  static void section(std::string symbol);
  static void wordSymbolList(std::string symbolList);
  static void wordNumber(int number);
  static void skip(int number);
  static void halt();
  static void interrupt(int number);
  static void iret();
  static void callNum(int number);
  static void callSymbol(std::string symbol);
  static void callPcrelSymbol(std::string symbol);
  static void callMemNum(int number);
  static void callMemSymbol(std::string string2);
  static void callReg(int number);
  static void callMemReg(int number);
  static void callMemRegNum(int number1, int number2);
  static void callMemRegSymbol(int number, std::string string2);
  static void ret();
  static void jmpNum(int number);
  static void jmpSymbol(std::string symbol);
  static void jmpPcrelSymbol(std::string symbol);
  static void jmpMemNum(int number);
  static void jmpMemSymbol(std::string string2);
  static void jmpReg(int number);
  static void jmpMemReg(int number);
  static void jmpMemRegNum(int number1, int number2);
  static void jmpMemRegSymbol(int number, std::string string2);
  static void jeqNum(int number);
  static void jeqSymbol(std::string symbol);
  static void jeqPcrelSymbol(std::string symbol);
  static void jeqMemNum(int number);
  static void jeqMemSymbol(std::string string2);
  static void jeqReg(int number);
  static void jeqMemReg(int number);
  static void jeqMemRegNum(int number1, int number2);
  static void jeqMemRegSymbol(int number, std::string string2);
  static void jneNum(int number);
  static void jneSymbol(std::string symbol);
  static void jnePcrelSymbol(std::string symbol);
  static void jneMemNum(int number);
  static void jneMemSymbol(std::string string2);
  static void jneReg(int number);
  static void jneMemReg(int number);
  static void jneMemRegNum(int number1, int number2);
  static void jneMemRegSymbol(int number, std::string string2);
  static void jgtNum(int number);
  static void jgtSymbol(std::string symbol);
  static void jgtPcrelSymbol(std::string symbol);
  static void jgtMemNum(int number);
  static void jgtMemSymbol(std::string string2);
  static void jgtReg(int number);
  static void jgtMemReg(int number);
  static void jgtMemRegNum(int number1, int number2);
  static void jgtMemRegSymbol(int number, std::string string2);
  static void push(int number);
  static void pop(int number);
  static void xchg(int number1, int number2);
  static void add(int number1, int number2);
  static void sub(int number1, int number2);
  static void mul(int number1, int number2);
  static void div(int number1, int number2);
  static void cmp(int number1, int number2);
  static void notReg(int number);
  static void andReg(int number1, int number2);
  static void orReg(int number1, int number2);
  static void xorReg(int number1, int number2);
  static void test(int number1, int number2);
  static void shl(int number1, int number2);
  static void shr(int number1, int number2);
  static void ldrValNum(int number1, int number2);
  static void ldrValSymbol(int number, std::string symbol);
  static void ldrMemNum(int number1, int number2);
  static void ldrMemSymbol(int number, std::string symbol);
  static void ldrPcrelSymbol(int number, std::string symbol);
  static void ldrReg(int number1, int number2);
  static void ldrMemReg(int number1, int number2);
  static void ldrMemRegNum(int number1, int number2, int number3);
  static void ldrMemRegSymbol(int number1, int number2, std::string symbol);
  static void strMemNum(int number1, int number2);
  static void strMemSymbol(int number, std::string symbol);
  static void strPcrelSymbol(int number, std::string symbol);
  static void strReg(int number1, int number2);
  static void strMemReg(int number1, int number2);
  static void strMemRegNum(int number1, int number2, int number3);
  static void strMemRegSymbol(int number1, int number2, std::string symbol);
  static void label(std::string symbol);
  static void end();
};