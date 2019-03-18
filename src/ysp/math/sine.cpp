#include <ysp/math/constants.h>
#include <ysp/math/interp.h>
#include <ysp/math/sine.h>

#include <cassert>

#define YSP_SINE_IMPL_QUARTER 1
#define YSP_SINE_IMPL_FULL_QUANTIZED 2
#define YSP_SINE_IMPL_FULL_INTERP 3

#ifndef YSP_SINE_IMPL
#define YSP_SINE_IMPL YSP_SINE_IMPL_QUARTER
#endif

#if YSP_SINE_IMPL == YSP_SINE_IMPL_FULL_QUANTIZED || YSP_SINE_IMPL == YSP_SINE_IMPL_FULL_INTERP
#include "sine_table_full.h"
#endif
#if YSP_SINE_IMPL == YSP_SINE_IMPL_QUARTER
#include "sine_table_quarter.h"
#endif

namespace ysp
{
namespace detail
{

#if YSP_SINE_IMPL == YSP_SINE_IMPL_QUARTER
inline float sin_impl( float radians )
{
    float theta = radians;
    float sign  = 1.f;

    if ( radians >= math::one_point_five_pi_f ) // quadrant 4
    {
        theta = math::two_pi_f - radians;
        sign  = -1.f;
    }
    else if ( radians >= math::pi_f ) // quadrant 3
    {
        theta -= math::pi_f;
        sign = -1.f;
    }
    else if ( radians >= math::pi_over_two_f ) // quadrant 2
    {
        theta = math::pi_f - radians;
    }

	float index = theta * math::one_over_pi_over_two_f * ( detail::k_sine_table_quarter.size() - 1 );
    return sign * ysp::interp_at( detail::k_sine_table_quarter, index );
}
#elif YSP_SINE_IMPL == YSP_SINE_IMPL_FULL_QUANTIZED
inline float sin_impl( float radians )
{
    size_t index = static_cast< size_t >( radians * math::one_over_two_pi_f * detail::k_sine_table_full.size() );
    return detail::k_sine_table_full[index];
}
#elif YSP_SINE_IMPL == YSP_SINE_IMPL_FULL_INTERP
inline float sin_impl( float radians )
{
    float  index    = radians * math::one_over_two_pi_f * detail::k_sine_table_full.size();
    return ysp::interp_at( detail::k_sine_table_full, index );
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
