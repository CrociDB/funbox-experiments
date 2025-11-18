#include "synth.h"

void Synth::init(float sample_rate)
{
  this->sample_rate = sample_rate;

  this->carrier.Init(sample_rate);
  this->carrier.SetWaveform(Oscillator::WAVE_SIN);
  this->carrier.SetAmp(0.5f);

  this->modulator.Init(sample_rate);
  this->modulator.SetWaveform(Oscillator::WAVE_SIN);
  this->modulator.SetAmp(1.0f);
}

float Synth::process()
{
  float mod_freq = carrier_freq * mod_ratio;
  this->modulator.SetFreq(mod_freq);

  float mod_out = this->modulator.Process();
  float fm_signal = mod_out * this->mod_index;

  carrier.SetFreq(this->carrier_freq + fm_signal);

  float sig = carrier.Process();
  return sig;
}
