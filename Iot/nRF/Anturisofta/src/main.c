/*
 * Copyright (c) 2020 Libre Solar Technologies GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 // :p
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
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

// integraatio

static const struct bt_le_adv_param *adv_param = BT_LE_ADV_PARAM(
	(BT_LE_ADV_OPT_CONN |
	 BT_LE_ADV_OPT_USE_IDENTITY), /* Connectable advertising and use identity address */
	800, /* Min Advertising Interval 500ms (800*0.625ms) */
	801, /* Max Advertising Interval 500.625ms (801*0.625ms) */
	NULL); /* Set to NULL for undirected advertising */

static struct k_work adv_work;
extern volatile int suunta;

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)
#define STACKSIZE 1024
#define PRIORITY 7
#define NOTIFY_INTERVAL 500

#define USER_LED1         	 	DK_LED1
#define USER_LED2          		DK_LED2
#define USER_LED3               DK_LED3
#define USER_LED4               DK_LED4

#define USER_BUTTON_1           DK_BTN1_MSK
#define USER_BUTTON_2           DK_BTN2_MSK
#define USER_BUTTON_3           DK_BTN3_MSK
#define USER_BUTTON_4           DK_BTN4_MSK

LOG_MODULE_REGISTER(MAIN, LOG_LEVEL_INF);


// integraatio
void send_data_thread(void)
{
	while (1) {
		/* Simulate data */
		struct Measurement m = readADCValue();
		/* Send notification, the function sends notifications only if a client is subscribed */
		my_lbs_send_sensor_notify(&m);
		printk("x = %d,  y = %d,  z = %d, d = %d \n",m.x,m.y,m.z,m.d);
		k_sleep(K_MSEC(NOTIFY_INTERVAL));
	}
}

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

static const struct bt_data sd[] = {
	BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_LBS_VAL),
};

static void adv_work_handler(struct k_work *work)
{
	int err = bt_le_adv_start(adv_param, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));

	if (err) {
		printk("Advertising failed to start (err %d)\n", err);
		return;
	}

	printk("Advertising successfully started\n");
}
static void advertising_start(void)
{
	k_work_submit(&adv_work);
}
static void recycled_cb(void)
{
	printk("Connection object available from previous conn. Disconnect is complete!\n");
	advertising_start();
}

static void on_connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		printk("Connection failed (err %u)\n", err);
		return;
	}

	printk("Connected\n");
}

static void on_disconnected(struct bt_conn *conn, uint8_t reason)
{
	printk("Disconnected (reason %u)\n", reason);

}

struct bt_conn_cb connection_callbacks = {
	.connected = on_connected,
	.disconnected = on_disconnected,
	.recycled = recycled_cb,
};

static void button_changed(uint32_t button_state, uint32_t has_changed)
{
	//printk("button_state = %d\n",button_state);
	//printk("has_changed = %d\n",has_changed);
	if ((has_changed & USER_BUTTON_1) && (button_state & USER_BUTTON_1)) 
	{
		printk("Nappi 1 alhaalla\n");
	}

	if ((has_changed & USER_BUTTON_2) && (button_state & USER_BUTTON_2)) 
	{
		suunta++;
		if (suunta > 5){
			suunta = 0;
		}
		
	}		
	
	if ((has_changed & USER_BUTTON_3) && (button_state & USER_BUTTON_3)) 
	{
		printk("Nappi 3 alhaalla\n");
	}		

	if ((has_changed & USER_BUTTON_4) && (button_state & USER_BUTTON_4)) 
	{
		printk("Nappi 4 alhaalla\n");
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

	err = bt_enable(NULL);
	if (err) {
		LOG_ERR("Bluetooth init failed (err %d)\n", err);
		return -1;
	}
	bt_conn_cb_register(&connection_callbacks);


	LOG_INF("Bluetooth initialized\n");
	k_work_init(&adv_work, adv_work_handler);
	advertising_start();
	
	return 0;
}

K_THREAD_DEFINE(send_data_thread_id, STACKSIZE, send_data_thread, NULL, NULL, NULL, PRIORITY, 0, 0);
