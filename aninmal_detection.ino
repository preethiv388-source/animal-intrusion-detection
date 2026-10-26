#include <Servo.h> 
 
Servo sensorServo; 
 
// Pins 
const int pirPin = 2; 
 
const int greenLED = 4; 
const int yellowLED = 5; 
const int redLED = 6; 
 
const int buzzer = 7; 
const int servoPin = 9; 
 
const int lidarPin = A0; 
const int geophonePin = A1; 
 
void setup() { 
 
  sensorServo.attach(servoPin); 
 
  pinMode(pirPin, INPUT); 
 
  pinMode(greenLED, OUTPUT); 
  pinMode(yellowLED, OUTPUT); 
  pinMode(redLED, OUTPUT); 
  pinMode(buzzer, OUTPUT); 
 
  Serial.begin(9600); 
 
  // Initial state = GREEN 
  digitalWrite(greenLED, HIGH); 
  digitalWrite(yellowLED, LOW); 
  digitalWrite(redLED, LOW); 
  digitalWrite(buzzer, LOW); 
} 
 
void loop() { 
 
  // Read sensors 
  int pir = digitalRead(pirPin); 
  int lidarValue = analogRead(lidarPin); 
  int vibration = analogRead(geophonePin); 
 
  // Convert LiDAR simulation to distance 
  int distance = map(lidarValue, 0, 1023, 200, 0); 
 
  // Print values 
  Serial.print("PIR: "); 
  Serial.print(pir); 
 
  Serial.print(" | Distance: "); 
  Serial.print(distance); 
  Serial.print(" cm"); 
 
  Serial.print(" | Vibration: "); 
  Serial.println(vibration); 
 
 
  // ========================= 
  // HIGH RISK 
  // ========================= 
  if (pir == HIGH && distance <= 80 && vibration >= 500) { 
 
    digitalWrite(greenLED, LOW); 
    digitalWrite(yellowLED, LOW); 
    digitalWrite(redLED, HIGH); 
 
    tone(buzzer, 1000); 
    delay(5000); 
    noTone(buzzer); 
 
  } 
 
  // ========================= 
  // ANIMAL DETECTED 
  // ========================= 
  else if (pir == HIGH || distance <= 80 || vibration >= 500) { 
 
    digitalWrite(greenLED, LOW); 
    digitalWrite(yellowLED, HIGH); 
    digitalWrite(redLED, LOW); 
 
    noTone(buzzer); 
 
  } 
 
  // ========================= 
  // NORMAL 
  // ========================= 
  else { 
 
    digitalWrite(greenLED, HIGH); 
    digitalWrite(yellowLED, LOW); 
    digitalWrite(redLED, LOW); 
 
    noTone(buzzer); 
  } 
 
 
  // Servo scanning 
  sensorServo.write(0); 
  delay(300); 
 
  sensorServo.write(90); 
  delay(300); 
 
  sensorServo.write(180); 
  delay(300); 
 
  sensorServo.write(90); 
  delay(300); 
 
  sensorServo.write(0); 
  delay(300); 
}