#include "../inc/asembler.hpp"
#include <queue>
#include <math.h>
extern FILE *yyin;
std::ofstream outout_text_file;
int Asembler::offset = 0;
std::list<Symbol> Asembler::symbolTable = std::list<Symbol>();
std::list<Relocation> Asembler::relocationTable = std::list<Relocation>();
std::list<Section> Asembler::code = std::list<Section>();
std::list<Backpatch> Asembler::backpatch = std::list<Backpatch>();
std::string Asembler::sectionName = "";

void Asembler::global(std::string symbolList)
{
  std::queue<std::string> stringQueue;
  std::string currentSymbol = "";
  for (int i = 0; i < symbolList.length(); i++)
  {

    if (symbolList[i] == ',')
    {
      stringQueue.push(currentSymbol);
      currentSymbol = "";
    }
    else
      currentSymbol += symbolList[i];
  }
  stringQueue.push(currentSymbol);
  currentSymbol = "";
  bool found = false;
  std::list<Symbol> symbolTable2 = std::list<Symbol>();
  while (!stringQueue.empty())
  {
    for (Symbol sym : Asembler::symbolTable)
    {
      if (sym.name == stringQueue.front())
      {
        Symbol sym2 = Symbol(sym.value, sym.name, sym.sectionName, sym.type, true, sym.defined);
        sym.global = true;
        found = true;
        symbolTable2.push_back(sym2);
      }
      else
      {
        symbolTable2.push_back(sym);
      }
    }
    if (!found)
    {
      Asembler::symbolTable.push_back(Symbol(0, stringQueue.front(), "undefined", "undefined", true, false));
    }
    else
    {
      Asembler::symbolTable.swap(symbolTable2);
      symbolTable2.clear();
    }
    stringQueue.pop();
  }
  return;
}

void Asembler::externSymbols(std::string symbolList)
{
  std::queue<std::string> stringQueue;
  std::string currentSymbol = "";
  for (int i = 0; i < symbolList.length(); i++)
  {

    if (symbolList[i] == ',')
    {
      stringQueue.push(currentSymbol);
      currentSymbol = "";
    }
    else
      currentSymbol += symbolList[i];
  }
  stringQueue.push(currentSymbol);
  currentSymbol = "";
  bool found = false;
  std::list<Symbol> symbolTable2 = std::list<Symbol>();
  while (!stringQueue.empty())
  {
    for (Symbol sym : Asembler::symbolTable)
    {
      if (sym.name == stringQueue.front())
      {
        Symbol sym2 = Symbol(sym.value, sym.name, sym.sectionName, sym.type, true, sym.defined);
        sym.global = true;
        found = true;
        symbolTable2.push_back(sym2);
      }
      else
      {
        symbolTable2.push_back(sym);
      }
    }
    if (!found)
    {
      Asembler::symbolTable.push_back(Symbol(0, stringQueue.front(), "undefined", "undefined", true, false));
    }
    else
    {
      Asembler::symbolTable.swap(symbolTable2);
      symbolTable2.clear();
    }
    stringQueue.pop();
  }
  return;
}

void Asembler::section(std::string symbol)
{
  Asembler::code.push_back(Section(symbol));
  Asembler::sectionName = symbol;
  Asembler::offset = 0;
  Asembler::symbolTable.push_back(Symbol(0, symbol, symbol, "section", false, true));
}

void Asembler::wordSymbolList(std::string symbolList)
{
  std::queue<std::string> stringQueue;
  std::string currentSymbol = "";
  for (int i = 0; i < symbolList.length(); i++)
  {
    if (symbolList[i] == ',')
    {
      stringQueue.push(currentSymbol);
      currentSymbol = "";
    }
    else
      currentSymbol += symbolList[i];
  }
  stringQueue.push(currentSymbol);
  currentSymbol = "";
  while (!stringQueue.empty())
  {
    bool found = false;
    for (Symbol sym : Asembler::symbolTable)
    {
      if (stringQueue.front() == sym.name)
      {
        found = true;
        if (sym.defined == true)
        {
          for (Section &sec : Asembler::code)
          {
            if (sec.name == Asembler::sectionName)
            {
              if (sym.sectionName == sec.name)
              {
                std::ostringstream ss;
                ss << std::hex << sym.value;
                std::string hexVal = ss.str();
                std::string pushBack = "";
                Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name, true));
                for (int i = 4; i > hexVal.length(); i--)
                {
                  pushBack += "0";
                }
                pushBack = pushBack + hexVal;
                std::string value = "";
                for (int i = 1; i >= 0; i--)
                {
                  value += pushBack[i];
                }
                for (int i = 3; i >= 2; i--)
                {
                  value += pushBack[i];
                }
                for (int i = 0; i < 4; i++)
                {
                  sec.code.push_back(value[i]);
                  // sec.code.push_back(pushBack[i]);
                }
              }
              else
              {
                Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name, true));
                {
                  for (int i = 0; i < 4; i++)
                    sec.code.push_back('0');
                }
              }
            }
          }
        }
        else
        {
          Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset, true));
          for (Section &sec : Asembler::code)
          {
            if (sec.name == Asembler::sectionName)
            {
              for (int i = 0; i < 4; i++)
                sec.code.push_back('0');
            }
          }
        }
      }
    }
    if (!found)
    {
      Asembler::symbolTable.push_back(Symbol(0, stringQueue.front(), "undefined", "undefined", true, false));
      Asembler::backpatch.push_back(Backpatch(stringQueue.front(), Asembler::sectionName, Asembler::offset, true));
      for (Section &sec : Asembler::code)
      {
        if (sec.name == Asembler::sectionName)
        {
          for (int i = 0; i < 4; i++)
            sec.code.push_back('0');
        }
      }
    }
    Asembler::offset += 2;
    stringQueue.pop();
  }
  return;
}

void Asembler::wordNumber(int number)
{
  if (number > pow(2, 15) - 1)
  {
    number -= pow(2, 16);
  }
  std::ostringstream ss;
  std::string numberString = "";
  ss << std::setfill('0') << std::setw(4) << std::hex << number;
  numberString = ss.str();

  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
    }
  }
  Asembler::offset += 2;
}

void Asembler::skip(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      for (int i = 0; i < 2 * number; i++)
      {
        sec.code.push_back('0');
      }
    }
  }

  Asembler::offset += number;
}

void Asembler::halt()
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      for (int i = 1; i >= 0; i--)
      {
        sec.code.push_back('0');
      }
    }
  }
  Asembler::offset++;
}

void Asembler::interrupt(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('1');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('f');
    }
  }
  Asembler::offset += 2;
}

void Asembler::iret()
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('2');
      sec.code.push_back('0');
    }
  }
  Asembler::offset++;
}

void Asembler::callNum(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('3');
      sec.code.push_back('0');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(4) << std::hex << number;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::callSymbol(std::string string2)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('3');
      sec.code.push_back('0');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('0');
      Asembler::offset += 3;
      if(Asembler::offset != sec.code.size() / 2) std::cout << "BIG ERROR" <<std::endl;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (string2 == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              std::ostringstream ss;
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, string2, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(string2, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::callPcrelSymbol(std::string string2)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('3');
      sec.code.push_back('0');
      sec.code.push_back('f');
      sec.code.push_back('7');
      sec.code.push_back('0');
      sec.code.push_back('5');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (string2 == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              std::ostringstream ss;
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, string2, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(string2, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::callMemNum(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('3');
      sec.code.push_back('0');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('4');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(4) << std::hex << number;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::callMemSymbol(std::string string2)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('3');
      sec.code.push_back('0');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('4');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (string2 == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              std::ostringstream ss;
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, string2, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(string2, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::callReg(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('3');
      sec.code.push_back('0');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('1');
    }
  }
  Asembler::offset += 3;
}

void Asembler::callMemReg(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('3');
      sec.code.push_back('0');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('2');
    }
  }
  Asembler::offset += 3;
}

void Asembler::callMemRegNum(int number1, int number2)
{
  if (number2 > pow(2, 15) - 1)
  {
    number2 -= pow(2, 16);
  }
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('3');
      sec.code.push_back('0');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('3');
      numberString = "";
      ss.clear();
      ss << std::setfill('0') << std::setw(4) << std::hex << number2;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::callMemRegSymbol(int number, std::string symbol)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('3');
      sec.code.push_back('0');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();
      ss.clear();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('3');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (symbol == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, symbol, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(symbol, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::ret()
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('4');
      sec.code.push_back('0');
    }
  }
  Asembler::offset++;
}

void Asembler::jmpNum(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('0');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('0');
      std::ostringstream ss;
      ss << std::setfill('0') << std::setw(4) << std::hex << number;
      std::string numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::jmpSymbol(std::string string2)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('0');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('0');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (string2 == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              std::ostringstream ss;
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, string2, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(string2, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::jmpPcrelSymbol(std::string string2)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('0');
      sec.code.push_back('f');
      sec.code.push_back('7');
      sec.code.push_back('0');
      sec.code.push_back('5');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (string2 == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              std::ostringstream ss;
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, string2, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(string2, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::jmpMemNum(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('0');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('4');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(4) << std::hex << number;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::jmpMemSymbol(std::string string2)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('0');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('4');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (string2 == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));

              std::ostringstream ss;
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, string2, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(string2, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::jmpReg(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('0');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('1');
    }
  }
  Asembler::offset += 3;
}

void Asembler::jmpMemReg(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('0');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('2');
    }
  }
  Asembler::offset += 3;
}

void Asembler::jmpMemRegNum(int number1, int number2)
{
  if (number2 > pow(2, 15) - 1)
  {
    number2 -= pow(2, 16);
  }
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('0');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('3');
      numberString = "";
      ss.clear();
      ss << std::setfill('0') << std::setw(4) << std::hex << number2;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::jmpMemRegSymbol(int number, std::string symbol)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('0');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();
      ss.clear();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('3');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (symbol == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));

              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, symbol, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(symbol, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::jeqNum(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('1');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('0');
      std::ostringstream ss;
      ss << std::setfill('0') << std::setw(4) << std::hex << number;
      std::string numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::jeqSymbol(std::string string2)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('1');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('0');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (string2 == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));

              std::ostringstream ss;
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, string2, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(string2, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::jeqPcrelSymbol(std::string string2)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('1');
      sec.code.push_back('f');
      sec.code.push_back('7');
      sec.code.push_back('0');
      sec.code.push_back('5');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (string2 == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));

              std::ostringstream ss;
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, string2, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(string2, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::jeqMemNum(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('1');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('4');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(4) << std::hex << number;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::jeqMemSymbol(std::string string2)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('1');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('4');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (string2 == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));

              std::ostringstream ss;
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, string2, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(string2, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::jeqReg(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('1');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('1');
    }
  }
  Asembler::offset += 3;
}

void Asembler::jeqMemReg(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('1');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('2');
    }
  }
  Asembler::offset += 3;
}

void Asembler::jeqMemRegNum(int number1, int number2)
{
  if (number2 > pow(2, 15) - 1)
  {
    number2 -= pow(2, 16);
  }
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('1');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('3');
      numberString = "";
      ss.clear();
      ss << std::setfill('0') << std::setw(4) << std::hex << number2;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::jeqMemRegSymbol(int number, std::string symbol)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('1');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();
      ss.clear();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('3');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (symbol == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, symbol, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(symbol, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::jneNum(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('2');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('0');
      std::ostringstream ss;
      ss << std::setfill('0') << std::setw(4) << std::hex << number;
      std::string numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::jneSymbol(std::string string2)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('2');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('0');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (string2 == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              std::ostringstream ss;
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, string2, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(string2, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::jnePcrelSymbol(std::string string2)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('2');
      sec.code.push_back('f');
      sec.code.push_back('7');
      sec.code.push_back('0');
      sec.code.push_back('5');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (string2 == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              std::ostringstream ss;
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, string2, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(string2, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::jneMemNum(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('2');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('4');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(4) << std::hex << number;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::jneMemSymbol(std::string string2)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('2');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('4');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (string2 == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              std::ostringstream ss;
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, string2, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(string2, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::jneReg(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('2');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('1');
    }
  }
  Asembler::offset += 3;
}

void Asembler::jneMemReg(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('2');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('2');
    }
  }
  Asembler::offset += 3;
}

void Asembler::jneMemRegNum(int number1, int number2)
{
  if (number2 > pow(2, 15) - 1)
  {
    number2 -= pow(2, 16);
  }
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('2');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('3');
      numberString = "";
      ss.clear();
      ss << std::setfill('0') << std::setw(4) << std::hex << number2;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::jneMemRegSymbol(int number, std::string symbol)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('2');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();
      ss.clear();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('3');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (symbol == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, symbol, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(symbol, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::jgtNum(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('3');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('0');
      std::ostringstream ss;
      ss << std::setfill('0') << std::setw(4) << std::hex << number;
      std::string numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::jgtSymbol(std::string string2)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('3');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('0');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (string2 == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              std::ostringstream ss;
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, string2, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(string2, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::jgtPcrelSymbol(std::string string2)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('3');
      sec.code.push_back('f');
      sec.code.push_back('7');
      sec.code.push_back('0');
      sec.code.push_back('5');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (string2 == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              std::ostringstream ss;
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, string2, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(string2, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::jgtMemNum(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('3');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('4');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(4) << std::hex << number;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::jgtMemSymbol(std::string string2)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('3');
      sec.code.push_back('f');
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('4');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (string2 == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              std::ostringstream ss;
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, string2, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(string2, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::jgtReg(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('3');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('1');
    }
  }
  Asembler::offset += 3;
}

void Asembler::jgtMemReg(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('3');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('2');
    }
  }
  Asembler::offset += 3;
}

void Asembler::jgtMemRegNum(int number1, int number2)
{
  if (number2 > pow(2, 15) - 1)
  {
    number2 -= pow(2, 16);
  }
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('3');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('3');
      numberString = "";
      ss.clear();
      ss << std::setfill('0') << std::setw(4) << std::hex << number2;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::jgtMemRegSymbol(int number, std::string symbol)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('5');
      sec.code.push_back('3');
      sec.code.push_back('f');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();
      ss.clear();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('3');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (symbol == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, symbol, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(symbol, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}
void Asembler::push(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('b');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('6');

      sec.code.push_back('3');
      sec.code.push_back('2');
    }
  }

  Asembler::offset += 3;
}

void Asembler::pop(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('a');
      sec.code.push_back('0');

      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('6');
      sec.code.push_back('2');
      sec.code.push_back('2');
    }
  }
  Asembler::offset += 3;
}

void Asembler::xchg(int number1, int number2)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('6');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(2) << std::hex << number1;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);

      ss.clear();
      ss << std::setfill('0') << std::setw(2) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 2;
}

void Asembler::add(int number1, int number2)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('7');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      ss << std::setfill('0') << std::setw(1) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 2;
}

void Asembler::sub(int number1, int number2)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('7');
      sec.code.push_back('1');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      ss << std::setfill('0') << std::setw(1) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 2;
}

void Asembler::mul(int number1, int number2)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('7');
      sec.code.push_back('2');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      ss << std::setfill('0') << std::setw(2) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 2;
}

void Asembler::div(int number1, int number2)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('7');
      sec.code.push_back('3');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      ss << std::setfill('0') << std::setw(1) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 2;
}

void Asembler::cmp(int number1, int number2)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('7');
      sec.code.push_back('4');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      ss << std::setfill('0') << std::setw(1) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 2;
}

void Asembler::notReg(int number)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('8');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
    }
  }
  Asembler::offset += 2;
}

void Asembler::andReg(int number1, int number2)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('8');
      sec.code.push_back('1');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      ss << std::setfill('0') << std::setw(1) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 2;
}

void Asembler::orReg(int number1, int number2)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('8');
      sec.code.push_back('2');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      ss << std::setfill('0') << std::setw(1) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 2;
}

void Asembler::xorReg(int number1, int number2)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('8');
      sec.code.push_back('3');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      ss << std::setfill('0') << std::setw(1) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 2;
}

void Asembler::test(int number1, int number2)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('8');
      sec.code.push_back('4');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      ss << std::setfill('0') << std::setw(1) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 2;
}

void Asembler::shl(int number1, int number2)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('9');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      ss << std::setfill('0') << std::setw(1) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 2;
}

void Asembler::shr(int number1, int number2)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('9');
      sec.code.push_back('1');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      ss << std::setfill('0') << std::setw(1) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 2;
}

void Asembler::ldrValNum(int number1, int number2)
{

  if (number2 > pow(2, 15) - 1)
  {
    number2 -= pow(2, 16);
  }

  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('a');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();
      //  std::cout << numberString << std::endl;

      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('0');

      ss.clear();
      ss << std::setfill('0') << std::setw(4) << std::hex << number2;
      numberString = ss.str();
      //  std::cout << numberString << std::endl;
      for (int i = numberString.length() - 4; i <= numberString.length() - 1; i++)
      {
        sec.code.push_back(numberString[i]);
      }
    }
  }
  Asembler::offset += 5;
}

void Asembler::ldrValSymbol(int number, std::string symbol)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('a');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);

      ss.clear();
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('0');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (symbol == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, symbol, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(symbol, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::ldrMemNum(int number1, int number2)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('a');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      sec.code.push_back('0');

      sec.code.push_back('0');
      sec.code.push_back('4');
      ss << std::setfill('0') << std::setw(4) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::ldrMemSymbol(int number, std::string symbol)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('a');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);

      ss.clear();
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('4');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (symbol == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, symbol, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(symbol, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::ldrPcrelSymbol(int number, std::string symbol)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('a');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);

      ss.clear();
      sec.code.push_back('7');
      sec.code.push_back('0');
      sec.code.push_back('5');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (symbol == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, symbol, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(symbol, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::ldrReg(int number1, int number2)
{

  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('a');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      ss << std::setfill('0') << std::setw(1) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('1');
    }
  }
  Asembler::offset += 3;
}

void Asembler::ldrMemReg(int number1, int number2)
{

  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {

      sec.code.push_back('a');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      ss << std::setfill('0') << std::setw(1) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('2');
    }
  }
  Asembler::offset += 3;
}

void Asembler::ldrMemRegNum(int number1, int number2, int number3)
{

  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      //  std::cout << sec.name << " " << Asembler::offset << std::endl;
      sec.code.push_back('a');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      ss << std::setfill('0') << std::setw(1) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('3');
      ss.clear();
      ss << std::setfill('0') << std::setw(4) << std::hex << number3;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::ldrMemRegSymbol(int number1, int number2, std::string symbol)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('a');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();
      ss.clear();
      sec.code.push_back(numberString[numberString.size() - 1]);
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();
      ss.clear();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('3');

      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (symbol == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, symbol, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(symbol, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::strMemNum(int number1, int number2)
{
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('b');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      sec.code.push_back('0');

      sec.code.push_back('0');
      sec.code.push_back('4');
      ss << std::setfill('0') << std::setw(4) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::strMemSymbol(int number, std::string symbol)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('b');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);

      ss.clear();
      sec.code.push_back('0');
      sec.code.push_back('0');
      sec.code.push_back('4');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (symbol == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, symbol, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(symbol, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::strPcrelSymbol(int number, std::string symbol)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('b');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);

      ss.clear();
      sec.code.push_back('7');
      sec.code.push_back('0');
      sec.code.push_back('5');
      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (symbol == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, symbol, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(symbol, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::strReg(int number1, int number2)
{

  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('b');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      ss << std::setfill('0') << std::setw(1) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('1');
    }
  }
  Asembler::offset += 3;
}

void Asembler::strMemReg(int number1, int number2)
{

  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('b');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      ss << std::setfill('0') << std::setw(1) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('2');
    }
  }
  Asembler::offset += 3;
}

void Asembler::strMemRegNum(int number1, int number2, int number3)
{

  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('b');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 1]);
      ss.clear();
      ss << std::setfill('0') << std::setw(1) << std::hex << number2;
      numberString = ss.str();

      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('3');
      ss.clear();
      ss << std::setfill('0') << std::setw(4) << std::hex << number2;
      numberString = ss.str();
      sec.code.push_back(numberString[numberString.size() - 4]);
      sec.code.push_back(numberString[numberString.size() - 3]);
      sec.code.push_back(numberString[numberString.size() - 2]);
      sec.code.push_back(numberString[numberString.size() - 1]);
    }
  }
  Asembler::offset += 5;
}

void Asembler::strMemRegSymbol(int number1, int number2, std::string symbol)
{
  bool found = false;
  for (Section &sec : Asembler::code)
  {
    if (sec.name == Asembler::sectionName)
    {
      sec.code.push_back('b');
      sec.code.push_back('0');
      std::ostringstream ss;
      std::string numberString = "";
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();
      ss.clear();
      sec.code.push_back(numberString[numberString.size() - 1]);
      ss << std::setfill('0') << std::setw(1) << std::hex << number1;
      numberString = ss.str();
      ss.clear();
      sec.code.push_back(numberString[numberString.size() - 1]);
      sec.code.push_back('0');
      sec.code.push_back('3');

      Asembler::offset += 3;
      for (Symbol sym : Asembler::symbolTable)
      {
        if (symbol == sym.name)
        {
          found = true;
          if (sym.defined == true)
          {
            if (sym.sectionName == sec.name)
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              ss << std::hex << sym.value;
              std::string hexVal = ss.str();
              std::string pushBack = "";
              for (int i = 4; i > hexVal.length(); i--)
              {
                pushBack += "0";
              }
              pushBack = pushBack + hexVal;
              std::string value = "";
              for (int i = 2; i >= 0; i--)
              {
                value += pushBack[i];
              }
              for (int i = 4; i >= 3; i--)
              {
                value += pushBack[i];
              }
              for (int i = 0; i < 4; i++)
              {
                //  sec.code.push_back(value[i]);
                sec.code.push_back(pushBack[i]);
              }
            }
            else
            {
              Asembler::relocationTable.push_back(Relocation(Asembler::sectionName, sym.sectionName, sym.value, Asembler::offset, sym.name));
              {
                for (int i = 0; i < 4; i++)
                  sec.code.push_back('0');
              }
            }
          }
          else
          {

            Asembler::backpatch.push_back(Backpatch(sym.name, Asembler::sectionName, Asembler::offset));

            for (int i = 0; i < 4; i++)
              sec.code.push_back('0');
          }
        }
      }
    }
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(0, symbol, "undefined", "undefined", true, false));
    Asembler::backpatch.push_back(Backpatch(symbol, Asembler::sectionName, Asembler::offset));
    for (Section &sec : Asembler::code)
    {
      if (sec.name == Asembler::sectionName)
      {
        for (int i = 0; i < 4; i++)
          sec.code.push_back('0');
      }
    }
  }
  Asembler::offset += 2;
}

void Asembler::label(std::string symbol)
{

  bool found = false;
  std::list<Symbol> symbolTable2 = std::list<Symbol>();
  for (Symbol sym : Asembler::symbolTable)
  {
    if (sym.name == symbol)
    {
      Symbol sym2 = Symbol(Asembler::offset, symbol, Asembler::sectionName, "notype", sym.global, true);
      symbolTable2.push_back(sym2);
      found = true;
    }
    else
      symbolTable2.push_back(sym);
  }
  if (!found)
  {
    Asembler::symbolTable.push_back(Symbol(Asembler::offset, symbol, Asembler::sectionName, "notype", false, true));
  }
  else
  {

    Asembler::symbolTable.swap(symbolTable2);
  }
}

void Asembler::end()
{
  /*
    for (Section &sec : Asembler::code)
    {
      if (sec.name == "my_code")
      {
        if (sec.code.size() == 0)
          std::cout << "ERROR" << std::endl;
      }
      else
      {
        for (char c : sec.code)
        {
          std::cout << c;
        }
        std::cout << std::endl;
      }
    }
  */
  for (Backpatch bp : Asembler::backpatch)
  {
    for (Symbol sym : Asembler::symbolTable)
    {
      if (sym.name == bp.symbol)
      {
        if (sym.sectionName == bp.section)
        {
          Asembler::relocationTable.push_back(Relocation(bp.section, sym.sectionName, sym.value, bp.offset, sym.name, bp.word));
          std::ostringstream ss;
          std::string numberString = "";
          ss << std::setfill('0') << std::setw(4) << std::hex << sym.value;
          for (Section &sec : Asembler::code)
          {
            if (sec.name == sym.sectionName)
            {
              for (int i = 0; i < 4; i++)
              {
                sec.code[bp.offset * 2 + i] = numberString[numberString.size() - 4 + i];
              }
              // std::cout << sec.code[0] << std::endl;
            }
          }
        }
        else
        {
          Asembler::relocationTable.push_back(Relocation(bp.section, sym.sectionName, sym.value, bp.offset, sym.name, bp.word));
        }
      }
    }
  }
  outout_text_file << "/\n";
  for (Symbol sym : Asembler::symbolTable)
  {
    outout_text_file << sym.name << " " << sym.sectionName << " " << sym.type << " " << sym.value << " " << sym.global << " " << sym.defined << "\n";
  }
  outout_text_file << "//\n";
  for (Relocation rel : Asembler::relocationTable)
  {
    outout_text_file << rel.sectionName << " " << rel.symbolName << " " << rel.symbolSectionName << " " << rel.addend << " " << rel.offset << " " << rel.word << "\n";
  }
  outout_text_file << "///\n";
  for (Section &sec : Asembler::code)
  {
    outout_text_file << sec.name << " ";
    for (char c : sec.code)
    {
      outout_text_file << c;
    }
    outout_text_file << "\n";
  }
  outout_text_file << "////";
  /*
    for (Symbol sym : Asembler::symbolTable)
    {
      std::cout << sym.name << " " << sym.sectionName << " " << sym.global << " " << sym.defined << " " << sym.type << " " << sym.value << std::endl;
    }

    for (Relocation rel : Asembler::relocationTable)
    {
      std::cout << rel.addend << " " << rel.symbolName << " " << rel.symbolSectionName << " " << rel.sectionName << " " << rel.offset << std::endl;
    }
    */
  /*
  for(Backpatch bp : Asembler::backpatch)
  {
    std::cout << bp.section << " " << bp.offset << " " << bp.symbol << std::endl;
  }
  */
 outout_text_file.close();
}

int main(int argc, char *argv[])
{
  FILE *myfile;
  Asembler *asembler = new Asembler();
  if (argc != 2 && argc != 4)
  {
    return -1;
  }
  bool name_option_enabled = !(strcmp("-o", argv[1]));
  if (!name_option_enabled)
  {
    myfile = fopen(argv[1], "r");
    outout_text_file.open("asembler.o");
    // make sure it is valid:
    if (!myfile)
    {
      std::cout << "ERROR1" << std::endl;
      return -1;
    }
  }
  else
  {
    myfile = fopen(argv[3], "r");
    // make sure it is valid:
    if (!myfile)
    {
      std::cout << "ERROR2" << std::endl;

      return -1;
    }
    outout_text_file.open(argv[2]);
  }
  // Set flex to read from it instead of defaulting to STDIN:
  yyin = myfile;
  
  // Parse through the input:
  yyparse();
}