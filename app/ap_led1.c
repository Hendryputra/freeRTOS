/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "hardware.h"

#include "sys.h"
#include "ap_led1.h"


xTaskHandle hdl_relay;





//fungsi task 2
static portTASK_FUNCTION(task_relay, pvParameters )	{
	( void ) pvParameters;
	
	FIO1DIR |= RLY_2; //bit 1.1 led utama modul rinjani
	
	for (;;)	{
	
		
		FIO1PIN ^= RLY_2;
		
		 
		vTaskDelay(300);
		
		
	}
}



void init_relay(void) {
	xTaskCreate(task_relay, ( signed portCHAR * ) "relay",  (configMINIMAL_STACK_SIZE * 2) ,\
		 NULL, tskIDLE_PRIORITY - 1, ( xTaskHandle * ) &hdl_relay );
	
	
}
