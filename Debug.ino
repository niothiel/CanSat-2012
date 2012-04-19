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
        Serial.println("Debugging mode enabled.");
        showHelp();
        debugEnabled = true;
        break;
      case 'x':
        Serial.println("Debugging mode disabled.");
        debugEnabled = false;
        delay(2000);
        break;
      case 'a':
        Serial.println("Here are a few readings of the barometer:");
        for(int x = 0; x < 5; x++) {
          printBarometerReading();
          delay(20);
        }
        break;
      case 'b':
        testBuzzer();
        break;
      case 'g':
        testGps();
        break;
      case 's':
        testServo();
      default:
        Serial.print("Unrecognized character: ");
        Serial.println(c);
    }
  }
  
  return debugEnabled;
}

void showHelp() {
  Serial.println("The following commands are valid:");
  Serial.println("a             - Show a few lines of altimeter output.");
  Serial.println("b             - Toggles the buzzer.");
  Serial.println("g             - Show some GPS output.");
  Serial.println("s             - Toggles the servo between the two positions");
  Serial.println("x             - Exits debug mode.");
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
