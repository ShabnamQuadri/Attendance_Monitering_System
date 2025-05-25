#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
#define BUZZER_PIN 8

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Student Data
struct Student {
    String cardID;
    String rollNo;
    String name;
    bool isPresent;  // Track current status
};

Student students[] = {
    {"43 60 B8 27", "ECU-01 ", "Shabnam", false},
    {"62 FA 13 51", "ECU-02 ","Bushra", false},
    {"A3 1A 64 29","ECU-03 ", "Umar", false},
    {"93 AD BD 27", "ECU-04 ","Shaher", false},
    {"13 12 C7 27", "ECU-05 ","Aizel", false}
};

void setup() {
    Serial.begin(9600);
    Serial.println("Time,Card ID, Roll no,Name,Status"); // CSV headers

    SPI.begin();
    rfid.PCD_Init();
    lcd.begin(16, 2);
    lcd.backlight();
    pinMode(BUZZER_PIN, OUTPUT);

    showWelcomeMessage();
}

void loop() {
    if (!rfid.PICC_IsNewCardPresent()) return;
    if (!rfid.PICC_ReadCardSerial()) return;

    String cardID = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
        cardID += String(rfid.uid.uidByte[i], HEX);
        if (i < rfid.uid.size - 1) cardID += " ";
    }
    cardID.toUpperCase();

    bool found = false;
    for (int i = 0; i < sizeof(students) / sizeof(students[0]); i++) {
        if (cardID == students[i].cardID) {
            found = true;

            // Toggle presence state
            students[i].isPresent = !students[i].isPresent;
            String status = students[i].isPresent ? "Entered" : "Exited";

            tone(BUZZER_PIN, 1000, 200);
            delay(200);
            noTone(BUZZER_PIN);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Name: " + students[i].name);
            lcd.setCursor(0, 1);
            lcd.print("Status: " + status);

            Serial.print(getCurrentTime());
            Serial.print(",");
            Serial.print(cardID);
            Serial.print(",");
            Serial.print(students[i].name);
            Serial.print(",");
            Serial.println(status);

            delay(3000);
            break;
        }
    }

    if (!found) {
        tone(BUZZER_PIN, 3000, 1000);
        delay(1000);
        noTone(BUZZER_PIN);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Unknown Card");

        Serial.print(getCurrentTime());
        Serial.print(",");
        Serial.print(cardID);
        Serial.print(",");
        Serial.print("Unknown");
        Serial.print(",");
        Serial.println("Unauthorized");

        delay(2000);
    }

    showWelcomeMessage();
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
}

void showWelcomeMessage() {
    lcd.clear();
    lcd.init();
    lcd.setCursor(4, 0);
    lcd.print("Welcome");
    delay(500);
    lcd.clear();
    lcd.init();
    lcd.setCursor(0, 0);
    lcd.print("Scan your ID");
}

String getCurrentTime() {
    unsigned long ms = millis() / 1000;
    int h = (ms / 3600) % 24;
    int m = (ms / 60) % 60;
    int s = ms % 60;

    char buf[9];
    sprintf(buf, "%02d:%02d:%02d", h, m, s);
    return String(buf);
}
