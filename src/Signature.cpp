/*!
 * @file Signature.cpp
 *
 * This file is part of the Signature library. It gives easy access to the
 * signature row of AVR microcontrollers. The library contains functions that
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

#include "Signature.hpp"

#include <avr/boot.h>

Signature::signature_t signature_t::signature = {};
uint8_t Signature::rcOscillatorCalibration = 0;
bool Signature::INIT_STATUS = false;

/*!
 * @def DEVICE_SIG_BYTE_1
 * @brief Address of first signature byte
 */
/*!
 * @def DEVICE_SIG_BYTE_2
 * @brief Address of second signature byte
 */
/*!
 * @def DEVICE_SIG_BYTE_3
 * @brief Address of third signature byte
 */
/*!
 * @def RC_OSCILLATOR_CALIBRATION_BYTE
 * @brief Address of RC oscillator calibration byte
 */
void Signature::INIT() {
#define DEVICE_SIG_BYTE_1 0x0000
#define DEVICE_SIG_BYTE_2 0x0002
#define DEVICE_SIG_BYTE_3 0x0004

#define RC_OSCILLATOR_CALIBRATION_BYTE 0x0001

  if (!INIT_STATUS) {
    signature.sig1 = boot_signature_byte_get(DEVICE_SIG_BYTE_1);
    signature.sig2 = boot_signature_byte_get(DEVICE_SIG_BYTE_2);
    signature.sig3 = boot_signature_byte_get(DEVICE_SIG_BYTE_3);

    rcOscillatorCalibration =
        boot_signature_byte_get(RC_OSCILLATOR_CALIBRATION_BYTE);

    INIT_STATUS = true;
  }

#undef RC_OSCILLATOR_CALIBRATION_BYTE
#undef DEVICE_SIG_BYTE_3
#undef DEVICE_SIG_BYTE_2
#undef DEVICE_SIG_BYTE_1
}

String Signature::getSignatureString() {
  String sigStr = F("0x");
  sigStr += String(signature.sig1, HEX);
  sigStr += String(signature.sig2, HEX);
  sigStr += String(signature.sig3, HEX);
  return sigStr;
}

String Signature::getChipName() {
  return Chip::getChipName(signature.sig1, signature.sig2, signature.sig3);
}

String Signature::getSummary() {
  INIT();

  String summary = F("Signature Information:\n");
  summary += F("\tBoard: ");
  summary += getChipName();
  summary += F(" (");
  summary += getSignatureString();
  summary += F(")\n");
  summary += F("\tRC Oscillator Calibration: 0x");
  summary += String(rcOscillatorCalibration, HEX);
  return summary;
}

String Signature::Chip::getChipName(uint8_t sig1, uint8_t sig2, uint8_t sig3) {
  if (sig1 == 0x1E) {
    if (sig2 == 0x92) {
      if (sig3 == 0x05) {
        return "ATmega48A";
      } else if (sig3 == 0x0A) {
        return "ATmega48PA";
      }
    } else if (sig2 == 0x93) {
      if (sig3 == 0x0A) {
        return "ATmega88A";
      } else if (sig3 == 0x0F) {
        return "ATmega88PA";
      }
    } else if (sig2 == 0x94) {
      if (sig3 == 0x06) {
        return "ATmega168A";
      } else if (sig3 == 0x0B) {
        return "ATmega168PA";
      }
    } else if (sig2 == 0x95) {
      if (sig3 == 0x14) {
        return "ATmega328";
      } else if (sig3 == 0x0F) {
        return "ATmega328P";
      }
    }
  }
  return "UNKNOWN";
}
