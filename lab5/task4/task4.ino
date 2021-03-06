/*
  keyestudio super learning kit
  Project 25
  ADXL345
  http//www.keyestudio.com
*/

#include <Wire.h>

// Registers for ADXL345
// address for device is 8 bit but shift to the
// right by 1 bit to make it 7 bit because the
// wire library only takes in 7 bit addresses
#define ADXL345_ADDRESS (0xA6 >> 1)
#define ADXL345_REGISTER_XLSB (0x32)

int accelerometer_data[3];
int summedAccData[3];
int n = 1;  // Number averaged values
int averagingCounter;
int readingsCounter;
int printCounter;


// void because this only tells the cip to send data to its output register
// writes data to the slave's buffer
void i2c_write(int address, byte reg, byte data) {
  // Send output register address
  Wire.beginTransmission(address);
  // Connect to device
  Wire.write(reg);
  // Send data
  Wire.write(data); //low byte
  Wire.endTransmission();
}


// void because using pointers
// microcontroller reads data from the sensor's input register
void i2c_read(int address, byte reg, int count, byte* data) {
  // Used to read the number of data received
  int i = 0;
  // Send input register address
  Wire.beginTransmission(address);
  // Connect to device
  Wire.write(reg);
  Wire.endTransmission();

  // Connect to device
  Wire.beginTransmission(address);
  // Request data from slave
  // Count stands for number of bytes to request
  Wire.requestFrom(address, count);
  while (Wire.available()) // slave may send less than requested
  {
    char c = Wire.read(); // receive a byte as character
    data[i] = c;
    i++;
  }
  Wire.endTransmission();
}


void init_adxl345() {
  byte data = 0;

  i2c_write(ADXL345_ADDRESS, 0x31, 0x0B);   // 13-bit mode  +_ 16g
  i2c_write(ADXL345_ADDRESS, 0x2D, 0x08);   // Power register

  i2c_write(ADXL345_ADDRESS, 0x1E, 0x00);   // x
  i2c_write(ADXL345_ADDRESS, 0x1F, 0x00);   // Y
  i2c_write(ADXL345_ADDRESS, 0x20, 0x05);   // Z

  // Check to see if it worked!
  i2c_read(ADXL345_ADDRESS, 0X00, 1, &data);
  //  if (data == 0xE5)
  //    Serial.println("it work Success");
  //  else
  //    Serial.println("it work Fail");
}


void read_adxl345() {
  byte bytes[6];
  memset(bytes, 0, 6);

  // Read 6 bytes from the ADXL345
  i2c_read(ADXL345_ADDRESS, ADXL345_REGISTER_XLSB, 6, bytes);
  // Unpack data
  for (int i = 0; i < 3; ++i) {
    accelerometer_data[i] = (int)bytes[2 * i] + (((int)bytes[2 * i + 1]) << 8);
  }
}


void setup() {
  Wire.begin();
  Serial.begin(9600);

  for (int i = 0; i < 3; ++i) {
    accelerometer_data[i]  = 0;
  }

  init_adxl345();

  Serial.print("X");
  Serial.print("\t");
  Serial.print("Y");
  Serial.print("\t");
  Serial.println("Z");
}


void loop() {
  read_adxl345();
  sumAccData();
  averagingCounter++;
  //readingsCounter++;

  // Print 10k readings
  //  if (averagingCounter == n && readingsCounter < 10000) {
  //    //printSummedAccData();
  //    printAccData();
  //    resetVariables();
  //  }

  // Print 100 readings of each n
  if (averagingCounter == n && n < 102) {
    //printSummedAccData();
    printAccData();
    resetVariables();
    printCounter++;
  }

  if (printCounter == 99) {
    printCounter = 0;
    n += 25;
  }

  //delay(50 / n);
}


void sumAccData() {
  summedAccData[0] += accelerometer_data[0];
  summedAccData[1] += accelerometer_data[1];
  summedAccData[2] += accelerometer_data[2];
}


void printSummedAccData() {
  Serial.print(summedAccData[0]);
  Serial.print("\t");
  Serial.print(summedAccData[1]);
  Serial.print("\t");
  Serial.print(summedAccData[2]);
  Serial.print("\t");
}


void printAccData() {
  //Serial.print(readingsCounter);
  //Serial.print("\t");
  Serial.print(summedAccData[0] / averagingCounter);
  Serial.print("\t");
  Serial.print(summedAccData[1] / averagingCounter);
  Serial.print("\t");
  Serial.println(summedAccData[2] / averagingCounter);
}


void resetVariables() {
  averagingCounter = 0;
  summedAccData[0] = 0;
  summedAccData[1] = 0;
  summedAccData[2] = 0;
}
