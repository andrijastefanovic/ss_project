%{
#include "bison.tab.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
%}
%option noyywrap
%%
[ \t] ;
.global {return GLOBAL;}
.extern {return EXTERN;}
.section {return SECTION;}
.word {return WORD;}
.skip {return SKIP;}
.end {return END;}
halt {return HALT;}
int {return INT;}
iret {return IRET;}
call {return CALL;}
ret {return RET;}
jmp {return JMP;}
jeq {return JEQ;}
jne {return JNE;}
jgt {return JGT;}
push {return PUSH;}
pop {return POP;}
xchg {return XCHG;}
add {return ADD;}
sub {return SUB;}
mul {return MUL;}
div {return DIV;}
cmp {return CMP;}
not {return NOT;}
and {return AND;}
or {return OR;}
xor {return XOR;}
test {return TEST;}
shl {return SHL;}
shr {return SHR;}
ldr {return LDR;}
str {return STR;}
[$] {return VAL;}
[0][x][A-Fa-f0-9]+ {sscanf(yytext,"%x",&yylval.number);return NUM;}
r[0-7] {yylval.number=atoi(yytext+1);return REG;}
"[" {return REGIND1;}
"]" {return REGIND2;}
sp {yylval.number=6;return REG;}
pc {yylval.number=7;return REG;}
psw {yylval.number=8;return REG;}
% {return PCREL;}
[+] {return PLUS;}
[*] {return STAR;}
\n {return ENDL;}
[-]?[0-9]+ {yylval.number=atoi(yytext);return NUM;}
: {return COLON;}
, {yylval.string=strdup(yytext);return COMMA;}
[a-zA-Z_]+[0-9]* {yylval.string=strdup(yytext);return SYMBOL;}
[#][^\n]* ;
. {std::cout<<"UNSUPPORTED ELEMENT "<<yytext<<std::endl;exit(-1);}
%%
