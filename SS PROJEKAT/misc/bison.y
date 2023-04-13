%{
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "../inc/asembler.hpp"
extern int yylex();
extern FILE *yyin;
 
void yyerror(const char *s);
%}
%union{
  int number;
  char *string;
}
%token GLOBAL EXTERN ENDL SECTION WORD COLON SKIP END HALT INT IRET CALL PCREL VAL REGIND1 REGIND2 STAR RET JMP JEQ JNE JGT PUSH POP XCHG ADD SUB MUL DIV CMP NOT AND OR XOR TEST SHL SHR LDR STR
%token<string>SYMBOL 
%token<number>NUM 
%token<number>REG
%token<string>COMMA
%token<string>PLUS
%type<string> SYMBOLLIST
%%

bison:
lines;
lines:
lines line | line;
line:
label | label directive | directive | ENDL;
directive:
GLOBAL SYMBOLLIST ENDL{
  
  Asembler::global($2);
} |
EXTERN SYMBOLLIST ENDL{
  
  Asembler::externSymbols($2);
} | 
SECTION SYMBOL ENDL{
  
  Asembler::section($2);
} | 
WORD SYMBOLLIST ENDL{
  
  Asembler::wordSymbolList($2);
} | 
WORD NUM ENDL{
  
  Asembler::wordNumber($2);
} | 
SKIP NUM ENDL{
  
  Asembler::skip($2);
} | 
END{
  Asembler::end();
} | 
HALT ENDL{
  Asembler::halt();
} |
INT REG ENDL{
  
  Asembler::interrupt($2);
} | 
IRET ENDL{
  Asembler::iret();
} | 
CALL NUM ENDL{
  
  Asembler::callNum($2);
} |
CALL SYMBOL ENDL{
  
  Asembler::callSymbol($2);
} |
CALL PCREL SYMBOL ENDL{
  
  Asembler::callPcrelSymbol($3);
} |
CALL STAR NUM ENDL{
  
  Asembler::callMemNum($3);
} |
CALL STAR SYMBOL ENDL{
  
  Asembler::callMemSymbol($3);
} |
CALL STAR REG ENDL{
  
  Asembler::callReg($3);
} |
CALL STAR REGIND1 REG REGIND2 ENDL{
  
  Asembler::callMemReg($4);
} |
CALL STAR REGIND1 REG PLUS NUM REGIND2 ENDL{
  
  Asembler::callMemRegNum($4,$6);
} |
CALL STAR REGIND1 REG PLUS SYMBOL REGIND2{
  
  Asembler::callMemRegSymbol($4,$6);
} |
RET ENDL{
  Asembler::ret();
} | 
JMP NUM ENDL{
  
  Asembler::jmpNum($2);
} |
JMP SYMBOL ENDL{
  
  Asembler::jmpSymbol($2);
} |
JMP PCREL SYMBOL ENDL{
  
  Asembler::jmpPcrelSymbol($3);
} |
JMP STAR NUM ENDL{
  
  Asembler::jmpMemNum($3);
} |
JMP STAR SYMBOL ENDL{
  
  Asembler::jmpMemSymbol($3);
} |
JMP STAR REG ENDL{
  
  Asembler::jmpReg($3);
} |
JMP STAR REGIND1 REG REGIND2 ENDL{
  
  Asembler::jmpMemReg($4);
} |
JMP STAR REGIND1 REG PLUS NUM REGIND2 ENDL{
  
  Asembler::jmpMemRegNum($4,$6);
} |
JMP STAR REGIND1 REG PLUS SYMBOL REGIND2{
  
  Asembler::jmpMemRegSymbol($4,$6);
} |
JEQ NUM ENDL{
  
  Asembler::jeqNum($2);
} |
JEQ SYMBOL ENDL{
  
  Asembler::jeqSymbol($2);
} |
JEQ PCREL SYMBOL ENDL{
  
  Asembler::jeqPcrelSymbol($3);
} |
JEQ STAR NUM ENDL{
  
  Asembler::jeqMemNum($3);
} |
JEQ STAR SYMBOL ENDL{
  
  Asembler::jeqMemSymbol($3);
} |
JEQ STAR REG ENDL{
  
  Asembler::jeqReg($3);
} |
JEQ STAR REGIND1 REG REGIND2 ENDL{
  
  Asembler::jeqMemReg($4);
} |
JEQ STAR REGIND1 REG PLUS NUM REGIND2 ENDL{
  
  Asembler::jeqMemRegNum($4,$6);
} |
JEQ STAR REGIND1 REG PLUS SYMBOL REGIND2{
  
  Asembler::jeqMemRegSymbol($4,$6);
} |
JNE NUM ENDL{
  
  Asembler::jneNum($2);
} |
JNE SYMBOL ENDL{
  
  Asembler::jneSymbol($2);
} |
JNE PCREL SYMBOL ENDL{
  
  Asembler::jnePcrelSymbol($3);
} |
JNE STAR NUM ENDL{
  
  Asembler::jneMemNum($3);
} |
JNE STAR SYMBOL ENDL{
  
  Asembler::jneMemSymbol($3);
} |
JNE STAR REG ENDL{
  
  Asembler::jneReg($3);
} |
JNE STAR REGIND1 REG REGIND2 ENDL{
  
  Asembler::jneMemReg($4);
} |
JNE STAR REGIND1 REG PLUS NUM REGIND2 ENDL{
  
  Asembler::jneMemRegNum($4,$6);
} |
JNE STAR REGIND1 REG PLUS SYMBOL REGIND2{
  
  Asembler::jneMemRegSymbol($4,$6);
} |
JGT NUM ENDL{
  
  Asembler::jgtNum($2);
} |
JGT SYMBOL ENDL{
  
  Asembler::jgtSymbol($2);
} |
JGT PCREL SYMBOL ENDL{
  
  Asembler::jgtPcrelSymbol($3);
} |
JGT STAR NUM ENDL{
  
  Asembler::jgtMemNum($3);
} |
JGT STAR SYMBOL ENDL{
  
  Asembler::jgtMemSymbol($3);
} |
JGT STAR REG ENDL{
  
  Asembler::jgtReg($3);
} |
JGT STAR REGIND1 REG REGIND2 ENDL{
  
  Asembler::jgtMemReg($4);
} |
JGT STAR REGIND1 REG PLUS NUM REGIND2 ENDL{
  
  Asembler::jgtMemRegNum($4,$6);
} |
JGT STAR REGIND1 REG PLUS SYMBOL REGIND2{
  
  Asembler::jgtMemRegSymbol($4,$6);
} |
PUSH REG ENDL{
  
  Asembler::push($2);
} |
POP REG ENDL{
  
  Asembler::pop($2);
} |
XCHG REG COMMA REG ENDL{
  
  Asembler::xchg($2,$4);
} | 
ADD REG COMMA REG ENDL{
  
  Asembler::add($2,$4);
} |
SUB REG COMMA REG ENDL{
  
  Asembler::sub($2,$4);
} |
MUL REG COMMA REG ENDL{
  
  Asembler::mul($2,$4);
} |
DIV REG COMMA REG ENDL{
  
  Asembler::div($2,$4);
} |
CMP REG COMMA REG ENDL{
  
  Asembler::cmp($2,$4);
} |
NOT REG ENDL{
  
  Asembler::notReg($2);
} |
AND REG COMMA REG ENDL{ 
  
  Asembler::andReg($2,$4);
} | 
OR REG COMMA REG ENDL{
  
  Asembler::orReg($2,$4);
} | 
XOR REG COMMA REG ENDL{
  
  Asembler::xorReg($2,$4);
} | 
TEST REG COMMA REG ENDL{
  
  Asembler::test($2,$4);
} | 
SHL REG COMMA REG ENDL{
  
  Asembler::shl($2,$4);
} | 
SHR REG COMMA REG ENDL{
  
  Asembler::shr($2,$4);
} |
LDR REG COMMA VAL NUM ENDL{
  
  Asembler::ldrValNum($2,$5);
} |
LDR REG COMMA VAL SYMBOL ENDL{
  
  Asembler::ldrValSymbol($2,$5);
} |
LDR REG COMMA NUM ENDL{
  
  Asembler::ldrMemNum($2,$4);
} |
LDR REG COMMA SYMBOL ENDL{
  
  Asembler::ldrMemSymbol($2,$4);
} |
LDR REG COMMA PCREL SYMBOL ENDL{
  
  Asembler::ldrPcrelSymbol($2,$5);
} |
LDR REG COMMA REG ENDL{
  
  Asembler::ldrReg($2,$4);
} |
LDR REG COMMA REGIND1 REG REGIND2 ENDL{
  
  Asembler::ldrMemReg($2,$5);
} |
LDR REG COMMA REGIND1 REG PLUS NUM REGIND2{
  
  Asembler::ldrMemRegNum($2,$5,$7);
} |
LDR REG COMMA REGIND1 REG PLUS SYMBOL REGIND2{
  
  Asembler::ldrMemRegSymbol($2,$5,$7);
} |
STR REG COMMA NUM ENDL{
  
  Asembler::strMemNum($2,$4);
} |
STR REG COMMA SYMBOL ENDL{
  
  Asembler::strMemSymbol($2,$4);
} |
STR REG COMMA PCREL SYMBOL ENDL{
  
  Asembler::strPcrelSymbol($2,$5);
} |
STR REG COMMA REG ENDL{
  
  Asembler::strReg($2,$4);
} |
STR REG COMMA REGIND1 REG REGIND2 ENDL{
  
  Asembler::strMemReg($2,$5);
} |
STR REG COMMA REGIND1 REG PLUS NUM REGIND2{
  
  Asembler::strMemRegNum($2,$5,$7);
} |
STR REG COMMA REGIND1 REG PLUS SYMBOL REGIND2{
  
  Asembler::strMemRegSymbol($2,$5,$7);
};
label:
SYMBOL COLON {
Asembler::label($1);
} | 
SYMBOL COLON ENDL{
Asembler::label($1);
};
SYMBOLLIST:
SYMBOL{$$=$1;}| SYMBOLLIST COMMA SYMBOL{strcpy($$,$1);strcat($$,$2);strcat($$,$3);};
%%
void yyerror(const char *s){
  std::cout<<"ERROR"<<std::endl;
  exit(-1);
}