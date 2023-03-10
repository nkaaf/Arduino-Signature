/*!
 * @file Features.cpp
 *
 * This file is part of the Signature library. It gives easy access to the
 * signature of AVR microcontrollers. The library contains functions that
 * provides the information of the signature bytes.
 *
 * Copyright (C) 2022-2023  Niklas Kaaf
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

#define FEATURE_RC_OSCILLATOR_CALIBRATION

#include "Features.hpp"

// Fix until https://github.com/avrdudes/avr-libc/issues/907 is fixed
#if defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny25__) ||                  \
    defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny45__) ||                  \
    defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny85__) ||                  \
    defined(__AVR_ATtiny441__) || defined(__AVR_ATtiny828__) ||                \
    defined(__AVR_ATtiny841__) || defined(__AVR_ATtiny1634__) ||               \
    defined(__AVR_ATtiny4313__)
#define SIGRD RSIG
#endif

#include <avr/boot.h>

#if defined(CHAR_PTR_STRING)
#include <avr/pgmspace.h>
#define F(s) ((String)PSTR(s))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#else
#include <Print.h>
#endif

#ifdef FEATURE_RC_OSCILLATOR_CALIBRATION
uint8_t Features::rcOscillatorCalibration = 0;
#endif

#ifdef FEATURE_INTERNAL_8MHZ_OSCILLATOR_CALIBRATION
uint8_t Features::internal8MHzOscillatorCalibration = 0;
#endif

#ifdef FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_A
uint8_t Features::oscillatorTemperatureCalibrationA = 0;
#endif

#ifdef FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_B
uint8_t Features::oscillatorTemperatureCalibrationB = 0;
#endif

#ifdef FEATURE_INTERNAL_32KHZ_OSCILLATOR_CALIBRATION
uint8_t Features::internal32kHzOscillatorCalibration = 0;
#endif

#ifdef FEATURE_TEMPERATURE_SENSOR_GAIN_CALIBRATION
uint8_t Features::temperatureSensorGainCalibration = 0;
#endif

#ifdef FEATURE_TEMPERATURE_SENSOR_OFFSET_CALIBRATION
uint8_t Features::temperatureSensorOffsetCalibration = 0;
#endif

void Features::INIT() {
#ifdef FEATURE_RC_OSCILLATOR_CALIBRATION
#define RC_OSCILLATOR_CALIBRATION_BYTE 0x01
  rcOscillatorCalibration =
      boot_signature_byte_get(RC_OSCILLATOR_CALIBRATION_BYTE);
#undef RC_OSCILLATOR_CALIBRATION_BYTE
#endif
#ifdef FEATURE_INTERNAL_8MHZ_OSCILLATOR_CALIBRATION
#define INTERNAL_8MHZ_OSCILLATOR_CALIBRATION_BYTE 0x01
  internal8MHzOscillatorCalibration =
      boot_signature_byte_get(INTERNAL_8MHZ_OSCILLATOR_CALIBRATION_BYTE);
#undef INTERNAL_8MHZ_OSCILLATOR_CALIBRATION_BYTE
#endif
#ifdef FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_A
#define OSCILLATOR_TEMPERATURE_CALIBRATION_A_BYTE 0x03
  oscillatorTemperatureCalibrationA =
      boot_signature_byte_get(OSCILLATOR_TEMPERATURE_CALIBRATION_A_BYTE);
#undef OSCILLATOR_TEMPERATURE_CALIBRATION_A_BYTE
#endif
#ifdef FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_B
#define OSCILLATOR_TEMPERATURE_CALIBRATION_B_BYTE 0x05
  oscillatorTemperatureCalibrationB =
      boot_signature_byte_get(OSCILLATOR_TEMPERATURE_CALIBRATION_B_BYTE);
#undef OSCILLATOR_TEMPERATURE_CALIBRATION_B_BYTE
#endif
#ifdef FEATURE_INTERNAL_32KHZ_OSCILLATOR_CALIBRATION
#define INTERNAL_32KHZ_OSCILLATOR_CALIBRATION_BYTE 0x07
  internal32kHzOscillatorCalibration =
      boot_signature_byte_get(INTERNAL_32KHZ_OSCILLATOR_CALIBRATION_BYTE);
#undef INTERNAL_32KHZ_OSCILLATOR_CALIBRATION_BYTE
#endif
#ifdef FEATURE_TEMPERATURE_SENSOR_GAIN_CALIBRATION
#define TEMPERATURE_SENSOR_GAIN_CALIBRATION_BYTE 0x2C
  temperatureSensorGainCalibration =
      boot_signature_byte_get(TEMPERATURE_SENSOR_GAIN_CALIBRATION_BYTE);
#undef TEMPERATURE_SENSOR_GAIN_CALIBRATION_BYTE
#endif
#ifdef FEATURE_TEMPERATURE_SENSOR_OFFSET_CALIBRATION
#define TEMPERATURE_SENSOR_OFFSET_CALIBRATION_BYTE 0x2D
  temperatureSensorOffsetCalibration =
      boot_signature_byte_get(TEMPERATURE_SENSOR_OFFSET_CALIBRATION_BYTE);
#undef TEMPERATURE_SENSOR_OFFSET_CALIBRATION_BYTE
#endif
}

String Features::getSummary() {
#if defined(CHAR_PTR_STRING)
  size_t size = 0;
#else
  String summary = F("");
#endif
#ifdef FEATURE_RC_OSCILLATOR_CALIBRATION
  String stringRCOscillatorCalibration = F("\n\tRC Oscillator Calibration: 0x");
#if defined(CHAR_PTR_STRING)
  size += snprintf(nullptr, 0, "%s%X", stringRCOscillatorCalibration,
                   rcOscillatorCalibration);
#else
  summary += stringRCOscillatorCalibration;
  summary += String(rcOscillatorCalibration, HEX);
#endif
#endif
#ifdef FEATURE_INTERNAL_8MHZ_OSCILLATOR_CALIBRATION
  String stringInternal8MHZOscillatorCalibration =
      F("\n\tInternal 8MHz Oscillator Calibration (OSCCAL0): 0x");
#if defined(CHAR_PTR_STRING)
  size += snprintf(nullptr, 0, "%s%X", stringInternal8MHZOscillatorCalibration,
                   internal8MHzOscillatorCalibration);
#else
  summary += stringInternal8MHZOscillatorCalibration;
  summary += String(internal8MHzOscillatorCalibration, HEX);
#endif
#endif
#ifdef FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_A
  String stringOscillatorTemperatureCalibrationA =
      F("\n\tOscillator Temperature Calibration Register A (OSCTCAL0A): 0x");
#if defined(CHAR_PTR_STRING)
  size += snprintf(nullptr, 0, "%s%X", stringOscillatorTemperatureCalibrationA,
                   oscillatorTemperatureCalibrationA);
#else
  summary += stringOscillatorTemperatureCalibrationA;
  summary += String(oscillatorTemperatureCalibrationA, HEX);
#endif
#endif
#ifdef FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_B
  String stringOscillatorTemperatureCalibrationB =
      F("\n\tOscillator Temperature Calibration Register B (OSCTCAL0B): 0x");
#if defined(CHAR_PTR_STRING)
  size += snprintf(nullptr, 0, "%s%X", stringOscillatorTemperatureCalibrationB,
                   oscillatorTemperatureCalibrationB);
#else
  summary += stringOscillatorTemperatureCalibrationB;
  summary += String(oscillatorTemperatureCalibrationB, HEX);
#endif
#endif
#ifdef FEATURE_INTERNAL_32KHZ_OSCILLATOR_CALIBRATION
  String stringInternal32KHZOscillatorCalibration =
      F("\n\tInternal 32kHz Oscillator Calibration (OSCCAL1): 0x");
#if defined(CHAR_PTR_STRING)
  size += snprintf(nullptr, 0, "%s%X", stringInternal32KHZOscillatorCalibration,
                   internal32kHzOscillatorCalibration);
#else
  summary += stringInternal32KHZOscillatorCalibration;
  summary += String(internal32kHzOscillatorCalibration, HEX);
#endif
#endif
#ifdef FEATURE_TEMPERATURE_SENSOR_GAIN_CALIBRATION
  String stringTemperatureSensorGainCalibration =
      F("\n\tTemperature Sensor Gain Calibration: 0x");
#if defined(CHAR_PTR_STRING)
  size += snprintf(nullptr, 0, "%s%X", stringTemperatureSensorGainCalibration,
                   temperatureSensorGainCalibration);
#else
  summary += stringTemperatureSensorGainCalibration;
  summary += String(temperatureSensorGainCalibration, HEX);
#endif
#endif
#ifdef FEATURE_TEMPERATURE_SENSOR_OFFSET_CALIBRATION
  String stringTemperatureSensorOffsetCalibration =
      F("\n\tTemperature Sensor Offset Calibration: 0x");
#if defined(CHAR_PTR_STRING)
  size += snprintf(nullptr, 0, "%s%X", stringTemperatureSensorOffsetCalibration,
                   temperatureSensorOffsetCalibration);
#else
  summary += stringTemperatureSensorOffsetCalibration;
  summary += String(temperatureSensorOffsetCalibration, HEX);
#endif
#endif
#if defined(CHAR_PTR_STRING)
  auto summary = (String)malloc(sizeof(unsigned char) * size + 1);
#ifdef FEATURE_RC_OSCILLATOR_CALIBRATION
  sprintf((char *)summary, "%s%s%X", summary, stringRCOscillatorCalibration,
          rcOscillatorCalibration);
#endif
#ifdef FEATURE_INTERNAL_8MHZ_OSCILLATOR_CALIBRATION
  sprintf((char *)summary, "%s%s%X", summary,
          stringInternal8MHZOscillatorCalibration,
          internal8MHzOscillatorCalibration);
#endif
#ifdef FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_A
  sprintf((char *)summary, "%s%s%X", summary,
          stringOscillatorTemperatureCalibrationA,
          oscillatorTemperatureCalibrationA);
#endif
#ifdef FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_B
  sprintf((char *)summary, "%s%s%X", summary,
          stringOscillatorTemperatureCalibrationB,
          oscillatorTemperatureCalibrationB);
#endif
#ifdef FEATURE_INTERNAL_32KHZ_OSCILLATOR_CALIBRATION
  sprintf((char *)summary, "%s%s%X", summary,
          stringInternal32KHZOscillatorCalibration,
          internal32kHzOscillatorCalibration);
#endif
#ifdef FEATURE_TEMPERATURE_SENSOR_GAIN_CALIBRATION
  sprintf((char *)summary, "%s%s%X", summary,
          stringTemperatureSensorGainCalibration,
          temperatureSensorGainCalibration);
#endif
#ifdef FEATURE_TEMPERATURE_SENSOR_OFFSET_CALIBRATION
  sprintf((char *)summary, "%s%s%X", summary,
          stringTemperatureSensorOffsetCalibration,
          temperatureSensorOffsetCalibration);
#endif
#endif
  return summary;
}
