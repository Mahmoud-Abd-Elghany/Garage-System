/*
 * servo_motor.c
 *
 * Created: 24-Jun-22 8:33:25 AM
 *  Author: Mahmoud Abdelghany
 */ 

#include "servo_motor.h"



void servo_rotate_0(char channel){
	switch (channel){
		case 'A':
		timer1_wave_fastPWM_A(0.99999);
		break;
		case'B':
		timer1_wave_fastPWM_B(0.99999);
		break;
	}
}
void servo_rotate_90(char channel){
	switch (channel){
		case 'A':
		timer1_wave_fastPWM_A(1.499999);
		break;
		case'B':
		timer1_wave_fastPWM_B(1.499999);
		break;
	}
}
void servo_rotate_180(char channel){
	switch (channel){
		case 'A':
		timer1_wave_fastPWM_A(1.99999);
		break;
		case'B':
		timer1_wave_fastPWM_B(1.99999);
		break;
	}
}