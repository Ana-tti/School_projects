#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <hal/nrf_saadc.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include "adc.h"
#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

LOG_MODULE_DECLARE(Lesson4_Exercise2);

static bool notify_mysensor_enabled;
static bool indicate_enabled;
static bool button_state;
static struct my_lbs_cb lbs_cb;
volatile int suunta = 0;

#if !DT_NODE_EXISTS(DT_PATH(zephyr_user)) || \
	!DT_NODE_HAS_PROP(DT_PATH(zephyr_user), io_channels)
#error "No suitable devicetree overlay specified"
#endif

#define DT_SPEC_AND_COMMA(node_id, prop, idx) \
	ADC_DT_SPEC_GET_BY_IDX(node_id, idx),

static const struct adc_dt_spec adc_channels[] = {
	DT_FOREACH_PROP_ELEM(DT_PATH(zephyr_user), io_channels,
			     DT_SPEC_AND_COMMA)
};


void printDebugInfo(void)
{
   printk("printing first adc_dt_spec structure contents for all channels\n");
   for(int i = 0;i<3;i++)
   {
   printk("adc_dt_spec structure, channel %d = \n",i);
   printk("Device pointer = %p\n",adc_channels[1].dev);
   printk("Channel Id = %d\n",adc_channels[i].channel_id);
   printk("Voltage reference = %d\n",adc_channels[i].vref_mv);
   printk("Resolution = %d\n",adc_channels[i].resolution);
   printk("Oversampling = %d\n",adc_channels[i].oversampling);
   printk("\n\n");
   }

}

int initializeADC(void)
{

    int err;
	
	for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) {
		if (!device_is_ready(adc_channels[i].dev)) {
			printk("ADC controller device not ready\n");
			return -1;
		}

		err = adc_channel_setup_dt(&adc_channels[i]);
		if (err < 0) {
			printk("Could not setup channel #%d (%d)\n", i, err);
			return -1;
		}
	}

    return 0;

}

struct Measurement readADCValue(void)
{
	int16_t buf;
    struct Measurement m;
    struct adc_sequence sequence = {
	  .buffer = &buf,

	  .buffer_size = sizeof(buf),
    };

    printk("ADC reading:\n");
	for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) 
    {
		int err;
        int32_t val_mv;
        // For debug use... 
		/*
        printk("- %s, channel %d: ",
		       adc_channels[i].dev->name,
		       adc_channels[i].channel_id);
        */

		(void)adc_sequence_init_dt(&adc_channels[i], &sequence);

		err = adc_read(adc_channels[i].dev, &sequence);
		if (err < 0) {
			printk("Could not read (%d)\n", err);
			continue;
		} else {
            if(i==0)
            {
                m.x = val_mv;
            }
            else if (i==1)
            {
               m.y = val_mv;
            }
            else if (i==2)
            {
                m.z = val_mv;
            }           
			//printk("%"PRId16, buf);
		}

		
		val_mv = buf;
		err = adc_raw_to_millivolts_dt(&adc_channels[i],&val_mv);
		if (err < 0) 
        {
			printk(" (value in mV not available)\n");
		} 
        else 
        {
			if(i==0)
            {
                m.x = val_mv;
            }
            else if (i==1)
            {
               m.y = val_mv;
            }
            else if (i==2)
            {
                m.z = val_mv;
            }           
            //printk(" = %"PRId32" mV\n", val_mv);
		}
		m.d = suunta;
	}
    return m;
}
/* STEP 4 - Define an indication parameter */
static struct bt_gatt_indicate_params ind_params;

/* STEP 3 - Implement the configuration change callback function */
static void mylbsbc_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
	indicate_enabled = (value == BT_GATT_CCC_INDICATE);
}

/* STEP 13 - Define the configuration change callback function for the MYSENSOR characteristic */
static void mylbsbc_ccc_mysensor_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
	notify_mysensor_enabled = (value == BT_GATT_CCC_NOTIFY);
}

// This function is called when a remote device has acknowledged the indication at its host layer
static void indicate_cb(struct bt_conn *conn, struct bt_gatt_indicate_params *params, uint8_t err)
{
	LOG_DBG("Indication %s\n", err != 0U ? "fail" : "success");
}
static ssize_t write_led(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf,
			 uint16_t len, uint16_t offset, uint8_t flags)
{
	LOG_DBG("Attribute write, handle: %u, conn: %p", attr->handle, (void *)conn);

	if (len != 1U) {
		LOG_DBG("Write led: Incorrect data length");
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
	}

	if (offset != 0) {
		LOG_DBG("Write led: Incorrect data offset");
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	if (lbs_cb.led_cb) {
		// Read the received value
		uint8_t val = *((uint8_t *)buf);

		if (val == 0x00 || val == 0x01) {
			// Call the application callback function to update the LED state
			lbs_cb.led_cb(val ? true : false);
		} else {
			LOG_DBG("Write led: Incorrect value");
			return BT_GATT_ERR(BT_ATT_ERR_VALUE_NOT_ALLOWED);
		}
	}

	return len;
}

static ssize_t read_button(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf,
			   uint16_t len, uint16_t offset)
{
	// get a pointer to button_state which is passed in the BT_GATT_CHARACTERISTIC() and stored in attr->user_data
	const char *value = attr->user_data;

	LOG_DBG("Attribute read, handle: %u, conn: %p", attr->handle, (void *)conn);

	if (lbs_cb.button_cb) {
		// Call the application callback function to update the get the current value of the button
		button_state = lbs_cb.button_cb();
		return bt_gatt_attr_read(conn, attr, buf, len, offset, value, sizeof(*value));
	}

	return 0;
}

/* LED Button Service Declaration */
BT_GATT_SERVICE_DEFINE(
	my_lbs_svc, BT_GATT_PRIMARY_SERVICE(BT_UUID_LBS),
	/* STEP 1 - Modify the Button characteristic declaration to support indication */
	BT_GATT_CHARACTERISTIC(BT_UUID_LBS_BUTTON, BT_GATT_CHRC_READ | BT_GATT_CHRC_INDICATE,
			       BT_GATT_PERM_READ, read_button, NULL, &button_state),
	/* STEP 2 - Create and add the Client Characteristic Configuration Descriptor */
	BT_GATT_CCC(mylbsbc_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

	BT_GATT_CHARACTERISTIC(BT_UUID_LBS_LED, BT_GATT_CHRC_WRITE, BT_GATT_PERM_WRITE, NULL,
			       write_led, NULL),
	/* STEP 12 - Create and add the MYSENSOR characteristic and its CCCD  */
	BT_GATT_CHARACTERISTIC(BT_UUID_LBS_MYSENSOR, BT_GATT_CHRC_NOTIFY, BT_GATT_PERM_NONE, NULL,
			       NULL, NULL),

	BT_GATT_CCC(mylbsbc_ccc_mysensor_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

);
/* A function to register application callbacks for the LED and Button characteristics  */
int my_lbs_init(struct my_lbs_cb *callbacks)
{
	if (callbacks) {
		lbs_cb.led_cb = callbacks->led_cb;
		lbs_cb.button_cb = callbacks->button_cb;
	}

	return 0;
}

/* STEP 5 - Define the function to send indications */
int my_lbs_send_button_state_indicate(bool button_state)
{
	if (!indicate_enabled) {
		return -EACCES;
	}
	ind_params.attr = &my_lbs_svc.attrs[2];
	ind_params.func = indicate_cb; // A remote device has ACKed at its host layer (ATT ACK)
	ind_params.destroy = NULL;
	ind_params.data = &button_state;
	ind_params.len = sizeof(button_state);
	return bt_gatt_indicate(NULL, &ind_params);
}

/* STEP 14 - Define the function to send notifications for the MYSENSOR characteristic */
int my_lbs_send_sensor_notify(const struct Measurement *m)
{
	if (!notify_mysensor_enabled) {
		return -EACCES;
	}

	return bt_gatt_notify(NULL, &my_lbs_svc.attrs[7], m, sizeof(struct Measurement));
}