#include <lfq/common/cache_line.hpp>

#include <gtest/gtest.h>

namespace {

TEST(CacheLine, IsPowerOfTwoAndAtLeast64) {
    EXPECT_EQ(lfq::cache_line_size & (lfq::cache_line_size - 1), 0u);
    EXPECT_GE(lfq::cache_line_size, 64u);
}

TEST(CacheLine, AlignasSeparatesMembers) {
    struct Padded {
        alignas(lfq::cache_line_size) int a;
        alignas(lfq::cache_line_size) int b;
    };
    EXPECT_EQ(offsetof(Padded, b), lfq::cache_line_size);
    EXPECT_EQ(alignof(Padded), lfq::cache_line_size);
}

}  // namespace
