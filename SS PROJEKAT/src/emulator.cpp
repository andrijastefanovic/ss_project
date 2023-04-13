#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <iomanip>
#include <math.h>

unsigned char memory[1 << 16] = {0};
unsigned short r[8] = {0};
unsigned short psw;

void loadMemory(std::ifstream &input_file)
{
  std::string line = "";
  while (getline(input_file, line))
  {
    std::string adress = line.substr(0, 4);
    unsigned index;
    sscanf(adress.c_str(), "%x", &index);
    unsigned pos = 6;
    for (int i = 0; i < 8; i++)
    {
      std::string hex = line.substr(pos, 2);
      unsigned num;
      sscanf(hex.c_str(), "%x", &num);
      memory[index] = (unsigned char)num;
      pos += 3;
      index++;
    }
  }
}

void print_output()
{
    std::cout << "Emulated processor executed halt instruction\nEmulated processor state:\npsw=0b";
  std::bitset<16> x(psw);
    std::cout << x << std::endl;

  for (int i = 0; i < 8; i++)
  {
      std::cout << 'r' << i << "=0x";
    printf("%x ", r[i]);
  }

  return;
}

void software_interrupt()
{
  r[7]++;
  int interruptNumber = memory[r[7]] >> 4;
  r[7]++;
  
  r[6]--;
  memory[r[6]] = r[7] >> 8;
  r[6]--;
  memory[r[6]] = r[7] & 0xFF;
  r[6]--;
  memory[r[6]] = psw >> 8;
  r[6]--;
  memory[r[6]] = psw & 0xFF;
  

  r[7] = *(short *)& memory[(r[interruptNumber] % 8) * 2];
   // std::cout << r[6] << std::endl;
  return;
}

void software_interrupt_return()
{
  r[7]++;
  psw = 0;
  r[7] = 0;
  
  psw = memory[r[6]];
  r[6]++;
  psw |= (unsigned short)memory[r[6]] << 8;
  r[6]++;
  r[7] = (unsigned short) memory[r[6]];
  r[6]++;
  r[7] |= (unsigned short) memory[r[6]] << 8;
  r[6]++;

 // std::cout << r[6] << std::endl;
  return;
}

short getOperand()
{
  short i = 0;
  i = memory[r[7]] << 8;
  r[7]++;
  i |= memory[r[7]];
  r[7]++;
  return i;
}

void call_subroutine()
{
  r[7]++;
  int registerNumber = memory[r[7]] & 0x0F;
  r[7]++;
  int registerMode = memory[r[7]] >> 4;
  int addressMode = memory[r[7]] & 0x0F;
  r[7]++;
//  // // std::cout << addressMode << std::endl;
  switch (addressMode)
  {
  case 0:
  {
    unsigned short value = (unsigned short)getOperand();
    r[6]--;
    memory[r[6]] = r[7] >> 8;
    r[6]--;
    memory[r[6]] = r[7] & 0xFF;
    
    
    r[7] = value;
  }
  break;
  case 1:
  {
    r[6]--;
    memory[r[6]] = r[7] >> 8;
    r[6]--;
    memory[r[6]] = r[7] & 0xFF;
    
    
    r[7] = r[registerNumber];
  }
  break;
  case 2:
  {
    // // std::cout << "POSLEDNJA INSTRUKCIJA?" << std::endl;
    r[6]--;
    memory[r[6]] = r[7] >> 8;
    r[6]--;
    memory[r[6]] = r[7] & 0xFF;
    
    // // std::cout << registerNumber << std::endl;
    // // std::cout << r[registerNumber] << std::endl;
    r[7] = (unsigned short) memory[r[registerNumber] + 1] << 8;
  //  r[7] = 0;
    // // std::cout << r[7] << std::endl;
    r[7] |= (unsigned short) memory[r[registerNumber]];
  // r[7] |= (unsigned short) r[registerNumber];
    // // std::cout << r[7] << std::endl;
  }
  break;
  case 5:
  {
    if (registerNumber == 7)
    {
      unsigned short value = (unsigned short)getOperand();
      r[6]--;
      memory[r[6]] = r[7] >> 8;
      r[6]--;
      memory[r[6]] = r[7] & 0xFF;
      
      r[7] = value;
    }
    else
    {
      short value = getOperand();
      r[6]--;
      memory[r[6]] = r[7] >> 8;
      r[6]--;
      memory[r[6]] = r[7] & 0xFF;
      
      r[7] = r[registerNumber] + value;
    }
  }
  break;
  case 4:
  {
    unsigned short value = (unsigned short)getOperand();
    r[6]--;
    memory[r[6]] = r[7] >> 8;
    r[6]--;
    memory[r[6]] = r[7] & 0xFF;
    
    r[7] = (unsigned short)memory[value + 1] << 8;
    r[7] |= (unsigned short) memory[value];
  }
  case 3:
  {
    short value = getOperand();
    r[6]--;
    memory[r[6]] = r[7] >> 8;
    r[6]--;
    memory[r[6]] = r[7] & 0xFF;
    
    r[7] = (unsigned short)memory[r[registerNumber] + value + 1] << 8;
    r[7] |= (unsigned short) memory[r[registerNumber] + value];
  }
  break;
  }

  // std::cout << r[6] << std::endl;
  return;
}

void return_subroutine()
{
  
  r[7] = memory[r[6]];
  r[6]++;
  r[7] |= (unsigned short)memory[r[6]] << 8;
  r[6]++;
  // std::cout << r[6] << std::endl;
  return;
}

void jump_location()
{
  r[7]++;
  int registerNumber = memory[r[7]] & 0x0F;
  r[7]++;
  int registerMode = memory[r[7]] >> 4;
  int addressMode = memory[r[7]] & 0x0F;
  r[7]++;

  switch (addressMode)
  {
  case 0:
  {
    unsigned short value = (unsigned short)getOperand();

    r[7] = value;
  }
  break;
  case 1:
  {

    r[7] = r[registerNumber];
  }
  case 2:
  {

    r[7] = (unsigned short)memory[r[registerNumber] + 1] << 8;
    r[7] |= (unsigned short) memory[r[registerNumber]];
  }
  break;
  case 5:
  {
    if (registerNumber == 7)
    {
      unsigned short value = (unsigned short)getOperand();

      r[7] = value;
    }
    else
    {
      short value = getOperand();

      r[7] = r[registerNumber] + value;
    }
  }
  break;
  case 4:
  {
    unsigned short value = (unsigned short)getOperand();
    r[7] = (unsigned short)memory[value + 1] << 8;
    r[7] = (unsigned short) memory[value];
  }
  case 3:
  {
    short value = getOperand();

    r[7] = (unsigned short) memory[r[registerNumber] + value + 1] << 8;
    r[7] |= (unsigned short) memory[r[registerNumber] + value];
  }
  break;
  }

  return;
}

void jump_equal_location()
{
  r[7]++;
  int registerNumber = memory[r[7]] & 0x0F;
  r[7]++;
  int registerMode = memory[r[7]] >> 4;
  int addressMode = memory[r[7]] & 0x0F;
  r[7]++;

  switch (addressMode)
  {
  case 0:
  {
    unsigned short value = (unsigned short)getOperand();
    if (psw & 0x01)
      r[7] = value;
  }
  break;
  case 1:
  {

    if (psw & 0x01)
      r[7] = r[registerNumber];
  }
  case 2:
  {

    if (psw & 0x01){
      r[7] = (unsigned short) memory[r[registerNumber] + 1] << 8; 
      r[7] |= (unsigned short) memory[r[registerNumber]];
    }
  }
  break;
  case 5:
  {
    if (registerNumber == 7)
    {
      unsigned short value = (unsigned short)getOperand();

      if (psw & 0x01)
        r[7] = value;
    }
    else
    {
      short value = getOperand();

      if (psw & 0x01)
        r[7] = r[registerNumber] + value;
    }
  }
  break;
  case 4:
  {
    unsigned short value = (unsigned short)getOperand();
    if (psw & 0x01)
    {
      r[7] = (unsigned short) memory[value + 1] << 8;
      r[7] |= (unsigned short) memory[value];
    }
  }
  case 3:
  {
    unsigned short value = (unsigned short)getOperand();

    if (psw & 0x01){
      r[7] = (unsigned short) memory[r[registerNumber] + value + 1] << 8;
      r[7] |= (unsigned short) memory[r[registerNumber] + value];
    }
  }
  break;
  }

  return;
}

void jump_not_equal_location()
{
  r[7]++;
  int registerNumber = memory[r[7]] & 0x0F;
  r[7]++;
  int registerMode = memory[r[7]] >> 4;
  int addressMode = memory[r[7]] & 0x0F;
  r[7]++;

  switch (addressMode)
  {
  case 0:
  {
    unsigned short value = (unsigned short)getOperand();
    if (psw & 0x01 == 0)
      r[7] = value;
  }
  break;
  case 1:
  {

    if (psw & 0x01 == 0)
      r[7] = r[registerNumber];
  }
  case 2:
  {

    if (psw & 0x01 == 0)
    {
      r[7] = (unsigned short) memory[r[registerNumber] + 1] << 8;
      r[7] |= (unsigned short) memory[r[registerNumber]];
    }
  }
  break;
  case 5:
  {
    if (registerNumber == 7)
    {
      unsigned short value = (unsigned short)getOperand();

      if (psw & 0x01 == 0)
        r[7] = value;
    }
    else
    {
      short value = getOperand();

      if (psw & 0x01 == 0)
        r[7] = r[registerNumber] + value;
    }
  }
  break;
  case 4:
  {
    unsigned short value = (unsigned short)getOperand();
    if (psw & 0x01 == 0)
    {
      r[7] = (unsigned short)memory[value + 1] << 8;
      r[7] |= (unsigned short) memory[value];
    }
  }
  case 3:
  {
    short value = getOperand();

    if (psw & 0x01 == 0)
    {
      r[7] = (unsigned short) memory[r[registerNumber] + value + 1] << 8;
      r[7] |= (unsigned short) memory[r[registerNumber] + value];
    }
  }
  break;
  }

  return;
}

void jump_greater_location()
{
  r[7]++;
  int registerNumber = memory[r[7]] & 0x0F;
  r[7]++;
  int registerMode = memory[r[7]] >> 4;
  int addressMode = memory[r[7]] & 0x0F;
  r[7]++;

  switch (addressMode)
  {
  case 0:
  {
    unsigned short value = (unsigned short)getOperand();
    if (psw & 0x01 == 0 && (psw >> 1 & 0x01 == psw >> 2 & 0x01))
      r[7] = value;
  }
  break;
  case 1:
  {

    if (psw & 0x01 == 0 && (psw >> 1 & 0x01 == psw >> 2 & 0x01))
      r[7] = r[registerNumber];
  }
  case 2:
  {

    if (psw & 0x01 == 0 && (psw >> 1 & 0x01 == psw >> 2 & 0x01))
    {
      r[7] = (unsigned short) memory[r[registerNumber] + 1] << 8;
      r[7] |= (unsigned short) memory[r[registerNumber]];
    }
  }
  break;
  case 5:
  {
    if (registerNumber == 7)
    {
      unsigned short value = (unsigned short)getOperand();

      if (psw & 0x01 == 0 && (psw >> 1 & 0x01 == psw >> 2 & 0x01))
        r[7] = value;
    }
    else
    {
      short value = getOperand();

      if (psw & 0x01 == 0 && (psw >> 1 & 0x01 == psw >> 2 & 0x01))
        r[7] = r[registerNumber] + value;
    }
  }
  break;
  case 4:
  {
    unsigned short value = (unsigned short)getOperand();
    if (psw & 0x01 == 0 && (psw >> 1 & 0x01 == psw >> 2 & 0x01)){
      r[7] = (unsigned short) memory[value + 1] << 8;
      r[7] |= (unsigned short) memory[value];
    }
  }
  case 3:
  {
    short value = getOperand();

    if (psw & 0x01 == 0 && (psw >> 1 & 0x01 == psw >> 2 & 0x01))
    {
      r[7] = (unsigned short) memory[r[registerNumber] + value + 1] << 8;
      r[7] |= (unsigned short) memory[r[registerNumber] + value];
    }
  }
  break;
  }

  return;
}

void swap()
{
  r[7]++;
  int reg1 = memory[r[7]] & 0x0F;
  int reg2 = memory[r[7]] >> 4 & 0x0F;
  short tmp = r[reg1];
  r[reg1] = r[reg2];
  r[reg2] = tmp;
  r[7]++;
  return;
}

void add()
{
  r[7]++;
  int reg2 = memory[r[7]] & 0x0F;
  int reg1 = memory[r[7]] >> 4 & 0x0F;
   // std::cout << r[reg1] << "+" << r[reg2] << "="; 
  r[reg1] += r[reg2];
   // std::cout << r[reg1] << std::endl;
  r[7]++;
  return;
}
void sub()
{
  r[7]++;
  int reg2 = memory[r[7]] & 0x0F;
  int reg1 = memory[r[7]] >> 4 & 0x0F;
  r[reg1] -= r[reg2];
  r[7]++;
  return;
}

void mul()
{
  r[7]++;
  int reg2 = memory[r[7]] & 0x0F;
  int reg1 = memory[r[7]] >> 4 & 0x0F;
  r[reg1] *= r[reg2];
  r[7]++;
  return;
}

void div()
{
  r[7]++;
  int reg2 = memory[r[7]] & 0x0F;
  int reg1 = memory[r[7]] >> 4 & 0x0F;
  r[reg1] /= r[reg2];
  r[7]++;
  return;
}

void cmp()
{
  r[7]++;
  int reg2 = memory[r[7]] & 0x0F;
  int reg1 = memory[r[7]] >> 4 & 0x0F;
  short temp = r[reg1] - r[reg2];
  if (temp == 0)
    psw |= 0x01;
  else
    psw &= ~0x01;
  if (temp < 0)
    psw |= 0x08;
  else
    psw &= ~0x08;
  if (abs(r[reg1]) > abs(r[reg2]))
    psw |= 0x04;
  else
    psw &= ~0x04;
  if (temp >> 15 != r[reg1] >> 15)
    psw |= 0x02;
  else
    psw &= ~0x02;
  r[7]++;
}

void notOperation()
{
  r[7]++;
  int reg = memory[r[7]] >> 4 & 0x0F;
  r[reg] = ~r[reg];
  r[7]++;
}

void andOperation()
{
  r[7]++;
  int reg2 = memory[r[7]] & 0x0F;
  int reg1 = memory[r[7]] >> 4 & 0x0F;
  r[reg1] &= r[reg2];
}

void orOperation()
{
  r[7]++;
  int reg2 = memory[r[7]] & 0x0F;
  int reg1 = memory[r[7]] >> 4 & 0x0F;
  r[reg1] |= r[reg2];
}

void xorOperation()
{
  r[7]++;
  int reg2 = memory[r[7]] & 0x0F;
  int reg1 = memory[r[7]] >> 4 & 0x0F;
  r[reg1] ^= r[reg2];
}

void test()
{
  r[7]++;
  int reg2 = memory[r[7]] & 0x0F;
  int reg1 = memory[r[7]] >> 4 & 0x0F;
  short temp = r[reg1] & r[reg2];
  if (temp == 0)
    psw |= 0x01;
  else
    psw &= ~0x01;
  if (temp < 0)
    psw |= 0x08;
  else
    psw &= ~0x08;
  r[7]++;
}

void shiftLeft()
{
  r[7]++;
  int reg2 = memory[r[7]] & 0x0F;
  int reg1 = memory[r[7]] >> 4 & 0x0F;
  r[reg1] <<= r[reg2];
  if (r[reg1] == 0)
    psw |= 0x01;
  else
    psw &= ~0x01;
  if (r[reg1] < 0)
    psw |= 0x08;
  else
    psw &= ~0x08;
  r[7]++;
}

void shiftRight()
{
  r[7]++;
  int reg2 = memory[r[7]] & 0x0F;
  int reg1 = memory[r[7]] >> 4 & 0x0F;
  r[reg1] >>= r[reg2];
  if (r[reg1] == 0)
    psw |= 0x01;
  else
    psw &= ~0x01;
  if (r[reg1] < 0)
    psw |= 0x08;
  else
    psw &= ~0x08;
  r[7]++;
}

void loadData()
{
  r[7]++;
  int registerNumber1 = memory[r[7]] >> 4;
  int registerNumber2 = memory[r[7]] & 0x0F;
  r[7]++;
  int registerMode = memory[r[7]] >> 4;
  int addressMode = memory[r[7]] & 0x0F;
  r[7]++;
  switch (addressMode)
  {
  case 0:
  {
    unsigned short value = (unsigned short)getOperand();
     // std::cout << value << std::endl;
    // // std::cout << registerNumber1 << std::endl;
    
    r[registerNumber1] = value;
    // std::cout << r[registerNumber1] << std::endl;
  }
  break;
  case 1:
  {
    r[registerNumber1] = r[registerNumber2];
  }
  break;
  case 2:
  {
    if (registerMode == 2 && registerNumber2 == 6)
    {
      unsigned short value = (unsigned short)memory[r[6] + 1] << 8;
      value |= (unsigned short) memory[r[6]];



      r[registerNumber1] = value;
      r[6] += 2;
      // std::cout << r[6] << std::endl;
    }
    else
    {
      // // std::cout << "POSTOJI LI?" << std::endl;
      // // std::cout << r[registerNumber1] << std::endl;
      unsigned short memreg = (unsigned short) memory[r[registerNumber2]] ;
     // // // std::cout << (unsigned short) memory[r[registerNumber2]] << std::endl;
      r[registerNumber1] = (unsigned short)memory[r[registerNumber2] + 1] << 8;
      // // std::cout << memreg << std::endl;
      // // std::cout << (unsigned short) memory[r[registerNumber2]] << std::endl;
    //  r[registerNumber1] |= (unsigned short) memory[r[registerNumber2]];
      r[registerNumber1] |= memreg;
      // // std::cout << r[registerNumber1] << std::endl;
    }
  }
  break;
  case 3:
  {
    short value = getOperand();
     // std::cout << " CHECK " << std::endl;
     for(int i = 0; i < 8 ; i++)
     {
      // std::cout << (unsigned short) memory[r[registerNumber2] + i] << " ";
     }
     // std::cout << "\n";
    r[registerNumber1] = (unsigned short) memory[r[registerNumber2] + value + 1] << 8;
    r[registerNumber1] |= (unsigned short) memory[r[registerNumber2] + value];
  }
  break;
  case 4:
  {
    unsigned short value = (unsigned short)getOperand();
    r[registerNumber1] = (unsigned short) memory[value + 1] << 8;
    r[registerNumber1] |= (unsigned short) memory[value];
  }
  break;
  case 5:
  {
    if (registerNumber2 == 7)
    {
      short value = getOperand();

      r[registerNumber1] = value;
    }
    else
    {
      short value = getOperand();

      r[registerNumber1] = r[registerNumber2] + value;
    }
  }
  break;
  }
  return;
}

void storeData()
{
  r[7]++;
  unsigned short registerNumber1 = memory[r[7]] >> 4;
  unsigned short registerNumber2 = memory[r[7]] & 0x0F;
  r[7]++;
  unsigned short registerMode = memory[r[7]] >> 4;
  unsigned short addressMode = memory[r[7]] & 0x0F;
  r[7]++;
  

  // // std::cout << "REGISTER TO STORE " << r[registerNumber1] << std::endl;
  switch (addressMode)
  {
  case 1:
  {
    r[registerNumber2] = r[registerNumber1];
  }
  break;
  case 2:
  {
    if (registerMode == 3 && registerNumber2 == 6)
    {
      // // std::cout << r[6] << std::endl;
      memory[r[registerNumber2] - 1] = r[registerNumber1] >> 8;
      memory[r[registerNumber2 ] - 2] = r[registerNumber1] & 0xFF;
      
      r[registerNumber2] -= 2;
      // std::cout << r[registerNumber1] << std::endl;
      // std::cout << r[6] << std::endl;
    }
    else
    {
      // // std::cout << (r[registerNumber1] & 0xFF) << std::endl;
      // // std::cout << "STORING" << r[registerNumber2] << std::endl;
      memory[r[registerNumber2]] = r[registerNumber1] & 0xFF;
      memory[r[registerNumber2] + 1] = r[registerNumber1] >> 8;
    }
  }
  break;
  case 3:
  {
    short value = getOperand();
    memory[r[registerNumber2] + value] = r[registerNumber1] & 0xFF;
    memory[r[registerNumber2] + value + 1] = r[registerNumber1] >> 8;
  }
  break;
  case 4:
  {
    unsigned short value = (unsigned short)getOperand();
    memory[value] = r[registerNumber1] & 0xFF;
    memory[value + 1] = r[registerNumber1] >> 8;
  }
  break;
  case 5:
  {
    if (registerNumber2 == 7)
    {
      unsigned short value = (unsigned short)getOperand();
      memory[value] = r[registerNumber1] & 0xFF;
      memory[value + 1] = r[registerNumber1] >> 8;
    }
    else
    {
      short value = getOperand();
      // // std::cout << r[registerNumber1] << std::endl;
      memory[r[registerNumber2] + value] = r[registerNumber1] & 0xFF;
      memory[r[registerNumber2] + value + 1] = r[registerNumber1] >> 8;
    }
  }
  break;
  }
  // // std::cout << (unsigned short) memory[299] << " " << (unsigned short) memory[298] << std::endl;
  return;
}

int main(int argc, char *argv[])
{
  std::ifstream memoryFile(argv[1]);
  loadMemory(memoryFile);
  r[6] = 0xFFFF;
//  // // std::cout << std::setbase(16) << r[6] << std::setbase(10) << std::endl;
//  // // std::cout << std::setbase(16) <<  *(unsigned short*) &memory[0] << std::setbase(10) << std::endl;
//  std::setbase(10);
//  r[7] = *(short *)&memory[0];
// // std::cout << std::setbase(16) << (unsigned short) memory[1] << std::setbase(10) << std::endl;
// // std::cout << std::setbase(16) << (unsigned short) memory[0] << std::setbase(10) << std::endl;
r[7] = (unsigned short) memory[1] << 8;
r[7] += (unsigned short) memory[0];
// // std::cout << std::setbase(16) << r[7] << std::setbase(10) <<std::endl;
  while (r[7] < (1 << 16))
  {
     // std::cout << std::setbase(16) <<  (memory[r[7]] >> 4) << (memory[r[7]] & 0x0F) << " ADDRESS: " << r[7] << std::setbase(10) << std::endl ;
    switch (memory[r[7]] >> 4)
    {
  //  // // std::cout << (memory[r[7]] >> 4) << std::endl;
    case 0:
    {
    
      print_output();
      return 0;
    }
    break;
    case 1:
    {
      software_interrupt();
    }
    break;
    case 2:
    {
      software_interrupt_return();
    }
    break;
    case 3:
    {
      call_subroutine();
    }
    break;
    case 4:
    {
    //  // // std::cout << r[7] << std::endl;
      return_subroutine();
    }
    break;
    case 5:
    {
    //  // // std::cout << std::setbase(16) <<  (memory[r[7]] >> 4) << (memory[r[7]] & 0x0F) << std::setbase(10) << std::endl;
    // // // std::cout << "JUMP" << std::endl;
      switch (memory[r[7]] & 0x0F)
      {
      case 0:
      {
        jump_location();
      }
      break;
      case 1:
      {
        jump_equal_location();
      }
      break;
      case 2:
      {
        jump_not_equal_location();
      }
      break;
      case 3:
      {
        jump_greater_location();
      }
      break;
      }
    }
    break;
    case 6:
    {
      swap();
    }
    break;
    case 7:
    {
      switch (memory[r[7]] & 0x0F)
      {
      case 0:
      {
        add();
      }
      break;
      case 1:
      {
        sub();
      }
      break;
      case 2:
      {
        mul();
      }
      break;
      case 3:
      {
        div();
      }
      break;
      case 4:
      {
        cmp();
      }
      break;
      }
    }
    break;
    case 8:
    {
      switch (memory[r[7]] & 0x0F)
      {
      case 0:
      {
        notOperation();
      }
      break;
      case 1:
      {
        andOperation();
      }
      break;
      case 2:
      {
        orOperation();
      }
      break;
      case 3:
      {
        xorOperation();
      }
      break;
      case 4:
      {
        test();
      }
      break;
      }
    }
    break;
    case 9:
    {
      switch (memory[r[7]] & 0x0F)
      {
      case 0:
      {
        shiftLeft();
      }
      break;
      case 1:
      {
        shiftRight();
      }
      break;
      }
    }
    break;
    case 10:
    {
      loadData();
    }
    break;
    case 11:
    {
      storeData();
    }
    }
  }
  return 0;
}