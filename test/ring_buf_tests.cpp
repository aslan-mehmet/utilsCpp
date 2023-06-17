#include <gtest/gtest.h>
#include "ring_buf.h"

TEST(Normal, 1)
{
    uint8_t numOfItem = 10;
    RingBuf<uint8_t> rb {numOfItem};

    for(int i = 0; i < numOfItem; ++i) {
        if(!rb.isFull()) {
            rb.enqueue(i);
        } else {
            FAIL();
        }
    }

    for(int i = 0; i < numOfItem; ++i) {
        if(rb.isEmpty()) {
            FAIL();
        } else {
            if(rb.front() != i) {
                FAIL();
            }
            rb.dequeue();
        }
    }
}

TEST(Normal, 2)
{
    uint8_t numOfItem = 10;
    RingBuf<uint8_t> rb {numOfItem};

    for(int i = 0; i < (numOfItem/2); ++i) {
        rb.enqueue(i);
        rb.dequeue();
    }

    for(int i = 0; i < numOfItem; ++i) {
        if(!rb.isFull()) {
            rb.enqueue(i);
        } else {
            FAIL();
        }
    }

    for(int i = 0; i < numOfItem; ++i) {
        if(rb.isEmpty()) {
            FAIL();
        } else {
            if(rb.front() != i) {
                FAIL();
            }
            rb.dequeue();
        }
    }
}

TEST(NormalStruct, 1)
{
    constexpr uint8_t numOfItem = 3;

    struct Person {
        int age;
        int height;
        char initial;

        bool operator == (const Person &p) {
            return (age == p.age &&
                    height == p.height &&
                    initial == p.initial) ? true : false;
        }

        bool operator != (const Person &p) {
            return !((*this)==p);
        }
    };

    Person personArr[numOfItem] = {
        {
            .age = 29,
            .height = 193,
            .initial = 'm'
        },
        {
            .age = 23,
            .height = 170,
            .initial = 'e'
        },
        {
            .age = 50,
            .height = 185,
            .initial = 'i'
        }
    };

    RingBuf<Person> rb {numOfItem};

    for(int i = 0; i < numOfItem; ++i) {
        rb.enqueue(personArr[i]);
    }

    for(int i = 0; i < numOfItem; ++i) {
        Person p = rb.front();
        rb.dequeue();
        if(p != personArr[i]) {
            FAIL();
        }
    }
}

TEST(EnqueueFail, 1)
{
    RingBufExcpt ex = RingBufExcpt::okay;
    uint8_t numOfItem = 10;
    RingBuf<uint8_t> rb{numOfItem};

    for(int i = 0; i < numOfItem + 1; ++i) {
        try {
            rb.enqueue(i);
        } catch(const RingBufExcpt &e) {
            if(i < numOfItem) { // it should not throw, while it is not full
                FAIL();
            }
            ex = e;
        }
    }

    EXPECT_EQ(ex, RingBufExcpt::bufferIsFull);
}

TEST(DequeueFail, 1)
{
    RingBufExcpt ex = RingBufExcpt::okay;
    uint8_t numOfItem = 10;
    RingBuf<uint8_t> rb{numOfItem};

    for(int i = 0; i < numOfItem; ++i) {
        rb.enqueue(i);
    }

    for(int i = 0; i < numOfItem + 1; ++i) {
        try {
            rb.dequeue();
        } catch(const RingBufExcpt &e) {
            if(i < numOfItem) { // it should not throw, while buffer is not empty
                FAIL();
            }
            ex = e;
        }
    }

    EXPECT_EQ(ex, RingBufExcpt::bufferIsEmpty);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
