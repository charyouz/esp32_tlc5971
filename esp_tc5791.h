#ifndef esp_tc5791_h
#define esp_tc5791_h

#include <Arduino.h>

class Led {
    int r = 0;
    int g = 0;
    int b = 0;

  public:
    Led();
    void set_led(int red, int green, int blue);
    int get_r();
    int get_g();
    int get_b();
};

// struct for each individual controllet
class Controller {
  private:
    int WRITE_CMD = 0x25;  // 6 long
    int FC_BLOCK = 0b10010;  // 5 long
    int BCB = 0x7F;  // 7 long
    int BCG = 0x7F;
    int BCR = 0x7F;
    Led leds[4] = {Led(), Led(), Led(), Led()};
    int data_block[14];

  public:
    Controller();
    void set_led(int led, int r, int g, int b);
    int * get_controller_data();
    int get_led_r(int led);
    int get_led_g(int led);
    int get_led_b(int led);
};

class Chain {
  private:
    int kHz;
    int data_pin;
    int clock_pin;
    
  public:
    Chain();
    void begin(int data_pin, int clock_pin, int kHz);
    void print_data();
    void send(int dt[]);
};
#endif
