#include <LiquidCrystal.h>

// deklaracja portów LCD:
LiquidCrystal lcd (2, 3, 4, 5, 6, 7);

void setup() {
Serial.begin(9600);
// lcd start:
lcd.begin (16,2);
lcd.clear();
// czujniki:
pinMode(A5, INPUT); // fotorezystor
pinMode(A0, INPUT); // czujnik temperatury
pinMode(A4, INPUT);// wilgotnosci gleby
// piny do płytek:
pinMode(A1, OUTPUT);
}

void loop() {

  lcd.clear();

 // odczyt temperatury:
  int odczytTemp = analogRead(A0);
  float tempVoltage = odczytTemp * (5.0/1024.0);
  float tempKoncowa = tempVoltage * 100;

  // wyświetl temperature:
  lcd.setCursor(0,1);
  lcd.print("T: ");
  lcd.print(tempKoncowa);

  // odczyt natężenia świtała:
  int odczytRezyst = analogRead(A5);
  int NatSwiatla = map(odczytRezyst, 0, 1023, 0, 100); // pokazanie wartości w %

  // wyświetl nateżenie swiatła:
  lcd.setCursor(9, 1);
  lcd.print("S: ");
  lcd.print(NatSwiatla);
  lcd.print("%");

  //odczyt wilgotności gleby:
  int wartWil = analogRead(A4);
  int wilGleb = 1023 - wartWil;

  //wyświetl wilgotnosc gleby:
  lcd.setCursor(0,0);
  lcd.print("W: ");
  if (wilGleb > 550)
  {
    lcd.print("Podlana :)");
  } else if (wilGleb < 550)
  {
    lcd.print("Podlej mnie!");
  }

    // Sterowanie jasnością światła w zależności od natężenia światła:
  if (NatSwiatla <= 70 && NatSwiatla >= 50) {
    analogWrite(9, 102);
  } else if (NatSwiatla <= 49 && NatSwiatla >= 30) {
    analogWrite(9, 120);
  } else if (NatSwiatla <= 29 && NatSwiatla >= 20) {
    analogWrite(9, 140);
  } else if (NatSwiatla <= 19) {
    analogWrite(9, 160);
  }
// opóźnienie:
  delay(3000);
  }

