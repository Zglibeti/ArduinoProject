#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial bluetooth(10, 11);  // RX, TX pins for Bluetooth communication
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address, number of columns, number of rows for LCD

int diodePins[] = {22, 24, 26, 28, 30, 34, 36, 38, 40, 42, 32, 44, 9, 18};  // Pins for diodes and RGB strips

void setup() {
  for (int i = 0; i < 14; i++) {
    pinMode(diodePins[i], OUTPUT);
  }
  
  lcd.begin(16, 2);
  
  bluetooth.begin(9600);
}

void loop() {
  if (bluetooth.available()) {
    int command = bluetooth.parseInt();

    // Check if a diode control command is received
    if (command >= 1 && command <= 12) {
      int diodeIndex = command - 1;
      toggleDiode(diodeIndex);
    }

    // Check if RGB strip 1 control command is received
    else if (command == 13) {
      int stripIndex = 12; // RGB strip number 1
      toggleDiode(stripIndex);
    }

    // Check if RGB strip 2 control command is received
    else if (command == 14) {
      int stripIndex = 13; // RGB strip number 2
      toggleDiode(stripIndex);
    }

    // Check if an LCD text command is received
    else if (command == 15) {
      displayText();
    }
  }
}

void toggleDiode(int index) {
  digitalWrite(diodePins[index], !digitalRead(diodePins[index]));
}

void displayText() {
  lcd.clear();

  String text = bluetooth.readString();
  lcd.print(text);
}
