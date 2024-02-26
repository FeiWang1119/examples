#include <cstring>
#include <iostream>

using namespace std;

struct Test
{
    bool a;
    int x;
    double y;
};

int main(int argc, char *argv[])
{
    char ch[] = "wangfei";
    char *str = "helloworld";
    cout << strlen(ch) << endl;
    cout << sizeof(ch) << endl;
    cout << strlen(str) << endl;

    cout << alignof(Test) << endl;
    return 0;
}
