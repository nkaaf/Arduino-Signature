#include <SignatureRow.hpp>

void setup() {
    Serial.begin(9600);

    // Microcontrollers like the ATmega328P used in Arduino Nano have bytes written on read-only memory by the
    // manufactures. These bytes are used for identification of the chip and calibration.

    // Prints out the signature of the chip in HEX format (with leading '0x')
    Serial.print("Signature: ");
    Serial.println(SignatureRow::getSignature());
    // You can also print out the type of the chip. This is internally processed by the signature. For example the
    // ATmega328P has the signature 0x1E950F (according to the datasheet).
    Serial.print("Chip Name: ");
    Serial.println(SignatureRow::getChipName());

    // In the SignatureRow of the microcontrollers are also values which can be used for calibrating internal processes
    // of the chip. For example for calibration the Internal RC Oscillator by software, you can use this value
    Serial.print("RC Oscillator Calibration: ");
    Serial.print(SignatureRow::getRcOscillatorCalibration()); // Prints the value as a decimal value
    Serial.print(" (decimal); ");
    Serial.print(SignatureRow::getRcOscillatorCalibration(), HEX); // Prints the value as a hex value
    Serial.println(" (hex)");

    // To get a summary of your chip and the SignatureRow, you can use the getSummary() method
    Serial.println(SignatureRow::getSummary());
}

void loop() {}