#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <execution>

using namespace std;

static bool odd(int n) { return n % 2; }

int main(int argc, char** argv)
{
	vector<int> d (50000000);

	mt19937 gen;
	uniform_int_distribution<int> dis(0, 100000);
	auto rand_num ([=] () mutable { return dis(gen); });

    generate(execution::par, begin(d), end(d), rand_num);

    reverse(execution::par, begin(d), end(d));

    auto odds (count_if(execution::par, begin(d), end(d), odd));

    cout << (100.0 * odds / d.size())
         << "% of the numbers are odd.\n";

	return 0;
}
