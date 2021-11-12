#include <Arduino.h>
#include <Servo.h>

//Who's your daddy

void inter();

#define interrupt_sensor 2
#define Switch_1 12
#define Switch_2 13

int current_task = 0;

#define MC_enable_A 11
#define M_1_dir_1 8
#define M_1_dir_2 7
#define drivingspeed 75 // 0-255 // 75

//servo setup
Servo servosingle;
Servo servodouble;
#define singleservopin 9
#define secondservopin 10
// int servosinglepos = 0;
// int servodoublepos = 0;
#define dropoffpointservo1 90
#define dropoffpointservo2 90
volatile int station = 0;
#define singlezeropoint 170
#define doublezeropoint 170

#define waittime 30000 //30000

volatile int timeoflaststation = 0;
unsigned int waituntil = 0;

void inter(){
  if (current_task != 0 and (millis() - timeoflaststation) > 3000){
    station++;
    timeoflaststation = millis();
  }
}


void setup() {

  Serial.begin(9600);

  delay(5000);
  // put your setup code here, to run once:
  pinMode(MC_enable_A, OUTPUT);
  pinMode(M_1_dir_1, OUTPUT);
  pinMode(M_1_dir_2, OUTPUT);

  servosingle.attach(singleservopin);
  servodouble.attach(secondservopin);
  // Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), inter, FALLING);
  servosingle.write(singlezeropoint);
  servodouble.write(doublezeropoint);

  pinMode(Switch_1, INPUT_PULLUP);
  pinMode(Switch_2, INPUT_PULLUP);
  Serial.println(digitalRead(Switch_1));
  Serial.println(digitalRead(Switch_2));
    if (digitalRead(Switch_1) == LOW and digitalRead(Switch_2) == LOW){
      current_task = 0;
    }
    if (digitalRead(Switch_1) and digitalRead(Switch_2) == LOW){
      current_task = 1;
    }
    if (digitalRead(Switch_1) and digitalRead(Switch_2)){
      current_task = 2;
    }
    Serial.println("end of setup");
  }

void loop() {
  // put your main code here, to run repeatedly:
  if (current_task == 0){ // challenge 1
  Serial.println("task1");
    digitalWrite(M_1_dir_1, HIGH);
    digitalWrite(M_1_dir_2, LOW);
    analogWrite(MC_enable_A, drivingspeed);
    while (true){
      Serial.println("am high");
    }
  }
  if (current_task == 1){
    Serial.println("task2");
    digitalWrite(M_1_dir_1, HIGH);
    digitalWrite(M_1_dir_2, LOW);
    while (station < 2){
      analogWrite(MC_enable_A, drivingspeed);
    }
    analogWrite(MC_enable_A, 0);
  }
  if (current_task == 2){
    Serial.println("task3");
    digitalWrite(M_1_dir_1, HIGH);
    digitalWrite(M_1_dir_2, LOW);
    while (station < 1){
      analogWrite(MC_enable_A, drivingspeed);
    }
    analogWrite(MC_enable_A, 0);
    delay(1500);
    servosingle.write(dropoffpointservo1);
    waituntil = millis() + waittime;
    while (waituntil > millis()){
      delay(100);
    }
    delay(2000);
    servosingle.write(singlezeropoint);
    while (station < 2)
    {
      analogWrite(MC_enable_A, drivingspeed);
    }
    analogWrite(MC_enable_A, 0);
    delay(2000);
    servodouble.write(dropoffpointservo2);
    waituntil = millis() + waittime;
    // servodouble.write(doublezeropoint);
    delay(1000);
    while (station < 3){
      analogWrite(MC_enable_A, drivingspeed);
    }
    analogWrite(MC_enable_A, 0);
    delay(10);
    waituntil = millis() + (waittime / 3);
    while(waituntil > millis()){
      delay(10);
    }
    while(station < 6){
      analogWrite(MC_enable_A, drivingspeed);
    }
    analogWrite(MC_enable_A, 0);
    current_task = 15;//random
  }



 // end script
 analogWrite(MC_enable_A, 0);
 digitalWrite(M_1_dir_1, LOW);
 digitalWrite(M_1_dir_2, LOW);
 delay(20000);

//  current_task++;
}