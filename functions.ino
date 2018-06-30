void printMacAddress()
{
  // get your MAC address
  byte mac[6];
  WiFi.macAddress(mac);

  // print MAC address
  char buf[20];
  sprintf(buf, "%02X:%02X:%02X:%02X:%02X:%02X", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
  Serial.print("MAC address: ");
  Serial.println(buf);
}

int checkOpen(String uid) {
  String jsonData = "";
  jsonData += "{'doorId':";
  jsonData += doorId;
  jsonData += ",'uid':'";
  jsonData += uid;
  jsonData += "'};";

  Serial1.print("AT+CIPSENDEX=3,");
  Serial1.print(jsonData.length());
  Serial1.print("\r\n");
  delay(100);
  Serial1.print(jsonData);
  Serial1.print("\r\n");

  long timeOut = millis();
  int status = 0;
  while (millis() - timeOut < 5000) {
    if (Serial1.available()) {
      if (Serial1.read() == ':') {
        timeOut = millis();
        status = 1;
        break;
      }
    }
  }

  if (status == 0) {
    Serial.println("Time out");
    return -1;
  }

  String readin = "";
  status = 0;

  while (millis() - timeOut < 10000) {
    if (Serial1.available()) {
      char t = Serial1.read();
      //      Serial.print(t);
      if (t == ';') {
        Serial.println();
        timeOut = millis();
        status = 1;
        delay(100);
        break;
      }
      readin.concat(t);
      //      Serial.println(readin);
    }
  }

  if (status == 0) {
    Serial.println("Time out");
  }

  Serial.print(readin.length());
  Serial.print(">");
  Serial.println(readin);

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& user =  jsonBuffer.parseObject(readin);
  const char* name = user["name"];
  boolean open = user["open"];
  eraseLine(1);
  lcd.print(name);
  if (open) {
    return 0;
  }
  else {
    return 1;
  }
}



