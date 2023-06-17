#ifndef DYN_RING_BUF_
#define DYN_RING_BUF_

#include "ring_buf.h"

//! Exceptions dynamic ring buffer can throw
enum class DynRingBufExcpt {
    okay,
    bufferIsEmpty
};

template <class data_t>
class DynRingBuf {
public:
    DynRingBuf<data_t>(uint32_t numOfItem, uint8_t incPerc):
        numOfItem{numOfItem},
        incPerc{incPerc},
        rb{new RingBuf<data_t>(numOfItem)}
    {}

    ~DynRingBuf<data_t>()
    {
        if(rb) {
            delete rb;
        }
    }

    void enqueue(const data_t& item)
    {
        if(rb->isFull()) {
            numOfItem += (numOfItem * incPerc / 100);
            RingBuf<data_t> *tmp = new RingBuf<data_t>(numOfItem);
            while(!rb->isEmpty()) {
                tmp->enqueue(rb->front());
                rb->dequeue();
            }
            tmp->enqueue(item);
            delete rb;
            rb = tmp;
        } else {
            rb->enqueue(item);
        }
    }

    data_t dequeue()
    {
        if(rb->isEmpty()) {
            throw DynRingBufExcpt::bufferIsEmpty;
        }
        return rb->dequeue();
    }

    data_t front() const
    {
        return rb->front();
    }

    bool isEmpty() const
    {
        return rb->isEmpty;
    }

private:
    uint32_t numOfItem;
    uint8_t incPerc;
    RingBuf<data_t> *rb;
}; // DynCircularBuf


#endif //DYN_RING_BUF_
