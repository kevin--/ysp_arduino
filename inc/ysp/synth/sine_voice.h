/**
 * sine voice
 * dead simple sine generator
 *
 * @author Kevin Dixon
 * @date   JAN 21 2019
 */

#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
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
    return value * 32767;
}
} // namespace detail

template < typename SampleType >
class sine_voice
{
public:
    sine_voice( float frequency, unsigned sampleRate )
    : m_sampleRate( sampleRate )
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
        m_radiansPerSample = 2 * M_PI * m_frequency / m_sampleRate;
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
        float value = m_gain * std::sin( m_phase );

        m_phase += m_radiansPerSample;
        if ( m_phase > 2 * M_PI )
            m_phase -= 2 * M_PI;

        return converter.convert( value );
    }

private:
    detail::sample_converter< SampleType > converter;
    const unsigned                         m_sampleRate       = 48000;
    float                                  m_frequency        = 0.f;
    float                                  m_radiansPerSample = 0.f;
    float                                  m_phase            = 0.f;
    float                                  m_gain             = 1.f;
};

} // namespace ysp
