/**
 * @file pwmHz.h
 * @brief Header file for the pwmHz class that controls pulse width modulation.
 */

#ifndef PWMHZ_H
#define PWMHZ_H

#include <mutex>

/**
 * @brief The pwmHz class controls pulse width modulation.
 */
class pwmHz {
public:
    /**
     * @brief Constructor for the pwmHz class.
     * @param initialHz The initial frequency in Hz.
     * @param initialBrightness The initial brightness as a percentage (0-100).
     */
    pwmHz(float initialHz = 1.0, unsigned long initialBrightness = 100);

    /**
     * @brief Sets the frequency in Hz.
     * @param hz The frequency in Hz.
     */
    void setFrequency(float hz);

    /**
     * @brief Sets the brightness as a percentage (0-100).
     * @param newBrightness The new brightness as a percentage (0-100).
     */
    void setBrightness(unsigned long newBrightness);

    /**
     * @brief Computes the pulse width modulation value for a given time.
     * @param time The time in milliseconds.
     * @return The pulse width modulation value as an unsigned char (0-255).
     */
    unsigned char pwm(unsigned int time);

private:
    float frequency; /**< The frequency in Hz. */
    unsigned long brightness; /**< The brightness as a percentage (0-100). */
    std::mutex mutex; /**< The mutex to protect member variables from concurrent access. */
};

#endif // PWMHZ_H