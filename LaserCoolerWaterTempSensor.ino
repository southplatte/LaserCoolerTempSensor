#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DS3231.h>


//setup display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


float tempF = 0.0;
int oneWireBus = 7;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
//clock for time stamp
DS3231 Clock;
bool Century = false;
bool h12;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;
float second, minute, hour, date, month, year, val;



void setup() {

  Serial.begin(9600);
  //setup temp sensor
  sensors.begin();
  Serial.println("Sensor Begin");
  Serial.println("Setup Time: ");
  ReadDS3231();
  Serial.println("");
  Serial.println("FSL Temp Monitoring Starting....");
  //led setup
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(6, HIGH);
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(6, LOW);
  digitalWrite(9, LOW);
  //lcd
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("W");
  delay(250);
  lcd.print("e");
  delay(250);
  lcd.print("l");
  delay(250);
  lcd.print("c");
  delay(250);
  lcd.print("o");
  delay(250);
  lcd.print("m");
  delay(250);
  lcd.print("e");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("FSL Temp Monitor");
}



void loop() {

  //read temp
  sensors.requestTemperatures();
  tempF = sensors.getTempCByIndex(0) * 1.8 + 32;
  if (tempF > 70) {
    digitalWrite(9, HIGH);
    digitalWrite(6, LOW);
    tone(8, 3800, 500);
    lcd.clear();
    lcd.print("WARNING");
    lcd.setCursor(0, 1);
    lcd.print("HIGH TEMP!");
  } else {
    lcd.clear();
    lcd.print("FSL Temp Monitor");
    lcd.setCursor(0, 1);
    lcd.write("Degrees F: ");
    lcd.print(tempF, 1);
    digitalWrite(9, LOW);
    digitalWrite(6, HIGH);
  }
  //Serial.print()
  ReadDS3231();
  Serial.print(" - Degrees F: ");
  Serial.println(tempF, 1);

  //lcd.print(" Degree");
  delay(1000);
}

void ReadDS3231() {
  int second, minute, hour, date, month, year, pm, clockTemp;

  second = Clock.getSecond();
  minute = Clock.getMinute();
  hour = Clock.getHour(h12, PM);
  date = Clock.getDate();
  month = Clock.getMonth(Century);
  year = Clock.getYear();
  clockTemp = Clock.getTemperature();

  Serial.print(month);
  Serial.print("/");
  Serial.print(date);
  Serial.print("/");
  Serial.print(year);
  Serial.print(" - ");
  Serial.print(hour);
  Serial.print(':');
  Serial.print(minute);
  Serial.print(':');
  Serial.print(second);
  Serial.print(" - Clock Temp: ");
  Serial.print(clockTemp * 1.8 + 32);
}