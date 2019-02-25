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
    EXPECT_EQ( buffer.available(), capacity );
    EXPECT_TRUE( buffer.canWrite() );
    EXPECT_FALSE( buffer.canRead() );
}

TEST( ciruclar_buffer_test, write_api_works )
{
    constexpr size_t                          capacity = 8;
    ysp::circular_buffer< int16_t, capacity > buffer;

    for ( int16_t i = 0; i < static_cast< int16_t >( buffer.capacity() ); ++i )
    {
        EXPECT_TRUE( buffer.canWrite() );
        buffer.write( i );
        EXPECT_TRUE( buffer.canRead() );
        EXPECT_EQ( buffer.size(), i + 1 );
        EXPECT_EQ( buffer.available(), buffer.capacity() - i - 1 );
    }

    EXPECT_TRUE( buffer.canRead() );
    EXPECT_FALSE( buffer.canWrite() );
    EXPECT_EQ( buffer.available(), 0 );
    EXPECT_EQ( buffer.size(), buffer.capacity() );
}

TEST( ciruclar_buffer_test, read_api_works )
{
    constexpr size_t                          capacity = 8;
    ysp::circular_buffer< int16_t, capacity > buffer;

    for ( int16_t i = 0; i < static_cast< int16_t >( buffer.capacity() ); ++i )
    {
        buffer.write( i );
    }
    EXPECT_TRUE( buffer.canRead() );
    EXPECT_FALSE( buffer.canWrite() );
    EXPECT_EQ( buffer.available(), 0 );
    EXPECT_EQ( buffer.size(), buffer.capacity() );

    int16_t expected_value   = 0;
    size_t  capacity_counter = capacity;

    while ( buffer.canRead() )
    {
        EXPECT_EQ( buffer.size(), capacity_counter-- );
        int16_t value = buffer.read();
        EXPECT_EQ( value, expected_value++ );
    }

    EXPECT_EQ( buffer.size(), 0 );
    EXPECT_EQ( buffer.available(), capacity );
    EXPECT_FALSE( buffer.canRead() );
    EXPECT_TRUE( buffer.canWrite() );
}
