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
  
  // Need to add a delay as random writes are way too slow on this EEPROM.
  delay(5);
}

// WARNING: address is a page address, 6-bit end will wrap around
// also, data can be maximum of about 30 bytes, because the Wire library has a buffer of 32 bytes
void i2c_eeprom_write_page( int deviceaddress, unsigned int eeaddresspage, byte* data, byte length ) {
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddresspage >> 8)); // MSB
  Wire.write((int)(eeaddresspage & 0xFF)); // LSB
  byte c;
  for ( c = 0; c < length; c++) {
    Wire.write(data[c]);
  }
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
  /*char somedata[] = "this is data from the eeprom"; // data to write
  i2c_eeprom_write_page(0x50, 0, (byte *)somedata, sizeof(somedata)); // write to EEPROM 

  delay(10); //add a small delay*/
}

// Logs the current telemetry packet to the EEPROM.
// Keeps track of the current address
void logPacket() {
  unsigned long loggingTime = millis();
  Serial.println("Logging Packet to EEPROM");
  
  for(int x = 0; x < strlen(packetBuffer); x++) {
    i2c_eeprom_write_byte( 0x50, currentEEAddress, (byte) packetBuffer[x]);
    currentEEAddress++;
  }
  
  // Write a NULL at the end so that we know when the dump is finished.
  i2c_eeprom_write_byte( 0x50, currentEEAddress, (byte) 0x00);
  
  Serial.print("Logging Done");
  Serial.println(millis() - loggingTime);
}

// Test method for logging packets using page writes..
// Using the byte write method is almost certainly going to be too slow for our purposes
// The function is currently broken and should not be used.
void logPacket2() {
  unsigned long loggingTime = millis();
  
  byte offset = 0;
  while(offset < strlen(packetBuffer)) {
    byte len = strlen(packetBuffer) - offset > 30 ? 30 : strlen(packetBuffer) - offset;
    
    i2c_eeprom_write_page(0x50, currentEEAddress, (byte*)(packetBuffer + offset), len);
    
    offset += len;
    currentEEAddress += len;
    
    Serial.print("Len: ");
    Serial.println(len);
    Serial.print("Offset: ");
    Serial.println(offset);
    Serial.print("EEADDR: ");
    Serial.println(currentEEAddress);
    delay(25);
  }
  
  // Write a NULL at the end so that we know when the dump is finished.
  i2c_eeprom_write_byte( 0x50, currentEEAddress, (byte) 0x00);
  
  Serial.print("Logging Done");
  Serial.println(millis() - loggingTime);
}

void dumpEeprom() {
  Serial.println("Eeprom Dump:");
  
  unsigned int addr = 0; //first address
  byte b = i2c_eeprom_read_byte(0x50, 0); // access the first address from the memory

  while (b!=0) 
  {
    Serial.print((char)b); //print content to serial port
    addr++; //increase address
    b = i2c_eeprom_read_byte(0x50, addr); //access an address from the memory
  }
  Serial.println("\nDump Done");
}

void testEeprom() {
  Serial.println("Testing Eeprom");
  
  //char testString[] = "Test Successful.";
  //i2c_eeprom_write_page(0x50, 0, (byte*)testString, sizeof(testString));
  
  i2c_eeprom_write_byte(0x50, 0, (byte)'a');
  i2c_eeprom_write_byte(0x50, 1, (byte)'b');
  i2c_eeprom_write_byte(0x50, 2, (byte)'c');
  i2c_eeprom_write_byte(0x50, 3, (byte)'d');
  i2c_eeprom_write_byte(0x50, 4, (byte)'e');
  i2c_eeprom_write_byte(0x50, 5, (byte)'f');
  i2c_eeprom_write_byte(0x50, 6, (byte)'g');
  i2c_eeprom_write_byte(0x50, 7, (byte)'h');
  i2c_eeprom_write_byte(0x50, 8, (byte)0x00);
  
  dumpEeprom();
}
