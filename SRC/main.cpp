#include "RFI.hpp"

int main(int argc, char **argv)
{srand (time(NULL));
int ret=0;
        if ((argc == 2) && (strcmp(argv[1], "--help") == 0))
                Help();
        else if ((argc == 2) && (strcmp(argv[1], "--install") == 0))
                install();
        else if ((argc == 2) && (strcmp(argv[1], "--uninstall") == 0))
                Uninstall();
        else if ((argc == 2) && (strcmp(argv[1], "--link") == 0))
                Link();
        else if ((argc == 2) && (strcmp(argv[1], "--update") == 0))
                Update();
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
                if(Code->size()>0){
                RFI *BF = new RFI(Code);
#ifdef __APPLE__ || __MACH__
                static std::__1::chrono::steady_clock::time_point t2 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> POSTINITMSTIME = t2 - t1;
#else
                time_t t2 = time(0);
                time_t InitTime = t2 - t1;
#endif
                ret=BF->Execute();
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
                else cout<<"File Doesn't exist: "<<argv[1]<<endl;
        }
        else
        {
                string Version;

                if (__cplusplus == 201703)
                        Version = "C++17";
                else if (__cplusplus == 201402)
                        Version = "C++14";
                else if (__cplusplus == 201103)
                        Version = "C++11";
                else if (__cplusplus == 199711)
                        Version = "C++98";
                else
                        Version = "pre-standard C++";
                cout << "RFI Version : " << RFIVERSION << endl;
                cout << RED << "[" << YELLOW << true_cxx << ver_string(__clang_major__, __clang_minor__, __clang_patchlevel__) << BOLDCYAN << "(" << Version << ")" << RESET << RED << " G++ " << YELLOW << ver_string(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__) << RED << "]" << RESET << endl;

                cout << "Welcome back " << getenv("USER") << "!" << endl;
                string Fname = "";
                string buff;

#define IFIS(A) (strcmp(Fname.c_str(), A) == 0)
string*Code=new string("");
RFI *BF = new RFI(Code);
                while (!IFIS("exit;"))
                {
                        cout <<YELLOW<<"──> "<<CYAN;
                        cin >> Fname;
                        buff = string(argv[0]) + " " + Fname + " -child";
                        if (IFIS("help"))
                                Help();
                                //cout<<Fname.size()<<endl;
                        Code->append(Fname);
                        BF->INIT();
                        BF->Execute(Code);
                        *Code="";
                }
        }
        return ret;
}