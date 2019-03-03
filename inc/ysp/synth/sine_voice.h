/**
 * sine voice
 * dead simple sine generator
 *
 * @author Kevin Dixon
 * @date   JAN 21 2019
 */

#pragma once

#include "voice.h"

#include <cmath>

namespace ysp
{

namespace detail
{
struct sine_functor
{
    float operator()( float phase )
    {
        return std::sin( phase );
    }
};
} // namespace detail

template< typename SampleType >
using sine_voice = voice< SampleType, detail::sine_functor >;

} // namespace ysp
