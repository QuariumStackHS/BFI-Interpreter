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
[M] print as Math ints
[S] print as String ints
["]begin Commentary&end Commentary
[%]( name direction set in name by first char(<>)) (Set Cells); exemple %<exemplename%
[*]square nbr   √
[@]open file( name direction set in name by first char(<>)) until value is 0 exemple @<@
[?]read next char from file overwriting cell
[!]write char to file
[;]exit program √
*/
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
#ifndef CODESEGMPTR
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
#define THISCELLVALUE THISCELL->This
/*
2 -2 0 0 0 0 0 0 0
2 0 0 0 0 0 0 0 0
++^++[>--*<-]
*/
struct Cell
{
    Cell *RightCell = nullptr;
    Cell *LeftCell = nullptr;
    Value This = 0;
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

#define STOP break;
class ExtendedBrainfuckhehe
{
private:
    CODESEGMPTR CodeSegm;
    VMAPPTR VMap;
    TEMPPTR temp;
    Value index = 0;
    DATASEGMPTR DataSegm;
    Cell *Go_Left(Cell *This)
    {
        index--;
        Cell *cell = This->LeftCell;
        if (!cell)
        {
            cell = new Cell;
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
            Link(This, cell);
        }
        return cell;
    }
    void INIT()
    {
        Value A;
        Value B;
        for (int i = 0; i < CodeSegm->size(); i++)
        {
            switch (CodeSegm->at(i))
            {
            case '[':
                temp->push_back(i);
                STOP case ']' : A = temp->at(temp->size() - 1);
                B = i;
                temp->pop_back();
                (*VMap)[A] = B; //&&
                (*VMap)[B] = A;
                /* code */
                STOP

                    default : STOP
            }
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
        int jreplace=0;
        for (int j = i; j < CodeSegm->size(); j++)
        {
            if ((*CodeSegm)[j] == '%')
            {jreplace=j;
                j = CodeSegm->size();
            }
            Noze = (direction == '<') ? Go_Left(Noze) : Go_Right(Noze);
            Noze->This = (int)(*CodeSegm)[j];
            ireplace = jreplace;

            // printcell(Noze);
        }
        index = Tempindex;
        THISCELL = temp;
        THISCELLVALUE = jreplace-i;

        return ireplace;
    }
    void printcell(Cell *T)
    {
        if (PrintasMath)
            cout << to_string((char)T->This);
        else
            cout << (char)T->This;
    }

public:
    void Execute()
    {
        for (Value i = 0; i < (CodeSegm->size()); i++)
        {
            // cout<<i<<endl;
            switch (CodeSegm->at(i))
            {
            case '<':
                THISCELL = Go_Left(THISCELL);
                STOP case '>' : THISCELL = Go_Right(THISCELL);
                STOP case '.' : printcell(THISCELL);
                STOP case ',' : THISCELL->This = getchar();
                STOP case '+' : THISCELLVALUE++;
                STOP case '-' : THISCELLVALUE--;
                STOP case '[' : i = (THISCELLVALUE != 0) ? i : (*VMap)[i];
                STOP case ']' : i = (THISCELLVALUE != 0) ? (*VMap)[i] : i;
                STOP case 'M' : PrintasMath = 1;
                STOP case 'S' : PrintasMath = 0;
                STOP case '%' : i = ReadConst(i);
                STOP case ';' : i=CodeSegm->size();
                STOP default : STOP
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