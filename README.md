# 📚 RFID Attendance System using Arduino UNO

## 🎯 Project Overview
This is an **automated attendance system** developed using an Arduino UNO, an RFID reader, an OLED display, and a buzzer. It allows students to scan RFID cards to mark their attendance, displaying relevant details and providing audio feedback for status confirmation.

## 🛠️ How It Works
- The RFID Reader (MFRC522) detects and reads the unique ID (UID) of an RFID tag/card.
- The system compares the UID against a list of registered users stored in the code.
- If the UID is recognized:
  - The **OLED Display (SSD1306)** shows the student’s name, their ID, and the status **“Present”**.
  - A **short beep** sounds from the buzzer for confirmation.
- If the UID is **not recognized**:
  - The OLED displays **"Unknown Card"** and the UID.
  - A **longer beep** indicates an invalid/unregistered card.

## 💡 Features
- Contactless attendance via RFID
- Real-time feedback on OLED display
- Audio feedback via buzzer
- Display includes:
  - Student ID
  - Student Name
  - Status: Present / Unknown
- Easily extendable for real-time clock integration, SD card logging, or database support

## 🧰 Components Used
| Component              | Description                      |
|------------------------|----------------------------------|
| Arduino UNO            | Main microcontroller             |
| MFRC522 RFID Reader    | For reading RFID card/tag UID    |
| SSD1306 OLED Display   | Displays student details         |
| 5V Buzzer              | For feedback (valid/invalid UID) |
| RFID Tags/Cards        | Each with unique UID             |
| Jumper Wires, Breadboard | For connections                |

## 🔌 Wiring Overview
### RFID MFRC522 to Arduino UNO:
| MFRC522 Pin | Arduino UNO Pin |
|-------------|------------------|
| SDA         | 10               |
| SCK         | 13               |
| MOSI        | 11               |
| MISO        | 12               |
| GND         | GND              |
| RST         | 9                |
| 3.3V        | 3.3V             |

### OLED SSD1306 (I2C) to Arduino UNO:
| OLED Pin | Arduino UNO Pin |
|----------|-----------------|
| VCC      | 5V               |
| GND      | GND              |
| SDA      | A4               |
| SCL      | A5               |

### Buzzer:
| Buzzer Pin | Arduino UNO Pin |
|------------|------------------|
| + (VCC)    | D8 (example)     |
| - (GND)    | GND              |

 
