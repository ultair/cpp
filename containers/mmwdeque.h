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
        return !head_ && !tail_;
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

    const size_t mapSize_{128};

    T** const blockMap_{nullptr};

    int headBlock_ = mapSize_ / 2;

    int tailBlock_ = mapSize_ / 2;

    T* head_{nullptr};

    T* tail_{nullptr};
};
}

template <typename T>
mmw::Deque<T>::Deque()
    : blockMap_(reinterpret_cast<T**>(calloc(mapSize_, sizeof(T**))))
{

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

    *head_ = item;

    if(!tail_)
    {
        tail_ = head_;

        tailBlock_ = headBlock_;
    }
}

template <typename T>
void mmw::Deque<T>::push_back(const T& item)
{
    ExtendBack();

    *tail_ = item;

    if(!head_)
    {
        head_ = tail_;

        headBlock_ = tailBlock_;
    }
}

template <typename T>
void mmw::Deque<T>::ExtendFront()
{
    if(head_)
    {
        // Are we at the start of the head node?
        if( blockMap_[headBlock_] == head_ )
        {
            if( headBlock_ == 0 )
            {
                std::cout << "Map size exceeded. Exit for now" << std::endl;
                exit(1);
            }
            else
            {
                --headBlock_;

                // Allocate a new head node
                blockMap_[headBlock_] = AllocateNode();

                head_ = blockMap_[headBlock_] + (GetNodeSize() - 1);
            }
        }
        else
        {
            --head_;
        }
    }
    else
    {
        --headBlock_;

        // Allocate a new head node
        blockMap_[headBlock_] = AllocateNode();

        head_ = blockMap_[headBlock_] + (GetNodeSize() - 1);
    }
}

template <typename T>
void mmw::Deque<T>::ExtendBack()
{
    if(tail_)
    {
        // Are we at the end of the tail node?
        if( (blockMap_[tailBlock_] + (GetNodeSize() - 1)) == tail_ )
        {
            if( (tailBlock_+1) >= mapSize_ )
            {
                std::cout << "Map size exceeded. Exit for now" << std::endl;
                exit(1);
            }
            else
            {
                ++tailBlock_;

                // Allocate a new tail node
                blockMap_[tailBlock_] = AllocateNode();

                tail_ = blockMap_[tailBlock_];
            }
        }
        else
        {
            ++tail_;
        }
    }
    else
    {
        tail_ = blockMap_[tailBlock_];
    }
}

template <typename T>
void mmw::Deque<T>::pop_front()
{
    if(head_)
    {
        std::destroy_at(head_);

        RegressFront();
    }
}

template <typename T>
void mmw::Deque<T>::pop_back()
{
    if(tail_)
    {
        std::destroy_at(tail_);

        RegressBack();
    }
}

template <typename T>
void mmw::Deque<T>::RegressFront()
{
    if(head_)
    {
        // Are we at the end of the head node?
        if( (blockMap_[headBlock_] + (GetNodeSize() - 1)) == head_ )
        {
            if( ++headBlock_ < (mapSize_ / 2) )
            {
                // Deallocate the node
                free(blockMap_[headBlock_]);

                blockMap_[headBlock_] = nullptr;

                head_ = blockMap_[headBlock_];
            }
            else
            {
                head_ = nullptr;
            }
        }
        else
        {
            ++head_;
        }
    }
}

template <typename T>
void mmw::Deque<T>::RegressBack()
{
    if(tail_)
    {
        if( tail_ == head_ )
        {
            clear();
        }
        else if( blockMap_[tailBlock_] == tail_ )
        {
            if(tailBlock_ > 0)
            {
                // Deallocate the node
                free(blockMap_[tailBlock_]);

                blockMap_[tailBlock_] = nullptr;

                --tailBlock_;

                tail_ = blockMap_[tailBlock_] + (GetNodeSize() - 1);
            }
        }
        else
        {
            --tail_;
        }
    }
}

template <typename T>
T& mmw::Deque<T>::front()
{
    if(head_)
    {
        return *head_;
    }
    else if(tail_)
    {
        return blockMap_[headBlock_][0];
    }
    else
    {
        throw std::out_of_range("Out of range");
    }
}

template <typename T>
T& mmw::Deque<T>::back()
{
    if(tail_)
    {
        return *tail_;
    }
    else if(head_)
    {
        return blockMap_[tailBlock_ - 1][GetNodeSize() - 1];
    }
    else
    {
        throw std::out_of_range("Out of range");
    }
}

template <typename T>
void mmw::Deque<T>::clear()
{
/*    if(!this->is_empty())
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

        headBlock_ = mapSize_ / 2;

        tailBlock_ = mapSize_ / 2;

        head_ = nullptr;

        tail_ = nullptr;
    }*/
}

template <typename T>
size_t mmw::Deque<T>::size()
{
    size_t numElements{0};

    if(head_ || tail_)
    {
        int remainingNodes = tailBlock_ - headBlock_;

        if(head_)
        {
            numElements += (blockMap_[headBlock_] + GetNodeSize()) - head_;

            --remainingNodes;
        }

        if(tail_)
        {
            numElements += (tail_ - blockMap_[tailBlock_]) + 1;
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

    if(head_)
    {
        int headLastPos = (blockMap_[headBlock_] + GetNodeSize() - 1) - head_;

        if(pos <= headLastPos)
        {
            // The element is in the head node
            return *(head_ + pos);
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

    return blockMap_[headBlock_ + nodeIndex][nodeOffset];
}

#endif
