/*
 * ArduinoNunchuk.cpp - Improved Wii Nunchuk library for Arduino
 *
 * Copyright 2011-2013 Gabriel Bianconi, http://www.gabrielbianconi.com/
 *
 * Project URL: http://www.gabrielbianconi.com/projects/arduinonunchuk/
 *
 * Based on the following resources:
 *   http://www.windmeadow.com/node/42
 *   http://todbot.com/blog/2008/02/18/wiichuck-wii-nunchuck-adapter-available/
 *   http://wiibrew.org/wiki/Wiimote/Extension_Controllers
 *
 */

#include "ArduinoNunchuk.hpp"

#include <Arduino.h>
#include <Wire.h>

ArduinoNunchuk::ArduinoNunchuk() {
    Wire.begin();
}

ArduinoNunchuk::~ArduinoNunchuk() {
    Wire.end();
}

void ArduinoNunchuk::init() {
    _sendByte(0xF0, 0x55);
    _sendByte(0xFB, 0x00);

    update();

    _connected = true;
}

void ArduinoNunchuk::update() {
    _receiveBytes(0x00, _report, 6);
}

bool ArduinoNunchuk::connected() {
    return _connected;
}

uint8_t ArduinoNunchuk::stickX() {
    return _report[0];
}

uint8_t ArduinoNunchuk::stickY() {
    return _report[1];
}

uint16_t ArduinoNunchuk::accelX() {
    return (_report[2] << 2) | ((_report[5] >> 2) & 0x03);
}

uint16_t ArduinoNunchuk::accelY() {
    return (_report[3] << 2) | ((_report[5] >> 4) & 0x03);
}

uint16_t ArduinoNunchuk::accelZ() {
    return (_report[4] << 2) | ((_report[5] >> 6) & 0x03);
}

bool ArduinoNunchuk::buttonZ() {
    return !(_report[5] & 0x01);
}

bool ArduinoNunchuk::buttonC() {
    return !((_report[5] >> 1) & 0x01);
}

void ArduinoNunchuk::_sendByte(uint8_t location, uint8_t data) {
    Wire.beginTransmission(NUNCHUK_ADDRESS);

    Wire.write(location);
    Wire.write(data);

    Wire.endTransmission();
}

void ArduinoNunchuk::_receiveBytes(uint8_t location, uint8_t *buf, uint8_t length) {
    // Send the location we want to read from.
    Wire.beginTransmission(NUNCHUK_ADDRESS);
    Wire.write(location);
    Wire.endTransmission();

    // Conversion delay.
    delayMicroseconds(CONVERSION_DELAY_US);

    // Request to read a certain number of bytes from that location.
    Wire.requestFrom(NUNCHUK_ADDRESS, length);

    // Read requested number of bytes into
    for (int i = 0; i < length && Wire.available(); i++) {
        _report[i] = Wire.read();
    }
}
