/**
    Description:
    This example creates a Sine waveform on the RIGHT Audio channel of PT8211
    and a silence on the LEFT Audio channel.
    This is a very simple how-to-use an external I2S DAC example (DAC = Digital to Analog Converter).

    Created on 27 Aug 2015 by Vassilis Serasidis
    email:  avrsite@yahoo.gr

    Connections between PT8211 DAC and the STM32F103C8T6
    WS    <-->  PA3
    BCK   <-->  PA5 <-->  BOARD_SPI1_SCK_PIN
    DIN   <-->  PA7 <-->  BOARD_SPI1_MOSI_PIN

*/

#include <SPI.h>
#include <HardwareTimer.h>

#include "circular_buffer.h"
#include "sine_voice.h"

#define WS   PA3
#define BCK  PA5
#define DATA PA7

#define PT8211_SAMPLE_RATE 48000

#define MICROS_PER_MILLISECOND 1000
#define MILLIS_PER_SECOND 1000

HardwareTimer writeSampleTimer( 1 );

circular_buffer<int16_t, 512> buffer;
sine_voice<int16_t> voice( 1000.f, PT8211_SAMPLE_RATE );

void setup()
{
  Serial.begin(9600);

  // Setup SPI 1
  SPI.begin(); //Initialize the SPI_1 port.
  SPI.setBitOrder(MSBFIRST); // Set the SPI_1 bit order
  SPI.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 0
  SPI.setClockDivider(SPI_CLOCK_DIV16); // Slow speed (72 / 16 = 4.5 MHz SPI_1 speed)
  pinMode(WS, OUTPUT); //Set the Word Select pin (WS) as output.

  // Setup SPI write timer
  writeSampleTimer.pause();

  float seconds = 1.f / ( PT8211_SAMPLE_RATE / 2 );
  int32_t period = seconds * MILLIS_PER_SECOND * MICROS_PER_MILLISECOND;
 
  writeSampleTimer.setPeriod( period );
  writeSampleTimer.setMode(TIMER_CH1, TIMER_OUTPUT_COMPARE);
  writeSampleTimer.setCompare(TIMER_CH1, 1);  // Interrupt 1 count after each update
  writeSampleTimer.attachInterrupt(TIMER_CH1, onWriteFrame);
  writeSampleTimer.refresh();
  writeSampleTimer.resume();

  voice.setGain( 0.8f );
  voice.setFrequency( 500.f );
}

void onWriteFrame()
{
  if( !buffer.canRead() )
  {
    return;
  }
  
  int16_t sample = 0;
  if( buffer.canRead() )
  {
    sample = buffer.read();
  }

  digitalWrite(WS, LOW);  //Select RIGHT Audio channel
  SPI.transfer16( sample );

  digitalWrite(WS, HIGH); //Select LEFT Audio channel
  SPI.transfer16(0);
}

void loop()
{
  if( buffer.size() < buffer.capacity() / 4 )
  {
    while( buffer.canWrite() )
    {
      buffer.write( voice.next() );
    }
  }
}
