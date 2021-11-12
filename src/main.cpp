#include <Arduino.h>
#include <Servo.h>

//Who's your daddy

#define interrupt_sensor 2

int current_task = 0;

#define MC_enable_A 11
#define M_1_dir_1 3
#define M_1_dir_2 4
#define drivingspeed 255 // 0-255

//servo setup
Servo servosingle;
Servo servodouble;
#define singleservopin 9
#define secondservopin 10
// int servosinglepos = 0;
// int servodoublepos = 0;
#define dropoffpointservo1 15
#define dropoffpointservo2 -15
volatile int station = 0;

void inter(){
  if (current_task != 0){
    station++;
  }
}


void setup() {

  delay(5000);
  // put your setup code here, to run once:
  pinMode(MC_enable_A, OUTPUT);
  pinMode(M_1_dir_1, OUTPUT);
  pinMode(M_1_dir_2, OUTPUT);

  servosingle.attach(singleservopin);
  servodouble.attach(secondservopin);
  // Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), inter, FALLING);
  }

void loop() {
  // put your main code here, to run repeatedly:
  if (current_task == 0){ // challenge 1
    digitalWrite(M_1_dir_1, HIGH);
    digitalWrite(M_1_dir_2, LOW);
    while (true){
      analogWrite(MC_enable_A, drivingspeed);
    }
  }
  if (current_task == 1){
    digitalWrite(M_1_dir_1, HIGH);
    digitalWrite(M_1_dir_2, LOW);
    while (station < 2){
      analogWrite(MC_enable_A, drivingspeed);
    }
    analogWrite(MC_enable_A, 0);
  }
  if (current_task == 2){
    digitalWrite(M_1_dir_1, HIGH);
    digitalWrite(M_1_dir_2, LOW);
    while (station < 2){
      analogWrite(MC_enable_A, drivingspeed);
    }
    analogWrite(MC_enable_A, 0);
    delay(1500);
    servosingle.write(dropoffpointservo2);
    delay(2000);


    
    
  }



 // end script
 analogWrite(MC_enable_A, 0);
 digitalWrite(M_1_dir_1, LOW);
 digitalWrite(M_1_dir_2, LOW);
}