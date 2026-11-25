#pragma once

#include "ml_dsa/internals/utility/force_inline.hpp"
#include <cstdint>
#include <type_traits>

namespace ml_dsa_ct {

// Keep a value in data flow while preventing the optimizer from inferring its
// range and reconstructing secret-dependent control flow. The barrier emits no
// instructions on GCC and Clang.
template<typename T>
[[nodiscard]] forceinline constexpr T
value_barrier(T value)
{
  static_assert(std::is_integral_v<T>);

#if defined(__GNUC__) || defined(__clang__)
  if (!std::is_constant_evaluated()) {
    asm volatile("" : "+r"(value)); // NOLINT(hicpp-no-assembler)
  }
#endif

  return value;
}

// Select rhs when choice is true and lhs otherwise, using value flow only.
[[nodiscard]] forceinline constexpr uint32_t
select_u32(const bool choice, const uint32_t lhs, const uint32_t rhs)
{
  uint32_t mask = 0U - static_cast<uint32_t>(choice);
  mask = value_barrier(mask);
  return (lhs & ~mask) | (rhs & mask);
}

}
