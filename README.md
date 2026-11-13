# Smart Home Prototype

This was the final project for my high school Computer Engineering Technology course. It brings together the semester's work in circuit design, programming, troubleshooting and documentation. I built it during the last month of the semester, wrote weekly progress reports, and presented it in a final demonstration.

The house runs on **two Arduino boards**: one controls the main house and one controls the front door.

## Features

**Main house** ([src/smart_home/smart_home.ino](src/smart_home/smart_home.ino))
- **Climate control:** a thermistor reads the temperature and turns on a fan when it gets too hot.
- **Automatic garage door:** an ultrasonic sensor detects a car within about 1 m and a servo opens the door.
- **Motion-activated lights:** PIR sensors in two rooms turn on LEDs, but only when it is dark (checked with a photoresistor).
- **Flood detection:** a water-level sensor reports excess water.
- **LCD display:** a 16×2 I²C LCD shows the date and time from a DS3231 real-time clock, and switches to the temperature (°C/°F) every 5 seconds.
- **Serial monitor:** prints all sensor readings for debugging.

**Front door** ([src/door_circuit/door_circuit.ino](src/door_circuit/door_circuit.ino))
- **RFID lock:** scanning a registered tag on the MFRC522 reader unlocks the door with a servo and lights a status LED.
- **Doorbell:** pressing a button plays a melody on a piezo buzzer.

## Hardware

| Component | Purpose |
|---|---|
| Arduino Uno ×2 | Main house controller and door controller |
| Thermistor + DC fan | Temperature sensing and cooling |
| HC-SR04 ultrasonic sensor + servo | Garage door |
| PIR motion sensors ×2 + LEDs | Room lighting |
| Photoresistor | Ambient light detection |
| Water-level sensor | Flood detection |
| DS3231 RTC module | Date and time |
| 16×2 I²C LCD (0x27) | Display |
| MFRC522 RFID reader + tag | Door access |
| Servo, push button, piezo buzzer, LED | Door lock and doorbell |

## Pinout

| Main house | Pin | | Door | Pin |
|---|---|---|---|---|
| Thermistor | A0 | | Doorbell button | 6 |
| Photoresistor | A1 | | Buzzer | 5 |
| Water sensor | A2 | | RFID status LED | 7 |
| Fan | 5 | | Door servo | 4 |
| Ultrasonic trig / echo | 13 / 12 | | RFID SS (SPI) | 10 |
| Garage servo | 10 | | | |
| PIR A / PIR B | 7 / 6 | | | |
| Motion LED B | 8 | | | |
| LCD + RTC | I²C (A4/A5) | | | |

## Software

- **Language:** C++ (Arduino)
- **IDE:** Arduino IDE
- **Libraries:** `Servo`, `Wire`, `DS3231`, `LCD_I2C`, `MFRC522v2` (installed through the Arduino Library Manager)

**To run it:** open each `.ino` file in the Arduino IDE, install the libraries, select **Arduino Uno**, and upload. For the door, put your own tag's UID in `accessUID[]` (you can read it from the Serial Monitor at 9600 baud).

## Circuit

The schematic and PCB layout were made in **KiCad** and are in [Hardware/mainHouse/](Hardware/mainHouse/). Open `mainHouse.kicad_pro` to view them.

## Repository Structure

```
├── src/
│   ├── smart_home/      # Main house sketch
│   └── door_circuit/    # RFID door + doorbell sketch
├── Hardware/mainHouse/  # KiCad schematic & PCB
└── Progress_Reports/    # Weekly progress reports (PDF)
```
