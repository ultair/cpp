#include <iostream>

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

    T& at(size_t pos);

    void clear();

    bool is_empty();

    inline constexpr size_t GetNodeSize(size_t elSize)
    {
    	return ( elSize < blockSize_
                 ? size_t(blockSize_ / elSize) : size_t(1));
    }

private:

    void ExtendFront();

    void RegressFront();

    void ExtendBack();

    void RegressBack();

    static constexpr size_t blockSize_{512};

    size_t mapSize_{8};

    T** const blockMap_{nullptr};

    int blockBegin_{-1};

    int blockEnd_{3};

    T* front_{nullptr};

    T* back_{nullptr};
};

template <typename T>
MyDeque<T>::MyDeque()
    : blockMap_(reinterpret_cast<T**>(calloc(mapSize_, sizeof(T**))))
{
    // The first to be allocated is the 'back' queue
    blockMap_[blockEnd_] = reinterpret_cast<T*>(calloc(GetNodeSize(sizeof(T)), sizeof(T)));
}

template <typename T>
MyDeque<T>::~MyDeque()
{
    for(size_t i = 0; i < mapSize_; i++)
    {
        if(blockMap_[i])
        {
            free(blockMap_[i]);
        }
    }

    free(blockMap_);    
}

template <typename T>
void MyDeque<T>::push_front(const T& item)
{

}

template <typename T>
void MyDeque<T>::push_back(const T& item)
{
    ExtendBack();

    *back_ = item;
}

template <typename T>
void MyDeque<T>::ExtendBack()
{
    if(back_)
    {
        // Are we at the end of the tail node?
        if( (blockMap_[blockEnd_] + (GetNodeSize(sizeof(T)) - 1)) == back_)
        {
            if( (blockEnd_+1) >= mapSize_ )
            {
                std::cout << "Map size exceeded. Exit for now" << std::endl;
                exit(1);
            }
            else
            {
                std::cout << "Allocate a new node" << std::endl;

                ++blockEnd_;

                // Allocate a new tail node
                blockMap_[blockEnd_] = reinterpret_cast<T*>(calloc(GetNodeSize(sizeof(T)), sizeof(T)));

                back_ = blockMap_[blockEnd_];
            }
        }
        else
        {
            ++back_;
        }
    }
    else
    {
        back_ = blockMap_[blockEnd_];
    }
}

int main(int argc, char** argv)
{
    MyDeque<int> deque;

    for(int i=0; i<10000; i++)
    {
        deque.push_back(i);
    }

    return 0;
}
