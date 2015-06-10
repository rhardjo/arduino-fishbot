
/* ---------- LIBRARIES ---------- */
#include <AFMotor.h>
#include <SPI.h>  


/* ---------- CONSTANTS ---------- */
AF_DCMotor motorBL(1);
AF_DCMotor motorBR(2);
AF_DCMotor motorFR(3);
AF_DCMotor motorFL(4);

const int sonarPin = 2;


/* ---------- VARIABLES ---------- */
// Motor
int motorSpeed = 100;
int motorInterval = 1000;
int motorTurnInterval = 10000;

// Sonar
int sonarInterval = 100;
long pulse, inches, cm;

// Delay timers
unsigned long currentMillis = 0;
unsigned long previousSonarMillis = 0;
unsigned long previousMotorMillis = 0;


/* ---------- SETUP ---------- */

void setup() {
  
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Starting engine");
  
  motorBL.setSpeed(motorSpeed);     // set the speed to 200/255
  motorBR.setSpeed(motorSpeed);     // set the speed to 200/255
  motorFR.setSpeed(motorSpeed);     // set the speed to 200/255
  motorFL.setSpeed(motorSpeed);     // set the speed to 200/255
   
}


/* ---------- LOOP ---------- */
void loop() {   
  
  // Keep track of time
  currentMillis = millis();
  
  // Start the functions
  distanceChecker();
  canIRide();
  
}


void distanceChecker() {
//  if (currentMillis - previousSonarMillis > sonarInterval) {
//    previousSonarMillis += sonarInterval;
    
    pinMode(sonarPin, INPUT);
    pulse = pulseIn(sonarPin, HIGH);
    inches = pulse/147; // Calculate raw data to inches
    cm = inches * 2.54; // Calculate inches to centimetres
    Serial.println(cm);
//    delay(sonarInterval);
//  }   
}


void canIRide() {
  do {
    runMotor();
  } while (cm > 12);

  if (cm == 12) {
    stahp();
    Serial.println("STAHP");
    delay(1000);
    NoScope();
  }   
}


void runMotor() {
  
  if (currentMillis - previousMotorMillis >= motorInterval) {
    previousMotorMillis = currentMillis;
    motorBL.run(FORWARD);
    motorBR.run(FORWARD);
    motorFR.run(FORWARD);
    motorFL.run(FORWARD);
    Serial.println("Running motor");
  }
  
}


void stahp() {
  
  motorBL.run(RELEASE);
  motorBR.run(RELEASE);
  motorFR.run(RELEASE);
  motorFL.run(RELEASE);
  
}


void NoScope() {
  
  if (currentMillis - previousMotorMillis >= motorTurnInterval) {
    previousMotorMillis = currentMillis;
    motorBL.run(RELEASE);
    motorBR.run(FORWARD);
    motorFR.run(FORWARD);
    motorFL.run(RELEASE);
  }
  
}
