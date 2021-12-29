#include "RFI.hpp"
#include <chrono>
#include <filesystem>
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
        List->push_back(SET('=', "Require 1 argument and it is the Direction, run macro defined (See Macro file as exemple)"));
        cout << YELLOW << "-->" << GREEN << " Cell is use here to describe a structure with one Left Cell, Right Cell and an int so it can move < or >\n";
        cout << "    there is a Map of int to Cell pointer that can be use to go \"up\" set the entry of the 'Level' and come back to that state later" << endl;
        for (int i = 0; i < List->size(); i++)
                cout << RED << i << YELLOW << "--> " << GREEN << List->at(i)->c << RESET << " | " << BOLDCYAN << List->at(i)->Desc << RESET << endl;
}
void ONELINE(CODESEGMPTR Code)
{
        for (int i = 0; i < Code->size(); i++)
                if (Code->at(i) == '\n')
                        Code->erase(i, 1);
}

vector<string> Get_Paths()
{
        string P = getenv("PATH");
        string temp = "";
        vector<string> Paths;
        for (int i = 0; i < P.size(); i++)
        {
                if (P[i] == ':')
                {
                        Paths.push_back(temp);
                        temp = "";
                }
                else
                {
                        temp += P[i];
                }
        }
        Paths.push_back(temp);
        Paths.push_back("BFI");
        return Paths;
}
int Uninstall()
{
        if (!filesystem::exists(".RFIPATH"))
        {
                vector<string> Paths = Get_Paths();
                int ans = 0;
                for (int i = 0; i < Paths.size(); i++)
                {
                        cout << RED << i << YELLOW << "--> " << BOLDBLUE << Paths[i] << endl
                             << RESET;
                }
                cout << "type a number : ";
                cin >> ans;
                ofstream PF(".RFIPATH");
                PF << Paths[ans].c_str();
                PF.close();
                string command = "rm " + Paths[ans] + "/RFI";
                system(command.c_str());
        }
        else
        {
                ifstream PF(".RFIPATH");
                stringstream ss;
                ss << PF.rdbuf();
                string command = "rm " + ss.str() + ss.str() + "/RFI";
                if (system(command.c_str()))
                        cout << "Error while unsintalling RFI" << endl;
                else
                        cout << BLUE << "Uninstalled RFI at : " << YELLOW << ss.str() << RESET << endl;
        }
        return 0;
}
int Link()
{
        std::string path = "./";
        ifstream p;
        ofstream op;
        stringstream ss;
        string Found = "#Link#";
        string temp = "";
        string tempnc = "";
        string pathp;
        ifstream PF(".RFIPATH");
        stringstream ss2;
        ss2 << PF.rdbuf();PF.close();
        string INSPath=ss.str();
        bool Linked = 0;
        bool isincomment=0;
        int j = 0;
        for (const auto &entry : filesystem::directory_iterator(path))
        {
                try
                {pathp=entry.path().c_str();
                        p = ifstream(pathp);
                        /*#Linked#*/
                        // cout<<p.<<endl;
                        ss << p.rdbuf();
                        temp = ss.str();
                        // cout<<temp<<endl;
                        while (temp.size() > j)
                        {
                                if (Found[j] == (temp[j]))
                                        j++;
                                else if (temp[j] == '\n')
                                {
                                        Linked = 1;
                                        j = temp.size();
                                }
                                else
                                        j = temp.size();
                        }
                        if (Linked)
                        {
#define BackslashON(c)          \
        case c:                 \
                tempnc += '\\'; \
                tempnc += c;    \
                break;
                                for (int k = 0; k < temp.size(); k++)
                                {
                                        switch (temp[k])
                                        {
                                                BackslashON('"');
                                                BackslashON('\\');
                                                case '\n':
                                                break;
                                                case '#':
                                                isincomment=!isincomment;
                                                break;
                                        default:
                                                if(!isincomment)
                                                tempnc += temp[k];
                                                break;
                                        }
                                }
                        }
                        //cout<<pathp<<Linked<<endl;
                        if(Linked){
                        tempnc="#include <RFI.hpp>\nint main(){CODESEGM *Code=new CODESEGM(\""+tempnc+"\");RFI*Int=new RFI(Code);Int->Execute();delete Int;return 0;}";
                        op=ofstream(pathp+".cpp");
                        op<<tempnc;
                        op.close();
                        tempnc="g++ -std=c++17 "+pathp+".cpp -w -o "+pathp+"_RFI -I"+INSPath+"/.RFIHEADER;rm "+pathp+".cpp";
                        system(tempnc.c_str());
                        }
                        tempnc="";
                        Linked = 0;
                        j = 0;
                        ss = stringstream();
                        p.close();
                }
                catch (...)
                {
                }
        }
}
int install()
{string p;
        if (!filesystem::exists(".RFIPATH"))
        {
                vector<string> Paths = Get_Paths();
                int ans = 0;
                for (int i = 0; i < Paths.size(); i++)
                {
                        cout << RED << i << YELLOW << "--> " << BOLDBLUE << Paths[i] << endl
                             << RESET;
                }
                cout << "type a number : ";
                cin >> ans;
                ofstream PF(".RFIPATH");
                PF << Paths[ans].c_str();
                PF.close();
                p=Paths[ans];
                string command = "cp ./RFI " + Paths[ans];
                system(command.c_str());
        }
        else
        {
                ifstream PF(".RFIPATH");
                stringstream ss;
                ss << PF.rdbuf();
                string command = "cp ./RFI " + ss.str();
                p=ss.str();
                system(command.c_str());
                cout << BLUE << "Updated RFI at : " << YELLOW << ss.str() << RESET << endl;
        }
        if(!filesystem::exists(p+"/.RFIHEADER/"))
        system(("mkdir "+p+"/.RFIHEADER/").c_str());
        string np="cp SRC/RFI.hpp "+p+"/.RFIHEADER/";
        string np3="cp SRC/main.cpp "+p+"/.RFIHEADER/";
        ofstream UpdateRFI("Update_RFI");
        p+="/.RFIHEADER/";
        UpdateRFI<<"#Link#\n|PRE_INIT|(@^+++*+@V;)|Compile|(%>"<<"g++ -std=c++17 "<<p<<"/main.cpp -I"<<p<<"/.RFIHEADER"<<" -o RFI 2>Log 1>Log%$;)|Install|([>]%>./RFI --install%$@V%>rm Log ; rm RFI%$@^;)|ERROR_CHECKING|(<'=}_{[S%<NO ERROR!%[<.]^.V%<Install% =< ;]%>Log%&>S[?.]:S%<ERROR!%[<.]^.V;)%>PRE_INIT% => %>Compile% =>>%>ERROR_CHECKING% =>";
        system(np3.c_str());
        system(np.c_str());

        return 0;
}
int main(int argc, char **argv)
{
        if ((argc == 2) && (strcmp(argv[1], "--help") == 0))
                Help();
        else if ((argc == 2) && (strcmp(argv[1], "--install") == 0))
                install();
        else if ((argc == 2) && (strcmp(argv[1], "--uninstall") == 0))
                Uninstall();
        else if ((argc == 2) && (strcmp(argv[1], "--link") == 0))
                Link();
        else if (argc >= 2)
        {
#ifdef __APPLE__ || __MACH__
                static std::__1::chrono::steady_clock::time_point t1 = std::chrono::high_resolution_clock::now();
#else
                time_t t1 = time(0);
#endif
                ifstream File(argv[1]);
                stringstream ss;
                ss << File.rdbuf();
                string CD = ss.str();
                CODESEGMPTR Code = new CODESEGM(CD);
                RFI *BF = new RFI(Code);
#ifdef __APPLE__ || __MACH__
                static std::__1::chrono::steady_clock::time_point t2 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> POSTINITMSTIME = t2 - t1;
#else
                time_t t2 = time(0);
                time_t InitTime = t2 - t1;
#endif
                BF->Execute();
                // BF->DebugPrintAllCells(BF->DataSegm);
                //  cout<<*Code<<endl;
                delete BF;
#ifdef __APPLE__ || __MACH__
                static std::__1::chrono::steady_clock::time_point t3 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> POSTINITMSTIME2 = t3 - t2;
                cout.precision(6);
                cout << "Took " << POSTINITMSTIME2.count() / 1000 << " Second(s) To Execute && " << POSTINITMSTIME.count() << "Ms for PreExecution" << endl;
#else
                time_t t3 = time(0);
                time_t PostInitTime = t3 - t2;
                cout << "Took " << PostInitTime << " Second(s) To Execute" << endl;
#endif
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