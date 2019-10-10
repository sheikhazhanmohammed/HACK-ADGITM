#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   
#include <LiquidCrystal.h>
#include<Wire.h>
const int MPU6050_addr=0x68;
int16_t Temp;
//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
int myBPM;
int SmokeSensorValue;// Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
const int AOUTpin=2;//the AOUT pin of the alcohol sensor goes into analog pin A0 of the arduino
const int DOUTpin=8;//the DOUT pin of the alcohol sensor goes into digital pin D8 of the arduino
const int ledPin=13;//the anode of the LED connects to digital pin D13 of the arduino

int AlcoholLimit;
int AlcoholValue;
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"
 
#define rs 9 
#define en 8 
#define d4 7 
#define d5 6  
#define d6 5 
#define d7 4 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
void setup() {   
 
  Serial.begin(9600);          // For Serial Monitor
  ///////////////////////PULSE SENSOR START/////////////////////////////////////////////////
  pulseSensor.analogInput(A0);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   
  if (pulseSensor.begin()) {
    //Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
  ///////////////////////PULSE SENSOR END//////////////////////////////////////////////////
  //////////////////////ALCOHOL SENSOR/////////////////////////////////////////////////
  pinMode(DOUTpin, INPUT);//sets the pin as an input to the arduino
  ////////////////////////ALCOHOL SENSOR END//////////////////////////////////////////
  ///////////////////////SMOKE SENSOR START/////////////////////////////////////


    Wire.begin();
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Time,AlcoholValue,BPM,SmokeSensor,Temperature");
  
}
void printall()
{
  Serial.print("DATA,TIME,");
  Serial.print(AlcoholValue);
  Serial.print(",");
  Serial.print(myBPM);
  Serial.print(",");
  Serial.print(SmokeSensorValue);
  Serial.print(",");
  Serial.print(Temp/340.00+36.53);
  Serial.print("\n");
}
void loop() {
  
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr,14,true);
  Temp=Wire.read()<<8|Wire.read();
  
  delay(100);
SmokeSensorValue=analogRead(A1);
AlcoholValue= analogRead(AOUTpin);//reads the analaog value from the alcohol sensor's AOUT pin
AlcoholLimit= digitalRead(DOUTpin);//reads the digital value from the alcohol sensor's DOUT pin

delay(90);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
 myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 
 
if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
 
                        // Print the value inside of myBPM. 
    
}
 ///////////////////////////////////////////////////////////////////////////////////////////////



 
  printall();
  delay(90);                    // considered best practice in a simple sketch.
 
}
