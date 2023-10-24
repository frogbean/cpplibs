#include <mutex>

class pwmHz {
public:
    pwmHz(float initialHz = 1.0, unsigned long initialBrightness = 100)
    {
          setFrequency(initialHz);
          setBrightness(initialBrightness);
    }

    void setFrequency(float hz) {
        std::lock_guard<std::mutex> lock(mutex);
        if(hz <= 0) return;
        frequency = 1000 / hz;
    }

    void setBrightness(unsigned long newBrightness) {
        std::lock_guard<std::mutex> lock(mutex);
        if(newBrightness <= 0) brightness = 0;
        else if(newBrightness >= 100) brightness = 100;
        else brightness = newBrightness;
    }

    unsigned char pwm(unsigned int time) {
        std::lock_guard<std::mutex> lock(mutex);
        unsigned long freq_ms = static_cast<unsigned long>(frequency);
        unsigned long modulas = time % freq_ms;
        static float previous_frequency = frequency;
        
        static unsigned long starting_modulas = modulas;
        if(previous_frequency != frequency) previous_frequency = frequency, starting_modulas = modulas;

        unsigned long zero_phase_modulas = (freq_ms + (modulas - starting_modulas)) % freq_ms;
        unsigned char max_pwm = static_cast<unsigned char>((static_cast<double>(brightness)/100) * 255);
        double phase = static_cast<double>(zero_phase_modulas) / frequency;

        if(phase >= 0.5)
          return static_cast<unsigned char>((1.0 - (phase - 0.5) * 2.0) * max_pwm);
          else return static_cast<unsigned char>(phase * 2.0 * max_pwm);
    }

private:
    float frequency;
    unsigned long brightness;
    std::mutex mutex;
};