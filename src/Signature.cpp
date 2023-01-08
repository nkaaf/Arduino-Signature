/*!
 * @file Signature.cpp
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

#include "Signature.hpp"

#include <avr/boot.h>

#include <Print.h>

Signature::signature_t Signature::signature = {};
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
void Signature::INIT() {
#define DEVICE_SIG_BYTE_1 0x00
#define DEVICE_SIG_BYTE_2 0x02
#define DEVICE_SIG_BYTE_3 0x04

  if (!INIT_STATUS) {
    Features::INIT();

    signature.sig1 = boot_signature_byte_get(DEVICE_SIG_BYTE_1);
    signature.sig2 = boot_signature_byte_get(DEVICE_SIG_BYTE_2);
    signature.sig3 = boot_signature_byte_get(DEVICE_SIG_BYTE_3);

    INIT_STATUS = true;
  }

#undef DEVICE_SIG_BYTE_3
#undef DEVICE_SIG_BYTE_2
#undef DEVICE_SIG_BYTE_1
}

String Signature::getSignatureString() {
  String sigStr = F("0x");

  if (signature.sig1 < 16) {
    sigStr += F("0");
  }
  sigStr += String(signature.sig1, HEX);

  if (signature.sig2 < 16) {
    sigStr += F("0");
  }
  sigStr += String(signature.sig2, HEX);

  if (signature.sig3 < 16) {
    sigStr += F("0");
  }
  sigStr += String(signature.sig3, HEX);
  return sigStr;
}

String Signature::getSummary() {
  INIT();

  String summary = F("Signature Information:\n");
  summary += F("\tBoard: ");
  summary += getChipName();
  summary += F(" (");
  summary += getSignatureString();
  summary += F(")");
  summary += Features::getSummary();
  return summary;
}

String Signature::getChipName() {
  return
#if defined(__AVR_ATmega48A__)
      F("ATmega48A")
#elif defined(__AVR_ATmega48PA__)
      F("ATmega48PA")
#elif defined(__AVR_ATmega88A__)
      F("ATmega88A")
#elif defined(__AVR_ATmega88PA__)
      F("ATmega88PA")
#elif defined(__AVR_ATmega168A__)
      F("ATmega168A")
#elif defined(__AVR_ATmega168PA__)
      F("ATmega168PA")
#elif defined(__AVR_ATmega328__)
      F("ATmega328")
#elif defined(__AVR_ATmega328P__)
      F("ATmega328P")
#elif defined(__AVR_ATmega328PB__)
      F("ATmega328PB")
#elif defined(__AVR_ATtiny828__)
      F("ATtiny828")
#else
      F("UNKNOWN")
#endif
          ;
}
