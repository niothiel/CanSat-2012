boolean debugEnabled = false;

boolean buzzerOn = false;
boolean servoPos = false;

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
  delay(250);
  Serial.println("a) Altimeter");
  delay(250);
  Serial.println("b) Buzzer");
  delay(250);
  Serial.println("e) EEPROM");
  delay(250);
  Serial.println("g) GPS");
  delay(250);
  Serial.println("r) Retrieve EEPROM data");
  delay(250);
  Serial.println("s) Servo");
  delay(250);
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
      delay(2000);
      return debugEnabled;
    }
    
    // If debug is not enabled, just return and carry on
    // with what we were doing.
    if(!debugEnabled)
      return debugEnabled;
    
    if(c == 'a') {
      Serial.println("Barometer:");
      for(int x = 0; x < 5; x++) {
        //printBarometerReading();
        delay(20);
      }
    }
    else if(c == 'b') {
      //testsomething();
      testBuzzer();
    }
    else if(c == 'e') {
      Serial.println("Testing eeprom.");
      testEeprom();
    }
    else if(c == 'g') {
      testGps();
    }
    else if(c == 'h') {
      showHelp();
    }
    else if(c == 'r') {
      dumpEeprom();
      Serial.println("Dumping eeprom.");
    }
    else if(c == 'z') {
      Serial.println("Testing servo.");
      testsomething();
      Serial.println("Testing servo. after..");
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
  if(servoPos) {
    servoPos1();
    Serial.println("Servo in position 1");
  }
  else {
    servoPos2();
    Serial.println("Servo in position 2");
  }
  servoPos = !servoPos;
}

void testGps() {
  Serial.println("Here's the last known GPS data.");
  printGPSData();
}

void dumpEeprom() {
  Serial.println("Dumping Eeprom values:");
}

void testEeprom() {
  Serial.println("Testing Eeprom");
}
