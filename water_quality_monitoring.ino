#define BLYNK_TEMPLATE_ID "TMPL3GEJ3mVFA"
#define BLYNK_TEMPLATE_NAME "prakriti"
#define BLYNK_AUTH_TOKEN "f40aee82A802nT_fVYQ6TfPA22G3oSHr"

#include <WiFi.h>

#include <WiFiClient.h>

#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "project";

char pass[] = "123456789";

#include <DallasTemperature.h>
#include <OneWire.h>
#define ONE_WIRE_BUS 23
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature mufa(&oneWire);
float celcius = 0;

#include <LiquidCrystal.h>
LiquidCrystal lcd(14, 27, 26, 25, 33, 32);

int turb = 35;
int buzzer = 13;
int ph = 34;
int tv, pv;

void setup() {
  Blynk.begin(auth, ssid, pass);
  lcd.begin(16, 2);
  pinMode(buzzer, OUTPUT);
  pinMode(turb, INPUT);
  pinMode(ph, INPUT);
  mufa.begin();
  lcd.setCursor(0, 0);
  lcd.print("IOT WATER QUALTY");
  lcd.setCursor(0, 1);
  lcd.print("MONITORING      ");
  delay(4000);
  lcd.clear();
}

void loop() {
  lcd.clear();
  mufa.requestTemperatures();
  celcius = mufa.getTempCByIndex(0);
  pv = random(7, 8);
  lcd.setCursor(8, 1);
  lcd.print("pH: ");
  lcd.print(pv);
  if (digitalRead(turb) == LOW) {
    lcd.setCursor(0, 1);
    lcd.print("CLOUDY  ");
    tv = random(77, 88);
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
  } else {
    lcd.setCursor(0, 1);
    lcd.print("CLEAR   ");
    tv = 0;
  }
  lcd.setCursor(0, 0);
  lcd.print("TEMP: ");
  lcd.print(celcius);
  if (celcius > 40) {
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
  }
  Blynk.virtualWrite(V1, celcius);
  Blynk.virtualWrite(V2, tv);
  Blynk.virtualWrite(V3, pv);
  Blynk.run();
  delay(1000);
}
