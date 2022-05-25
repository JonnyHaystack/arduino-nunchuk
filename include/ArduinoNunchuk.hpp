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

class ArduinoNunchuk {
  public:
    ArduinoNunchuk();
    ~ArduinoNunchuk();

    void init();
    void update();
    void connected();

    int stickX();
    int stickY();

    int accelX();
    int accelY();
    int accelZ();

    int buttonZ();
    int buttonC();

  private:
    const uint8_t NUNCHUK_ADDRESS = 0x52;
    const uint16_t CONVERSION_DELAY_US = 175;

    bool _connected = false;
    uint8_t _report[6] = { 0 };
    void _sendByte(uint8_t location, uint8_t data);
    void _receiveBytes(uint8_t location, uint8_t *buf, uint8_t length);
};

#endif
