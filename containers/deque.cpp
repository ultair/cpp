#include <iostream>
#include <memory>

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

    size_t size();

    inline constexpr size_t GetNodeSize(size_t elSize)
    {
    	return ( elSize < blockSize_
                 ? size_t(blockSize_ / elSize) : size_t(1));
    }

private:

    T* AllocateNode();

    void ExtendFront();

    void RegressFront();

    void ExtendBack();

    void RegressBack();

    static constexpr size_t blockSize_{512};

    size_t mapSize_{8};

    T** const blockMap_{nullptr};

    int blockBegin_{3};

    int blockEnd_{3};

    T* front_{nullptr};

    T* back_{nullptr};
};

template <typename T>
MyDeque<T>::MyDeque()
    : blockMap_(reinterpret_cast<T**>(calloc(mapSize_, sizeof(T**))))
{
    // The first to be allocated is the 'back' queue
    blockMap_[blockEnd_] = AllocateNode();
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
T* MyDeque<T>::AllocateNode()
{
    return reinterpret_cast<T*>(calloc(GetNodeSize(sizeof(T)), sizeof(T)));
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
void MyDeque<T>::pop_back()
{
    if(back_)
    {
        std::destroy_at(back_);

        RegressBack();
    }
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
                ++blockEnd_;

                // Allocate a new tail node
                blockMap_[blockEnd_] = AllocateNode();

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

template <typename T>
void MyDeque<T>::RegressBack()
{
    if(back_)
    {
        // Are we at the start of the tail node?
        if( blockMap_[blockEnd_] == back_ )
        {
            if(blockEnd_ > blockBegin_)
            {
                // Deallocate the node
                free(blockMap_[blockEnd_]);

                --blockEnd_;

                back_ = blockMap_[blockEnd_] + (GetNodeSize(sizeof(T)) - 1);
            }
            else
            {
                back_ = nullptr;
            }
        }
        else
        {
            --back_;
        }
    }
}

template <typename T>
size_t MyDeque<T>::size()
{
    if(front_)
    {
        return 0;
    }
    else if(back_)
    {
        size_t nodeElementCount = (blockEnd_ - blockBegin_) * GetNodeSize(sizeof(T));

        return 1 + (back_ - blockMap_[blockEnd_]) + nodeElementCount;
    }

    return 0;
}

template <typename T>
T& MyDeque<T>::at(size_t pos)
{
    if(front_)
    {
        // PLACEHOLDER
        return blockMap_[0][0];
    }
    else if(back_)
    {
        int nodeIndex = pos / GetNodeSize(sizeof(T));

        int nodeOffset = pos - (GetNodeSize(sizeof(T)) * nodeIndex);

        return blockMap_[blockBegin_ + nodeIndex][nodeOffset];
    }

    // PLACEHOLDER
    return blockMap_[0][0];
}

int main(int argc, char** argv)
{
    MyDeque<int> deque;

    std::cout << "Size: " << deque.size() << std::endl;

    deque.push_back(100);

    return 0;
}
