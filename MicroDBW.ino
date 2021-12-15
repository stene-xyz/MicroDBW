/*
 * MicroDBW Version 1.0.0
 * 
 * Copyright 2021 Johnny Stene <johnny@stene.xyz>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * This software allows an Arduino to control an ESC and a servo from 
 * serial commands. I'm using this ESC: 
 * https://www.amazon.ca/gp/product/B08FZYFXMW but Any ESC with the 
 * standard 3-pin R/C connection (the same thing that servos use) should
 * work just fine. One thing to note is that you should never, ever 
 * connect the center pin to your Arduino - it could fry your USB port 
 * if the battery voltage is anywhere above 5V (most newer computers 
 * have protections against that but it's best to be safe).
 * 
 * Default pin configuration:
 * Servo + -> Arduino 5V
 * Servo Pulse -> Arduino D10
 * Servo - -> Arduino GND
 * ESC + -> Do not connect
 * ESC Pulse -> Arduino D9
 * ESC - -> Arduino GND
 */
 
// Settings
#define SERIAL_BAUD_RATE 9600
#define ESC_CONTROL_PIN 9
#define ESC_CONTROL_CHARACTER 'D'
#define SERVO_CONTROL_PIN 10
#define SERVO_CONTROL_CHARACTER 'S'

// Needed to control ESC and steering servo
#include <Servo.h>

// Servos can go from 0 to 180 degrees, thus 90 is the neutral position
Servo ESC;
int ESC_position = 90;

Servo steering_servo;
int steering_position = 90;

void setup() {
	Serial.begin(9600); // Standard 9600 baud
	
	// Attach both motors to their respective pulse pins
	ESC.attach(ESC_CONTROL_PIN);
	steering_servo.attach(SERVO_CONTROL_PIN);

	Serial.setTimeout(35565);
	Serial.println("OK"); // Tell the computer we are ready
}

void loop() {
	char command[1]; // Stores the incoming command byte (either D or S)
	long int value; // Stores the recieved integer value
	
	Serial.readBytes(command, 1); // 1 byte for the command
	value = Serial.parseInt(SKIP_NONE); // Read an integer
	
	value += 90; // Neutral position is 90
	if(value < 0 || value > 180) // Don't allow values too big/low
		Serial.println("ERR1");
	else { // Set positions to recieved value
		if(command[0] == ESC_CONTROL_CHARACTER) {
			  ESC_position = value;
			Serial.println("OK");
		} else if(command[0] == SERVO_CONTROL_CHARACTER) {
			steering_position = value;
			Serial.println("OK");
		} else Serial.println("ERR2"); // Error if bad command character
	}
	
	// Write new positions
	ESC.write(ESC_position);
	steering_servo.write(steering_position);
}
