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
[0] yes 0 is a keyword for.. setting to zero the pointed cell
[M] print as Math ints
[S] print as String ints
[#]begin Commentary&end Commentary
[%]( name direction set in name by first char(<>)) (Set Cells); exemple %<exemplename%
[*]square nbr   √
[@]open file( name direction set in name by first char(<>)) until value is 0 exemple @<@
[?]read next char from file overwriting cell
[!]write char to file
[;]exit program √
*/

#ifndef CODESEGMPTR
#include "DataSegm.hpp"
class ExtendedBrainfuckhehe
{
private:
    CODESEGMPTR CodeSegm;
    VMAPPTR VMap;
    TEMPPTR temp;
    Value index = 0;
    DATASEGMPTR DataSegm;
    map<int, bool> CodeOrCom = map<int, bool>();
    Cell *Go_Left(Cell *This)
    {
        index--;
        Cell *cell = This->LeftCell;
        if (!cell)
        {
            cell = new Cell;
            cell->Index = index;
            Link(cell, This);
        }
        return cell;
    }
    Cell *Go_Right(Cell *This)
    {
        index++;
        Cell *cell = This->RightCell;
        if (!cell)
        {
            cell = new Cell;
            cell->Index = index;
            Link(This, cell);
        }
        return cell;
    }
    string ReadtoRight(){
        string Ret="";
        Cell *cell
        while (cell->This!=0){
             cell= This->RightCell;
            ret+=(char)cell->This;
        }
        return Ret;
    }
    void INIT()
    {
        Value A;
        Value B;
        bool isCod = 1;
        for (int i = 0; i < CodeSegm->size(); i++)
        {
            switch (CodeSegm->at(i))
            {
            case '[':
                if (isCod)
                {
                    temp->push_back(i);
                }
                STOP case ']' : if (isCod)
                {
                    A = temp->at(temp->size() - 1);
                    B = i;
                    temp->pop_back();
                    (*VMap)[A] = B; //&&
                    (*VMap)[B] = A;
                }
                /* code */
                STOP case '#' : isCod = (CodeSegm->at(i - 1) == '\\') ? isCod : !isCod;
                STOP default : STOP
            }
            CodeOrCom[i] = isCod;
        }
    }
    bool PrintasMath = 0;
    int ReadConst(int i)
    {
        int Tempindex = index;
        Cell *Noze = THISCELL;
        Cell *temp = Noze;
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

    void printcell(Cell *T)
    {
        if (PrintasMath)
            cout << to_string((char)T->This);
        else
            cout << (char)T->This;
    }
    void DebugPrintAllCells(Cell *head)
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
                cout << sp << "[" << to_string((char)head->This) << " ( " << (char)head->This << " , " << head->Index << " )]," << sp;
            head = head->RightCell;
        }
        cout << endl;
    }

public:
    // we whould add a map of Value to bool for comentary
    void Execute()
    {
        ofstream *K;
        for (Value i = 0; i < (CodeSegm->size()); i++)
        {
            // cout<<i<<endl;
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
                    THISCELL->This = getchar();
                    STOP;
                case '+':
                    THISCELLVALUE++;
                    STOP;
                case '-':
                    THISCELLVALUE--;
                    STOP;
                case '*':
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
             << "Program ended with Value : " << to_string((char)THISCELLVALUE) << " at index : " << index << endl;
    }
    ExtendedBrainfuckhehe(CODESEGMPTR code)
    {
        VMap = new VMAP;
        temp = new TEMP;
        DataSegm = new DATASEGM;
        CodeSegm = code;
        INIT();
    }
    ExtendedBrainfuckhehe(const char *code)
    {
        VMap = new VMAP;
        temp = new TEMP;
        DataSegm = new DATASEGM;
        CodeSegm = new CODESEGM(code);
        INIT();
    }
    ~ExtendedBrainfuckhehe()
    {
        delete this->CodeSegm;
        delete this->temp;
        delete this->VMap;
    }
};
#endif