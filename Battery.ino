#define ANALOG_BATTERY_PIN 1

void initBattery() {
  // Maybe we should set the VRef for external here?
  // We might get a better resolution if we do.
  //analogReference(EXTERNAL);
}

// Read the voltage, assuming internal reference of 3.3v
// Currently the equation is [AnalogIn] * 3.3 / 1024 * 100
// I did it this way to avoid floating point.
void readBatteryVoltage() {
  voltage = (long)analogRead(ANALOG_BATTERY_PIN) * 330 / 1024;
}

void printBatteryVoltage() {
  Serial.print("Battery at ");
  float fVoltage = (float)voltage / 100;
  Serial.print(fVoltage);
  Serial.print(" V");
  
  Serial.println();
}
