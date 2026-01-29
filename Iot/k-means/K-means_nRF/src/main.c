
#include <zephyr/logging/log.h>
#include <dk_buttons_and_leds.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>
#include "adc.h"
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include "confusion.h"
#include <math.h>

#define USER_LED1         	 	DK_LED1
#define USER_LED2          		DK_LED2
#define USER_LED3               DK_LED3
#define USER_LED4               DK_LED4

#define USER_BUTTON_1           DK_BTN1_MSK
#define USER_BUTTON_2           DK_BTN2_MSK
#define USER_BUTTON_3           DK_BTN3_MSK
#define USER_BUTTON_4           DK_BTN4_MSK

#define DEBUG 0  // 0 = changes direction when button 3 is pressed
                 // 1 = fake 100 measurements done to each 6 directions when 3 pressed.
volatile int direction = 0;	// 0 = x direction high
							// 1 = x directon low	
							// 2 = y direction high
							// 3 = y direction low
							// 4 = z direction high
							// 5 = z direction low
                				 

LOG_MODULE_REGISTER(MAIN, LOG_LEVEL_INF);

extern int CM[6][6];
extern int measurements_array[6][3];

static void button_changed(uint32_t button_state, uint32_t has_changed)
{
	if ((has_changed & USER_BUTTON_1) && (button_state & USER_BUTTON_1)) 
	{
		direction++;
		if (direction > 5){
			direction = 0;
		}

		printk("Suunta: %d\n",direction);
		struct Measurement m = readADCValue();
		printk("x = %d, y= %d, z = %d\n",m.x,m.y,m.z);

	}

	if ((has_changed & USER_BUTTON_2) && (button_state & USER_BUTTON_2)) 
	{
		
		resetConfusionMatrix();
		printConfusionMatrix();
	}		
	
	if ((has_changed & USER_BUTTON_3) && (button_state & USER_BUTTON_3)) 
	{
		makeOneClassificationAndUpdateConfusionMatrix(direction);
		printConfusionMatrix();

		
	}		

	if ((has_changed & USER_BUTTON_4) && (button_state & USER_BUTTON_4)) 
	{
		
		for (int i = 0; i <6; i++){
			struct Measurement m = readADCValue();
			measurements_array[i][0] = m.x;
			measurements_array[i][1] = m.y;
			measurements_array[i][2] = m.z;
			//printk("luetut mittaustulokset taulukkoon: x = %d, y = %d, z = %d \n",measurements[i][0],measurements[i][1],measurements[i][2]);
			calculateDistanceToAllCentrePointsAndSelectWinner(measurements_array[i][0],measurements_array[i][1],measurements_array[i][2]);
		}
	}		
}


int main(void)
{
	int err;
	err = dk_leds_init();
	if (err) {
		LOG_ERR("LEDs init failed (err %d)\n", err);
		return -1;
	}

	err = dk_buttons_init(button_changed);
	if (err) {
		printk("Cannot init buttons (err: %d)\n", err);
		return -1;
	}
	
	
	if(initializeADC() != 0)
	{
	printk("ADC initialization failed!");
	return -1;
	}

	while (1) 
	{
		//struct Measurement m = readADCValue();
		//printk("x = %d,  y = %d,  z = %d\n",m.x,m.y,m.z);
		
		k_sleep(K_MSEC(1000));
		
		dk_set_led_on(USER_LED1);
		dk_set_led_on(USER_LED2);
		dk_set_led_on(USER_LED3);
		dk_set_led_on(USER_LED4);
		 
		k_sleep(K_MSEC(1000));
		
		dk_set_led_off(USER_LED1);
		dk_set_led_off(USER_LED2);
		dk_set_led_off(USER_LED3);
		dk_set_led_off(USER_LED4);


	}
	return 0;
}


