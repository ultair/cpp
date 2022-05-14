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

    inline constexpr size_t GetNodeSize()
    {
    	return ( sizeof(T) < blockSize_
                 ? size_t(blockSize_ / sizeof(T)) : size_t(1));
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

    int blockBegin_ = mapSize_ / 2;

    int blockEnd_ = mapSize_ / 2;

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
    std::cout << "Allocating a node with size of " << GetNodeSize() << std::endl;

    return reinterpret_cast<T*>(calloc(GetNodeSize(), sizeof(T)));
}

template <typename T>
void MyDeque<T>::push_front(const T& item)
{
    ExtendFront();

    *front_ = item;
}

template <typename T>
void MyDeque<T>::ExtendFront()
{
    if(front_)
    {
        // Are we at the start of the head node?
        if( blockMap_[blockBegin_] == front_ )
        {
            if( blockBegin_ == 0 )
            {
                std::cout << "Map size exceeded. Exit for now" << std::endl;
                exit(1);
            }
            else
            {
                --blockBegin_;

                // Allocate a new head node
                blockMap_[blockBegin_] = AllocateNode();

                front_ = blockMap_[blockBegin_] + (GetNodeSize() - 1);
            }
        }
        else
        {
            --front_;
        }
    }
    else
    {
        --blockBegin_;

        // Allocate a new head node
        blockMap_[blockBegin_] = AllocateNode();

        front_ = blockMap_[blockBegin_] + (GetNodeSize() - 1);
    }
}

template <typename T>
void MyDeque<T>::RegressFront()
{
    if(front_)
    {
        // Are we at the end of the head node?
        if( (blockMap_[blockBegin_] + (GetNodeSize() - 1)) == front_ )
        {
            if( blockBegin_ < blockEnd_ )
            {
                // Deallocate the node
                free(blockMap_[blockBegin_]);

                ++blockBegin_;

                front_ = blockMap_[blockBegin_];
            }
            else
            {
                front_ = nullptr;
            }
        }
        else
        {
            ++front_;
        }
    }
}

template <typename T>
void MyDeque<T>::push_back(const T& item)
{
    ExtendBack();

    *back_ = item;
}

template <typename T>
void MyDeque<T>::pop_front()
{
    if(front_)
    {
        std::destroy_at(front_);

        RegressFront();
    }
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
        if( (blockMap_[blockEnd_] + (GetNodeSize() - 1)) == back_ )
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

                back_ = blockMap_[blockEnd_] + (GetNodeSize() - 1);
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
        size_t nodeElementCount = (blockEnd_ - blockBegin_) * GetNodeSize();

        return 1 + (back_ - blockMap_[blockEnd_]) + nodeElementCount;
    }

    return 0;
}

template <typename T>
T& MyDeque<T>::at(size_t pos)
{
    //std::cout << "Search for " << pos << std::endl;

    int nodeM{0};

    if(front_)
    {
        int headLastPos = (blockMap_[blockBegin_] + GetNodeSize() - 1) - front_;

        if(pos <= headLastPos)
        {
            // The element is in the head node
            return *(front_ + pos);
        }
        else
        {
            // The element will be found in the second node onwards
            pos -= (headLastPos + 1);

            nodeM = 1;
        }
    }

    int nodeIndex = (pos / GetNodeSize()) + nodeM;

    int nodeOffset = pos;

    if(nodeOffset >= GetNodeSize())
    {
        nodeOffset = pos % GetNodeSize();
    }

/*    std::cout << "Pos: " << pos
              << " nodeM: " << nodeM
              << " nodeIndex: " << nodeIndex
              << " nodeOffset: " << nodeOffset
              << std::endl;*/

    return blockMap_[blockBegin_ + nodeIndex][nodeOffset];
}

int main(int argc, char** argv)
{
    MyDeque<int> deque;

    for(int i=1; i<=260; i++)
    {
        std::cout << "Push front: " << i << std::endl;
        deque.push_front(i);
    }

    for(int i=0; i<260; i++)
    {
        int n = deque.at(i);

        std::cout << "at " << i << ": " << n << std::endl;
    }

    return 0;
}
