unsigned char hz_at_time_to_pwm(float hz, unsigned long brightness_percent = 100, unsigned int time) {

  if(brightness_percent > 100) brightness_percent = 100;

  unsigned long hz_ms = 1000 / hz, modulas = time % hz_ms;
  static float previous_hz = hz;
  static unsigned long starting_modulas = modulas;

  if(hz != previous_hz) previous_hz = hz, starting_modulas = modulas;

  unsigned long zero_phase_modulas = (hz_ms + (modulas - starting_modulas)) % hz_ms;
  unsigned char max_pwm = static_cast<unsigned char>((static_cast<double>(brightness_percent)/100) * 255);
  double phase = static_cast<double>(zero_phase_modulas) / hz_ms;

  if(phase >= 0.5)
    return static_cast<unsigned char>((1.0 - (phase - 0.5) * 2.0) * max_pwm);
    else return static_cast<unsigned char>(phase * 2.0 * max_pwm);
}