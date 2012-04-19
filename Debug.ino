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
  Serial.println("The following commands are valid:");
  delay(250);
  Serial.println("a) Show a few lines of altimeter output.");
  delay(250);
  Serial.println("b) Toggles the buzzer.");
  delay(250);
  Serial.println("e) Tests EEPROM r/w functionality. WARNING: Will erase data.");
  delay(250);
  Serial.println("g) Show some GPS output.");
  delay(250);
  Serial.println("r) Retrieves EEPROM data and prints it into the terminal for PFR Retrieval.");
  delay(250);
  Serial.println("s) Toggles the servo between the two positions");
  delay(250);
  Serial.println("x) Exits debug mode.");
}

boolean debug() {
  if(Serial.available()) {
    char c = Serial.read();
    
    if(!debugEnabled && c == 'd') {
      Serial.println("Debugging mode enabled.");
      Serial.println("Type \"x\" to leave debug mode.");
      showHelp();
      debugEnabled = true;
      return debugEnabled;
    }
    else if(debugEnabled && c == 'x') {
      Serial.println("Debugging mode disabled.");
      debugEnabled = false;
      delay(2000);
      return debugEnabled;
    }
    
    // If debug is not enabled, just return and carry on
    // with what we were doing.
    if(!debugEnabled)
      return debugEnabled;
    
    if(c == 'a') {
      Serial.println("Here are a few readings of the barometer:");
      for(int x = 0; x < 5; x++) {
        //printBarometerReading();
        delay(20);
      }
    }
    else if(c == 'b') {
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
    else if(c == 's') {
      Serial.println("Testing servo.");
      testServo();
    }
    else {
      Serial.print("Unrecognized character: ");
      Serial.println(c);
    }
  }
  
  return debugEnabled;
}

void testBuzzer() {
  if(buzzerOn) {
    turnBuzzerOff();
    Serial.println("Buzzer has been turned off.");
  }
  else {
    turnBuzzerOn();
    Serial.println("Buzzer has been turned on.");
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
  Serial.println("Testing Eeprom. You should see the phrase 'EEPROM Test successful.'");
}
