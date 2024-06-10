#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 12

// Setup OneWire
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// deklaracja portów LCD:
LiquidCrystal lcd (2, 3, 4, 5, 6, 7);

void setup() {
Serial.begin(9600);
// biblioteka czujnik temperatury
sensors.begin();
setPwmFrequency(9, 64); 
// lcd start:
lcd.begin (16,2);
lcd.clear();
// czujniki:
pinMode(A5, INPUT); // fotorezystor
pinMode(A4, INPUT); // wilgotnosci gleby
// piny do płytek:
pinMode(A1, OUTPUT);
// pin do wysyłania info do płytki:
pinMode(9, OUTPUT);
}

void loop() {

  // odczyt temperatury:
  sensors.requestTemperatures(); 

  // wyświetl temperature:
  lcd.setCursor(0,1);
  lcd.print("T:");
  lcd.print(sensors.getTempCByIndex(0));             
  //lcd.print((int)tempKoncowa);
  lcd.print("C");

  // odczyt natężenia świtała:
  int odczytRezyst = analogRead(A5);
  int NatSwiatla = map(odczytRezyst, 0, 1023, 0, 100); // pokazanie wartości w %

  // wyświetl nateżenie swiatła:
  lcd.setCursor(8, 1);
  lcd.print(" SW:");
  lcd.print(NatSwiatla);
  lcd.print("%");

    // Sterowanie jasnością światła w zależności od natężenia światła: (nie można dawać zera), 1,7[V] = zaczyna świecić, 3[V] = maksymalnie
  if (NatSwiatla >= 50) {
    analogWrite(9, 80);
  } else if (NatSwiatla <= 49 && NatSwiatla >= 40) {
    analogWrite(9, 100);
  }else if (NatSwiatla <= 39 && NatSwiatla >= 30) {
    analogWrite(9, 120);
  } else if (NatSwiatla <= 29 && NatSwiatla >= 20) {
    analogWrite(9, 130);
  } else if (NatSwiatla <= 19 && NatSwiatla >= 10) {
    analogWrite(9, 140);
  } else if (NatSwiatla <= 9 && NatSwiatla >= 0) {
    analogWrite(9, 160);
  }

  //odczyt wilgotności gleby:
  int wilGleb = analogRead(A4);
  int wilGlebProc = map(wilGleb, 0, 1023, 0, 100); // pokazanie wartości w %
  int wilGlebProcPopr = 100 - wilGlebProc; // odwrócenie wartości
  
  //wyświetl wilgotnosc gleby:
  lcd.setCursor(0,0);
  lcd.print("W: ");
  lcd.print(wilGlebProcPopr);
  lcd.print("% ");

  lcd.setCursor(7, 0);
  lcd.print("");
  
  if (wilGlebProcPopr >= 76)
  {
    lcd.print("Przelana ");
  } else if (wilGlebProcPopr <= 75 && wilGlebProcPopr >= 40)
  {
    lcd.print("Podlana");
  } else if (wilGlebProcPopr <= 50)
  {
    lcd.print("Podlej ");
  }
  // opóźnienie
  delay(3000);
  }

// Funkcja PWM:
void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if (pin == 9 || pin == 10) {
    switch (divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    TCCR1B = TCCR1B & 0b11111000 | mode;
  }
}
