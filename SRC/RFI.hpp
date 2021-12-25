
#define SET(C, D) newHelpByChar(C, D)
#define IFNOTNULL(A)
#ifndef CODESEGMPTR
//#define DEBUG
#define SOCKET
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
#define Value int
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
#define Switchif(a) (CodeSegm->at(i - 1) == a)
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
};
static vector<Cell*> CellVector= vector<Cell*>();
Cell *New_Cell()
{ Cell*ret=new Cell;
    CellVector.push_back(ret);
    return ret;
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
HelpByChar *newHelpByChar(char c, string Desc)
{
    HelpByChar *P = new HelpByChar();
    P->c = c;
    P->Desc = Desc;
    return P;
}
class RFI
{
private:
    CODESEGMPTR CodeSegm;
    VMAPPTR VMap;
    TEMPPTR temp;
    Value index = 0;
    Value DATAindex = 0;
    DATASEGMPTRMAPPTR DataSegmS_;
    DATASEGMPTR DataSegm;
    DATASEGMPTR MATHCELL;
    map<string, int> Definition = map<string, int>();
    vector<int> StackRun = vector<int>();
#define THISMATHCELL MATHCELL
#define THISMATHCELLVALUE MATHCELL->This
    MAPINT2BOOL CodeOrCom;
    MAPINT2INT LINEATCHARIND;
#define SaveState (*DataSegmS_)[DATAindex] = THISCELL
#define Go(A)                                                                                  \
    A DATAindex; /*Flaw here*/                                                                 \
    \ 
    SaveState = ((*DataSegmS_)[DATAindex] == nullptr) ? New_Cell() : (*DataSegmS_)[DATAindex]; \
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
        for (int i = 0; i < CodeSegm->size(); i++)
        {
            LINEATCHARIND[i] = LINENBR;
            Vcode += CodeSegm->at(i);
            switch (CodeSegm->at(i))
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
                if (isCod && !inValue && (CodeSegm->at(i - 1) != '|'))
                {
                    cout << RED << "( require that the Previous char is '|' at line: " << endl
                         << BLUE << LINEATCHARIND[i] + 1 << RESET;
                    cout << Vcode << RED << CodeSegm->at(i + 1) << " <-- use ('<' '>')!" << RESET << endl;
                    errors++;
                }
                STOP;
            case '[':
                if (isCod)
                    temp->push_back(i);

                STOP;
            case '%':
                if (isCod && !((CodeSegm->at(i + 1) == '<') || (CodeSegm->at(i + 1) == '>')))
                {
                    if ((!inValue))
                    {
                        cout << RED << "% require that the next char is '<' | '>' at line: " << endl
                             << BLUE << LINEATCHARIND[i] + 1 << RESET;
                        cout << Vcode << RED << CodeSegm->at(i + 1) << " <-- use ('<' '>')!" << RESET << endl;
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
                    Vname += CodeSegm->at(i);
                STOP
            }
            CodeOrCom[i] = isCod;
        }
        if (errors >= 1)
            exit(1);
    }
    bool PrintasMath = 0;
    int ReadConst(int i)
    {
        int Tempindex = index;
        DATASEGMPTR Noze = THISCELL;
        DATASEGMPTR temp = Noze;
        i++;
        char direction = (*CodeSegm)[i];
        i++;
        int ireplace = 0;
        int jreplace = 0;
        for (int j = i; j < CodeSegm->size(); j++)
        {
            if ((*CodeSegm)[j] == '%' && (*CodeSegm)[j - 1] == '\\')
            {
            }
            else if ((*CodeSegm)[j] == '%')
            {
                jreplace = j;
                j = CodeSegm->size();
            }
            Noze = (direction == '<') ? Go_Left(Noze) : Go_Right(Noze);
            Noze->This = (int)(*CodeSegm)[j];
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
    void PerformMath(int *K)
    {
        ++*K;
        // cout << THISMATHCELLVALUE << " | " << THISCELLVALUE << endl;
        switch (CodeSegm->at(*K))
        {
#define THISCELLVSMATHCELL(OP)                                         \
    Go_Right(THISMATHCELL)->This = THISCELLVALUE OP THISMATHCELLVALUE; \
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
        case '%':
            THISCELLVSMATHCELL(%);
        case '!':
            THISCELLVSMATHCELL(!=);
        case '=':
            THISCELLVSMATHCELL(==);
        default:
            break;
        }
    }

public:
    void ShowHelp()
    {
    }
    void Execute()
    {
        string inbuff = "";
        string temp = "";
        ios_base::openmode fmode;
        fstream K = fstream("", ios::in | ios::out);
        string File = "";
        bool isfnc = 0;
        for (Value i = 0; i < (CodeSegm->size()); i++)
        {
            isfnc = (CodeSegm->at(i) == ')') ? 0 : isfnc;
            if (!isfnc)
                if (CodeOrCom[i])
                    switch (CodeSegm->at(i))
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
                        THISCELLVALUE = getchar();
                        STOP;
                    case '+':
                        THISCELLVALUE++;
                        STOP;
                    case '-':
                        THISCELLVALUE--;
                        STOP;
                    case '^':
                        Go(++);
                        STOP;
                    case 'V':
                        Go(--);
                        STOP;
                    case '$':
                        THISCELLVALUE = system(ReadtoRight().c_str());
                        STOP;
                    case '_':
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
                        temp = (CodeSegm->at(i + 1) == '<') ? ReadtoLeft() : ReadtoRight();
                        temp.pop_back();
                        i = Definition[temp] + 1;
                        if (i == 1)
                        {
                            i = CodeSegm->size();
                            cout << RED << "Error Unkown Macro : " << YELLOW << temp <<RED<<" at line : "<< BLUE << LINEATCHARIND[i] + 1<< RESET << endl;
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
                            i = CodeSegm->size();
                        }
                        STOP;
                    case '&':
                        File = (CodeSegm->at(i + 2) == '<') ? ReadtoLeft() : ReadtoRight();
                        fmode = (CodeSegm->at(i + 1) == 'W') ? ios::out : ios::in;
                        K.open(File, fmode);
                        STOP;
                    case '?':
                        THISCELLVALUE = (int)K.get();
                        THISCELLVALUE = (-1 == THISCELLVALUE) ? 0 : THISCELLVALUE;
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
                        THISCELLVALUE = THISCELLVALUE * THISCELLVALUE;
                        STOP;
                    case '0':
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
                    default:
                        STOP
                    }
        }
#if defined(DEBUG)

        cout
            << "Program ended with Value : " << THISCELLVALUE << " at index : " << index << endl;

#endif
    }
    RFI(CODESEGMPTR code)
    {
        VMap = new VMAP;
        temp = new TEMP;
        DataSegmS_ = new DATASEGMPTRMAP;
        MATHCELL = new DATASEGM;
        DataSegm = new DATASEGM;
        CodeSegm = code;
        INIT();
    }
    RFI(const char *code)
    {
        VMap = new VMAP;
        temp = new TEMP;
        MATHCELL = new DATASEGM;
        DataSegmS_ = new DATASEGMPTRMAP;
        DataSegm = new DATASEGM;
        CodeSegm = new CODESEGM(code);
        INIT();
    }
    ~RFI()
    {
        int it;
        /*for (it = 0; it != CellVector.size()-1; it++)
        {
            cout<<it<<endl;
            delete &CellVector[it];
        }*/
        // Delete_Cell_SAFFLY(THISCELL)
        delete this->CodeSegm;
        delete this->temp;
        delete this->DataSegm;
        delete this->DataSegmS_;
        delete this->VMap;
    }
};
#endif