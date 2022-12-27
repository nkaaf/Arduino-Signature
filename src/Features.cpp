/*!
* @file Features.cpp
*
* This file is part of the Signature library. It gives easy access to the
* signature of AVR microcontrollers. The library contains functions that
* provides the information of the signature bytes.
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

#include "Features.hpp"

#include <avr/boot.h>

#include <Print.h>

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
  String summary = F("");
#ifdef FEATURE_RC_OSCILLATOR_CALIBRATION
  summary += F("\n\tRC Oscillator Calibration: 0x");
  summary += String(rcOscillatorCalibration, HEX);
#endif
#ifdef FEATURE_INTERNAL_8MHZ_OSCILLATOR_CALIBRATION
  summary += F("\n\tInternal 8MHz Oscillator Calibration (OSCCAL0): 0x");
  summary += String(internal8MHzOscillatorCalibration, HEX);
#endif
#ifdef FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_A
  summary +=
      F("\n\tOscillator Temperature Calibration Register A (OSCTCAL0A): 0x");
  summary += String(oscillatorTemperatureCalibrationA, HEX);
#endif
#ifdef FEATURE_OSCILLATOR_TEMPERATURE_CALIBRATION_B
  summary +=
      F("\n\tOscillator Temperature Calibration Register B (OSCTCAL0B): 0x");
  summary += String(oscillatorTemperatureCalibrationB, HEX);
#endif
#ifdef FEATURE_INTERNAL_32KHZ_OSCILLATOR_CALIBRATION
  summary += F("\n\tInternal 32kHz Oscillator Calibration (OSCCAL1): 0x");
  summary += String(internal8MHzOscillatorCalibration, HEX);
#endif
#ifdef FEATURE_TEMPERATURE_SENSOR_GAIN_CALIBRATION
  summary += F("\n\tTemperature Sensor Gain Calibration: 0x");
  summary += String(temperatureSensorGainCalibration, HEX);
#endif
#ifdef FEATURE_TEMPERATURE_SENSOR_OFFSET_CALIBRATION
  summary += F("\n\tTemperature Sensor Offset Calibration: 0x");
  summary += String(temperatureSensorOffsetCalibration, HEX);
#endif
  return summary;
}
