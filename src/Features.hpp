#ifndef SIGNATURE_FEATURES_H
#define SIGNATURE_FEATURES_H

#include <WString.h>

#if defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48PA__) ||       \
        defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88PA__) ||   \
        defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || \
        defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
/*!
 * @def FEATURE_RC_OSCILLATOR_CALIBRATION
 * @brief Calibration data of the internal RC Oscillator (OSCCAL).
 */
#define FEATURE_RC_OSCILLATOR_CALIBRATION
#elif defined(__AVR_ATtiny828__)
/*!
 * @def FEATURE_INTERNAL_8MHZ_OSCILLATOR_CALIBRATION
 * @brief Calibration data of the internal 8MHz Oscillator (OSCCAL0).
 */
/*!
 * @def FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_A
 * @brief Calibration data of the Oscillator Temperature Register A (OSCTCAL0A).
 */
/*!
 * @def FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_B
 * @brief Calibration data of the Oscillator Temperature Register B (OSCTCAL0B).
 */
/*!
 * @def FEATURE_INTERNAL_32KHZ_OSCILLATOR_CALIBRATION
 * @brief Calibration data of the internal 32kHz Oscillator (OSCCAL1).
 */
/*!
 * @def FEATURE_TEMPERATURE_SENSOR_GAIN_CALIBRATION
 * @brief Calibration data for the temperature sensor (gain).
 */
/*!
 * @def FEATURE_TEMPERATURE_SENSOR_OFFSET_CALIBRATION
 * @brief Calibration data for the temperature sensor (offset).
 */
#define FEATURE_INTERNAL_8MHZ_OSCILLATOR_CALIBRATION
#define FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_A
#define FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_B
#define FEATURE_INTERNAL_32KHZ_OSCILLATOR_CALIBRATION
#define FEATURE_TEMPERATURE_SENSOR_GAIN_CALIBRATION
#define FEATURE_TEMPERATURE_SENSOR_OFFSET_CALIBRATION
#endif

class Features {
private:
#ifdef FEATURE_RC_OSCILLATOR_CALIBRATION
    static uint8_t rcOscillatorCalibration;/// Factory calibration value of the
                                           /// internal RC oscillator.
#endif
#ifdef FEATURE_INTERNAL_8MHZ_OSCILLATOR_CALIBRATION
    static uint8_t internal8MHzOscillatorCalibration;/// Factory calibration
                                                     /// value of the internal
                                                     /// 8MHz oscillator
#endif
#ifdef FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_A
    static uint8_t oscillatorTemperatureCalibrationA;/// Factory calibration
                                                     /// value of the Oscillator
                                                     /// Temperature Calibration
                                                     /// Register A (OSCTCAL0A)
#endif
#ifdef FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_B
    static uint8_t oscillatorTemperatureCalibrationB;/// Factory calibration
                                                     /// value of the Oscillator
                                                     /// Temperature Calibration
                                                     /// Register B (OSCTCAL0B)
#endif
#ifdef FEATURE_INTERNAL_32KHZ_OSCILLATOR_CALIBRATION
    static uint8_t internal32kHzOscillatorCalibration;/// Factory calibration
                                                      /// value of the internal
                                                      /// 32kHz oscillator
#endif
#ifdef FEATURE_TEMPERATURE_SENSOR_GAIN_CALIBRATION
    static uint8_t temperatureSensorGainCalibration;/// Factory calibration value
                                                    /// of the temperature sensor
                                                    /// (gain)
#endif
#ifdef FEATURE_TEMPERATURE_SENSOR_OFFSET_CALIBRATION
    static uint8_t temperatureSensorOffsetCalibration;/// Factory calibration
                                                      /// value of the
                                                      /// temperature sensor
                                                      /// (offset)
#endif
public:
    static void INIT();

#ifdef FEATURE_RC_OSCILLATOR_CALIBRATION
    static uint8_t getRcOscillatorCalibration() {
        INIT();
        return rcOscillatorCalibration;
    }
#endif

#ifdef FEATURE_INTERNAL_8MHZ_OSCILLATOR_CALIBRATION
    static uint8_t getInternal8MHzOscillatorCalibration() {
        INIT();
        return internal8MHzOscillatorCalibration;
    }
#endif

#ifdef FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_A
    static uint8_t getOscillatorTemperatureCalibrationA() {
        INIT();
        return oscillatorTemperatureCalibrationA;
    }
#endif

#ifdef FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_B
    static uint8_t getOscillatorTemperatureCalibrationB() {
        INIT();
        return oscillatorTemperatureCalibrationB;
    }
#endif

#ifdef FEATURE_INTERNAL_32KHZ_OSCILLATOR_CALIBRATION
    static uint8_t getInternal32kHzOscillatorCalibration() {
        INIT();
        return internal32kHzOscillatorCalibration;
    }
#endif

#ifdef FEATURE_TEMPERATURE_SENSOR_GAIN_CALIBRATION
    static uint8_t getTemperatureSensorGainCalibration() {
        INIT();
        return temperatureSensorGainCalibration;
    }
#endif

#ifdef FEATURE_TEMPERATURE_SENSOR_OFFSET_CALIBRATION
    static uint8_t getTemperatureSensorOffsetCalibration() {
        INIT();
        return temperatureSensorOffsetCalibration;
    }
#endif

    static String getSummary();
};

#endif// SIGNATURE_FEATURES_H
