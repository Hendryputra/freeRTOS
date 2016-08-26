
#ifndef __HARDWARE__
#define __HARDWARE__

#include "FreeRTOS.h"
#include "hardware.h"
#include "../modul/GPIO/gpio.h"

//#include "uip/uip_task.c"

/*
 * dipanggil pertama kali ketika booting 
 * 
 */
void setup_hardware() {
	sysInit();
	
	/* USB Power dinyalakan supaya memory USB bisa dipakai */
	PCONP   |= 0x80000000;
	FIO1DIR  = 0xFFFFFFFF;
	
	#ifdef PAKAI_RELAY
		setup_relay();
	#endif
	
	#ifdef PAKAI_LED_UTAMA
		setup_led_utama();
	#endif
	
	#ifdef PAKAI_BACKLIT
		setup_backlit();
	#endif

	#ifdef PAKAI_ADC
		setup_adc();
	//	init_ss1();
	#endif
	
	#ifdef CEK_BLINK
		blink_led();
	#endif

	#ifdef PAKAI_SHELL
		#ifdef PAKAI_KONTROL_RTC
			#ifdef PAKAI_MODE_POWER
			if (status_power()==0)
			#endif
				xSerialPortInitMinimal( BAUD_RATE_SHELL, configMINIMAL_STACK_SIZE  );
		#else
			xSerialPortInitMinimal( BAUD_RATE_SHELL, configMINIMAL_STACK_SIZE  );
		#endif
	#endif
	
	#ifdef PAKAI_I2C
		setup_gpio_i2c();
	#endif
	
	#ifdef PAKAI_GPIO_DIMMER
		setup_timer2();
	#endif
	
	#ifdef PAKAI_TIMER_2
		setup_timer2();
	#endif
	
	#ifdef PAKAI_SERIAL_3
		/* PCONP enable UART3 */
		
		#ifdef PAKAI_SERIAL_3_P0
			setup_serial3_P0();
		#endif
		
		/* PCLK UART3, PCLK = CCLK */
		//PCLKSEL1 &= ~(BIT(18) | BIT(19));
		//PCLKSEL1 |= BIT(18);
		
	#endif

	#ifdef PAKAI_SERIAL_2			
		/* PCONP enable UART2 */

		
		#ifdef PAKAI_SERIAL_2_P0
			setup_serial2_P0();
		#endif
		
		/* PCLK UART2, PCLK = CCLK */
		//PCLKSEL1 &= ~(BIT(16) | BIT(17));
		//PCLKSEL1 |= BIT(16);
		
		/* init TX2, RX2 */
		//PINSEL0 |= (BIT(20) | BIT(22));
	#endif
	
	#ifdef PAKAI_ADC_ORI
		setup_adc_ori();
	#endif

}

void init_hardware()	{
	int hsl = 0;
}
//***************************************************************/
/*
 *						APLIKASI ada di sini 
 */
//***************************************************************/

void dele(int dd)	{
	int g;
	int i;
	int dum;
		for (i=0; i<dd; i++)	{
		dum = FIO0DIR;
	}
}

#ifdef CEK_BLINK
	void blink_led(void)	{
		int t=0;
		while(t<5)
		{
			dele(1000000);
			FIO0CLR = LED_UTAMA;
			dele(1000000);
			FIO0SET = LED_UTAMA;
			t++;
		}
	}
#endif

#endif
