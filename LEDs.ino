#ifdef COMMON_ANODE
#define LED_ON LOW
#define LED_OFF HIGH
#else
#define LED_ON HIGH
#define LED_OFF LOW
#endif

#define openTimeinMillis 3

void ledsetup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  normalModeOn();
}

/////////////////////////////////////////  Solid Led    ///////////////////////////////////
void blueSolid () {
  digitalWrite(blueLed, LED_ON);   // Blue LED ON and ready to read card
  digitalWrite(redLed, LED_OFF);  // Make sure Red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure Green LED is off
}

void greenSolid () {
  digitalWrite(blueLed, LED_OFF);   // Turn off blue LED
  digitalWrite(redLed, LED_OFF);  // Turn off red LED
  digitalWrite(greenLed, LED_ON);   // Turn on green LED
}

void redSolid () {
  digitalWrite(blueLed, LED_OFF);   // Turn off blue LED
  digitalWrite(redLed, LED_ON);  // Turn on red LED
  digitalWrite(greenLed, LED_OFF);   // Turn off green LED
}

/////////////////////////////////////////  Blink Led    ///////////////////////////////////
void redBlink() {
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  delay(200);
  digitalWrite(redLed, LED_ON);   // Make sure red LED is on
  delay(200);
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  delay(200);
  digitalWrite(redLed, LED_ON);   // Make sure red LED is on
  delay(200);
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  delay(200);
  digitalWrite(redLed, LED_ON);   // Make sure red LED is on
  delay(200);
}

void blueBlink() {
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  delay(200);
  digitalWrite(blueLed, LED_ON);  // Make sure blue LED is on
  delay(200);
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  delay(200);
  digitalWrite(blueLed, LED_ON);  // Make sure blue LED is on
  delay(200);
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  delay(200);
  digitalWrite(blueLed, LED_ON);  // Make sure blue LED is on
  delay(200);
}

void greenBlink() {
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is on
  delay(200);
  digitalWrite(greenLed, LED_ON);   // Make sure green LED is on
  delay(200);
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  delay(200);
  digitalWrite(greenLed, LED_ON);   // Make sure green LED is on
  delay(200);
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  delay(200);
  digitalWrite(greenLed, LED_ON);   // Make sure green LED is on
  delay(200);
}


/////////////////////////////////////////  Action    ///////////////////////////////////
void granted () {
  tone(buzzer, NOTE_E7, 500);
  digitalWrite(blueLed, LED_OFF);   // Turn off blue LED
  digitalWrite(redLed, LED_OFF);  // Turn off red LED
  digitalWrite(greenLed, LED_ON);   // Turn on green LED
  digitalWrite(relay, LOW);
  delay(openTimeinMillis * 1000);
}

void denied() {
  tone(buzzer, 523, 200);
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  delay(200);
  noTone(buzzer);
  digitalWrite(redLed, LED_ON);   // Make sure red LED is on
  delay(200);
  tone(buzzer, 523, 200);
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  delay(200);
  noTone(buzzer);
  digitalWrite(redLed, LED_ON);   // Make sure red LED is on
  delay(200);
  tone(buzzer, 523, 200);
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  delay(200);
  noTone(buzzer);
  tone(buzzer, 523, 1000);
  digitalWrite(redLed, LED_ON);   // Make sure red LED is on
  delay(1000);
}

void cycleLeds() {
  tone(buzzer, NOTE_E7, 200);
  digitalWrite(redLed, LED_OFF);   // Make sure red LED is off
  digitalWrite(greenLed, LED_ON);   // Make sure green LED is on
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  delay(200);
  noTone(buzzer);
  tone(buzzer, NOTE_E7, 200);
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  digitalWrite(blueLed, LED_ON);  // Make sure blue LED is on
  delay(200);
  digitalWrite(redLed, LED_ON);   // Make sure red LED is on
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  delay(200);
  digitalWrite(redLed, LED_OFF);   // Make sure red LED is off
  digitalWrite(greenLed, LED_ON);   // Make sure green LED is on
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  delay(200);
  tone(buzzer, NOTE_E7, 200);
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  digitalWrite(blueLed, LED_ON);  // Make sure blue LED is on
  delay(200);
  digitalWrite(redLed, LED_ON);   // Make sure red LED is on
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  delay(200);
}

void addCard() {
  tone(buzzer, NOTE_E7, 200);
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is on
  delay(200);
  noTone(buzzer);
  digitalWrite(greenLed, LED_ON);   // Make sure green LED is on
  delay(200);
  tone(buzzer, NOTE_E7, 200);
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  delay(200);
  noTone(buzzer);
  digitalWrite(greenLed, LED_ON);   // Make sure green LED is on
  delay(200);
  tone(buzzer, NOTE_E7, 200);
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  delay(200);
  digitalWrite(greenLed, LED_ON);   // Make sure green LED is on
  delay(200);
}

void deleteCard() {
  tone(8, NOTE_F7, 200);
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  delay(200);
  noTone(8);
  digitalWrite(blueLed, LED_ON);  // Make sure blue LED is on
  delay(200);
  tone(8, NOTE_F7, 200);
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  delay(200);
  noTone(8);
  digitalWrite(blueLed, LED_ON);  // Make sure blue LED is on
  delay(200);
  tone(8, NOTE_F7, 200);
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  delay(200);
  digitalWrite(blueLed, LED_ON);  // Make sure blue LED is on
  delay(200);
}

//////////////////////////////////////// Normal Mode Led  ///////////////////////////////////
void normalModeOn () {
  switch (errorId) {
    case 0:
      blueSolid();
      break;
    case 1:
      redBlink();
      break;
    default:
      blueSolid();
      break;
  }

  if (clientStatus != 0) {
    connectionError();
  }
  digitalWrite(relay, LOW);
  
  if(errorId == 0){
    eraseLine(0);
    lcd.print("Scan ID card...");
  }
  else{
    eraseLine(0);
    lcd.print("Error: ");
    lcd.print(errorId);
  }
  eraseLine(1);
}

//////////////////////////////////////// Special Led  ///////////////////////////////////

void connectionError() {
  digitalWrite(blueLed, LED_OFF);
  digitalWrite(redLed, LED_ON);
  digitalWrite(greenLed, LED_OFF);
  delay(200);
  digitalWrite(redLed, LED_OFF);
  digitalWrite(blueLed, LED_ON);
  delay(200);
}

void wifiError() {
  digitalWrite(blueLed, LED_OFF);
  digitalWrite(redLed, LED_ON);
  digitalWrite(greenLed, LED_OFF);
  delay(200);
  digitalWrite(redLed, LED_OFF);
  delay(200);
}

