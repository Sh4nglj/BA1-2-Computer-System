#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int x = 1;
    int y = -1;
    int z = 0;

    int xB = x << 31;

    cout << ~x << " " << ~y << " " << ~z << endl;
    cout << (x >> 31) << " " << (y >> 31) << " " << (z >> 31) << endl;
    cout << !x << " " << !y << " " << !z << endl;
    cout << ((!x) >> 31) << " " << ((!y) >> 31) << " " << ((!z) >> 31) << endl;
    cout << !(x >> 31) << " " << !(y >> 31) << " " << !(z >> 31) << endl;
}