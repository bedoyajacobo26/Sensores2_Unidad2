#include "Wire.h"

#define DS3231_I2C_ADDRESS 0x68

bool detectDevice(uint8_t address);

byte decToBcd(byte val) {
  return ( (val / 10 * 16) + (val % 10) );
}

byte bcdToDec(byte val) {
  return ( (val / 16 * 10) + (val % 16) );
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  setDS3231time(10, 36, 22, 1, 19, 4, 21);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (detectDevice(DS3231_I2C_ADDRESS))
  {
    Serial.print("Sensor encontrado\t");
    displayTime();
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

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
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
