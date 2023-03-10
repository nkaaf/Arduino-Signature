/*!
 * @file Signature.cpp
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

#include "Signature.hpp"

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
  String sigStr = F("");
  String sigStrBegin = F("0x");
  String leadingZero = F("0");
#if defined(CHAR_PTR_STRING)
  size_t size = strlen((char *)sigStrBegin);
#else
  sigStr += sigStrBegin;
#endif

  if (signature.sig1 < 16) {
#if defined(CHAR_PTR_STRING)
    size += strlen((char *)leadingZero);
#else
    sigStr += leadingZero;
#endif
  }
#if defined(CHAR_PTR_STRING)
  size += snprintf(nullptr, 0, "%X", signature.sig1);
#else
  sigStr += String(signature.sig1, HEX);
#endif

  if (signature.sig2 < 16) {
#if defined(CHAR_PTR_STRING)
    size += strlen((char *)leadingZero);
#else
    sigStr += leadingZero;
#endif
  }
#if defined(CHAR_PTR_STRING)
  size += snprintf(nullptr, 0, "%X", signature.sig2);
#else
  sigStr += String(signature.sig2, HEX);
#endif

  if (signature.sig3 < 16) {
#if defined(CHAR_PTR_STRING)
    size += strlen((char *)leadingZero);
#else
    sigStr += leadingZero;
#endif
  }
#if defined(CHAR_PTR_STRING)
  size += snprintf(nullptr, 0, "%X", signature.sig3);
#else
  sigStr += String(signature.sig3, HEX);
#endif

#if defined(CHAR_PTR_STRING)
  sigStr = (String)malloc(sizeof(unsigned char) * size + 1);
  sprintf((char *)sigStr, "%s", sigStrBegin);
  if (signature.sig1 < 16) {
    sprintf((char *)sigStr, "%s%s", sigStr, leadingZero);
  }
  sprintf((char *)sigStr, "%s%X", sigStr, signature.sig1);
  if (signature.sig2 < 16) {
    sprintf((char *)sigStr, "%s%s", sigStr, leadingZero);
  }
  sprintf((char *)sigStr, "%s%X", sigStr, signature.sig2);
  if (signature.sig3 < 16) {
    sprintf((char *)sigStr, "%s%s", sigStr, leadingZero);
  }
  sprintf((char *)sigStr, "%s%X", sigStr, signature.sig3);
#endif
  return sigStr;
}

String Signature::getSummary() {
  INIT();

#if defined(CHAR_PTR_STRING)
  String chipName = getChipName();
  String signatureString = getSignatureString();
  String featuresSummary = Features::getSummary();
  size_t size = snprintf(nullptr, 0,
                         "Signature Information:\n"
                         "\tBoard: "
                         "%s"
                         " ("
                         "%s"
                         ")"
                         "%s",
                         chipName, signatureString, featuresSummary);
  auto summary = (String)malloc(sizeof(unsigned char) * size + 1);
  sprintf((char *)summary,
          "Signature Information:\n"
          "\tBoard: "
          "%s"
          " ("
          "%s"
          ")"
          "%s",
          chipName, signatureString, featuresSummary);
  free(signatureString);
  free(featuresSummary);
#else

  String summary = F("Signature Information:\n");
  summary += F("\tBoard: ");
  summary += getChipName();
  summary += F(" (");
  summary += getSignatureString();
  summary += F(")");
  summary += Features::getSummary();
#endif
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
