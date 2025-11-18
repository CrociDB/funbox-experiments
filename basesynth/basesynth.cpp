#include "basesynth.h"

void BaseSynth::init(float sample_rate)
{
  this->time = 0;

  for (int i = 0; i < TAP_TEMPO_SAMPLES; i++)
  {
    this->tap_tempo_samples[i] = 0;
  }

  this->tap_tempo_index = 0;
  this->tempo = TAP_TEMPO_DEFAULT;
  this->_last_tempo = 0;

  this->synth.init(sample_rate);
}

void BaseSynth::tap_tempo()
{
  // If too long since last tap, resets
  if (this->time - this->_last_tempo > TAP_TEMPO_THRESHOLD)
  {
    for (int i = 0; i < TAP_TEMPO_SAMPLES; i++)
    {
      this->tap_tempo_samples[i] = 0;
    }

    this->tap_tempo_index = 0;
  }

  this->_last_tempo = this->time;
  this->tap_tempo_samples[this->tap_tempo_index] = this->time;
  this->tap_tempo_index = (this->tap_tempo_index + 1) % TAP_TEMPO_SAMPLES;

  this->tempo = this->calculate_tempo();
}

uint64_t BaseSynth::calculate_tempo() { uint64_t total_diff = 0; uint64_t total_samples = 0;
  for (int i = 0; i < TAP_TEMPO_SAMPLES; i++) {
    uint64_t curr = this->tap_tempo_samples[i];
    uint64_t next = this->tap_tempo_samples[i == TAP_TEMPO_SAMPLES - 1 ? 0 : i + 1];

    if (next > curr && curr != 0)
    {
      uint64_t diff = next - curr;
      total_diff += diff;
      total_samples++;
    }
  }

  if (total_samples == 0)
    return TAP_TEMPO_DEFAULT;

  total_diff /= total_samples;
  return total_diff == 0 ? TAP_TEMPO_DEFAULT : total_diff;
}

bool BaseSynth::is_beat()
{
  uint64_t beat = this->time % this->tempo;
  return beat < TEMPO_DISPLAY_INFORMATION;
}

float BaseSynth::beat_norm()
{
  uint64_t beat = this->time % this->tempo;

  float duration = ((float)this->tempo) / 3.0f;
  float fb = ((float)beat);
  float value = (fb / duration);

  return fb > duration
             ? 0.0f
             : 1.0f - (value * value);
}
