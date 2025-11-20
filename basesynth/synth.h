#pragma once

#include "Control/adsr.h"
#include "daisy_seed.h"
#include "daisysp.h"

#define MAX_VOICES 8

using namespace daisysp;

class Voice
{
public:
  void init(float sample_rate);
  float process();

  void note_on(float freq);
  void note_off();

  inline void set_ratio(float v) { this->mod_ratio = 10.0f * v; };
  inline void set_index(float v) { this->mod_index = v * 2000.0f; };

  float freq;
  bool active = false;

private:
  Oscillator carrier;
  Oscillator modulator;
  Adsr envelope;
  float sample_rate;

  float mod_ratio = 2.0f;
  float mod_index = 100.0f;
};

class Synth
{
public:
  void init(float sample_rate);
  float process();
  void note_on(float freq);
  void note_off(float freq);

  inline void set_ratio(float v)
  {
    for (auto &voice : voices)
      voice.set_ratio(v);
  }

  inline void set_index(float v)
  {
    for (auto &voice : voices)
      voice.set_index(v);
  }

private:
  Voice voices[MAX_VOICES];
};
