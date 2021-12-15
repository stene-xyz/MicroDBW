# MicroDBW
Control an R/C car over USB with an Arduino with an easy to use serial interface.  

## WARNINGS
- Do NOT connect the power pin of your ESC to your Arduino. It will not end well.
- **DO NOT USE THIS FOR SAFETY-CRITICAL APPLICATIONS!!** See the `SAFETY NOTICE` section below. 

## Default Pin Configuration
By default, the ESC is connected to pin 9, and the steering servo is connected to pin 10.

## Command Structure
Commands follow a very basic format, containing one selection character, an integer from -90 to 90, and a newline.  
The selection characters are case-sensitive, and by default are `D` for the ESC, and `S` for the steering servo.  
Commands must be sent over serial at (by default) 9600 baud.  

## Returned values
| Value        | Meaning                                                                |
|--------------|------------------------------------------------------------------------|
| OK           | MicroDBW has initialised **OR** the command was executed successfully. |
| ERR1         | The command had a missing or invalid integer number.                   |
| ERR2         | The command had a missing or invalid control character.                |
  
Errors will also be thrown when a timeout occurs. MicroDBW will continue with the last recieved commands.

## Features
- Control a standard 3-pin ESC and servo
- Commands over serial
- Configurable in code

## Planned Features
- Reconfigure connected ESCs/servos, and selection characters on the fly

## SAFETY NOTICE
MicroDBW is unsuitable for safety-critical applications, for the following reasons:
- On error or timeout, it will continue with the last steering and throttle positions rather than stopping
- It may have weird bugs I haven't found yet
- It has only basic error checking, and has no way to verify that the connected devices are working as expected
