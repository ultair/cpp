#include "mmwdeque.h"

int main(int argc, char** argv)
{
    mmw::Deque<int> d;

    for(int i=0; i<130; i++)
    {
        d.push_front(i);
    }

    return 0;
}
