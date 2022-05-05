#include <iostream>
#include <vector>

template <typename T>
class MyDeque
{
public:
    MyDeque();

    ~MyDeque();

    void push_front(const T& item);

    void push_back(const T& item);

    void pop_front();

    void pop_back();

    T& front();

    T& back();

    void clear();

private:

    static constexpr int blockSize_{1024};

    int mapSize_{100};

    T** blockMap_{nullptr};

    T* front_{nullptr};

    T* back_{nullptr};
};

template <typename T>
MyDeque<T>::MyDeque()
    : blockMap_(reinterpret_cast<T**>(calloc(mapSize_, sizeof(T**))))
{
    
}

template <typename T>
MyDeque<T>::~MyDeque()
{
    free(blockMap_);    
}

int main(int argc, char** argv)
{
    MyDeque<int> deque;

    return 0;
}
