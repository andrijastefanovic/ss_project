#include <string>
#include <iostream>
#include <stdio.h>
#include <list>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>

#include <cstring>


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
  int addend;
  int offset;
  std::string symbolName;
  bool word;
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
  int priority1;
  int priority2;
  Section(std::string name)
  {
    this->name = name;
  }
  /*
  Section(std::string name, std::string code)
  {
    this->name = name;
    for(int i = 0; i < code.length(); i++)
    {
      this->code.push_back(code[i]);
    }
  }
  */
  Section(std::string name, std::string code, int priority1, int priority2)
  {
    this->name = name;
    for(int i = 0; i < code.length(); i++)
    {
      this->code.push_back(code[i]);
    }
    this->priority1 = priority1;
    this->priority2 = priority2;
  }
  Section()
  {
    this->name = "default";
  }
};

class Asembler
{
  public:
  std::string fileId;
  std::list<Symbol> symbolList;
  std::list<Relocation> relocationList;
  std::list<Section> sectionList;

  Asembler(int id)
  {
    this->fileId = std::to_string(id);
  }
};

class LinkerSection
{
  public:
  LinkerSection(std::string name, std::vector<char> code, int priority1, int priority2)
  {
    this->name = name;
    this->section = Section(name);
    this->section.code = code;
    this->startAddress = 0;
    this->priority1 = priority1;
    this->priority2 = priority2;
  }
  int startAddress;
  int priority1;
  int priority2;
  std::string name;
  std::list<Symbol> mySymbols;
  std::list<Relocation> relocationList; 
  Section section;
  
};

class Linker
{
  static bool compareByName(const LinkerSection &a, const LinkerSection &b) {
    return a.priority1 < b.priority1 || (a.priority1 == b.priority1 && a.priority2 < b.priority2);
}
  public:
  static std::list<LinkerSection> sectionList;
  static std::list<Asembler> asemblerList;
  static std::list<Symbol> globalSymbolList;
  static std::vector<char> code;
  static std::vector<std::string> sectionNames;
  static std::vector<int> numOfSections;
  static int offset;
  static void separateSections();
  static void setSectionStarts();
  static void insertCode();
  static void realocate();
  static void writeToFile(std::ofstream &output_file);
  Linker()
  {
  }
  static void restoreCode(std::ifstream &myfile, int i);
  static void sortList();
  static std::string getValue(bool word, std::string section, int addend);
  static int getAddress(std::string section, int offset);
  static std::string getValueOfImportedSymbol(bool word, std::string symbol);
};