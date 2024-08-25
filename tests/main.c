int globalVar = 5;

struct Structure
{
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
};

struct Structure  function1(int a)
{
    struct Structure structure;
    structure.a = 1;
    structure.b = 2;
    structure.c = 3;
    structure.d = 1;
    structure.e = 2;
    structure.f = 3;
    return structure;
}




int main()
{
    function1(5);
    return globalVar;
}
