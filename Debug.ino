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

boolean debug() {
  if(Serial.available()) {
    char c = Serial.read();
    
    switch(c) {
      case 'd':
        if(!debugEnabled) {
          Serial.println("Debugging mode enabled.");
          showHelp();
          debugEnabled = true;
        }
        break;
      case 'x':
        if(debugEnabled) {
          Serial.println("Debugging mode disabled.");
          debugEnabled = false;
          delay(2000);
        }
        break;
    }
    
    if(!debugEnabled)
      return debugEnabled;
    
    switch(c) {
      case 'a':
        Serial.println("Here are a few readings of the barometer:");
        for(int x = 0; x < 5; x++) {
          //printBarometerReading();
          delay(20);
        }
        break;
      case 'b':
        testBuzzer();
        break;
      case 'e':
        Serial.println("Testing eeprom.");
        testEeprom();
        break;
      case 'g':
        testGps();
        break;
      case 'r':
        Serial.println("Dumping eeprom.");
        dumpEeprom();
        break;
      case 's':
        Serial.println("Testing servo.");
        testServo();
        break;
      default:
        Serial.print("Unrecognized character: ");
        Serial.println(c);
    }
  }
  
  return debugEnabled;
}

void showHelp() {
  Serial.println("The following commands are valid:");
  delay(150);
  Serial.println("a - Show a few lines of altimeter output.");
  delay(150);
  Serial.println("b - Toggles the buzzer.");
  delay(150);
  Serial.println("e - Tests EEPROM r/w functionality. WARNING: Will erase data.");
  delay(150);
  Serial.println("g - Show some GPS output.");
  delay(150);
  Serial.println("r - Retrieves EEPROM data and prints it into the terminal for PFR Retrieval.");
  delay(150);
  Serial.println("s - Toggles the servo between the two positions");
  delay(150);
  Serial.println("x - Exits debug mode.");
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
  printGPSData();
}

void dumpEeprom() {
  Serial.println("Dumping Eeprom values:");
}

void testEeprom() {
  Serial.println("Testing Eeprom. You should see the phrase \"EEPROM Test successful.\"");
}
