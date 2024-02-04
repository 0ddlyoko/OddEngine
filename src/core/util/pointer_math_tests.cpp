#include <gtest/gtest.h>
#include "pointer_math.h"

TEST(PointerMath, IsAligned) {
    ASSERT_TRUE(core::util::pointer_math::isAligned(reinterpret_cast<const int *>(36), 4));
    ASSERT_FALSE(core::util::pointer_math::isAligned(reinterpret_cast<const int *>(37), 4));
    ASSERT_FALSE(core::util::pointer_math::isAligned(reinterpret_cast<const int *>(38), 4));
    ASSERT_FALSE(core::util::pointer_math::isAligned(reinterpret_cast<const int *>(39), 4));
    ASSERT_TRUE(core::util::pointer_math::isAligned(reinterpret_cast<const int *>(40), 4));

    ASSERT_TRUE(core::util::pointer_math::isAligned(reinterpret_cast<const int *>(36)));
    ASSERT_FALSE(core::util::pointer_math::isAligned(reinterpret_cast<const int *>(37)));
    ASSERT_FALSE(core::util::pointer_math::isAligned(reinterpret_cast<const int *>(38)));
    ASSERT_FALSE(core::util::pointer_math::isAligned(reinterpret_cast<const int *>(39)));
    ASSERT_TRUE(core::util::pointer_math::isAligned(reinterpret_cast<const int *>(40)));

    ASSERT_FALSE(core::util::pointer_math::isAligned(reinterpret_cast<const long *>(36)));
    ASSERT_FALSE(core::util::pointer_math::isAligned(reinterpret_cast<const long *>(37)));
    ASSERT_FALSE(core::util::pointer_math::isAligned(reinterpret_cast<const long *>(38)));
    ASSERT_FALSE(core::util::pointer_math::isAligned(reinterpret_cast<const long *>(39)));
    ASSERT_TRUE(core::util::pointer_math::isAligned(reinterpret_cast<const long *>(40)));
}

TEST(PointerMath, GetAlignment) {
    ASSERT_EQ(0, core::util::pointer_math::getAlignment(reinterpret_cast<const int *>(36), 4));
    ASSERT_EQ(3, core::util::pointer_math::getAlignment(reinterpret_cast<const int *>(37), 4));
    ASSERT_EQ(2, core::util::pointer_math::getAlignment(reinterpret_cast<const int *>(38), 4));
    ASSERT_EQ(1, core::util::pointer_math::getAlignment(reinterpret_cast<const int *>(39), 4));
    ASSERT_EQ(0, core::util::pointer_math::getAlignment(reinterpret_cast<const int *>(40), 4));
}

TEST(PointerMath, GetAlignmentWithHeader) {
    // Should be 8 (size of long) + 7 (needed to be aligned with long)
    ASSERT_EQ(8 + 7, core::util::pointer_math::getAlignWithHeader<long>(reinterpret_cast<const int *>(33), 4));
    // Should be 4 (size of int) + 3 (37 needs 3 to be aligned with 8)
    ASSERT_EQ(7, core::util::pointer_math::getAlignWithHeader<int>(reinterpret_cast<const int *>(33), 8));
}

TEST(PointerMath, GetBackwardAlignment) {
    ASSERT_EQ(0, core::util::pointer_math::getBackwardAlignment(reinterpret_cast<const int *>(36), 4));
    ASSERT_EQ(1, core::util::pointer_math::getBackwardAlignment(reinterpret_cast<const int *>(37), 4));
    ASSERT_EQ(2, core::util::pointer_math::getBackwardAlignment(reinterpret_cast<const int *>(38), 4));
    ASSERT_EQ(3, core::util::pointer_math::getBackwardAlignment(reinterpret_cast<const int *>(39), 4));
    ASSERT_EQ(0, core::util::pointer_math::getBackwardAlignment(reinterpret_cast<const int *>(40), 4));
}

TEST(PointerMath, Align) {
    ASSERT_EQ(reinterpret_cast<const int *>(36), core::util::pointer_math::align(reinterpret_cast<const int *>(36), 4));
    ASSERT_EQ(reinterpret_cast<const int *>(40), core::util::pointer_math::align(reinterpret_cast<const int *>(37), 4));
    ASSERT_EQ(reinterpret_cast<const int *>(40), core::util::pointer_math::align(reinterpret_cast<const int *>(38), 4));
    ASSERT_EQ(reinterpret_cast<const int *>(40), core::util::pointer_math::align(reinterpret_cast<const int *>(39), 4));
    ASSERT_EQ(reinterpret_cast<const int *>(40), core::util::pointer_math::align(reinterpret_cast<const int *>(40), 4));
}

TEST(PointerMath, AlignBackward) {
    ASSERT_EQ(reinterpret_cast<const int *>(36), core::util::pointer_math::alignBackward(reinterpret_cast<const int *>(36), 4));
    ASSERT_EQ(reinterpret_cast<const int *>(36), core::util::pointer_math::alignBackward(reinterpret_cast<const int *>(37), 4));
    ASSERT_EQ(reinterpret_cast<const int *>(36), core::util::pointer_math::alignBackward(reinterpret_cast<const int *>(38), 4));
    ASSERT_EQ(reinterpret_cast<const int *>(36), core::util::pointer_math::alignBackward(reinterpret_cast<const int *>(39), 4));
    ASSERT_EQ(reinterpret_cast<const int *>(40), core::util::pointer_math::alignBackward(reinterpret_cast<const int *>(40), 4));
}

TEST(PointerMath, Add) {
    ASSERT_EQ(reinterpret_cast<const int *>(40), core::util::pointer_math::add(reinterpret_cast<const int *>(36), 4));
    ASSERT_EQ(reinterpret_cast<const int *>(41), core::util::pointer_math::add(reinterpret_cast<const int *>(37), 4));
    ASSERT_EQ(reinterpret_cast<const int *>(42), core::util::pointer_math::add(reinterpret_cast<const int *>(38), 4));
    ASSERT_EQ(reinterpret_cast<const int *>(43), core::util::pointer_math::add(reinterpret_cast<const int *>(39), 4));
    ASSERT_EQ(reinterpret_cast<const int *>(44), core::util::pointer_math::add(reinterpret_cast<const int *>(40), 4));
}

TEST(PointerMath, Remove) {
    ASSERT_EQ(reinterpret_cast<const int *>(32), core::util::pointer_math::remove(reinterpret_cast<const int *>(36), 4));
    ASSERT_EQ(reinterpret_cast<const int *>(33), core::util::pointer_math::remove(reinterpret_cast<const int *>(37), 4));
    ASSERT_EQ(reinterpret_cast<const int *>(34), core::util::pointer_math::remove(reinterpret_cast<const int *>(38), 4));
    ASSERT_EQ(reinterpret_cast<const int *>(35), core::util::pointer_math::remove(reinterpret_cast<const int *>(39), 4));
    ASSERT_EQ(reinterpret_cast<const int *>(36), core::util::pointer_math::remove(reinterpret_cast<const int *>(40), 4));
}
