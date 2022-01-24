#include <iostream>
#include <ctime>

using namespace std;

uint64_t GetUnixTs()
{
    uint64_t timer = static_cast<uint64_t>(time(nullptr));

    return timer;
}

int main(int argc, char** argv)
{
    if(auto ts(GetUnixTs()); (ts % 2) == 0)
    {
        cout << "Even: " << ts << endl;
    }
    else
    {
        cout << "Odd: " << ts << endl;
    }

    // Will fail to compile. 'ts' is out of scope
    //cout << "Timestamp is " << ts << endl;

    exit(0);
}
