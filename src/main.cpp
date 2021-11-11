#include <Arduino.h>

//Who's your daddy

int current_task = 0;

#define led_pin 13
#define MC_enable_A 9
#define MC_enable_B 10
#define M_1_dir_1 2
#define M_1_dir_2 3
#define M_2_dir_1 4
#define M_2_dir_2 5
#define drivingspeed 255 // 0-255

void setup() {
  // put your setup code here, to run once:

  pinMode(led_pin, OUTPUT);

  pinMode(MC_enable_A, OUTPUT);
  pinMode(M_1_dir_1, OUTPUT);
  pinMode(M_1_dir_2, OUTPUT);



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




 // end script
 analogWrite(MC_enable_A, 0);
 digitalWrite(M_1_dir_1, LOW);
 digitalWrite(M_1_dir_2, LOW);
}