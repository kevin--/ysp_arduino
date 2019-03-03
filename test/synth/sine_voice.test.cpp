/**
 * circular buffer
 * super basic circular buffer
 *
 * @author Kevin Dixon
 * @date   JAN 21 2019
 */

#include <ysp/synth/sine_voice.h>

#include <gtest/gtest.h>

#include <array>
#include <cmath>

namespace
{

constexpr size_t constexpr_ceil( float value )
{
    return ( static_cast< float >( static_cast< size_t >( value ) ) == value )
               ? static_cast< size_t >( value )
               : static_cast< size_t >( value ) + ( ( value > 0 ) ? 1 : 0 );
}

constexpr size_t wavelength_samples( float frequency, unsigned sampleRate )
{
    return constexpr_ceil( sampleRate / frequency );
}

} // namespace

const std::array< int16_t, 48 > reference_data_i16_1cycle_1kHz_sine_48k{
    0,      4276,   8480,   12539,  16383,  19947,  23169,  25995,  28377,  30272,  31650,  32486,
    32767,  32486,  31650,  30272,  28377,  25995,  23169,  19947,  16383,  12539,  8480,   4276,
    0,      -4276,  -8480,  -12539, -16383, -19947, -23169, -25995, -28377, -30272, -31650, -32486,
    -32767, -32486, -31650, -30272, -28377, -25995, -23169, -19947, -16383, -12539, -8480,  -4276};

TEST( sine_voice_test, initial_state )
{
    ysp::sine_voice< int16_t > voice( 1000.f, 48000 );
    EXPECT_EQ( voice.frequency(), 1000.f );
    EXPECT_EQ( voice.gain(), 1.f );
}

TEST( sine_voice_test, setters )
{
    ysp::sine_voice< int16_t > voice( 1000.f, 48000 );
    voice.setFrequency( 500.f );
    EXPECT_EQ( voice.frequency(), 500.f );

    voice.setGain( 0.5f );
    EXPECT_EQ( voice.gain(), 0.5f );
}

TEST( sine_voice_test, sine_wave_1kHz )
{
    ysp::sine_voice< int16_t > voice( 1000.f, 48000 );

    std::array< int16_t, wavelength_samples( 1000.f, 48000 ) > samples;
    for ( auto& i : samples )
    {
        i = voice.next();
    }

	ASSERT_EQ( samples.size(), reference_data_i16_1cycle_1kHz_sine_48k.size() );

	for (size_t i = 0; i < samples.size(); ++i)
	{
        EXPECT_EQ( samples[i], reference_data_i16_1cycle_1kHz_sine_48k[i] ) << "sample at index " << i << " failed";
	}
}
