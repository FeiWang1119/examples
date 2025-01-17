#include <cstring>
#include <iostream>

using namespace std;

struct Test
{
    bool a;
    int x;
    double y;
};

char testCh()
{
    return 'x';
}

class TestA
{
public:
    TestA() = default;

    ~TestA()
    {
        if (ptext) {
            delete ptext;
            ptext = nullptr;
        }
    }

    TestA(char *p)
    {
        ptext = new char[strlen(p) + 1];
        memset(ptext, '\0', strlen(p) + 1);
        memcpy(ptext, p, strlen(p));
        cout << ptext << endl;
    }

    char &operator[](const size_t i) const { return ptext[i]; }

private:
    char *ptext = nullptr;
};

int main(int argc, char *argv[])
{
    /* char ch[] = "wangfei"; */
    /* char *str = "helloworld"; */
    /* cout << strlen(ch) << endl; */
    /* cout << sizeof(ch) << endl; */
    /* cout << strlen(str) << endl; */

    /* cout << alignof(Test) << endl; */
    /* ch[0] = 'W'; */
    /* cout << ch << endl; */

    /* testCh() = 'X'; */
    /* TestA t; */
    /* t[0] = 'X'; */

    const TestA ct("hello, world!");
    char *p = &ct[0];
    p[0] = 'H';
    cout << ct[0];

    return 0;
}
