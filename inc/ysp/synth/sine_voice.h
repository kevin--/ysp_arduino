/**
 * sine voice
 * dead simple sine generator
 *
 * @author Kevin Dixon
 * @date   JAN 21 2019
 */

#pragma once

#include "voice.h"

#include <ysp/math/functor.h>

namespace ysp
{

template< typename SampleType >
using sine_voice = voice< SampleType, math::sine_functor >;

} // namespace ysp
