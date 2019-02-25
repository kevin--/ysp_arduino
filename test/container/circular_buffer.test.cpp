/**
 * circular buffer
 * super basic circular buffer
 *
 * @author Kevin Dixon
 * @date   JAN 21 2019
 */

#include <ysp/container/circular_buffer.h>

#include <gtest/gtest.h>

TEST( ciruclar_buffer_test, initial_state )
{
    constexpr size_t                          capacity = 8;
    ysp::circular_buffer< int16_t, capacity > buffer;

    EXPECT_EQ( buffer.size(), 0 );
    EXPECT_EQ( buffer.capacity(), capacity );
    EXPECT_TRUE( buffer.canWrite() );
    EXPECT_FALSE( buffer.canRead() );
}
