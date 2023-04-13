#include "../inc/linker.hpp"

int Linker::offset = 0;
std::list<Asembler> Linker::asemblerList = std::list<Asembler>();
std::list<Symbol> Linker::globalSymbolList = std::list<Symbol>();
std::list<LinkerSection> Linker::sectionList = std::list<LinkerSection>();
std::vector<char> Linker::code = std::vector<char>();
std::vector<std::string> Linker::sectionNames = std::vector<std::string>();
std::vector<int> Linker::numOfSections = std::vector<int>();
std::ofstream output_file;

void Linker::restoreCode(std::ifstream &myfile, int i)
{
  std::string line;
  std::string str1 = "/";
  std::string str2 = "//";
  std::string str3 = "///";
  std::string str4 = "////";
  int status = 0;
  while (getline(myfile, line))
  {
    //  std::cout << line << std::endl;
    if (line == str1)
    {
      Linker::asemblerList.push_back(Asembler(i));
      status = 1;
    }
    else if (line == str2)
      status = 2;
    else if (line == str3)
      status = 3;
    else if (line == str4)
      break;
    else
    {
      switch (status)
      {
      case 1:
      {
        std::string token;
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        while (getline(ss, token, ' '))
        {
          tokens.push_back(token);
        }
        for (Asembler &as : Linker::asemblerList)
        {
          if (std::to_string(i) == as.fileId)
          {
            if (tokens[1] == "undefined")
            {
              as.symbolList.push_back(Symbol(std::stoi(tokens[3]), tokens[0], tokens[1], tokens[2], std::stoi(tokens[4]) == 1, std::stoi(tokens[5]) == 1));
            }
            else
            {
              as.symbolList.push_back(Symbol(std::stoi(tokens[3]), tokens[0], tokens[1] + as.fileId, tokens[2], std::stoi(tokens[4]) == 1, std::stoi(tokens[5]) == 1));
            }
          }
        }
      }
      break;

      case 2:
      {
        std::string token;
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        while (getline(ss, token, ' '))
        {
          tokens.push_back(token);
        }
        for (Asembler &as : Linker::asemblerList)
        {
          if (std::to_string(i) == as.fileId)
          {
            if (tokens[2] == "undefined")
            {
              as.relocationList.push_back(Relocation(tokens[0] + as.fileId, tokens[2], std::stoi(tokens[3]), std::stoi(tokens[4]), tokens[1], std::stoi(tokens[5]) == 1));
            }
            else
            {
              as.relocationList.push_back(Relocation(tokens[0] + as.fileId, tokens[2] + as.fileId, std::stoi(tokens[3]), std::stoi(tokens[4]), tokens[1], std::stoi(tokens[5]) == 1));
            }
          }
        }
      }
      break;
      case 3:
      {
        std::string token;
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        while (getline(ss, token, ' '))
        {
          tokens.push_back(token);
        }
        for (Asembler &as : Linker::asemblerList)
        {
          if (std::to_string(i) == as.fileId)
          {
            int result = -1;

            for (int i = 0; i < Linker::sectionNames.size(); i++)
            {
              if (Linker::sectionNames[i] == tokens[0])
                result = i;
            }
            //  auto result = std::find(Linker::sectionNames.begin(), Linker::sectionNames.end(), tokens[0]);

            int priority1;
            int priority2;
            if (result != -1)
            {
              priority1 = result;
              priority2 = Linker::numOfSections[priority1];
              Linker::numOfSections[priority1]++;
            }
            else
            {
              Linker::sectionNames.push_back(tokens[0]);
              priority1 = Linker::numOfSections.size() - 1;
              priority2 = 0;
              Linker::numOfSections.push_back(1);
            }
            as.sectionList.push_back(Section(tokens[0] + as.fileId, tokens[1], priority1, priority2));
          }
        }
      }
      }
    }
  }
}

void Linker::separateSections()
{

  for (Asembler &as : Linker::asemblerList)
  {
    for (Section &sec : as.sectionList)
    {
      LinkerSection ls(sec.name, sec.code, sec.priority1, sec.priority2);
      for (Symbol &sym : as.symbolList)
      {
        if (sym.defined)
          ls.mySymbols.push_back(sym);
        if (sym.global && sym.defined)
        {
          bool found = false;
          for (Symbol &sym2 : Linker::globalSymbolList)
          {
            if (sym2.name == sym.name)
            {
              found = true;
              if (sym2.sectionName != sym.sectionName)
              {
                std::cout << "ERROR" << std::endl;
                return;
              }
            }
          }
          if (!found)
            Linker::globalSymbolList.push_back(sym);
        }
      }
      for (Relocation &rel : as.relocationList)
      {
        if (rel.sectionName == sec.name)
        {
          ls.relocationList.push_back(rel);
        }
      }
      Linker::sectionList.push_back(ls);
    }
  }
  /*
  for(LinkerSection ls : Linker::sectionList)
  {
    std::cout << ls.name << " " << ls.section.code.size() << " " << ls.mySymbols.size() << " " << ls.relocationList.size() << std::endl;
  }
  for(Symbol sym : Linker::globalSymbolList)
  {
    std::cout << sym.name << " " << sym.sectionName << " " << sym.global << " " << sym.value << std::endl;
  }
  */
}

void Linker::sortList()
{
  Linker::sectionList.sort(Linker::compareByName);
}

void Linker::setSectionStarts()
{
  for (LinkerSection &ls : Linker::sectionList)
  {
    ls.startAddress = Linker::offset;
    Linker::offset += ls.section.code.size() / 2;
  }
  for (LinkerSection &ls : Linker::sectionList)
  {
  //  std::cout << ls.name << " " << ls.startAddress << " " << ls.section.code.size() << std::endl;
  }
}

void Linker::insertCode()
{
  for (LinkerSection &ls : Linker::sectionList)
  {
    for (char c : ls.section.code)
    {
      Linker::code.push_back(c);
    }
  }
}

void Linker::realocate()
{
  for (LinkerSection &ls : Linker::sectionList)
  {
    for (Relocation &rel : ls.relocationList)
    {
      std::string toWrite = "";
      int address = 0;
      if (rel.symbolSectionName != "undefined")
      {
        toWrite = Linker::getValue(rel.word, rel.symbolSectionName, rel.addend);
      }
      else
      {
        toWrite = Linker::getValueOfImportedSymbol(rel.word, rel.symbolName);
      }
      address = Linker::getAddress(rel.sectionName, rel.offset);
      for (int i = 0; i < 4; i++)
      {
        Linker::code[address * 2 + i] = toWrite[i];
      }
    }
  }
}

std::string Linker::getValueOfImportedSymbol(bool word, std::string symbol)
{
  std::string toWrite = "";
  for (Symbol &sym : Linker::globalSymbolList)
  {
    if (sym.name == symbol)
    {
      toWrite = Linker::getValue(word, sym.sectionName, sym.value);
    }
  }
  return toWrite;
}

std::string Linker::getValue(bool word, std::string section, int addend)
{
  int numberToConvert = 0;
  for (LinkerSection &sec : Linker::sectionList)
  {
    if (sec.name == section)
    {
      numberToConvert = sec.startAddress + addend;
    }
  }
  std::ostringstream ss;
  std::string numberString = "";
  ss << std::setfill('0') << std::setw(4) << std::hex << numberToConvert;
  numberString = ss.str();
  if (word)
  {
    std::string stringToReturn = "";
    stringToReturn += numberString[numberString.size() - 2];
    stringToReturn += numberString[numberString.size() - 1];
    stringToReturn += numberString[numberString.size() - 4];
    stringToReturn += numberString[numberString.size() - 3];
    return stringToReturn;
  }
  else
    return numberString;
}

int Linker::getAddress(std::string section, int offset)

{
  int address = 0;
  for (LinkerSection &sec : Linker::sectionList)
  {
    if (sec.name == section)
    {
      address = sec.startAddress + offset;
    }
  }
  return address;
}

void Linker::writeToFile(std::ofstream &output_file)
{
  while(Linker::code.size() % 16 != 0)
  {
    Linker::code.push_back('0');
  }

  for (int i = 0; i < Linker::code.size(); i++)
  {
    if(i % 16 == 0)
    {
    std::ostringstream ss;
    std::string numberString = "";
    ss << std::setfill('0') << std::setw(4) << std::hex << i / 2;
    numberString = ss.str();
    output_file << numberString[numberString.size() - 4];
    output_file << numberString[numberString.size() - 3];
    output_file << numberString[numberString.size() - 2];
    output_file << numberString[numberString.size() - 1];
    output_file << ": ";
    }
    output_file << Linker::code[i];
    if (i % 16 == 15 && i!= Linker::code.size() - 1)
    output_file << "\n";
    else if (i % 2 != 0 && i!= Linker::code.size() - 1) 
     output_file << " ";
    
  }
  

  output_file.close();
  
}

void writeToTerminal()
{
  for (int i = 0; i < Linker::code.size(); i++)
  {
    if(i % 16 == 0)
    {
    std::ostringstream ss;
    std::string numberString = "";
    ss << std::setfill('0') << std::setw(4) << std::hex << i;
    numberString = ss.str();
    std::cout << numberString[numberString.size() - 4];
    std::cout << numberString[numberString.size() - 3];
    std::cout << numberString[numberString.size() - 2];
    std::cout << numberString[numberString.size() - 1];
    std::cout << ": ";
    }
    std::cout << Linker::code[i];
    
    if (i % 2 != 0)
     std::cout << " ";
    if (i % 16 == 15)
    std::cout << "\n";
  }

  std::cout << "WROTE " << Linker::code.size() << std::endl;
  
}

int main(int argc, char *argv[])
{
  std::ofstream output_file;

  Linker *lin = new Linker();
  std::string name = "error.hex";
  FILE *myfile;
  bool name_option_enabled1 = !(strcmp("-o", argv[1]));
  bool name_option_enabled2 = !(strcmp("-o", argv[2]));
  if (name_option_enabled2)
  {
    for (int i = 4; i < argc; i++)
    {
    //  std::cout << i << std::endl;
      std::ifstream file(argv[i]);
      if (!file.is_open())
      {
        std::cout << "error" << std::endl;
        return -1;
      }
      Linker::restoreCode(file, i - 4);
      name = argv[3];
    }
  }
  else if(name_option_enabled1)
  {
    for (int i = 4; i < argc; i++)
    {
    //  std::cout << i << std::endl;
      std::ifstream file(argv[i]);
      if (!file.is_open())
      {
        std::cout << "error" << std::endl;
        return -1;
      }
      Linker::restoreCode(file, i - 4);
      name = argv[3];
    }
  }
  else{
    for (int i = 2; i < argc; i++)
    {
    //  std::cout << i << std::endl;
      std::ifstream file(argv[i]);
      if (!file.is_open())
      {
        std::cout << "error" << std::endl;
        return -1;
      }
      Linker::restoreCode(file, i - 2);
      name = "program.hex";
    }
  }
  Linker::separateSections();
  Linker::sortList();
  Linker::setSectionStarts();
  Linker::insertCode();
  Linker::realocate();

  output_file.open(name);

  if (!output_file) {
    std::cerr << "Failed to open file\n";
    return 1;
  }

 // output_file << "This is a test." << std::endl;
  
  
  //output_file << "This is a test." <<std::endl;

  Linker::writeToFile(output_file);
  output_file.close();
  return 0;
}