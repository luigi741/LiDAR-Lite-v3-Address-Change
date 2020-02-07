#include <Wire.h>

// LiDAR address definitions
#define LIDAR_ADDRESS 0x62
#define LIDAR_SERIAL  0x96
#define LIDAR_ID_HIGH 0x16
#define LIDAR_ID_LOW  0x17
#define I2C_ID_HIGH 0x18
#define I2C_ID_LOW 0x19
#define I2C_CONFIG 0x1E
#define I2C_SEC_ADDRESS 0x1A
#define NEW_I2C 0x70

// Global variables
int highSerialNumber = 0;
int lowSerialNumber  = 0;

void setup() {
    Wire.begin();
    Serial.begin(9600);

    scanDeviceI2C();
    
    highSerialNumber = serialNumberHigh();
    lowSerialNumber = serialNumberLow();
    
    Serial.print("Serial No.: ");
    Serial.print(highSerialNumber, HEX);
    Serial.println(lowSerialNumber, HEX);
    
    writeSerialNumber();
    writeNewAddress();
    disableLidarDefault();
}

void loop() {
    Serial.print("Serial No.: ");
    Serial.print(highSerialNumber, HEX);
    Serial.println(lowSerialNumber, HEX);
    
    scanDeviceI2C();
    delay(1000);
}

int serialNumberHigh() {
    // Get Serial No. HIGH byte
    Wire.beginTransmission((int) LIDAR_ADDRESS);
    Wire.write((int) LIDAR_ID_HIGH);
    Wire.endTransmission();
    Wire.requestFrom((int) LIDAR_ADDRESS, 1);
    while (Wire.available() == 0);
    int highResponse = Wire.read();
    return highResponse;
}

int serialNumberLow() {
    // Get Serial No. LOW byte
    Wire.beginTransmission((int) LIDAR_ADDRESS);
    Wire.write((int) LIDAR_ID_LOW);
    Wire.endTransmission();
    Wire.requestFrom((int) LIDAR_ADDRESS, 1);
    while (Wire.available() == 0);
    int lowResponse = Wire.read();
    return lowResponse;
}

void writeSerialNumber() {
    // Write Serial No. HIGH byte to 0x18
    Wire.beginTransmission((int) LIDAR_ADDRESS);
    Wire.write((int) I2C_ID_HIGH);
    Wire.write(highSerialNumber);
    Wire.endTransmission();
    delay(10);
    
    // Write Serial No. LOW  byte to 0x19
    Wire.beginTransmission((int) LIDAR_ADDRESS);
    Wire.write((int) I2C_ID_LOW);
    Wire.write(lowSerialNumber);
    Wire.endTransmission();
    delay(10);
}

void writeNewAddress() {
    // Write the new I2C address for the device to 0x1A
    // Use 0x7- and higher for new addresses
    Wire.beginTransmission((int) LIDAR_ADDRESS);
    Wire.write((int) I2C_SEC_ADDRESS);
    Wire.write((int) NEW_I2C);
    Wire.endTransmission();
    delay(10);
}

void disableLidarDefault() {
    // Disable the default LiDAR address (0x62)
    Wire.beginTransmission((int) LIDAR_ADDRESS);
    Wire.write((int) I2C_CONFIG);
    Wire.write((int) 0x08);
    Wire.endTransmission();
    delay(10);
}

void scanDeviceI2C() {
    Serial.println("Scanning for I2C Devices...");
    byte count = 0;
    for (byte i = 0; i < 120; i++) {
        Wire.beginTransmission(i);
        if (Wire.endTransmission() == 0) {
            Serial.print ("Found address: ");
            Serial.print (i, DEC);
            Serial.print (" (0x");
            Serial.print (i, HEX);
            Serial.println (")");
            count++;
            delay(1);
        }
    }
    Serial.println("Done.");
    Serial.print("Found ");
    Serial.print(count, DEC);
    Serial.println(" device(s).\n");
}
