#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    auto printOne([](){ cout << "One\n"; });
    auto printTwo([](){ cout << "Two\n"; });

    printOne();
    printTwo();

    auto just_one([](){return 1;});
    auto just_two([]{return 2;});

    cout << just_one() << ", " << just_two() << endl;

    auto plus( [](auto l, auto r){ return l + r; } );

    cout << plus(5,5) << endl;

    cout << plus(string{"a"}, "b") << endl;

    cout << [](auto l, auto r){
        return l + r;
    }(10,15) << endl;

    auto counter([count=0] () mutable { return ++count;} );

    for(int i=0; i<5; i++)
    {
        cout << counter() << ", ";
    }
    cout << endl;

    int a{0};

    auto incrementer([&a]() { ++a; });

    incrementer();
    incrementer();
    incrementer();

    cout << "Value of a: " << a << endl;

    auto plus_ten( [=](auto n) {return plus(n,10);} );

    cout << plus_ten(20) << endl;

    exit(0);
}
