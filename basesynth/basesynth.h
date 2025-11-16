#define TAP_TEMPO_SAMPLES 5
#define TAP_TEMPO_THRESHOLD 2000
#define TAP_TEMPO_DEFAULT 800

#define TEMPO_DISPLAY_INFORMATION 30
#define TEMPO_DISPLAY_DURATION 120

class BaseSynth
{
private:
  uint64_t calculate_tempo();

  uint64_t tap_tempo_samples[TAP_TEMPO_SAMPLES];
  size_t tap_tempo_index;
  uint64_t _last_tempo;

public:
  void init();
  inline void update() { this->time++; }

  void tap_tempo();
  bool is_beat();
  float beat_norm();

  uint64_t time;
  uint64_t tempo;
};
