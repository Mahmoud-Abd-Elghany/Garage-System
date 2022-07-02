/*
 * main.h
 *
 * Created: 25-Jun-22 11:21:29 AM
 *  Author: Mahmo
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>
#define F_CPU 1000000UL
#include "servo_motor.h"
#include "LCD.h"
#include "DIO.h"

#define WELCOME_MSG "Welcome"
#define GARAGE_TOTAL_SLOTS 3
#define PIR_PORT 'D'

#define ENTRY_PIR_PIN 0
#define ENTRY_PIR_CHECK_PIN 1

#define EXIT_PIR_PIN 2
#define EXIT_PIR_CHECK_PIN 3

#define ENTRY_PIR 0
#define ENTRY_CHECK_PIR 1

#define EXIT_PIR 0
#define EXIT_CHECK_PIR 1

#define ENTRY_SERVO_CHANNEL 'B'
#define EXIT_SERVO_CHANNEL 'A'

#define INPUT 0
#define OUTPUT 1

#define GARAGE_FULL "There are no empty spots"
#define GARAGE_EMPTY "No. of empty slots: "

typedef unsigned char uint_8;

typedef struct garage_state {
	uint_8 garage_total_slots;
	uint_8 garage_empty_slots;
	uint_8 garage_entry[2];
	uint_8 garage_exit[2];
	} garage_state;

void timeout_entry_callback(void);
void timeout_exit_callback(void);

#endif /* MAIN_H_ */