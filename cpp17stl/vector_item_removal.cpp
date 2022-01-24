#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
    vector<int> intList = {7,8,4,20,2,5,30,2};

    for(auto& i : intList)
    {
        cout << i << ", ";
    }
    cout << endl;

    // Erase-remove idiom
    const auto remove_two (remove(begin(intList), end(intList), 2));

    intList.erase(remove_two, end(intList));

    for(auto& i : intList)
    {
        cout << i << ", ";
    }

    cout << endl;
}
