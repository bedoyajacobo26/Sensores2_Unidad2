#include "Wire.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5


#define SEALEVELPRESSURE_HPA (1013.25)
#define DS3231_I2C_ADDRESS 0x68
Adafruit_BME280 bme(BME_CS); // hardware SPI
bool status;


byte decToBcd(byte val) {
  return ( (val / 10 * 16) + (val % 10) );
}

byte bcdToDec(byte val) {
  return ( (val / 16 * 10) + (val % 16) );
}
void setup() {
  Wire.begin();
  Serial.begin(115200);
  status = bme.begin();

  setDS3231time(10, 36, 22, 1, 19, 4, 21);

}
void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
                   dayOfMonth, byte month, byte year) {
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0);
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(dayOfWeek));
  Wire.write(decToBcd(dayOfMonth));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}
void readDS3231time(byte *second,
                    byte *minute,
                    byte *hour,
                    byte *dayOfWeek,
                    byte *dayOfMonth,
                    byte *month,
                    byte *year) {
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);

  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

void displayTime() {
  if (Serial.available() > 0) {
    if (Serial.read() == 0x73) {
      byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
      readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
                     &year);

      float temperature = bme.readTemperature();
      float pressure = (bme.readPressure() / 100.0F);
      float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
      float humidity = bme.readHumidity();

      uint8_t arr_temp[4] = {0};
      memcpy(arr_temp, (uint8_t *)&temperature, 4);
      uint8_t arr_pres[4] = {0};
      memcpy(arr_pres, (uint8_t *)&pressure, 4);
      uint8_t arr_alti[4] = {0};
      memcpy(arr_alti, (uint8_t *)&altitude, 4);
      uint8_t arr_humi[4] = {0};
      memcpy(arr_humi, (uint8_t *)&humidity, 4);


      uint8_t command[] = {second, minute, hour, dayOfWeek, dayOfMonth, month, year,
                           (unsigned char)arr_temp[0], (unsigned char)arr_temp[1], (unsigned char)arr_temp[2], (unsigned char)arr_temp[3],
                           (unsigned char)arr_pres[0], (unsigned char)arr_pres[1], (unsigned char)arr_pres[2], (unsigned char)arr_pres[3],
                           (unsigned char)arr_alti[0], (unsigned char)arr_alti[1], (unsigned char)arr_alti[2], (unsigned char)arr_alti[3],
                           (unsigned char)arr_humi[0], (unsigned char)arr_humi[1], (unsigned char)arr_humi[2], (unsigned char)arr_humi[3]
                          };
      Serial.write(command, sizeof(command));

    }
  }
}
void loop() {
  displayTime();
  delay(1000);
}
