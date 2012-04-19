#define GPS_TX 2
#define GPS_RX 3
TinyGPS gps;
SoftwareSerial gpsSerial(2, 3);

void initGPS() {
  gpsSerial.begin(9600);
}

void readGPS() {
  while (gpsSerial.available()) {
    char c = (char)gpsSerial.read();
    Serial.print(c);
    if(gps.encode(c))
    {
      gps.get_position(&latitude, &longitude, &fix_age);
      gps.get_datetime(&date, &time, &time_age);
      altitudeGps = gps.altitude();
      satellites = gps.satellites();      
      
      Serial.print("Longitude: ");
      Serial.println(longitude);
      Serial.print("Latitude: ");
      Serial.println(latitude);
      Serial.print("Satellites: ");
      Serial.println(satellites);
      Serial.print("Altitude: ");
      Serial.println(altitudeGps);
      
      Serial.print("Date: ");
      Serial.println(date);
      Serial.print("Time: ");
      Serial.println(time);
    }
  }
}
