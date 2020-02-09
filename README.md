
# clTerm

### clTerm, API based protable serial terminal utility.

![Version:1.0](https://img.shields.io/badge/Version-1.0-green)
![In Development](https://img.shields.io/badge/Status-In%20Development-orange.svg)
![IDE:CCStudio](https://img.shields.io/badge/IDE-CCStudio-red)
![Protocol:UART](https://img.shields.io/badge/Protocol-UART%20serial-blue)
![Terminal:Putty](https://img.shields.io/badge/Teminal-puTTY-blue)


![License:MIT](https://img.shields.io/github/license/adimalla/MQTT-3.1-C?label=License)
<br/>
<br/>

<img src="https://github.com/adimalla/clTerm/blob/master/screenshots/Selection_328.jpg" width="700" height="500" title="CLI">
<br/>

## Description
clTerm is an easy to port API based serial terminal utility which allows,users to add standard C like "command line arguments" based functions, or commands to their application. This utility is implemented via callback, which allows portability across any micro-controller that supports serial protocols.

<br/>

## Features

##### Current:-
* Read and Write API for reading from and writing to serial terminal
* Operations functions to link external character(byte) read and write functions to API, making it portable.
* Allowing user to add command line arrgument based commands to their applications, upto 255 commands.
* Clean API and exception handler for easy debugging and error reporting.
* Both Static and Dynamic allocation of API objects as per availaiblity of features.

##### Future Version:-
* Interrupt support.
* Linked List based command table for efficient resource management.
* String operation based utilities.

<br/>

## Porting and Instalation
Clone repository to the destination directory, include CLTERM_API into include files for the IDE, exclude or remove Examples test code if building a new application.

puTTY terminal is recommended for application development and testing with this utility.

<br/>

## Usage


## Contributors and Maintainers
Aditya Mall (UTA MSEE)
</br>
email: aditya.mall1990@gmail.com.
