#define RADIO_SLEEP_PIN 6

SoftwareSerial radio(6,7);

/**
Telemetry format is as follows:
( Start Char
UTC Time form GPS
Altitude from GPS
Latitude from GPS
Latitude hemisphere
Longitude from GPS
Longitude hemisphere
Number of Sattelites tracked
Altitude from Barometer (meters)
Ambient temperature from Barometer (Celsius)
Battery Voltage
) End char
*/
void assembleTelemetryPacket() {
  // Clear out the buffer
  memset(packetBuffer, 0x00, sizeof(packetBuffer));
  
  sprintf(packetBuffer, "(%d,%lu,%lu,%ld,%ld,%ld,%hu,%ld,%ld,%hd,%ld)",
    packetNumber++,
    time,
    date,
    altitudeGps,
    latitude,
    longitude,
    satellites,
    pressure,
    altitudeBaro,
    temperature,
    voltage);
}

/*
void assembleTelemetryPacket2() {
  // Clear out the buffer
  memset(packetBuffer, 0x00, sizeof(packetBuffer));
  
  // Temp variable for number conversions
  char temp[10];
  
  // Clear out the buffer
  memset(packetBuffer, 0x00, sizeof(packetBuffer));
  
  strcat(packetBuffer, "(");
  
  // GPS Time
  memset(temp, 0x00, sizeof(temp));
  sprintf(temp, "%lu", time);
  strcat(packetBuffer, temp);
  
  strcat(packetBuffer, ",");
  
  // GPS Altitude
  memset(temp, 0x00, sizeof(temp));
  sprintf(temp, "%l", altitudeGps);
  strcat(packetBuffer, temp);
  
  strcat(packetBuffer, ",");
  // Not complete
}
*/

// TODO: Hookup radio sleep pins and make sure it works
// to save power.
void initRadio() {
  // Initialize Radio I/O
  radio.begin(9600);
  
  // Set sleep pin to output
  //pinMode(RADIO_SLEEP_PIN, OUTPUT);
}

void sendPacket() {
  // Wake the radio from sleep
  //digitalWrite(RADIO_SLEEP_PIN, LOW);
  delay(15);
  
  radio.print(packetBuffer);
  Serial.println(packetBuffer);
  /*for(int x = 0; x < sizeof(packetBuffer); x++) {
    radio.print(packetBuffer[x]);
    Serial.print(packetBuffer[x]);
    delay(2);
  }*/
  
  // Set the time that we last sent the packet
  lastTelemetryTransmission = millis();
  
  // Put the radio back to sleep
  //digitalWrite(RADIO_SLEEP_PIN, HIGH);
  delay(15);
}
