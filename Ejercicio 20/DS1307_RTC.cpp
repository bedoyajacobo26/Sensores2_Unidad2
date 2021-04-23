#include "Arduino.h"
#include "DS1307_RTC.h"
#include <Wire.h>

DS1307_RTC :: DS1307_RTC (uint8_t address) {

    uint8_t DS3231_I2C_ADDRESS = address;
}

byte DS1307_RTC :: decToBcd(byte val){

     return ( (val / 10 * 16) + (val % 10) ); 
}

byte DS1307_RTC :: bcdToDec(byte val) {
  return ( (val / 16 * 10) + (val % 16) );
}

bool DS1307_RTC :: detectDevice(uint8_t address) {

  Wire.beginTransmission(address);
  Wire.write(0x00);

  if (Wire.endTransmission() != 0)
    return false;
  else
  {
    return true;
  }
}

void DS1307_RTC :: setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
                   dayOfMonth, byte month, byte year) {
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0x00);
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(dayOfWeek));
  Wire.write(decToBcd(dayOfMonth));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}

void DS1307_RTC :: readDS3231time(byte *second,
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

void DS1307_RTC :: displayTime() {

  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;

  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
                 &year);

  uint8_t command[] = {second, minute, hour, dayOfWeek, dayOfMonth, month, year};

  Serial.print("HORA: ");
  Serial.print(command[0]);
  Serial.print(" : ");
  Serial.print(command[1]);
  Serial.print(" : ");
  Serial.print(command[2]);
  Serial.print("\t");
  Serial.print("FECHA: ");
  Serial.print(command[3]);
  Serial.print(" - ");
  Serial.print(command[4]);
  Serial.print(" / ");
  Serial.print(command[5]);
  Serial.print(" / ");
  Serial.print(command[6]);
  
  Serial.println();
}