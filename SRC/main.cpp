#include "Brainfuck.hpp"

int main(int argc,char**argv){
CODESEGMPTR Code=new CODESEGM("S%>Hello_World%[>]+[.<];");
ExtendedBrainfuckhehe*BF=new ExtendedBrainfuckhehe(Code);
BF->Execute();
//delete BF;
}