boolean debugEnabled = false;

boolean buzzerOn = false;
boolean isServoOpen = false;

void setTestValues() {
   time = 6121501;
   date = 41812;
   altitudeGps = 120;
   latitude = -10;
   longitude = 12;
   satellites = 9;
   pressure = 101325;
   altitudeBaro = 125;
   temperature = 235;
   voltage = 621;
}

void showHelp() {
  Serial.println("Commands:");
  delay(100);
  Serial.println("a) Altimeter");
  delay(100);
  Serial.println("b) Buzzer");
  delay(100);
  Serial.println("e) EEPROM");
  delay(100);
  Serial.println("g) GPS");
  delay(100);
  Serial.println("p) Battery Voltage");
  delay(100);
  Serial.println("r) Retrieve EEPROM data");
  delay(100);
  Serial.println("s) Servo");
  delay(100);
  Serial.println("x) Exit");
}

boolean debug() {
  if(Serial.available()) {
    char c = Serial.read();
    
    if(!debugEnabled && c == 'd') {
      Serial.println("Debug enabled");
      showHelp();
      debugEnabled = true;
      return debugEnabled;
    }
    else if(debugEnabled && c == 'x') {
      Serial.println("Debug disabled");
      debugEnabled = false;
      delay(1000);
      return debugEnabled;
    }
    
    // If debug is not enabled, just return and carry on
    // with what we were doing.
    if(!debugEnabled)
      return debugEnabled;
    
    if(c == 'a') {
      Serial.println("Barometer:");
      for(int x = 0; x < 5; x++) {
        readBarometerBMP();
        printBarometerReading();
        delay(20);
      }
    }
    else if(c == 'b') {
      testBuzzer();
    }
    else if(c == 'e') {
      testEeprom();
    }
    else if(c == 'g') {
      printGPSData();
    }
    else if(c == 'h') {
      showHelp();
    }
    else if(c == 'p') {
      printBatteryVoltage();
    }
    else if(c == 'r') {
      dumpEeprom();
    }
    else if(c == 's') {
      testServo();
    }
    else {
      Serial.print("Unknown char: ");
      Serial.println(c);
    }
  }
  
  return debugEnabled;
}

void testBuzzer() {
  if(buzzerOn) {
    turnBuzzerOff();
    Serial.println("Buzzer off");
  }
  else {
    turnBuzzerOn();
    Serial.println("Buzzer on");
  }
    
  buzzerOn = !buzzerOn;
}

void testServo() {
 if(isServoOpen) {
    servoClose();
    Serial.println("Servo closed");
  }
  else {
    servoOpen();
    Serial.println("Servo open");
  }
  isServoOpen = !isServoOpen;
}
