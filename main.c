/*
 * Garage.c
 *
 * Author : Mahmoud Abdelghany
 */ 

#include "main.h"


int main(void)
{
	LCD_init();
	
	/* Entry and Entry Check, Entry PIR Pins */
	DIO_vsetPINDir(PIR_PORT,ENTRY_PIR_PIN, INPUT);
	DIO_vsetPINDir(PIR_PORT,ENTRY_PIR_CHECK_PIN, INPUT);
	
	/* Exit and Exit Check, Exit PIR Pins */
	DIO_vsetPINDir(PIR_PORT,EXIT_PIR_PIN, INPUT);
	DIO_vsetPINDir(PIR_PORT,EXIT_PIR_CHECK_PIN, INPUT);
	
	garage_state garage_state = {0};
	garage_state.garage_total_slots = GARAGE_TOTAL_SLOTS;
	garage_state.garage_empty_slots = GARAGE_TOTAL_SLOTS;
	servo_rotate_0(ENTRY_SERVO_CHANNEL);
	servo_rotate_0(EXIT_SERVO_CHANNEL);
	LCD_Display_String(WELCOME_MSG);
	
	/* Flags for Entry PIRs to to read the current state of the PIR  one per car*/
	uint_8 prev_entry_state_flag = 0;
	uint_8 prev_entry_check_state_flag = 0;
	
	/* Flags for Exit PIRs to to read the current state of the PIR once per car*/
	uint_8 prev_exit_state_flag = 0;
	uint_8 prev_exit_check_state_flag = 0;
    while (1){
		garage_state.garage_entry[ENTRY_PIR] = DIO_u8read(PIR_PORT,ENTRY_PIR_PIN);
		garage_state.garage_entry[ENTRY_CHECK_PIR] = DIO_u8read(PIR_PORT,ENTRY_PIR_CHECK_PIN);
		garage_state.garage_exit[EXIT_PIR] = DIO_u8read(PIR_PORT,EXIT_PIR_PIN);
		garage_state.garage_exit[EXIT_CHECK_PIR] = DIO_u8read(PIR_PORT,EXIT_PIR_CHECK_PIN);
		
		/*
		* Entry Sequence
		* 1- Checking the Entry PIR
		* 2- Check available slots
		* 3- Set timeout to close the gate if the car didn't enter or pass through second PIR
		* 4- Close the Gate when the car passes through second PIR or After predetermined duration.
		* 5- Decrement Empty slots
		*/
		if(garage_state.garage_entry[ENTRY_PIR] == 1 && prev_entry_state_flag == 0){
			prev_entry_state_flag = 1;
			
			/* Open Gate only in case there is empty slots */
			if(garage_state.garage_empty_slots > 0){
				servo_rotate_90(ENTRY_SERVO_CHANNEL);
				
				/* Setting timeout in case the car didn't pass second PIR after specific time. */
				timer_OVF_interrupt_Callback(timeout_entry_callback,60);
				
				/* LCD Display number of empty slots or That there is no empty slots */
				LCD_Send_Command(LCD_CLEAR_SCREEN);
				LCD_Display_String(GARAGE_EMPTY);
				LCD_Display_Character(garage_state.garage_empty_slots);
			}else{
				LCD_Send_Command(LCD_CLEAR_SCREEN);
				LCD_Display_String(GARAGE_FULL);
			}
		}
		else if(garage_state.garage_entry[ENTRY_PIR] == 0){
			prev_entry_state_flag = 0;
		}
		
		/*
		* Entry Check: Close gate When car passes through second PIR 
		*/
		if(garage_state.garage_entry[ENTRY_CHECK_PIR] == 1 && prev_entry_check_state_flag == 0){
			if(garage_state.garage_empty_slots > 0){
				garage_state.garage_empty_slots = garage_state.garage_empty_slots -1;
			}
			prev_entry_check_state_flag = 1;
			if(garage_state.garage_entry[ENTRY_PIR] == 0){
				servo_rotate_0(ENTRY_SERVO_CHANNEL);
			}
		}
		else if(garage_state.garage_entry[ENTRY_CHECK_PIR] == 0){
			prev_entry_check_state_flag = 0;
		}
		
		/*
		* Exit Sequence
		* 1- Checking the Exit first PIR
		* 2- Set timeout to close the gate if the car didn't enter or pass through second PIR
		* 3- Close the Gate when the car passes through second PIR or After predetermined duration.
		* 4- Increment Empty slots
		*/
		if(garage_state.garage_exit[EXIT_PIR] == 1 && prev_exit_state_flag == 0){
			prev_exit_state_flag = 1;
			servo_rotate_90(EXIT_SERVO_CHANNEL);
			timer_OVF_interrupt_Callback(timeout_exit_callback,60);
		}
		else if(garage_state.garage_exit[EXIT_PIR] == 0){
			prev_exit_state_flag = 0;
		}
		if(garage_state.garage_exit[EXIT_CHECK_PIR] == 1 && prev_exit_check_state_flag == 0){
			garage_state.garage_empty_slots = garage_state.garage_empty_slots +1;
			prev_exit_check_state_flag = 1;
			if(garage_state.garage_exit[EXIT_PIR] == 0){
				servo_rotate_0(EXIT_SERVO_CHANNEL);
			}
		}
		else if(garage_state.garage_exit[EXIT_CHECK_PIR] == 0){
			prev_exit_check_state_flag = 0;
		}
    }
}


void timeout_entry_callback(void){
	servo_rotate_0(ENTRY_SERVO_CHANNEL);
}

void timeout_exit_callback(void){
	servo_rotate_0(EXIT_SERVO_CHANNEL);
}

