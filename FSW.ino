#include <SPI.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

// Global sensor values

// Altimeter
short temperature;          // Temperature in 10th of a degree Celsius
long pressure;              // Pressure in Pa
long altitudeBaro;          // Altitude in centimeters

// GPS
long latitude;              // Latitude in hundred thousandths of a degree
long longitude;             // Longitude in hundred thousandths of a degree
long altitudeGps;           // Altitude in centimeters
unsigned short satellites;  // Number of satellites tracked
unsigned long fix_age;      // Age of fix in milliseconds
unsigned long date;         // Date as ddmmyy
unsigned long time;         // Time as hhmmsscc
unsigned long time_age;     // Age in milliseconds

// Battery Voltage
long voltage;               // Voltage in 100th of a Volt

// Radio Packet Buffer
int packetNumber = 0;
char packetBuffer[80];

// Flight control variables
boolean telemetryActive = true;
unsigned long lastTelemetryTransmission = 0;
#define TELEMETRY_INTERVAL 1900

void setup() {
  // Initialize Serial I/O
  Serial.begin(9600);
  
  // Initialize SPI Interface
  SPI.begin();
  
  // Initialize TWI Interface
  Wire.begin();
  
  // Initialize External Electronics
  //initBarometerBMP();
  //initGPS();
  //initEeprom();
  //initRadio();
  
  setTestValues();
}

void loop() {
  //readBarometerBMP();
  //readGPS();
  //readEeprom();
  
  // Radio in loopback
  //while(radio.available())
  //  Serial.write(radio.read());
  
  // Radio out loopback
  //while(Serial.available())
  //  radio.write(Serial.read());
  
  // Serial Loopback
  //while(Serial.available())
  //  Serial.write(Serial.read());
  
  // Send the telemetry packet
  // Checks if telemetry is enabled and if it's been long enough since the previous
  // packet was transmitted.
  if(telemetryActive && (millis() - lastTelemetryTransmission) > TELEMETRY_INTERVAL) {
    assembleTelemetryPacket();
    sendPacket();
  }
  
  delay(100);
}

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

/*
// Function to convert floats to ascii.
// Unused for now as we are going to try and avoid using floating point
void floatToAscii(float f, char* out) {
  memset(out, 0x00, sizeof(out));
  int temp = (f - (int)f) * 100;
  sprintf(out, "%0d.%d", (int)f, temp);
}
*/