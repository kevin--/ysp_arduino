#pragma once

namespace ysp
{

template < typename T >
inline T interp( T lhs, T rhs, float weight )
{
    return static_cast< T >( lhs * ( 1 - weight ) + rhs * weight );
}

template < typename Container >
inline auto interp_at( const Container& container, float index )
{
    size_t lower_index = static_cast< size_t >( index );
    return interp( container[lower_index], container[lower_index + 1], index - lower_index );
}

} // namespace ysp
