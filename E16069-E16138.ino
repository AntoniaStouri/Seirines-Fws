/*
  Sketch_14.1.2
  Ultrasonic Ranging

  modified 2016/6/5
  by http://www.freenove.com
*/

#include <NewPing.h>
#define trigPin 12 // define TrigPin
#define echoPin 11 // define EchoPin.
#define MAX_DISTANCE 200 // Maximum sensor distance is rated at 400-500cm.
#include <Servo.h>

Servo myservo;              // create servo object to control a servo

int pos = 0;                // variable to store the servo position
int servoPin = 3;           // define the pin of servo signal line

NewPing sonar(trigPin, echoPin, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int convertValue; // Define a variable to save the ADC value
void setup() {
  myservo.attach(servoPin); // attaches the servo on servoPin to the servo object
  Serial.begin(9600); // Open serial monitor at 9600 baud to see ping results.
}
float dist;
bool ppl=0, done = 0;
void loop() {
  delay(1000); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  dist = sonar.ping_cm();
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  convertValue = analogRead(A0);  // Read analog voltage value of A0 port, and save
  // Map analog to the 0-255 range, and works as ledPin duty cycle setting
  Serial.println(convertValue);

  if ( dist < 40 ){
    if ( ppl )
     ppl = 0 ;
     else {
      done = 0;
      ppl = 1 ;
     }
  }
  Serial.println(ppl);
  if( !ppl && convertValue < 400 && !done ){
    done = 1;
     for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable "pos"
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable "pos"
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  }
}
