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
Cell *New_Cell()
{
    return new Cell;
}
void Delete_Cell_SAFFLY(Cell *C)
{
#define ReCycle(CellC)                    \
    if (CellC)                     \
    {                                     \
        Delete_Cell_SAFFLY(CellC); \
        delete CellC;              \
    }
    if (C)
    {
        //ReCycle(C->RightCell);
        //ReCycle(C->LeftCell);
    }
}
void Link(Cell *left, Cell *Right)
{
    left->RightCell = Right;
    Right->LeftCell = left;
}

#define STOP \
    ;        \
    break;