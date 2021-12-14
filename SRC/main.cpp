#include "Brainfuck.hpp"
#include <chrono>
#include <sstream>
#include <time.h>
#include <unistd.h>
int main(int argc, char **argv)
{
    if (argc == 2)
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
        static std::__1::chrono::steady_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> POSTINITMSTIME = t2 - t1;
        cout.precision(10);
        cout << "Took " << POSTINITMSTIME.count() / 1000 << "Second(s) To Execute" << endl;
    }
    else
    {
        cout << "Welcome back " << getenv("USER") << "!" << endl;
        string Fname = "";
        string buff;
        #define IFIS(A) (strcmp(Fname.c_str(), A)==0)
        while (!IFIS("exit;"))
        {
            cout << ">>";
            cin >> Fname;
            buff = string(argv[0]) + " " + Fname;
            if(!IFIS("exit;"))
            system(buff.c_str());
        }
    }
    return 0;
}