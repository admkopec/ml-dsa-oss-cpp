#include "ml_dsa/internals/utility/value_barrier.hpp"
#include <gtest/gtest.h>

TEST(ML_DSA, ConstantTimeSelection)
{
  constexpr uint32_t lhs = 0x12345678U;
  constexpr uint32_t rhs = 0x87654321U;

  static_assert(ml_dsa_ct::select_u32(false, lhs, rhs) == lhs);
  static_assert(ml_dsa_ct::select_u32(true, lhs, rhs) == rhs);

  EXPECT_EQ(ml_dsa_ct::select_u32(false, lhs, rhs), lhs);
  EXPECT_EQ(ml_dsa_ct::select_u32(true, lhs, rhs), rhs);
}
