/*
[.]cout     √
[,]cin      √
[<]left     √
[>]right    √
['['] begin while Cell!=0   √
[']'] end while Cell==0     √
[-] decr    √
[+] incr    √
EXT:
[~] wait number of ms in cell
[0] yes 0 is a keyword for.. setting to zero the pointed cell √ alt+shift+o= Ø
["]Save *Cell to MATHCELL
[}]go to Right MATHCELL;
[{]go to Left MATHCELL;
['] '(!<=>+ /\*-) ex: '< : MATHCELL
[M] print as Math ints(ints being cellValue) √
[S] print as String ints √
[^] Save currentcell in map[Dataindex] then increment Dataindex and set currentcell to
[V] Save currentcell in map[Dataindex] then decrement Dataindex and set currentcell to
[#]begin Commentary&end Commentary
[%]( name direction set in name by first char(<>)) (Set Cells); exemple %<exemplename%
[*]square nbr   √
[)]go left until 0 alt + \
[(]go right until 0 alt+shift+ \
[@]save state (for ^ & V)
[&]open file( name direction set in name by first char(<>)) until value is 0 exemple @<@
[$]bash command
[?]read next char from file overwriting cell
[/]write char to file
[:]close file
[!]print all cell
[;]exit program
please concider that this code is a complete fuck to Programmer who would try to understand it
*/
#define IFNOTNULL(A)
#ifndef CODESEGMPTR
//#define DEBUG
#include "DataSegm.hpp"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
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
#define SaveState (*DataSegmS_)[DATAindex] = THISCELL
#define Go(A)                                                                                  \
    A DATAindex;                                                                               \
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
        string Vname;
        for (int i = 0; i < CodeSegm->size(); i++)
        {
            switch (CodeSegm->at(i))
            {
            case '|':
                inVName = (!inValue) && (isCod);
                STOP;
            case '[':
                if (isCod)
                {
                    temp->push_back(i);
                }
                STOP case '%' : if (isCod && !((CodeSegm->at(i + 1) == '<') || (CodeSegm->at(i + 1) == '>')))
                {
                    if ((!inValue))
                    {
                        cout << "% require that the next char is '<' | '>' at" << i << endl;
                        exit(1);
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
            default:

                STOP
            }
            CodeOrCom[i] = isCod;
        }
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
        //cout << THISMATHCELLVALUE << " | " << THISCELLVALUE << endl;
        switch (CodeSegm->at(*K))
        {
#define ITHINKITSBETTER(OP)                                            \
    Go_Right(THISMATHCELL)->This = THISCELLVALUE OP THISMATHCELLVALUE; \
    break;
        case '+':
            ITHINKITSBETTER(+);
        case '-':
            ITHINKITSBETTER(-);
        case '/':
            ITHINKITSBETTER(/);
        case '*':
            ITHINKITSBETTER(*);
        case '\'':
            THISCELLVALUE = THISMATHCELLVALUE;
            break;
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
                case ')':
                    ReadtoLeft();
                    THISCELL = LS;
                    STOP;
                case 'G':
                    cin >> inbuff;
                    cout << inbuff << endl;
                    STOP;
                case '(':
                    ReadtoRight();
                    THISCELL = LS;
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
        delete this->CodeSegm;
        delete this->temp;
        delete this->DataSegm;
        delete this->DataSegmS_;
        delete this->VMap;
    }
};
#endif