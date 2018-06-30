#include <ArduinoJson.h>
#include "WiFiEsp.h"
#include <SPI.h>
#include <MFRC522.h>
#include "pitch.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//Leds
#define redLed 6
#define greenLed 7
#define blueLed 8
#define buzzer 5
#define relay 2

#define doorId 1
//Wifi

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(3, 4); // RX, TX
#endif

long connect_Timer = 0;
long ping_Timer = 0;
long check_Timer = 0;
char ssid[] = "LAPTOP-TU2C615M 3741";            // your network SSID (name)
char pass[] = "kennlaptop";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
char server[] = "192.168.137.1";
boolean conStatus = false;

WiFiEspClient client;
int clientStatus = 1;//0 connected, 1 disconnected
long reConnect_Timer = 0;

//MFRC522
#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;


//LCD_Display
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // set LCD I2C Address
int errorId = 0;// 0 = no error, 1,2 = wifi error

void setup() {
  //LCD_Display
  init_lcd();
  
  // initialize serial for debugging
  Serial.begin(9600);
  // initialize serial for ESP module
  Serial1.begin(115200);
  // initialize ESP module with 115200, and change to 9600
  Serial1.println("AT+CIOBAUD=9600\r\n");
  Serial1.begin(9600);
  WiFi.init(&Serial1);

  // check for the presence of the shield
  status = WiFi.status();
  if (status == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    errorId = 1;
  }
  else {
    // attempt to connect to WiFi network
    connect_Timer = millis();
    while ( status != WL_CONNECTED) {
      Serial.print("Attempting to connect to WPA SSID: ");
      Serial.println(ssid);
      // Connect to WPA/WPA2 network
      status = WiFi.begin(ssid, pass);
      if (millis() - connect_Timer > 10000) break;
    }
    status = WiFi.status();
    if (status == WL_CONNECTED) {
      Serial.println("You're connected to the network");
      // Print WiFi MAC address
      printMacAddress();
    }
    else {
      Serial.println("Can't connect to the network");
      errorId = 2;
    }
  }

  //MFRC522
  SPI.begin();
  rfid.PCD_Init();
  rfid.PCD_DumpVersionToSerial();
  byte v = rfid.PCD_ReadRegister(VersionReg);
  if((v == 0x00) || (v == 0xFF)){
    errorId = 3;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  switch (errorId) {
    case 0:
      tone(buzzer, NOTE_E7, 1000);
      lcd.print("System Ready.");
      break;
    case 1:
      tone(buzzer, 523, 3000);
      lcd.print("WL_NO_SHIELD!");
      break;
    case 2:
      tone(buzzer, 523, 3000);
      lcd.print("WL_NO_CONNECTED!");
      break;
    default:
      tone(buzzer, 523, 3000);
      lcd.print("Unknow Error!");
      break;
  }
  lcd.noBlink();
  ledsetup();
  delay(3000);
  if(errorId == 3){
    break;
  }
  clientStatus = connect_To_Server();
}

void loop() {
  if (check_Timer - millis() > 10000) {
    conStatus = client.connected();
    check_Timer = millis();
  }
  if ((!conStatus) && (millis() - reConnect_Timer) > 10000) {
    clientStatus = connect_To_Server();
    conStatus = client.connected();
    Serial.print("conStatus:");
    Serial.println(conStatus);
    check_Timer = millis();
  }

  normalModeOn();

  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;
  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));
  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    eraseLine(0);
    lcd.print("Tag not support.");
    tone(buzzer, NOTE_C7, 500);
    redBlink();
    return;
  }

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
      (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
      String(rfid.uid.uidByte[i], HEX) +
      (i != 3 ? ":" : "");
  }
  strID.toUpperCase();
  Serial.println(strID);
  eraseLine(1);
  lcd.print("Searching...");

  int checkStatus = checkOpen(strID);

  eraseLine(1);
  if (checkStatus == 0) {
    eraseLine(0);
    lcd.print("Access Granted");
    granted();
  }
  else if(checkStatus == -1){
    eraseLine(1);
    lcd.print("Time out!");
    tone(buzzer, NOTE_D5, 3000);
    delay(2000);
  }
  else{
    eraseLine(0);
    lcd.print("Access Denied");
    denied();
    delay(2000);
  }
}

int connect_To_Server() {
  Serial.println();
  Serial.println("Starting connection to server...");
  reConnect_Timer = millis();
  if (client.connect(server, 6083)) {
    Serial.println("Connected to server");
    return 0;
  }
  else {
    Serial.println("Can't connect to server");
    return 1;
  }
}

