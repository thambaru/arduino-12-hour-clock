#include <stdlib.h>
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h> // Library for LCD

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

String sanitize(String value, bool hours = false) {
  String result = value;


  if (result.toInt() > 12 && hours) {
    int twelvehr = result.toInt() - 12;
    result = (String) twelvehr;
  }

  unsigned int valSize = result.length();
  if (valSize < 2) {
    result = String("0") + (String) result;
  }

  return result;
}

void setup ()
{
  Serial.begin(9600);
  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC lost power, lets set the time!");

    // Comment out below lines once you set the date & time.
    // Following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

    // Following line sets the RTC with an explicit date & time
    // for example to set January 27 2017 at 12:56 you would call:
    // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
  }

  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop ()
{


  DateTime now = rtc.now();

  //    Serial.println("Current Date & Time: ");
  //    Serial.print(now.year(), DEC);
  //    Serial.print('/');
  //    Serial.print(now.month(), DEC);
  //    Serial.print('/');
  //    Serial.print(now.day(), DEC);
  //    Serial.print(" (");
  //    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  //    Serial.print(") ");
  //    Serial.print(now.hour(), DEC);
  //    Serial.print(':');
  //    Serial.print(now.minute(), DEC);
  //    Serial.print(':');
  //    Serial.print(now.second(), DEC);
  //    Serial.println();

  //    Serial.println("Unix Time: ");
  //    Serial.print("elapsed ");
  //    Serial.print(now.unixtime());
  //    Serial.print(" seconds/");
  //    Serial.print(now.unixtime() / 86400L);
  //    Serial.println(" days since 1/1/1970");

  // calculate a date which is 7 days & 30 seconds into the future
  //    DateTime future (now + TimeSpan(7,0,0,30));
  //
  //    Serial.println("Future Date & Time (Now + 7days & 30s): ");
  //    Serial.print(future.year(), DEC);
  //    Serial.print('/');
  //    Serial.print(future.month(), DEC);
  //    Serial.print('/');
  //    Serial.print(future.day(), DEC);
  //    Serial.print(' ');
  //    Serial.print(future.hour(), DEC);
  //    Serial.print(':');
  //    Serial.print(future.minute(), DEC);
  //    Serial.print(':');
  //    Serial.print(future.second(), DEC);
  //    Serial.println();

  //    Serial.println();

  lcd.setCursor(3, 0);
//  lcd.print("Date: ");
  lcd.print(sanitize((String) now.day()));
  lcd.print("/");
  lcd.print(sanitize((String) now.month()));
  lcd.print("/");
  lcd.print(now.year(), DEC);

  lcd.setCursor(3, 1);
//  lcd.print("Time: ");
  lcd.print(sanitize((String) now.hour(), true));
  lcd.print(":");
  lcd.print(sanitize((String) now.minute()));
  lcd.print(":");
  lcd.print(sanitize((String) now.second()));

  if(((String) now.hour()).toInt() > 12){
    lcd.print("pm");  
  }else{
    lcd.print("am");
  }

  delay(1000);
}
