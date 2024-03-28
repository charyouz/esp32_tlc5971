#include <ESP32Servo.h>

#include "esp_tc5791.h"
#include <SoftwareSerial.h>

// SW version
#define MAJOR 0
#define MINOR 3
#define PATCH 0

//onboard LED
#define LED 2

// setup LED drivers (2)
Controller chain[2] = {Controller(), Controller()};
float led_driver_prcnt = 1;
int led_max = 65500;
int led_max_value;

Chain chaine;


// Servo motor pin
#define SERVO_PIN 32
Servo servo;
int pos = 0;
int max_servo_degree = 180;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //ledSerial.begin(115200);

  //LED driver setup
  chaine.begin(19, 18, 8); // data, clock, kHz
  chaine.print_data();

  Serial.println("Program starting");

  // on board led
  pinMode(LED,OUTPUT);
  Serial.println("Onboard LED setup");

  //setup random seed
  randomSeed(analogRead(0));
  Serial.println("Random seed setup");

  //set LEDs to some color at start:
  for (int i; i<2; i++) {
    for (int j; j<4; j++) {
      chain[i].set_led(j, 3000, 3000, 3000);
      }
  };
  led_max_value = led_max * led_driver_prcnt;
  Serial.println("LED drivers init");

  // setup servo
  servo.attach(SERVO_PIN);
  Serial.println("Servo init");

  // Show version via onboard LED
  flash_version(2);
}

void loop() {
  Serial.println("in loop");
  digitalWrite(LED,HIGH);
  // get random led
  int rand_contr = random(0,1);
  int rand_led = random(0,3);
  int rand_led_val_r = random(led_max_value);
  int rand_led_val_g = random(led_max_value);
  int rand_led_val_b = random(led_max_value);
  int rand_serv_pos = random(max_servo_degree);

  //chain[rand_contr].set_led(rand_led, rand_led_val_r, rand_led_val_g, rand_led_val_b);
  for (int i = 0; i <=3; i++){
    chain[0].set_led(i, rand_led_val_r, rand_led_val_g, rand_led_val_b);
  }

  Serial.println("Random LED updated, pushing data...");

  for (int j = 0; j<2; j++) {
    Serial.print("Data for controller ");
    Serial.println(j);
    int * contr_data = chain[0].get_controller_data();  // CHANGE 0 TO j IN PRODUCTION
    chaine.send(contr_data);
  };

  Serial.println("Setting servo pos");
  //servo.write(rand_serv_pos);

  delay(50);
  digitalWrite(LED,LOW);
  Serial.println("Waiting");
 // delay(random(500, 3000));
  delay(1000);  //delay 1 sec for testing purposes
}

void flash_version(int led_pin) {
  // flash major
  flash_led(1, led_pin, 500);
  flash_led(MAJOR, led_pin, 250);

  //flash minor
  flash_led(2, led_pin, 500);
  flash_led(MINOR, led_pin, 250);

  //flash patch
  flash_led(3, led_pin, 500);
  flash_led(PATCH, led_pin, 250);
};

void flash_led(int times, int led_pin, int wait){
    for (int i=0; i<=times; i++) {
      digitalWrite(led_pin, HIGH);
      delay(wait);
      digitalWrite(led_pin, LOW);
  }
};
