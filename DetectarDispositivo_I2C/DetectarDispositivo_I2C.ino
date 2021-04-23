#include "Wire.h"

#define DS3231_I2C_ADDRESS 0x68
bool detectDevice(uint8_t address);

void setup() {
  Wire.begin();
  Serial.begin(115200);

}

void loop() {

  if (detectDevice(DS3231_I2C_ADDRESS))
  {
    Serial.println("Sensor encontrado");
  }

  else
  {
    Serial.println("No se ha encontrado sensor");
  }

  delay(1000);
}

bool detectDevice(uint8_t address) {

  Wire.beginTransmission(address);
  Wire.write(0x00);

  if (Wire.endTransmission() != 0)
    return false;
  else
  {
    return true;
  }
}
