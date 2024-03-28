#include "esp_tlc5971.h"

// SW version
#define MAJOR 0
#define MINOR 3
#define PATCH 0

//onboard LED
#define LED 2

// setup LED drivers (2)
// Change this to however may TLC5971 there are in a line
Controller chain[2] = {Controller(), Controller()};
float led_driver_prcnt = 1;
int led_max = 65500;
int led_max_value;

Chain chaine;

void setup() {
  //LED driver setup
  chaine.begin(19, 18, 8); // data, clock, kHz
  chaine.print_data();

  Serial.println("Program starting");

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
}

void loop() {
  // get random led and set random values to its RGB data
  int rand_contr = random(0,1);
  int rand_led = random(0,3);
  int rand_led_val_r = random(led_max_value);
  int rand_led_val_g = random(led_max_value);
  int rand_led_val_b = random(led_max_value);

  // set values for all LEDs in a line
  for (int i = 0; i <=3; i++){
    chain[0].set_led(i, rand_led_val_r, rand_led_val_g, rand_led_val_b);
  }

  Serial.println("Random LED updated, pushing data...");

  for (int j = 0; j<2; j++) {
    Serial.print("Data for controller ");
    Serial.println(j);
    int * contr_data = chain[0].get_controller_data();
    chaine.send(contr_data);
  };


  delay(50);
  digitalWrite(LED,LOW);
  Serial.println("Waiting");
  delay(1000);  //delay 1 sec for testing purposes
}
