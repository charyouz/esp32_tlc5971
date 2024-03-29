#include "esp_tlc5971.h"

// setup LED drivers here 2 conterollers are connected in series
// Change this to however may TLC5971 there are in a line
Controller chain[2] = {Controller(), Controller()};

// Setup max values to LEDs, this is dependent on the LED and how much current they can draw.
// Also if you want the LEDs to be dimmer, change these values to be lower.
// These are currently the MAX values that the driver allows
float led_driver_prcnt = 1;
int led_max = 65500;
int led_max_value;

// Setup a Chain struct so tthat data can be sent to the TLC5971 drivers.
Chain chaine;

void setup() {
  //LED driver setup
  chaine.begin(19, 18, 8); // data pin, clock pin, kHz for data transmission
  chaine.print_data(); //print debug data

  Serial.println("Program starting");

  //setup random seed for LED random colours
  randomSeed(analogRead(0));
  Serial.println("Random seed setup");

  // set LEDs to some color at start
  // Use the same way ot manuallly set LED colours command is:
  // set_led(led_number, red, green, blue)
  // the max value is 65500, and this is basically the percentage value between 0 and that
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
    // get controller data
    int * contr_data = chain[0].get_controller_data();
    // send data to controllers
    chaine.send(contr_data);
  };


  Serial.println("Waiting");
  delay(1000);  //delay 1 sec before changing LED colours
}
