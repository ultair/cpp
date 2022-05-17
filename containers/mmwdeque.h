#ifndef MMW_DEQUE_H
#define MMW_DEQUE_H

#include <iostream>
#include <memory>
#include <stdexcept>
#include <cstring>

namespace mmw
{

template <typename T>
class Deque
{
public:
    Deque();

    ~Deque();

    void push_front(const T& item);

    void push_back(const T& item);

    void pop_front();

    void pop_back();

    T& front();

    T& back();

    T& at(size_t pos);

    void clear();

    inline bool is_empty()
    {
        return !front_ && !back_;
    }

    size_t size();

    inline constexpr size_t GetNodeSize()
    {
    	return (sizeof(T) < blockSize_
                 ? size_t(blockSize_ / sizeof(T)) : size_t(1));
    }

private:

    T* AllocateNode();

    void ExtendFront();

    void RegressFront();

    void ExtendBack();

    void RegressBack();

    static constexpr size_t blockSize_{512};

    const size_t mapSize_{8};

    T** const blockMap_{nullptr};

    int blockBegin_ = mapSize_ / 2;

    int blockEnd_ = mapSize_ / 2;

    T* front_{nullptr};

    T* back_{nullptr};
};
}

template <typename T>
mmw::Deque<T>::Deque()
    : blockMap_(reinterpret_cast<T**>(calloc(mapSize_, sizeof(T**))))
{
    // The first to be allocated is the 'back' queue
    blockMap_[blockEnd_] = AllocateNode();
}

template <typename T>
mmw::Deque<T>::~Deque()
{
    this->clear();

    free(blockMap_);    
}

template <typename T>
T* mmw::Deque<T>::AllocateNode()
{
    return reinterpret_cast<T*>(calloc(this->GetNodeSize(), sizeof(T)));
}

template <typename T>
void mmw::Deque<T>::push_front(const T& item)
{
    ExtendFront();

    *front_ = item;
}

template <typename T>
void mmw::Deque<T>::ExtendFront()
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
void mmw::Deque<T>::RegressFront()
{
    if(front_)
    {
        // Are we at the end of the head node?
        if( (blockMap_[blockBegin_] + (GetNodeSize() - 1)) == front_ )
        {
            if( ++blockBegin_ < (mapSize_ / 2) )
            {
                // Deallocate the node
                free(blockMap_[blockBegin_]);

                blockMap_[blockBegin_] = nullptr;

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
void mmw::Deque<T>::push_back(const T& item)
{
    ExtendBack();

    *back_ = item;
}

template <typename T>
void mmw::Deque<T>::pop_front()
{
    if(front_)
    {
        std::destroy_at(front_);

        RegressFront();
    }
}

template <typename T>
void mmw::Deque<T>::pop_back()
{
    if(back_)
    {
        std::destroy_at(back_);

        RegressBack();
    }
}

template <typename T>
void mmw::Deque<T>::ExtendBack()
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
void mmw::Deque<T>::RegressBack()
{
    if(back_)
    {
        // Are we at the start of the tail node?
        if( blockMap_[blockEnd_] == back_ )
        {
            if(blockEnd_ > (mapSize_ / 2))
            {
                // Deallocate the node
                free(blockMap_[blockEnd_]);

                blockMap_[blockEnd_] = nullptr;

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
T& mmw::Deque<T>::front()
{
    if(front_)
    {
        return *front_;
    }
    else if(back_)
    {
        return blockMap_[blockBegin_][0];
    }
    else
    {
        throw std::out_of_range();
    }
}

template <typename T>
T& mmw::Deque<T>::back()
{
    if(back_)
    {
        return *back_;
    }
    else if(front_)
    {
        return blockMap_[blockEnd_ - 1][GetNodeSize() - 1];
    }
    else
    {
        throw std::out_of_range();
    }
}

template <typename T>
void mmw::Deque<T>::clear()
{
    if(!this->is_empty())
    {
        size_t sz = this->size();

        for(size_t i = 0; i < (sz - 1); i++)
        {
            try {
                std::destroy_at(&this->at(i));
            }  catch(...) {

            }
        }

        for(size_t i = 0; i < (mapSize_ / 2); i++)
        {
            if(blockMap_[i])
            {
                free(blockMap_[i]);
                blockMap_[i] = nullptr;
            }
        }

        // Zero out the middle block but don't de-allocate it
        memset(blockMap_[mapSize_ / 2], '\0', GetNodeSize() * sizeof(T));

        for(size_t i = (mapSize_ / 2) + 1; i < mapSize_; i++)
        {
            if(blockMap_[i])
            {
                free(blockMap_[i]);
                blockMap_[i] = nullptr;
            }
        }

        blockBegin_ = mapSize_ / 2;

        blockEnd_ = mapSize_ / 2;

        front_ = nullptr;

        back_ = nullptr;
    }
}

template <typename T>
size_t mmw::Deque<T>::size()
{
    size_t numElements{0};

    if(front_ || back_)
    {
        int remainingNodes = blockEnd_ - blockBegin_;

        if(front_)
        {
            numElements += (blockMap_[blockBegin_] + GetNodeSize()) - front_;

            --remainingNodes;
        }

        if(back_)
        {
            numElements += (back_ - blockMap_[blockEnd_]) + 1;
        }

        numElements += (GetNodeSize() * remainingNodes);
    }

    return numElements;
}

template <typename T>
T& mmw::Deque<T>::at(size_t pos)
{
    if(pos > (size()-1))
    {
        throw std::out_of_range("Out of range");
    }

    int skipHeadNode{0};

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

            skipHeadNode = 1;
        }
    }

    int nodeIndex = (pos / GetNodeSize()) + skipHeadNode;

    int nodeOffset = pos % GetNodeSize();

    return blockMap_[blockBegin_ + nodeIndex][nodeOffset];
}

#endif
