#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <Servo.h>
  
// Defines Tirg and Echo pins of the Ultrasonic Sensor
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int trigPin = 13;
const int echoPin = 12;
const int speakerPin = 8;
const int ledPin = 5;
const int joyY = 0;

// Variables for the duration and the distance
long duration;
int distance;
int joyVal;
Servo myServo; // Creates a servo object for controlling the servo motor


void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  myServo.attach(11); // Defines on which pin is the servo motor attached
    lcd.begin();
}


void loop() {
  joyVal = analogRead(joyY);
  joyVal = map(joyVal, 0, 1023, 0, 180);
  myServo.write(joyVal);

  delay(30);  
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing

  if(distance < 100){
    tone(speakerPin, 2000, 500);
    lcd.clear();
    digitalWrite(ledPin, HIGH);
    lcd.backlight();
    lcd.print("Threat Detected");
    
  }else{
    digitalWrite(ledPin, LOW);
    lcd.clear();
  }
}


// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}
