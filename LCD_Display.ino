void init_lcd(){
  lcd.begin(16, 2);
  // lcd blink 3 times
  for(int i = 0; i < 3; i++) {
    lcd.backlight(); 
    delay(250);
    lcd.noBacklight(); 
    delay(250);
  }
  //open and close backlight for 3 times
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Booting...");
  lcd.blink();
  delay(1000);
}
void eraseLine(int l){
  lcd.setCursor(0,l);
  for(int i=0;i<16;i++){
    lcd.print(" ");
  }
  lcd.setCursor(0,l);
}

