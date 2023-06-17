/**
 * @file ring_buf.h
 * @author Mehmet Aslan
 * @version 1.0
 * @date 2023-06-17
 *
 * @copyright Copyright (c) 2023(DO whatEVER you want licenced)
 */

#ifndef RING_BUF_H_
#define RING_BUF_H_

#include <cstdint>

//! Exceptions ring buffer can throw
enum class RingBufExcpt {
    okay,
    bufferIsFull,
    bufferIsEmpty
};

template <class data_t>
class RingBuf {
public:
    /**
     * @brief Constructor that allocates number of items from heap
     * @param [in] numOfItem - number of items
     */
    RingBuf<data_t>(uint32_t numOfItem):
        head{0},
        tail{0},
        numOfItem{numOfItem},
        itemCount{0},
        buf{new data_t[numOfItem]}
    {}

    /**
     * @brief Destructor that deallocates buffer from heap
     */
    ~RingBuf<data_t>()
    {
        delete[] buf;
    }

    void enqueue(const data_t& item)
    {
        if(isFull()) {
            throw RingBufExcpt::bufferIsFull;
        }
        ++itemCount;
        buf[tail] = item;
        tail = (tail + 1) % numOfItem;
    }

    data_t dequeue()
    {
        if(isEmpty()) {
            throw RingBufExcpt::bufferIsEmpty;
        }
        --itemCount;
        data_t item = buf[head];

        head = (head + 1) % numOfItem;

        return item;
    }

    data_t front() const
    {
        return buf[head];
    }

    bool isEmpty() const
    {
        return (itemCount == 0);
    }

    bool isFull() const
    {
        return (itemCount == numOfItem);
    }
private:
    uint32_t head;
    uint32_t tail;
    uint32_t numOfItem;
    uint32_t itemCount;
    data_t  *buf;
}; // class RingBuf

#endif // RING_BUF_H_
