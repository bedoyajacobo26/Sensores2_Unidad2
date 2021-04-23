#ifndef DS1307_RTC_h
#define DS1307_RTC_h
#include "Arduino.h"

class DS1307_RTC
{
    public:
        DS1307_RTC(uint8_t address);
        bool detectDevice(uint8_t address);
        byte decToBcd(byte val);
        byte bcdToDec(byte val);
        void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
                   dayOfMonth, byte month, byte year);
        void readDS3231time(byte *second,
                    byte *minute,
                    byte *hour,
                    byte *dayOfWeek,
                    byte *dayOfMonth,
                    byte *month,
                    byte *year);
        void displayTime();
}

#endif