#include <Servo.h>
Servo myservo;

int touchSensorPin = 2;
const int vibrationPin = A0; 
// Define the pin for the buzzer
int buzzerPin = 3;
int condition;
// Define the pin for the servo motor
int servoPin = 9;
#define trigPin A2
#define echoPin A3
#define some A5
long i;
long duration;
int led =5;
const int led_new = 7;

int maxIntensity = 255;


// Define the variables to track the touch sensor state and timing
int touchSensorState = LOW;
unsigned long touchStartTime = 0;
unsigned long touchDuration = 0;
unsigned long enterstarttime = 0;
unsigned long enterduration = 0;


void setup() {
  // Set the touch sensor pin as input
  pinMode(touchSensorPin, INPUT);
  
  // Set the buzzer pin as output
  pinMode(buzzerPin, OUTPUT);
  
  // Attach the servo motor to the servo pin
  myservo.attach(servoPin);
  pinMode(vibrationPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(some,OUTPUT);
  pinMode(13,INPUT);
  pinMode(led,OUTPUT);
  pinMode(led_new,OUTPUT);
  pinMode(6,OUTPUT);
  Serial.begin(9600);

}
void led_blink(void){
  int  val=digitalRead(13);
   if ( val == 0){
    digitalWrite(led_new,HIGH);
    delay(1000);
    digitalWrite(led_new,LOW);
   }
}

void loop() {
  led_blink();
  condition = analogRead(A0);
  if (condition < 600){
    digitalWrite(buzzerPin,HIGH);
    digitalWrite(led,HIGH);
    delay(2000);
    digitalWrite(buzzerPin,LOW);
    digitalWrite(led,LOW);
}
digitalWrite(trigPin,LOW);
delayMicroseconds(2);
digitalWrite(trigPin,HIGH);
delayMicroseconds(10);
digitalWrite(trigPin,LOW);

duration=pulseIn(echoPin,HIGH);

i=duration*0.017;
Serial.print("Distance");
Serial.println(i);


if (i<=10){
  digitalWrite(LED_BUILTIN,HIGH);
  // delay(20*i);
  digitalWrite(6,HIGH);
  delay(20*i);
  digitalWrite(LED_BUILTIN,LOW);
  // delay(20*i);
  digitalWrite(6,LOW);
  delay(20*i);
}

  
  myservo.write(0);
  int touchSensorValue = digitalRead(touchSensorPin); // Read the touch sensor value

  if (touchSensorValue == HIGH && touchSensorState == LOW) { // Check if the touch sensor is being touched for the first time
    touchStartTime = millis(); // Get the current time
    touchSensorState = HIGH; // Update the touch sensor state
  } else if (touchSensorValue == HIGH && touchSensorState == HIGH) { // Check if the touch sensor is still being touched
    touchDuration = millis() - touchStartTime; // Calculate the touch duration
  } else if (touchSensorValue == LOW && touchSensorState == HIGH) { // Check if the touch sensor has been released
    if (touchDuration >= 3000 && touchDuration <= 5000) { // Check if the touch duration is within the desired range
       
        myservo.write(180);
        
        enterstarttime=millis();
        
        while(millis()-enterstarttime<5000){
          digitalWrite(trigPin, LOW);
          delayMicroseconds(2);

          digitalWrite(trigPin, HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW);

          long duration = pulseIn(echoPin, HIGH);

          // convert duration to distance
          float distance = duration * 340 / 20000;
          }
        myservo.write(0);
        
      } else { // If the touch duration is outside the desired range
      digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
      digitalWrite(led,HIGH);
      delay(100); // Wait for 100 milliseconds
      digitalWrite(buzzerPin, LOW); // Turn off the buzzer
      digitalWrite(led,LOW);
      delay(100); // Wait for 100 milliseconds
      digitalWrite(buzzerPin, HIGH); // Turn on the buzzer again
      digitalWrite(led,HIGH);
      delay(100); // Wait for 100 milliseconds
      digitalWrite(buzzerPin, LOW); // Turn off the buzzer again
      digitalWrite(led,LOW);
      delay(100);
      digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
      digitalWrite(led,HIGH);
      delay(100); // Wait for 100 milliseconds
      digitalWrite(buzzerPin, LOW); // Turn off the buzzer
      digitalWrite(led,LOW);
      delay(100); // Wait for 100 milliseconds
      digitalWrite(buzzerPin, HIGH); // Turn on the buzzer again
      digitalWrite(led,HIGH);
      delay(100); // Wait for 100 milliseconds
      digitalWrite(buzzerPin, LOW);
      digitalWrite(led,LOW);
    }
    touchSensorState = LOW; // Reset the touch sensor state
    touchDuration = 0; // Reset the touch duration
  } else { // Check if the touch sensor is not being touched
    touchSensorState = LOW; // Reset the touch sensor state
    touchDuration = 0; // Reset the touch duration
    digitalWrite(buzzerPin,LOW);
  }}


