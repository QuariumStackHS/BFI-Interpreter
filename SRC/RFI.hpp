
#define SET(C, D) newHelpByChar(C, D)
#define IFNOTNULL(A)
#ifndef CODESEGMPTR
//#define DEBUG
#define SOCKET
#include <chrono>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <time.h>
#include <unistd.h>
#include <vector>
//#include <.RFIPATH.h>
using namespace std;
#define Value int
#define RFIVERSION "0.0.0"
#define VMAP map<Value, Value>
#define DATASEGM Cell
#define CODESEGM string
#define TEMP vector<Value>
#define VMAPPTR VMAP *
#define TEMPPTR TEMP *
#define CODESEGMPTR CODESEGM *
#define DATASEGMPTR DATASEGM *
#define THISCELL DataSegm
#define THISCELLPTR DataSegm *
#define THISCELLVALUE THISCELL->This
#define DATASEGMPTRMAP map<Value, DATASEGMPTR>
#define DATASEGMPTRMAPPTR map<Value, DATASEGMPTR> *
#define MAPINT2BOOL map<int, bool>
#define MAPINT2INT map<int, int>
#define Switchif(a) (CodeSegm[FileName]->at(i - 1) == a)
#define ON(var) ? var : !var
#define ELSE0 :0;
#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */
#define RESET "\033[0m"
#define BLACK "\033[30m"   /* Black */
#define RED "\033[31m"     /* Red */
#define GREEN "\033[32m"   /* Green */
#define YELLOW "\033[33m"  /* Yellow */
#define BLUE "\033[34m"    /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m"    /* Cyan */
struct Cell
{
    Cell *RightCell = nullptr;
    Cell *LeftCell = nullptr;
    Value This = 0;
    Value Index = 0;
    bool locked = 0;
};
Cell *New_Cell()
{
    return new Cell;
}
void Link(Cell *left, Cell *Right)
{
    left->RightCell = Right;
    Right->LeftCell = left;
}

#define STOP \
    ;        \
    break;
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
struct HelpByChar
{
    char c;
    string Desc;
};
string *get_Code(string filename)
{
    ifstream file(filename);
    if (!file.good())
        exit(0);
    stringstream ss;
    ss << file.rdbuf();
    string *ret = new string(ss.str());
    return ret;
}
HelpByChar *newHelpByChar(char c, string Desc)
{
    HelpByChar *P = new HelpByChar();
    P->c = c;
    P->Desc = Desc;
    return P;
}
class RFI
{
public:
    DATASEGMPTR DataSegm;

    // private:
    map<string, CODESEGMPTR> CodeSegm;
    string FileName = "";
    VMAPPTR VMap;
    TEMPPTR temp;
    Value index = 0;
    Value DATAindex = 0;
    DATASEGMPTRMAPPTR DataSegmS_;

    DATASEGMPTR MATHCELL;
    map<string, int> Definition = map<string, int>();
    vector<int> StackRun = vector<int>();
#define THISMATHCELL MATHCELL
#define THISMATHCELLVALUE MATHCELL->This
    MAPINT2BOOL CodeOrCom;
    MAPINT2INT LINEATCHARIND;
#define SaveState (*DataSegmS_)[DATAindex] = THISCELL
#define Go(A)                                                                                 \
    A DATAindex; /*Flaw here*/                                                                \
    \ 
    THISCELL = ((*DataSegmS_)[DATAindex] == nullptr) ? New_Cell() : (*DataSegmS_)[DATAindex]; \
    index = THISCELL->Index;
    DATASEGMPTR LS;
    DATASEGMPTR Go_Left(DATASEGMPTR This)
    {
        index--;
        DATASEGMPTR cell = This->LeftCell;
        if (!cell)
        {
            cell = new Cell;
            cell->Index = index;
            Link(cell, This);
        }
        LS = cell;
        return cell;
    }
    DATASEGMPTR Go_Right(DATASEGMPTR This)
    {
        index++;
        DATASEGMPTR cell = This->RightCell;
        if (!cell)
        {
            cell = new Cell;
            cell->Index = index;
            Link(This, cell);
        }
        LS = cell;
        return cell;
    }
    string ReadtoRight()
    {
        string Ret = "";
        DATASEGMPTR cell = THISCELL;
        while (cell->This != 0)
        {
            cell = cell->RightCell;
            Ret += (char)cell->This;
        }
        return Ret;
    }
    string ReadtoLeft()
    {
        string Ret = "";
        DATASEGMPTR cell = THISCELL;
        while (cell->This != 0)
        {
            cell = cell->LeftCell;
            Ret += (char)cell->This;
        }
        return Ret;
    }
    void INIT()
    {
        Value A;
        Value B;
        bool isCod = 1;
        bool inValue = 0;
        bool inVName = 0;
        int errors = 0;
        string Vname = "";
        string Vcode = "";
        int LINENBR = 0;
        LINEATCHARIND = map<int, int>();
        for (int i = 0; i < CodeSegm[FileName]->size(); i++)
        {
            LINEATCHARIND[i] = LINENBR;
            Vcode += CodeSegm[FileName]->at(i);
            switch (CodeSegm[FileName]->at(i))
            {
            case '|':
                if (inVName)
                {
                    this->Definition[Vname] = i;
                    // exit(0);
                    Vname = "";
                }
                inVName = (!inVName);
                STOP;
            case '(':
                if (isCod && !inValue && (CodeSegm[FileName]->at(i - 1) != '|'))
                {
                    cout << RED << "( require that the Previous char is '|' at line: " << endl
                         << BLUE << LINEATCHARIND[i] + 1 << RESET;
                    cout << Vcode << RED << CodeSegm[FileName]->at(i + 1) << " <-- use ('<' '>')!" << RESET << endl;
                    errors++;
                }
                STOP;
            case '[':
                if (isCod)
                    temp->push_back(i);

                STOP;
            case '%':
                if (isCod && !((CodeSegm[FileName]->at(i + 1) == '<') || (CodeSegm[FileName]->at(i + 1) == '>')))
                {
                    if ((!inValue))
                    {
                        cout << RED << "% require that the next char is '<' | '>' at line: " << endl
                             << BLUE << LINEATCHARIND[i] + 1 << RESET;
                        cout << Vcode << RED << CodeSegm[FileName]->at(i + 1) << " <-- use ('<' '>')!" << RESET << endl;
                        errors++;
                    }
                }
                inValue = !inValue;
                STOP;
            case ']':
                if (isCod)
                {
                    A = temp->at(temp->size() - 1);
                    B = i;
                    temp->pop_back();
                    (*VMap)[A] = B; //&&
                    (*VMap)[B] = A;
                }
                STOP;
            case '#':
                isCod = (i != 0) ? Switchif('\\') ON(isCod) ELSE0;
                STOP;
            case '\n':
                Vcode = "";
                LINENBR++;
                STOP;
            default:
                if (inVName)
                    Vname += CodeSegm[FileName]->at(i);
                STOP
            }
            CodeOrCom[i] = isCod;
        }
        if (temp->size() > 0)
            cout << "error missing ] but we dont know where good luck!" << endl;
        if (errors >= 1)
            exit(1);
    }
    bool PrintasMath = 0;
    void WriteConst(string j)
    {
        DATASEGMPTR Noze = THISCELL;
        for (int i = 0; i < j.size(); i++)
        {
            Noze->This = j[i];
            Go_Right(Noze);
        }
    }
    int ReadConst(int i)
    {
        int Tempindex = index;
        DATASEGMPTR Noze = THISCELL;
        DATASEGMPTR temp = Noze;
        i++;
        char direction = (*CodeSegm[FileName])[i];
        i++;
        int ireplace = 0;
        int jreplace = 0;
        for (int j = i; j < CodeSegm[FileName]->size(); j++)
        {
            if ((*CodeSegm[FileName])[j] == '%' && (*CodeSegm[FileName])[j - 1] == '\\')
            {
            }
            else if ((*CodeSegm[FileName])[j] == '%')
            {
                jreplace = j;
                j = CodeSegm[FileName]->size();
            }
            Noze = (direction == '<') ? Go_Left(Noze) : Go_Right(Noze);
            Noze->This = (int)(*CodeSegm[FileName])[j];
            ireplace = jreplace;

            // printcell(Noze);
        }
        index = Tempindex;
        THISCELL = temp;
        THISCELLVALUE = jreplace - i;

        return ireplace;
    }

    void printcell(DATASEGMPTR T)
    {
        if (PrintasMath)
            cout << to_string(T->This);
        else
            cout << (char)T->This;
    }

    void PerformMath(int *K)
    {
        ++*K;
        // cout << THISMATHCELLVALUE << " | " << THISCELLVALUE << endl;
        switch (CodeSegm[FileName]->at(*K))
        {
#define THISCELLVSMATHCELL(OP)                       \
    \                                                         
        Go_Right(THISMATHCELL)                       \
        ->This = THISCELLVALUE OP THISMATHCELLVALUE; \
    break;
        case '+':
            THISCELLVSMATHCELL(+);
        case '-':
            THISCELLVSMATHCELL(-);
        case '/':
            THISCELLVSMATHCELL(/);
        case '*':
            THISCELLVSMATHCELL(*);
        case '>':
            THISCELLVSMATHCELL(>);
        case '<':
            THISCELLVSMATHCELL(<);
        case '&':
            THISCELLVSMATHCELL(&&);
        case '|':
            THISCELLVSMATHCELL(||);
        case '^':
            THISCELLVSMATHCELL(^);
        case '%':
            THISCELLVSMATHCELL(%);
        case '!':
            THISCELLVSMATHCELL(!=);
        case '=':
            THISCELLVSMATHCELL(==);
        case 'R':
            Go_Right(THISMATHCELL)->This = (rand() % THISCELLVALUE + THISMATHCELLVALUE);
            break;
        default:
            break;
        }
    }

public:
    void ShowHelp()
    {
    }
    void Execute(CODESEGMPTR P)
    {
        CodeSegm[FileName] = P;
        Execute();
    }
    int Execute()
    {
        int ret = 0;
        string inbuff = "";
        string temp = "";
        ios_base::openmode fmode;
        fstream K = fstream("", ios::in | ios::out);
        string File = "";
        string tempcin = "";
        DATASEGMPTR tempptr;
        bool isfnc = 0;
        this->StackRun.push_back(CodeSegm[FileName]->size());
        for (Value i = Definition["Main"] + 2; i < (CodeSegm[FileName]->size()); i++)
        { // cout<<CodeSegm[FileName]->at(i)<<endl;
            if (i == 2)
            {
                i = CodeSegm[FileName]->size();
                cout << RED << "Error Unkown Macro : " << YELLOW << "Main" << RED << ", Please Define" << BOLDCYAN << " |Main|(*" << BLUE << "Code" << BOLDCYAN << "*)" << RESET << RED " inside your code!" << endl;
                exit(1);
            };
            isfnc = (CodeSegm[FileName]->at(i) == ')') ? 0 : isfnc;
            if (!isfnc)
                if (CodeOrCom[i])
                    switch (CodeSegm[FileName]->at(i))
                    {
                        ;
                    case '|':
                        isfnc = 1;
                        STOP;
                    case '<':
                        THISCELL = Go_Left(THISCELL);
                        STOP;
                    case '>':
                        THISCELL = Go_Right(THISCELL);
                        STOP;
                    case '.':
                        printcell(THISCELL);
                        STOP;
                    case ',':
                        THISCELLVALUE = (!DataSegm->locked) ? getchar() : THISCELLVALUE;
                        STOP;
                    case '+':
                        if (!DataSegm->locked)
                            THISCELLVALUE++;
                        STOP;
                    case '-':
                        if (!DataSegm->locked)
                            THISCELLVALUE--;
                        STOP;
                    case '^':
                        Go(++);
                        STOP;
                    case 'V':
                        Go(--);
                        STOP;
                    case '$':
                        if (!DataSegm->locked)
                            THISCELLVALUE = (!DataSegm->locked) ? system(ReadtoRight().c_str()) : THISCELLVALUE;
                        STOP;
                    case 'L':
                        DataSegm->locked = 1;
                        STOP;
                    case 'l':
                        DataSegm->locked = 0;
                        STOP;
                    case '_':
                        if (!DataSegm->locked)
                            THISCELLVALUE = THISMATHCELLVALUE;
                        STOP;
                    case '@':
                        SaveState;
                        STOP;
                    case '(':
                        isfnc = 1;
                        STOP;
                    case ')':
                        isfnc = 0;
                        STOP;
                    case '=':
                        StackRun.push_back(i + 1);
                        temp = (CodeSegm[FileName]->at(i + 1) == '<') ? ReadtoLeft() : ReadtoRight();
                        temp.pop_back();
                        i = Definition[temp] + 1;
                        if (i == 1)
                        {
                            i = CodeSegm[FileName]->size();
                            cout << RED << "Error Unkown Macro : " << YELLOW << temp << RED << " at line : " << BLUE << LINEATCHARIND[i] + 1 << RESET << endl;
                        }
                        temp = "";
                        STOP;
                    case ';':
                        // cout<< (StackRun.size()>0)<<endl;
                        if (StackRun.size() > 0)
                        {
                            i = StackRun[StackRun.size() - 1];
                            // cout<<i<<endl;
                            StackRun.pop_back();
                        }
                        else
                        {
                            ret = THISCELLVALUE;
                            i = CodeSegm[FileName]->size();
                        }
                        STOP;
                    case 'E':
                        tempptr=THISCELL;
                        THISCELL=THISMATHCELL;
                        THISMATHCELL=tempptr;
                        STOP;
                    case '&':
                        File = (CodeSegm[FileName]->at(i + 2) == '<') ? ReadtoLeft() : ReadtoRight();
                        fmode = (CodeSegm[FileName]->at(i + 1) == 'W') ? ios::out : ios::in;
                        K.open(File, fmode);
                        STOP;
                    case '?':
                        if (!DataSegm->locked)
                        {
                            THISCELLVALUE = (int)K.get();
                            THISCELLVALUE = (-1 == THISCELLVALUE) ? 0 : THISCELLVALUE;
                        }
                        STOP;
                    case '/':
                        if (THISCELLVALUE)
                            K << (char)THISCELLVALUE;
                        else
                            K << endl;
                        STOP;
                    case '~':
                        sleep(THISCELLVALUE);
                        STOP;
                    case ':':
                        K.close();
                        STOP;
                    case '*':
                        // cout << THISCELLVALUE << endl;
                        if (!DataSegm->locked)
                            THISCELLVALUE = THISCELLVALUE * THISCELLVALUE;
                        STOP;
                    case '0':
                        if (!DataSegm->locked)
                            THISCELLVALUE = 0;
                        STOP;
                    case '[':
                        i = (THISCELLVALUE != 0) ? i : (*VMap)[i];
                        STOP;
                    case ']':
                        i = (THISCELLVALUE != 0) ? (*VMap)[i] : i;
                        STOP;
                    case 'M':
                        PrintasMath = 1;
                        STOP;
                    case 'S':
                        PrintasMath = 0;
                        STOP;
                    case 'G':
                        cin >> tempcin;
                        WriteConst(tempcin);
                        STOP;
                    case '%':
                        i = ReadConst(i);
                        STOP;
                    case '!':
                        DebugPrintAllCells(THISCELL);
                        STOP;
                    case '"':
                        THISMATHCELLVALUE = THISCELLVALUE;
                        STOP;
                    case '}':
                        THISMATHCELL = Go_Right(THISMATHCELL);
                        STOP;
                    case '{':
                        THISMATHCELL = Go_Left(THISMATHCELL);
                        STOP;
                    case '\'':
                        PerformMath(&i);
                        STOP;
#if defined(SOCKET)
                    case 'O':
                        // open socket read ip >
                        STOP;
                    case 'P':
                        // put what is to right in socket to the interet
                        STOP;
                    case 'I':
                        // input from connection to the
                        STOP;
#endif
                    case ' ':
                        // cout << "Space ERROR you can't have a ' ' in the code! come on!" << endl;
                        // exit(0);
                        STOP;
                    default:
                        STOP
                    }
        }
#if defined(DEBUG)

        cout
            << "Program ended with Value : " << THISCELLVALUE << " at index : " << index << endl;

#endif
        return ret;
    }
    void DebugPrintAllCells(DATASEGMPTR head)
    {
        char sp = 0;
        while (head->LeftCell != nullptr)
            head = head->LeftCell;
        while (head != nullptr)
        {
            if (index == head->Index)
                sp = '*';
            else
                sp = 0;
            if (head)
                cout << sp << "[(" << head->This << " , " << head->Index << " )]," << sp;
            head = head->RightCell;
        }
        cout << endl;
    }
    RFI(CODESEGMPTR code)
    {
        VMap = new VMAP;
        temp = new TEMP;
        DataSegmS_ = new DATASEGMPTRMAP;
        MATHCELL = new DATASEGM;
        DataSegm = new DATASEGM;
        CodeSegm[FileName] = code;
        INIT();
    }
    RFI(const char *code)
    {
        VMap = new VMAP;
        temp = new TEMP;
        MATHCELL = new DATASEGM;
        DataSegmS_ = new DATASEGMPTRMAP;
        DataSegm = new DATASEGM;
        CodeSegm[FileName] = new CODESEGM(code);
        INIT();
    }
    ~RFI()
    {
        delete this->CodeSegm[FileName];
        delete this->temp;
        // i know there is not a TOTAL delete
        delete this->DataSegm;
        delete this->DataSegmS_;
        delete this->VMap;
    }
};
string ver_string(int a, int b, int c)
{
    std::ostringstream ss;
    ss << a << '.' << b << '.' << c;
    return ss.str();
}
std::string true_cxx =
#ifdef __clang__
    "clang++";
#else
    "g++";
#endif

std::string getOsName()
{
#ifdef _WIN32
    return "Windows 32-bit";
#elif _WIN64
    return "Windows 64-bit";
#elif __APPLE__ || __MACH__
    return "Mac OSX";
#elif __linux__
    return "Linux";
#elif __FreeBSD__
    return "FreeBSD";
#elif __unix || __unix__
    return "Unix";
#else
    return "Other";
#endif
}
void Help()
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

    vector<HelpByChar *> *List = new vector<HelpByChar *>();
    cout << "RFI Version : " << RFIVERSION << endl;
    cout << RED << "[" << YELLOW << true_cxx << ver_string(__clang_major__, __clang_minor__, __clang_patchlevel__) << BOLDCYAN << "(" << Version << ")" << RESET << RED << " G++ " << YELLOW << ver_string(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__) << RED << "]" << YELLOW << "-> " << getOsName() << RESET << endl;
    List->push_back(SET('<', "Go to The Left Cell(THISCELLPTR=THISCELLPTR->Left)"));
    List->push_back(SET('>', "Go to The Right Cell(THISCELLPTR=THISCELLPTR->Right)"));
    List->push_back(SET('.', "Print the Value of Your Cell (As Char(S) or int(M))"));
    List->push_back(SET(',', "Get from user a char >> Your Cell (As Char(S))"));
    List->push_back(SET('+', "Increment Current Cell (THISCELLVALUE++)"));
    List->push_back(SET('-', "Decrement Current Cell (THISCELLVALUE--)"));
    List->push_back(SET('[', "jump to correct ']' if THISCELLVALUE==0"));
    List->push_back(SET(']', "jump to correct '[' if THISCELLVALUE!=0"));
    List->push_back(SET('L', "Lock THISCELLVALUE to read only"));
    List->push_back(SET('l', "unLock THISCELLVALUE from read only"));
    List->push_back(SET('E', "swap THISCELLPTR and THISMATHCELLPTR"));
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
    List->push_back(SET('!', "Debug char"));
    List->push_back(SET('\'', "Require 1 argument and it is the operator, Right Cell of MathCell = THISCELLVALUE operator THISMATHCELL (a list of operator is: +,-,/,*,<,>,&,|,%,!,=,R;)"));
    List->push_back(SET('=', "Require 1 argument and it is the Direction, run macro defined (See Macro file as exemple)"));
    cout << YELLOW << "──>" << GREEN << " Cell is use here to describe a structure with one Left Cell, Right Cell and an int so it can move < or >\n";
    cout << "    there is a Map of int to Cell pointer that can be use to go \"up\" set the entry of the 'Level' and come back to that state later" << endl;
    string Zeros = "";
    for (int i = 0; i < List->size(); i++)
    {
        if (i < 10 - 1)
            Zeros = "0";
        else
            Zeros = "";
        cout << RED << Zeros << i + 1 << YELLOW << " ──> " << GREEN << List->at(i)->c << RESET << " │ " << BOLDCYAN << List->at(i)->Desc << RESET << endl;
    }
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
    ss2 << PF.rdbuf();
    PF.close();
    string INSPath = ss2.str();
    bool Linked = 0;
    bool isincomment = 0;
    int j = 0;
    for (const auto &entry : filesystem::directory_iterator(path))
    {
        try
        {
            pathp = entry.path().c_str();
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
#define BackslashON(c)  \
    case c:             \
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
                        isincomment = !isincomment;
                        break;
                    default:
                        if (!isincomment)
                            tempnc += temp[k];
                        break;
                    }
                }
            }
            // cout<<pathp<<Linked<<endl;
            if (Linked)
            {
                tempnc = "#include <RFI.hpp>\nint main(){CODESEGM *Code=new CODESEGM(\"" + tempnc + "\");RFI*Int=new RFI(Code);Int->Execute();delete Int;return 0;}";
                op = ofstream(pathp + ".cpp");
                op << tempnc;
                op.close();
                tempnc = "g++ -std=c++17 " + pathp + ".cpp -w -o " + pathp + "_RFI -I" + INSPath + "/.RFIHEADER ;rm " + pathp + ".cpp";
                system(tempnc.c_str());
            }
            tempnc = "";
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
#define RFISTR << "#Link#\n|Update|(%>RFI --update%$;)|PRE_INIT|(@^+++*+@V;)|Compile|(%>" \
               << "g++ -std=c++17 " << p << "/main.cpp -I" << p << " -o RFI 2>Log 1>Log%$;)|Install|([>]%>./RFI --install%$@V%>rm Log ; rm RFI%$@^;)|ERROR_CHECKING|(<'=}_{[S%<NO ERROR!%[<.]^.V%<Install% =< ;]%>Log%&>S[?.]:S%<ERROR!%[<.]^.V;)|Main|(%>Update% =>%>PRE_INIT% => %>Compile% =>>%>ERROR_CHECKING% =>)";
int Update()
{
    ifstream PF(".RFIPATH");
    stringstream ss;
    ss << PF.rdbuf();
    string p = ss.str();
    if (!filesystem::exists(p + "/.RFIHEADER/"))
        system(("mkdir " + p + "/.RFIHEADER/").c_str());

    string np = "cp SRC/RFI.hpp " + p + "/.RFIHEADER/";
    string np3 = "cp SRC/main.cpp " + p + "/.RFIHEADER/";
    ofstream UpdateRFI("Update_RFI");
    p += "/.RFIHEADER";
    UpdateRFI RFISTR;
    system(np3.c_str());
    system(np.c_str());
}
int install()
{
    string p;
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
        p = Paths[ans];
        string command = "cp ./RFI " + Paths[ans];
        system(command.c_str());
    }
    else
    {
        ifstream PF(".RFIPATH");
        stringstream ss;
        ss << PF.rdbuf();
        string command = "cp ./RFI " + ss.str();
        p = ss.str();
        system(command.c_str());
        cout << BLUE << "Updated RFI at : " << YELLOW << ss.str() << RESET << endl;
    }
    if (!filesystem::exists(p + "/.RFIHEADER/"))
        system(("mkdir " + p + "/.RFIHEADER/").c_str());
    string np = "cp SRC/RFI.hpp " + p + "/.RFIHEADER/";
    string np3 = "cp SRC/main.cpp " + p + "/.RFIHEADER/";
    ofstream UpdateRFI("Update_RFI");
    p += "/.RFIHEADER";
    UpdateRFI RFISTR;
    system(np3.c_str());
    system(np.c_str());
    return 0;
}

#endif