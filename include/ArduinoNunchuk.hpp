/*
 * ArduinoNunchuk.h - Improved Wii Nunchuk library for Arduino
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

#ifndef ArduinoNunchuk_H
#define ArduinoNunchuk_H

#include <Arduino.h>
#include <Wire.h>

class ArduinoNunchuk {
  public:
    ArduinoNunchuk(TwoWire &wire);
    ~ArduinoNunchuk();

    bool init();
    void update();
    bool connected();

    uint8_t stickX();
    uint8_t stickY();

    uint16_t accelX();
    uint16_t accelY();
    uint16_t accelZ();

    bool buttonZ();
    bool buttonC();

  private:
    const uint8_t NUNCHUK_ADDRESS = 0x52;
    const uint16_t CONVERSION_DELAY_US = 175;

    TwoWire &_wire;
    bool _connected = false;
    uint8_t _report[6] = { 0 };
    bool _sendByte(uint8_t location, uint8_t data);
    bool _receiveBytes(uint8_t location, uint8_t *buf, uint8_t length);
};

#endif
