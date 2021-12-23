#include "Brainfuck.hpp"
#include <chrono>
#include <sstream>
#include <time.h>
#include <unistd.h>

void Help()
{
    vector<HelpByChar *> *List = new vector<HelpByChar *>();
    List->push_back(SET('<', "Go to The Left Cell(THISCELLPTR=THISCELLPTR->Left)"));
    List->push_back(SET('>', "Go to The Right Cell(THISCELLPTR=THISCELLPTR->Right)"));
    List->push_back(SET('.', "Print the Value of Your Cell (As Char(S) or int(M))"));
    List->push_back(SET(',', "Get from user a char >> Your Cell (As Char(S))"));
    List->push_back(SET('+', "Increment Current Cell (THISCELLVALUE++)"));
    List->push_back(SET('-', "Decrement Current Cell (THISCELLVALUE--)"));
    List->push_back(SET('[', "jump to correct ']' if THISCELLVALUE==0"));
    List->push_back(SET(']', "jump to correct '[' if THISCELLVALUE!=0"));
    List->push_back(SET('^', "Set current Cell to Up in 1D map (THIS is a bit complex)"));
    List->push_back(SET('V', "Set current Cell to Down in 1D map (THIS is a bit complex)"));
    List->push_back(SET('$', "read a string in Cell->Right until 0 and run it as sh output is then put in current Cell"));
    List->push_back(SET('_', "Set this cell Value to current pointed Math cell Value"));
    List->push_back(SET('@', "SaveState for ^ & V (THIS is a bit complex)"));
    List->push_back(SET('&', "Require 2 arguments (W | R) (< | >) to set direction to read filename to open and first arg for Write | Read"));
    List->push_back(SET('?', "Set Cell to next char in opened File"));
    List->push_back(SET('/', "Output to file THISCELLVALUE"));
    List->push_back(SET(':', "Close current File"));
    List->push_back(SET('~', "Sleep(THISCELLVALUE)"));
    List->push_back(SET('*', "Square THISCELLVALUE"));
    List->push_back(SET('0', "Set Current Cell to 0"));
    List->push_back(SET('M', "Set Terminal output to Math "));
    List->push_back(SET('S', "Set Terminal output to String "));
    List->push_back(SET('%', "Read in Code a string and set it to the Right'>' or Left'<' exemple %>This is A const%"));
    List->push_back(SET(';', "Terminate Program"));
    List->push_back(SET('"', "Set this Pointed Math Value to this cell Value"));
    List->push_back(SET('}', "Go To the Right on this Math Cell"));
    List->push_back(SET('{', "Go To the Left on this Math Cell"));
    List->push_back(SET('\'', "Require 1 argument and it is the operator, Right Cell of MathCell = THISCELLVALUE operator THISMATHCELL (a list of operator is: +,-,/,*,<,>,&,|,%,!,=;)"));
    cout<<YELLOW<<"-->"<<GREEN<<" Cell is use here to describe a structure with one Left Cell, Right Cell and an int so it can move < or >\n";
    cout<<"    there is a Map of int to Cell pointer that can be use to go \"up\" set the entry of the 'Level' and come back to that state later"<<endl;
    for(int i =0;i<List->size();i++)
        cout <<RED<<i<<YELLOW<< "--> "<<GREEN << List->at(i)->c <<RESET<<" | "<<BOLDCYAN << List->at(i)->Desc <<RESET<< endl;
}
void ONELINE(CODESEGMPTR Code){
    for(int i=0;i<Code->size();i++)if(Code->at(i)=='\n')
        Code->erase(i,1);
}
int main(int argc, char **argv)
{
    if ((argc == 2) && (strcmp(argv[1], "help") == 0))
        Help();

    else if (argc >= 2)
    {

        static std::__1::chrono::steady_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        ifstream File(argv[1]);
        stringstream ss;
        ss << File.rdbuf();
        string CD = ss.str();
        CODESEGMPTR Code = new CODESEGM(CD);
        RelttFuck *BF = new RelttFuck(Code);
        static std::__1::chrono::steady_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> POSTINITMSTIME = t2 - t1;
        
        BF->Execute();
        
        //cout<<*Code<<endl;
        delete BF;
        static std::__1::chrono::steady_clock::time_point t3 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> POSTINITMSTIME2 = t3 - t2;
        cout.precision(6);
        cout << "Took " << POSTINITMSTIME2.count() / 1000 << " Second(s) To Execute && " << POSTINITMSTIME.count() << "Ms for PreExecution" << endl;
    }
    else
    {

        cout << "Welcome back " << getenv("USER") << "!" << endl;
        string Fname = "";
        string buff;

#define IFIS(A) (strcmp(Fname.c_str(), A) == 0)
        while (!IFIS("exit;"))
        {
            cout << ">>";
            cin >> Fname;
            buff = string(argv[0]) + " " + Fname + " -child";

            if (IFIS("help"))
                Help();
            else if (!IFIS("exit;"))
                system(buff.c_str());
        }
    }
    return 0;
}