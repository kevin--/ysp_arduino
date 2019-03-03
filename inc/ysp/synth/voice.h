/**
 * voice
 * dead simple voice generator
 *
 * @author Kevin Dixon
 * @date   JAN 21 2019
 */

#pragma once

#include <ysp/math/constants.h>

#include <cstdint>

namespace ysp
{

namespace detail
{
template < typename SampleType >
class sample_converter
{
public:
    SampleType convert( float value ) const;
};

template <>
int16_t sample_converter< int16_t >::convert( float value ) const
{
    return static_cast< int16_t >( value * 32767 );
}
} // namespace detail

template < typename SampleType, typename Function >
class voice
{
public:
    voice( float frequency, unsigned sampleRate )
    : m_sampleRate( sampleRate )
    {
        setFrequency( frequency );
    }
    voice( float frequency, unsigned sampleRate, Function )
    : m_function( std::move( function ) )
    , m_sampleRate( sampleRate )
    {
        setFrequency( frequency );
    }

    float frequency() const
    {
        return m_frequency;
    }
    void setFrequency( float freq )
    {
        m_frequency        = freq;
        m_radiansPerSample = 2 * math::pi_f * m_frequency / m_sampleRate;
    }

    float gain() const
    {
        return m_gain;
    }
    void setGain( float g )
    {
        m_gain = g;
    }

    SampleType next()
    {
        float value = m_gain * m_function( m_phase );

        m_phase += m_radiansPerSample;
        if ( m_phase > 2 * math::pi_f )
            m_phase -= 2 * math::pi_f;

        return m_converter.convert( value );
    }

private:
    Function                               m_function;
    detail::sample_converter< SampleType > m_converter;
    const unsigned                         m_sampleRate       = 48000;
    float                                  m_frequency        = 0.f;
    float                                  m_radiansPerSample = 0.f;
    float                                  m_phase            = 0.f;
    float                                  m_gain             = 1.f;
};

} // namespace ysp
