#include <ysp/math/constants.h>
#include <ysp/math/sine.h>

#include <cassert>

#define YSP_SINE_IMPL_QUARTER 1
#define YSP_SINE_IMPL_FULL_QUANTIZED 2
#define YSP_SINE_IMPL_FULL_INTERP 3

#ifndef YSP_SINE_IMPL
#define YSP_SINE_IMPL YSP_SINE_IMPL_FULL_INTERP
#endif

#if YSP_SINE_IMPL == YSP_SINE_IMPL_FULL_QUANTIZED || YSP_SINE_IMPL == YSP_SINE_IMPL_FULL_INTERP
#include "sine_table_full.h"
#endif

namespace ysp
{
namespace detail
{

#if YSP_SINE_IMPL == YSP_SINE_IMPL_QUARTER
inline float sin_impl( float radians )
{
}
#elif YSP_SINE_IMPL == YSP_SINE_IMPL_FULL_QUANTIZED
inline float sin_impl( float radians )
{
    size_t index = static_cast< size_t >( radians * math::one_over_two_pi_f * detail::k_sine_table_full.size() );
    return detail::k_sine_table[index];
}
#elif YSP_SINE_IMPL == YSP_SINE_IMPL_FULL_INTERP
inline float sin_impl( float radians )
{
    float  bin    = radians * math::one_over_two_pi_f * detail::k_sine_table_full.size();
    size_t index  = static_cast< size_t >( bin );
    float  weight = bin - index;
    return detail::k_sine_table_full[index] * ( 1 - weight ) + detail::k_sine_table_full[index + 1] * weight;
}
#else
#error YSP_SINE_IMPL invalid -- No sine impl selected!
#endif
} // namespace detail

float ysp::sin( float radians )
{
    assert( radians >= 0.f );
    assert( radians <= math::two_pi_f );
    return detail::sin_impl( radians );
}

} // namespace ysp
