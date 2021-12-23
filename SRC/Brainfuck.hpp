
#define SET(C, D) newHelpByChar(C, D)
#define IFNOTNULL(A)
#ifndef CODESEGMPTR
//#define DEBUG
#define SOCKET
#include "DataSegm.hpp"
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
class RelttFuck
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
        int errors=0;
        string Vname = "";
        string Vcode="";
        int LINENBR=0;
        LINEATCHARIND = map<int, int>();
        for (int i = 0; i < CodeSegm->size(); i++)
        {
            LINEATCHARIND[i] = LINENBR;
            Vcode+=CodeSegm->at(i);
            switch (CodeSegm->at(i))
            {
            /*case '|':
                if(inVName)
                inVName = (!inValue) && (isCod);
                STOP;*/
            case '[':
                if (isCod)
                    temp->push_back(i);

                STOP case '%' : if (isCod && !((CodeSegm->at(i + 1) == '<') || (CodeSegm->at(i + 1) == '>')))
                {
                    if ((!inValue))
                    {
                        cout <<RED<< "% require that the next char is '<' | '>' at line: "<<endl<<BLUE << LINEATCHARIND[i]+1<<RESET;
                        cout<<Vcode<<RED<<CodeSegm->at(i+1)<<" <-- use ('<' '>')!"<<RESET<<endl;
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
            Vcode="";
                LINENBR++;
                STOP;
            default:
                if (inVName)
                    Vname += CodeSegm->at(i);
                STOP
            }
            CodeOrCom[i] = isCod;
        }
        if(errors>=1)exit(1);
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
        ios_base::openmode fmode;
        fstream K = fstream("", ios::in | ios::out);
        string File = "";
        for (Value i = 0; i < (CodeSegm->size()); i++)
        {
            if (CodeOrCom[i])
                switch (CodeSegm->at(i))
                {
                    ;
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
                case ';':
                    i = CodeSegm->size();
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
                    cout << "Space ERROR you can't have a ' ' in the code! come on!" << endl;
                    exit(0);
                    STOP;
                default:
                    STOP
                }
        }
#if defined(DEBUG)

        cout
            << "Program ended with Value : " << THISCELLVALUE << " at index : " << index << endl;

#endif
    }
    RelttFuck(CODESEGMPTR code)
    {
        VMap = new VMAP;
        temp = new TEMP;
        DataSegmS_ = new DATASEGMPTRMAP;
        MATHCELL = new DATASEGM;
        DataSegm = new DATASEGM;
        CodeSegm = code;
        INIT();
    }
    RelttFuck(const char *code)
    {
        VMap = new VMAP;
        temp = new TEMP;
        MATHCELL = new DATASEGM;
        DataSegmS_ = new DATASEGMPTRMAP;
        DataSegm = new DATASEGM;
        CodeSegm = new CODESEGM(code);
        INIT();
    }
    ~RelttFuck()
    {
        DATASEGMPTRMAP::iterator it;
        for (it = DataSegmS_->begin(); it != DataSegmS_->end(); it++)
        {
            Delete_Cell_SAFFLY(it->second);
        } //*/
        // Delete_Cell_SAFFLY(THISCELL)
        delete this->CodeSegm;
        delete this->temp;
        delete this->DataSegm;
        delete this->DataSegmS_;
        delete this->VMap;
    }
};
#endif