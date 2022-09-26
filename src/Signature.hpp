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

#ifndef SIGNATURE_ROW_SIGNATURE_ROW_HPP
#define SIGNATURE_ROW_SIGNATURE_ROW_HPP

#include <Print.h>

/*!
 * @brief   Class representing the signature of the microcontroller.
 */
class Signature {
private:
  /** structure of signature */
  typedef struct {
    uint8_t sig1, sig2, sig3; /// The bytes of the signature.
  } signature_t;

  static signature_t signature;           /// Signature of AVR microcontroller.
  static uint8_t rcOscillatorCalibration; /// Factory calibration value of the
                                          /// internal RC oscillator.
  static bool INIT_STATUS; /// Indicating if the class is initialized.

  /*!
   * @brief   Initialise the class.
   */
  static void INIT() __attribute__((__gnu_inline__));

  /*!
   * @brief Get the signature as a string.
   *
   * @return    A string of the signature formatted as a hex value (with leading
   *            '0x').
   */
  static String getSignatureString();

  /*!
   * @brief Internal class holding methods for the chip.
   */
  class Chip {
  public:
    /*!
     * @brief   Get the name of the chip by the signature.
     *
     * @param sig1  Byte 1 of the signature.
     * @param sig2  Byte 2 of the signature.
     * @param sig3  Byte 3 of the signature.
     * @return  The name of the chip.
     */
    static String getChipName(uint8_t sig1, uint8_t sig2, uint8_t sig3);
  };

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

  /*!
   * @brief Get the factory calibration the the internal RC oscillator.
   *
   * @return    Calibration value as an unsigned char.
   */
  static uint8_t getRcOscillatorCalibration() {
    INIT();
    return rcOscillatorCalibration;
  }

  /*!
   * @brief Writing a summary of the signature of the chip into a string.
   *        Usefully for giving information about the used microcontroller for
   *        debugging or logging intents.
   *
   * @return    A string containing a summary of the signature.
   */
  static String getSummary();
};

#endif // SIGNATURE_ROW_SIGNATURE_ROW_HPP
