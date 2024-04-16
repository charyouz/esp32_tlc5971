# ESP32 TLC5971

An esp32 library for using TLC5791 microchip for ESP32.

## Description

A library to control TLC5971 with an ESP32 module. Requires 2 pins to be connected from the ESP32 to the TLC5971.
This library uses one of the pins as a clock signal and the other as a data line.

## Usage

Check examples folder, for examples on how to use the library

The basic idea is that you have 4 LEDs connected to X amount of controllers, that are all wired in series.

The minimum to get 8 LEDs connected to 2 Controllers to work is:

```
#include "esp_tlc5971.h"

//Setup 2 LED controllers
Controller chain[2] = {Controller(), Controller()};
```
If you have more or less controllers, set the correct amount here.

Currently, you need to send each controllers data individually with send_data(). So you would iterate over the controllers you have set up and
then use their pointers as input for the send_data() function.


## Roadmap

- [ ] Auto send all data to chain
- [ ] Allow optional setting of global data

## License

Shield: [![CC BY-NC-SA 4.0][cc-by-nc-sa-shield]][cc-by-nc-sa]

This work is licensed under a
[Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License][cc-by-nc-sa].

[![CC BY-NC-SA 4.0][cc-by-nc-sa-image]][cc-by-nc-sa]

[cc-by-nc-sa]: http://creativecommons.org/licenses/by-nc-sa/4.0/
[cc-by-nc-sa-image]: https://licensebuttons.net/l/by-nc-sa/4.0/88x31.png
[cc-by-nc-sa-shield]: https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey.svg
