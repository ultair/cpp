#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int GetRandomInt()
{
    int randInt{0};

    FILE* uRand = fopen ("/dev/urandom", "rb");

    if(uRand)
    {
        size_t res = fread(&randInt, sizeof(int), 1, uRand);

        fclose(uRand);
    }

    return randInt;
}

int main(int argc, char** argv)
{
    vector<int> intList;

    for(int i=0; i<20; i++)
    {
        intList.push_back( GetRandomInt() );
    }

    for(auto& i : intList)
    {
        cout << i << ", ";
    }
    cout << endl;

    // Erase-remove idiom
    const auto isOdd([](int i) { return i%2 != 0; });

    intList.erase( remove_if(begin(intList), end(intList), isOdd), end(intList));

    for(auto& i : intList)
    {
        cout << i << ", ";
    }
    cout << endl;
}
