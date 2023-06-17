#include <gtest/gtest.h>
#include "dyn_ring_buf.h"

TEST(Normal, 1)
{
    DynRingBuf<uint8_t> rb(10, 50);
    for(int i = 0; i < 12; ++i) {
        rb.enqueue(i);
    }

    for(int i = 0; i < 100; ++i) {
        rb.enqueue(i);
    }

    for(int i = 0; i < 12; ++i) {
        if(i != rb.front()) {
            FAIL();
        }
        rb.dequeue();
    }

    for(int i = 0; i < 100; ++i) {
        if(i != rb.front()) {
            FAIL();
        }
        rb.dequeue();
    }
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
