#include "synth.h"

// Voice
void Voice::init(float sample_rate)
{
  this->sample_rate = sample_rate;

  this->carrier.Init(sample_rate);
  this->carrier.SetWaveform(Oscillator::WAVE_SIN);
  this->carrier.SetAmp(0.5f);

  this->modulator.Init(sample_rate);
  this->modulator.SetWaveform(Oscillator::WAVE_SIN);
  this->modulator.SetAmp(1.0f);
}

float Voice::process()
{
  float mod_freq = freq * mod_ratio;
  this->modulator.SetFreq(mod_freq);

  float mod_out = this->modulator.Process();
  float fm_signal = mod_out * this->mod_index;

  carrier.SetFreq(this->freq + fm_signal);

  float sig = carrier.Process();
  return sig;
}

void Voice::note_on(float freq)
{
  this->freq = freq;
  this->active = true;
}

void Voice::note_off()
{
  this->active = false;
}


// Synth
void Synth::init(float sample_rate)
{
  for (auto &voice : voices)
  {
    voice.init(sample_rate);
  }
}

float Synth::process()
{
  float sig = 0.0f;
  
  for (auto &voice : voices)
  {
    if (voice.active)
    {
      sig += voice.process();
    }
  }

  return sig * 0.5f; // Scale down to prevent clipping
}

void Synth::note_on(float freq)
{
  for (auto &voice : voices)
  {
    if (!voice.active)
    {
      voice.note_on(freq);
      break;
    }
  }
}

void Synth::note_off(float freq)
{
  for (auto &voice : voices)
  {
    if (voice.active && voice.freq == freq)
    {
      voice.note_off();
      break;
    }
  }
}
