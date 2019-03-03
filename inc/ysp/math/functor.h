#pragma once

#ifndef YSP_USE_STD_SINE
#define YSP_USE_STD_SINE 0
#endif

#if YSP_USE_STD_SINE
#include <cmath>
#else
#include <ysp/math/sine.h>
#endif

namespace ysp
{
namespace math
{

struct sine_functor
{
    float operator()( float phase )
    {
#if YSP_USE_STD_SINE
        return std::sin( phase );
#else
        return ysp::sin( phase );
#endif
    }
};

} // namespace math
} // namespace ysp
