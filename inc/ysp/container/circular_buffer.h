/**
 * circular buffer
 * super basic circular buffer
 *
 * @author Kevin Dixon
 * @date   JAN 21 2019
 */

#pragma once

#include <assert.h>

namespace ysp
{

template < typename T, size_t Capacity >
class circular_buffer
{
public:
    bool canRead() const
    {
        return size() > 0;
    }
    T read()
    {
        assert( canRead() );
        if ( m_read >= Capacity )
            m_read = 0;
        return m_buffer[m_read++];
    }

    bool canWrite() const
    {
        return available() > 0;
    }
    void write( T value )
    {
        assert( canWrite() );
        if ( m_write >= Capacity )
            m_write = 0;
        m_buffer[m_write++] = value;
    }

    size_t available() const
    {
        return Capacity - size();
    }
    size_t size() const
    {
        if ( m_write < m_read )
        {
            return Capacity - m_read + m_write;
        }
        else if ( m_write > m_read )
        {
            return m_write - m_read;
        }
        return 0;
    }
    size_t capacity() const
    {
        return Capacity;
    }

private:
    size_t m_read  = 0;
    size_t m_write = 0;
    T      m_buffer[Capacity];
};

} // namespace ysp
