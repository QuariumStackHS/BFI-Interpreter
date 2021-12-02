#include "Brainfuck.hpp"
#include <sstream>
int main(int argc,char**argv){
    //4GAME
ifstream File(argv[1]);
stringstream ss;
ss<<File.rdbuf();
string CD=ss.str();
CODESEGMPTR Code=new CODESEGM(CD);
ExtendedBrainfuckhehe*BF=new ExtendedBrainfuckhehe(Code);
BF->Execute();
//delete BF;
}