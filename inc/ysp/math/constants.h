#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

namespace ysp
{

namespace math
{

constexpr double pi_d = M_PI;
constexpr float  pi_f = static_cast< float >( M_PI );
constexpr double one_over_pi_d = 1.0 / pi_d;
constexpr float  one_over_pi_f = static_cast< float >( 1.f / pi_f );

constexpr double two_pi_d = M_PI * 2;
constexpr float  two_pi_f = static_cast< float >( M_PI * 2 );
constexpr double one_over_two_pi_d = 1.0 / two_pi_d;
constexpr double one_over_two_pi_f = 1.f / two_pi_f;

} // namespace math
} // namespace ysp
