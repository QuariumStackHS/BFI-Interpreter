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
#define THISCELLPTR DataSegm*
#define THISCELLVALUE THISCELL->This
#define DATASEGMPTRMAP map<Value, DATASEGMPTR>
#define DATASEGMPTRMAPPTR map<Value, DATASEGMPTR> *
#define MAPINT2BOOL map<int, bool>
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
void Link(Cell *left, Cell *Right)
{
    left->RightCell = Right;
    Right->LeftCell = left;
}

#define STOP \
    ;        \
    break;