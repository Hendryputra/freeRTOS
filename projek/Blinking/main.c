/*
	FreeRTOS.org V5.1.1 - Copyright (C) 2003-2008 Richard Barry.
	
	entri dari boot.s adalah ke main
	
	20 feb 2009
	buat buffer file index.html dilakukan di task led.
	
	15 april 2009
	coba porting untuk Komon_A (RTD & 4-20 mA)
	
	21 April 2009
	Clean up untuk release stable versi 1.4
	
	3 Nov 2009
	Untuk Komon_420 saja !
*/

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "hardware.h"

#include "sys.h"
#include "ap_led1.h"

#define LED_STATUS BIT(18) //1.18

int loop_idle;
void init_led_utama(void);

xTaskHandle hdl_led;




int main( void )	{
	setup_hardware();				// @"../../hardware/hardware.h"
	//create aplikasi
	init_led_utama();
	
	FIO1CLR =RLY_1;  //matiin dulu pertama on
	FIO1CLR =RLY_2;  //matiin dulu pertama on
	FIO1CLR =RLY_3;  //matiin dulu pertama on
	FIO1CLR =RLY_4;  //matiin dulu pertama on
	
	init_relay();
	
	init_hardware();

	vTaskStartScheduler();

	//printf("Keluar dari Scheduler !!!!\r\n");
	vTaskDelay(4000);
    /* Will only get here if there was insufficient memory to create the idle task. */
	return 0;

}
void IdleTaskHook()	{
	
}


//fungsi task 1
static portTASK_FUNCTION(task_led, pvParameters )	{
	( void ) pvParameters; //just stop compiler warning
	FIO1DIR |= LED_STATUS; //bit 1.18 led utama modul rinjani
	for (;;)	{
	
		
		FIO1PIN ^= LED_STATUS;
		
		 
		vTaskDelay(500);
		
	}
}


//create aplikasi/task

void init_led_utama(void) {
	xTaskCreate(task_led, ( signed portCHAR * ) "Led",  (configMINIMAL_STACK_SIZE * 2) ,\
		 NULL, tskIDLE_PRIORITY - 2, ( xTaskHandle * ) &hdl_led );
		 
	FIO1SET |=LED_STATUS;  //matiin dulu pertama on
	
		 
		 
}




