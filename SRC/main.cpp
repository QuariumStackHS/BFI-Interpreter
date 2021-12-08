#include "Brainfuck.hpp"
#include <sstream>
#include <chrono>
#include <unistd.h>
#include <time.h>
int main(int argc, char **argv)
{
    static std::__1::chrono::steady_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    ifstream File(argv[1]);
    stringstream ss;
    ss << File.rdbuf();
    string CD = ss.str();

    CODESEGMPTR Code = new CODESEGM(CD);
    RelttFuck *BF = new RelttFuck(Code);
    
    BF->Execute();
    delete BF;
    //usleep(1);
    static std::__1::chrono::steady_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> POSTINITMSTIME = t2 - t1;
    cout<<"Took "<<POSTINITMSTIME.count()<<"ms To Execute"<<endl;
    
    return 0;
}