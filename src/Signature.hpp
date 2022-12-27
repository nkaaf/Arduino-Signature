/*!
 * @file Signature.hpp
 *
 * @mainpage
 *
 * @section intro_sec Introduction
 *
 * This is the documentation for the Signature Library for the Arduino
 * platform. Because of the independence of Arduino libraries, it could be
 * theoretically used for every C/C++ program. It gives easy access to the
 * signature of AVR microcontrollers. The library contains functions that
 * provides the information of the signature bytes.
 *
 *
 * @section author Author
 *
 * Written by Niklas Kaaf (nkaaf@protonmail.com) with passion and the goal to
 * provide a simple and well implemented basic structure for building great
 * software.
 *
 * @section license License
 *
 * This file is part of the Signature library.
 *
 * Copyright (C) 2022  Niklas Kaaf
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#ifndef SIGNATURE_SIGNATURE_HPP
#define SIGNATURE_SIGNATURE_HPP

#include "Features.hpp"

#include <WString.h>

/*!
 * @brief   Class representing the signature of the microcontroller.
 */
class Signature {
private:
  /** structure of signature */
  typedef struct {
    uint8_t sig1, sig2, sig3; /// The bytes of the signature.
  } signature_t;

  static signature_t signature; /// Signature of AVR microcontroller.

  static bool INIT_STATUS; /// Indicating if the class is initialized.

  /*!
   * @brief   Initialise the class.
   */
  static void INIT();

  /*!
   * @brief Get the signature as a string.
   *
   * @return    A string of the signature formatted as a hex value (with leading
   *            '0x').
   */
  static String getSignatureString();

public:
  /*!
   * @brief Get the signature as a string.
   *
   * @return    A string of the signature formatted as a hex value (with leading
   *            '0x').
   */
  static String getSignature() {
    INIT();
    return getSignatureString();
  }

  /*!
   * @brief Get the name of the chip.
   *
   * @return    Name as a string.
   */
  static String getChipName();

#ifdef FEATURE_RC_OSCILLATOR_CALIBRATION
  /*!
   * @brief Get the factory calibration of the internal RC oscillator (OSCCAL).
   *
   * @return    Calibration value as an unsigned char.
   */
  static uint8_t getRcOscillatorCalibration() {
    INIT();
    return Features::getRcOscillatorCalibration();
  }
#endif

#ifdef FEATURE_INTERNAL_8MHZ_OSCILLATOR_CALIBRATION
  /*!
   * @brief Get the factory calibration of the internal 8MHz oscillator
   *        (OSCCAL0).
   *
   * @return    Calibration value as an unsigned char.
   */
  static uint8_t getInternal8MHzOscillatorCalibration() {
    INIT();
    return Features::getInternal8MHzOscillatorCalibration();
  }
#endif

#ifdef FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_A
  /*!
   * @brief Get the factory calibration of the Oscillator Temperature
   *        Calibration Register A (OSCTCAL0A).
   *
   * @return    Calibration value as an unsigned char.
   */
  static uint8_t getOscillatorTemperatureCalibrationA() {
    INIT();
    return Features::getOscillatorTemperatureCalibrationA();
  }
#endif

#ifdef FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_B
  /*!
   * @brief Get the factory calibration of the Oscillator Temperature
   *        Calibration Register B (OSCTCAL0B).
   * @return    Calibration value as an unsigned char.
   */
  static uint8_t getOscillatorTemperatureCalibrationB() {
    INIT();
    return Features::getOscillatorTemperatureCalibrationB();
  }
#endif

#ifdef FEATURE_INTERNAL_32KHZ_OSCILLATOR_CALIBRATION
  /*!
   * @brief Get the factory calibration of the internal 32kHz oscillator
   *        (OSCCAL1).
   *
   * @return    Calibration value as an unsigned char.
   */
  static uint8_t getInternal32kHzOscillatorCalibration() {
    INIT();
    return Features::getInternal32kHzOscillatorCalibration();
  }
#endif

#ifdef FEATURE_TEMPERATURE_SENSOR_GAIN_CALIBRATION
  /*!
   * @brief Get the factory calibration (gain) of the temperature sensor.
   *
   * @return    Calibration value as an unsigned char.
   */
  static uint8_t getTemperatureSensorGainCalibration() {
    INIT();
    return Features::getTemperatureSensorGainCalibration();
  }
#endif

#ifdef FEATURE_TEMPERATURE_SENSOR_OFFSET_CALIBRATION
  /*!
   * @brief Get the factory calibration (offset) of the temperature sensor.
   *
   * @return    Calibration value as an unsigned char.
   */
  static uint8_t getTemperatureSensorOffsetCalibration() {
    INIT();
    return Features::getTemperatureSensorOffsetCalibration();
  }
#endif

  /*!
   * @brief Writing a summary of the signature of the chip into a string.
   *        Usefully for giving information about the used microcontroller for
   *        debugging or logging intents.
   *
   * @return    A string containing a summary of the signature.
   */
  static String getSummary();
};

#endif // SIGNATURE_SIGNATURE_HPP
