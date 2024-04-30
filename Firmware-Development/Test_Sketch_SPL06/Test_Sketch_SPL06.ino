#include <Wire.h>
#include <SPI.h>
#include "SPL06-001.h"

#define i2cAddress  0x76 //SDO to ground slave address is 0x76 (Our case)
                         //if SDO is connected to VDDIO then address will be 0x77
#define _Scl  6 
#define _Sda  5

SPL06 press_spl06; // I2C

void setup() {
  //while (! Serial);
  Serial.begin(115200);
  Wire.setPins(_Sda, _Scl);

  Serial.println("SPL06-001 Demo\n");
  unsigned status = press_spl06.begin(i2cAddress);
  if (!status) 
  {
    Serial.println(F("Could not find a valid SPL06-001 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was:   0x"); Serial.println(press_spl06.sensorID(),HEX); //HEX
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    while (1) delay(10);
  }

  //following call to setSampling is optional
  press_spl06.setSampling(SPL06::MODE_BACKGND_BOTH,     /* Operating Mode. */
                  SPL06::SAMPLING_X16,     /* Temperature oversampling */
                  SPL06::SAMPLING_X16,    /* Pressure oversampling */
                  SPL06::RATE_X16,      /* Temprature Rate */
                  SPL06::RATE_X16);   /* Pressure Rate */

}

void loop() {
  Serial.print(F("Temperature = "));
  Serial.print(press_spl06.readTemperature());
  Serial.print(" \xc2\xb0"); Serial.println("C");

  Serial.print(press_spl06.readPressureMBar()); Serial.println(" mbar");
  Serial.print(press_spl06.readPressureAltitudeMeter()); Serial.println(" meters (uncorrected)");
  Serial.print(press_spl06.readPressureAltitudeFeet(29.91)); Serial.println(" feet");

  delay(5000); // 5 sec

}