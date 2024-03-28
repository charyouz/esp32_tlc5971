#include "esp_tlc5971.h"

int COLOR_MAX = 65500;

Led::Led(){};

void Led::set_led(int red, int green, int blue) {
  r = red;
  b = blue;
  g = green;
  };

int Led::get_r() {
  return r;
};

int Led::get_g(){
  return g;
};

int Led::get_b(){
  return b;
};

Controller::Controller() {};

int percentage_to_led_brightness(int per) {
  if (per == 0){
    return 0;
  }
  else {
    int new_range = (COLOR_MAX - 1)  ;
    int new_value = (((per - 1) * new_range) / 99) + 1;
    return new_value;
  }
}

void Controller::set_led(int led, int r, int g, int b) {
  leds[led].set_led(r, g, b);
};

int Controller::get_led_r(int led) {
  return leds[led].get_r();
};

int Controller::get_led_g(int led) {
  return leds[led].get_g();
};

int Controller::get_led_b(int led) {
  return leds[led].get_b();
};

int * Controller::get_controller_data() {
  // Command bits are for default commands
  // 10010110 01011111 11111111 11111111


  // Currently set command bits here.
  // The first 6 bits are the write command '100101'
  // Then comes OUTMG, EXTCLK, TMGRST, DSPRPT and BLANK, these should be '10010'
  // After that comes global brightness bits, currently 3 (RGB) x 7 bits of ones.
  data_block[0] = 0b1001011001011111;
  data_block[1] = 0b1111111111111111;

  int j = 2;
  for (int i = 0; i<4; i++) {
    data_block[j] = leds[i].get_b();
    j++;
    data_block[j] = leds[i].get_g();
    j++;
    data_block[j] = leds[i].get_r();
    j++;
  }
//  Serial.println("Controller data: ");
//  for (int j = 0; j<= 13; j++) {
//     for (int i = 15; i >= 0; i--)
//    {
//        bool b = bitRead(data_block[j], i);
//        Serial.print(b);
    }
//    Serial.print("\n");
  }
  return data_block;
};

Chain::Chain() {};

void Chain::begin(int data_pin, int clock_pin, int kHz){
  pinMode(data_pin,OUTPUT);
  pinMode(clock_pin,OUTPUT);

  // Set pins to low
  digitalWrite(data_pin, LOW);
  digitalWrite(clock_pin, LOW);
};

void Chain::send(int dt[]) {

  // time to wait between clock signal high's in us
  int wait_time = 1000 / (2 * kHz);

//  Serial.print("Wait time between bits is ");
//  Serial.print(wait_time);
//  Serial.println(" milliseconds");

for (int c = 0; c <= sizeof controllers; c++) {
  // Send data MSB first
  for (int j = 0; j <= 13; j++) {
    for (int i = 15; i >= 0; i--) {
      bool b = bitRead(dt[j], i);
      digitalWrite(data_pin, b);
      delayMicroseconds(wait_time);
      digitalWrite(clock_pin, HIGH);
      delayMicroseconds(wait_time);
      digitalWrite(clock_pin, LOW);
    };
  };
  digitalWrite(data_pin, LOW);  // set data pin to low between data.
// Serial.println("Data sent");
};


void Chain::print_data() {
  Serial.println(kHz);
}
