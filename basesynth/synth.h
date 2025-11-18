#pragma once

#include "daisy_seed.h"
#include "daisysp.h"

using namespace daisysp;

class Synth
{
public:
  void init(float sample_rate);
  float process();
  inline void set_ratio(float v) { this->mod_ratio = 10.0f * v; };
  inline void set_index(float v) { this->mod_index = v * 2000.0f; };
  inline void set_freq(float v) { this->carrier_freq = 440.0f * powf(2.0f, v); };

private:
  Oscillator carrier;
  Oscillator modulator;
  float sample_rate;

  float carrier_freq = 440.0f; // Base frequency (A4)
  float mod_ratio = 2.0f;      // Ratio of Modulator freq to Carrier freq
  float mod_index = 100.0f;    // How strong the modulation is (FM depth)
};
