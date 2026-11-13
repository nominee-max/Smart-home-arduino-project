
#include <Wire.h>        
#include <Servo.h>       
// Libraries for RFID tag 
#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>


#define bellButtonPin 6
#define bellBuzzPin 5
#define rfidLedOutPin 7
#define servoDoorPin 4

// Notes
#define NOTE_C4 262
#define NOTE_G3 196
#define NOTE_A3 220
#define NOTE_B3 247

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

//instance
Servo entryDoorServo;
int angle2 = 0;  // Stores the angle value
// Registered valid tag address
byte accessUID[4] = {0x91, 0xDC, 0xC0, 0x26};  // <<<<<<<<<< tag address

// Configuring RFID reader
MFRC522DriverPinSimple ss_pin(10);   
MFRC522DriverSPI driver{ss_pin};     
MFRC522 mfrc522{driver};             
void setup() {
  // Initializing communication at 9600 baud
  Serial.begin(9600);
  Wire.begin();

  pinMode(bellButtonPin, INPUT_PULLUP);  // Button
  pinMode(bellBuzzPin, OUTPUT);          // Buzzer
  pinMode(rfidLedOutPin, OUTPUT);        // RFID status output

  entryDoorServo.attach(servoDoorPin);   // Attach the servo
  entryDoorServo.write(0);               // Start with the door closed

  mfrc522.PCD_Init();                    // Init MFRC522 board
  MFRC522Debug::PCD_DumpVersionToSerial(mfrc522, Serial);  // Show reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
  // Buzzer
  if (digitalRead(bellButtonPin) == LOW) {
    for (int thisNote = 0; thisNote < 8; thisNote++) {
      int noteDuration = 1000 / noteDurations[thisNote];

      if (melody[thisNote] != 0) {
        tone(bellBuzzPin, melody[thisNote], noteDuration);
      }

      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      noTone(bellBuzzPin);
    }
  }

  // scan and lock the door
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is called automatically.
  // Check the scanned tag address against the registered address above.
  if (mfrc522.uid.uidByte[0] == accessUID[0] &&
      mfrc522.uid.uidByte[1] == accessUID[1] &&
      mfrc522.uid.uidByte[2] == accessUID[2] &&
      mfrc522.uid.uidByte[3] == accessUID[3]) {

    Serial.println("access granted");
    digitalWrite(rfidLedOutPin, HIGH);      // Turn the green LED on
    Serial.println("main door unlocked");

    // Turn the servo from 0 to 180 degrees in steps of 1 degree
    for (angle2 = 0; angle2 <= 180; angle2 += 1) {
      entryDoorServo.write(angle2);
      delay(15);
    }
  }
  else {
    Serial.println("access denied");
    digitalWrite(rfidLedOutPin, LOW);       
  }

  delay(5000);                              
  digitalWrite(rfidLedOutPin, LOW);         
  mfrc522.PICC_HaltA();
}