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
[Ø] yes 0 is a keyword for.. setting to zero the pointed cell √ alt+shift+o= Ø
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
[$] bash command
[?]read next char from file overwriting cell
[/]write char to file
[:]close file
[!]print all cell
[;]exit program
*/
#define IFNOTNULL(A)
#ifndef CODESEGMPTR
#include "DataSegm.hpp"
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
    MAPINT2BOOL CodeOrCom;
#define SaveState (*DataSegmS_)[DATAindex] = THISCELL
#define Go(A) \
    A DATAindex;\
    SaveState = ((*DataSegmS_)[DATAindex] == nullptr) ? New_Cell() : (*DataSegmS_)[DATAindex];\
    index = THISCELL->Index;
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
        bool inValue=0;
        for (int i = 0; i < CodeSegm->size(); i++)
        {
            switch (CodeSegm->at(i))
            {
            case '[':
                if (isCod)
                {
                    temp->push_back(i);
                }
                STOP /*case '&' : if (isCod && ((CodeSegm->at(i) != '<') || (CodeSegm->at(i) != '>')))
                {
                    cout<<"& require that the next char is '<' | '>'"<<endl;
                    exit(1);
                }
                STOP case '%': if(isCod && ((CodeSegm->at(i) != '<') || (CodeSegm->at(i) != '>'))){
                    if((!inValue)){
                    cout<<"% require that the next char is '<' | '>'"<<endl;
                    exit(1);
                    }
                }*/
                inValue = (i != 0) ? (CodeSegm->at(i - 1) == '\\') ? inValue : !inValue : 0;
                STOP case ']' : if (isCod)
                {
                    A = temp->at(temp->size() - 1);
                    B = i;
                    temp->pop_back();
                    (*VMap)[A] = B; //&&
                    (*VMap)[B] = A;
                }
                STOP case '#' : isCod = (i != 0) ? (CodeSegm->at(i - 1) == '\\') ? isCod : !isCod : 0;
                STOP default : STOP
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
            if ((*CodeSegm)[j] == '%')
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

public:
    void ShowHelp()
    {
    }
    void Execute()
    {
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
                    system(ReadtoRight().c_str());
                    STOP;
                case ')':
                    ReadtoLeft();
                    STOP;
                case '(':
                    ReadtoRight();
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
                case ':':
                    K.close();
                    STOP;
                case '*':
                    //cout << THISCELLVALUE << endl;
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
                default:
                    STOP
                }
        }
        cout << endl
             << "Program ended with Value : " << THISCELLVALUE << " at index : " << index << endl;
    }
    RelttFuck(CODESEGMPTR code)
    {
        VMap = new VMAP;
        temp = new TEMP;
        DataSegmS_ = new DATASEGMPTRMAP;
        DataSegm = new DATASEGM;
        CodeSegm = code;
        INIT();
    }
    RelttFuck(const char *code)
    {
        VMap = new VMAP;
        temp = new TEMP;
        DataSegmS_ = new DATASEGMPTRMAP;
        DataSegm = new DATASEGM;
        CodeSegm = new CODESEGM(code);
        INIT();
    }
    ~RelttFuck()
    {
        delete this->CodeSegm;
        delete this->temp;
        delete this->VMap;
    }
};
#endif