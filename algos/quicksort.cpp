/**
 * Quicksort sorting algorithm
 *
 * Consists of two functions - quicksort and partition.
 *
 * The quicksort entry function divides the array into two partitions
 * along a 'pivot', returned by partition. It recursively calls itself
 * for each side of the partition.
 *
 * The partition function:
 * - picks a pivot (can be random)
 * - sets an index for low-1
 * - iterates from low to high
 * - if element is less than pivot,
 *   increment the index,
 *   swap the element with index
 *
 * - After loop completion
 * - Increment index
 * - Swap index with array[high]
 * - Return index
 */

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

void printVector(const vector<int> v);

int GetRandom();

void quickSort(vector<int>& v, int low, int high);

int partition(vector<int>& v, int low, int high);

void swap(int& a, int& b);

int main(int argc, char** argv)
{
    vector<int> numbers;

    for(int i=0; i<20; i++)
    {
        numbers.push_back(GetRandom());
    }

    printVector(numbers);

    quickSort(numbers, 0, numbers.size()-1);

    printVector(numbers);

    return 0;
}

void printVector(const vector<int> v)
{
    if(!v.empty())
    {
        for(int i=0; i<v.size()-1; i++)
        {
            cout << v[i] << ", ";
        }
        cout << v.back() << endl;
    }
}

int GetRandom()
{
    FILE* urand = fopen("/dev/urandom", "rb");

    if(urand)
    {
        int rand{0};

        fread(&rand, sizeof(int), 1, urand);

        rand = abs(rand);

        rand = (rand%100)+1;

        fclose(urand);

        return rand;
    }
    else
    {
        cerr << "Unable to open file" << endl;
        return -1;
    }
}

void quickSort(vector<int>& v, int low, int high)
{
    if(low<high)
    {
        int pi = partition(v, low, high);

        quickSort(v, low, pi-1);
        quickSort(v, pi+1, high);
    }
}

int partition(vector<int>& v, int low, int high)
{
    int pivot{v[high]};

    int i = low - 1;

    for(int j=low; j<high; j++)
    {
        if(v[j] < pivot)
        {
            ++i;
            swap(v[j], v[i]);
        }
    }
    swap(v[i+1], v[high]);

    return i+1;
}

void swap(int& a, int& b)
{
    int t{a};
    a=b;
    b=t;
}
