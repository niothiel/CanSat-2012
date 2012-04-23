/* 
  *  Use the I2C bus with EEPROM 24LC64 
  *  Sketch:    eeprom.pde
  *  
  *  Author: hkhijhe
  *  Date: 01/10/2010
  * 
  *   
  */
unsigned int currentEEAddress = 0;

void i2c_eeprom_write_byte( int deviceaddress, unsigned int eeaddress, byte data ) {
  int rdata = data;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8)); // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(rdata);
  Wire.endTransmission();
}

// WARNING: address is a page address, 6-bit end will wrap around
// also, data can be maximum of about 30 bytes, because the Wire library has a buffer of 32 bytes
void i2c_eeprom_write_page( int deviceaddress, unsigned int eeaddresspage, byte* data, byte length ) {
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddresspage >> 8)); // MSB
  Wire.write((int)(eeaddresspage & 0xFF)); // LSB
  byte c;
  for ( c = 0; c < length; c++)
    Wire.write(data[c]);
  Wire.endTransmission();
}

byte i2c_eeprom_read_byte( int deviceaddress, unsigned int eeaddress ) {
  byte rdata = 0xFF;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8)); // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(deviceaddress,1);
  if (Wire.available()) rdata = Wire.read();
  return rdata;
}

// Note: don't read more than 30 or 32 bytes at a time! The EEPROM doesn't allow for
// reading past one page at a time.
void i2c_eeprom_read_buffer( int deviceaddress, unsigned int eeaddress, byte *buffer, int length ) {
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8)); // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(deviceaddress,length);
  int c = 0;
  for ( c = 0; c < length; c++ )
    if (Wire.available()) buffer[c] = Wire.read();
}

void initEeprom() 
{
  char somedata[] = "this is data from the eeprom"; // data to write
  i2c_eeprom_write_page(0x50, 0, (byte *)somedata, sizeof(somedata)); // write to EEPROM 

  delay(10); //add a small delay

  Serial.println("Memory written");
}

// Logs the current telemetry packet to the EEPROM.
// Keeps track of the current address
void logPacket() {
  return;
  Serial.println("Logging packet to EEPROM...");
  
  for(int x = 0; x < strlen(packetBuffer); x++) {
    Serial.print("Data: ");
    Serial.print( (char)packetBuffer[x]);
    Serial.print("    Addr: ");
    Serial.println(currentEEAddress);
    
//    i2c_eeprom_write_byte( 0x50, currentEEAddress, (byte) packetBuffer[x]);
//    delay(1);

    currentEEAddress++;
  }
  
  Serial.println("Logging finished...");
}

void readEeprom() 
{
  int addr=0; //first address
  byte b = i2c_eeprom_read_byte(0x50, 0); // access the first address from the memory

  while (b!=0) 
  {
    Serial.print((char)b); //print content to serial port
    addr++; //increase address
    b = i2c_eeprom_read_byte(0x50, addr); //access an address from the memory
  }
  Serial.println(" ");
  delay(2000);
}
