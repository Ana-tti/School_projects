#include "oma_gatt.h"
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <hal/nrf_saadc.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <dk_buttons_and_leds.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

LOG_MODULE_REGISTER(oma_gatt);

static bool notify_mysensor_enabled;
volatile int direction = 0;
static struct Measurement sensor_value;


#define BT_UUID_CHAR_USER_DESC  BT_UUID_DECLARE_16(0x2901)

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

static void my_sensorbc_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
	notify_mysensor_enabled = (value == BT_GATT_CCC_NOTIFY);
}

// servicen ja sille karakteristiikan määritys
BT_GATT_SERVICE_DEFINE( oma_gatt_svc, BT_GATT_PRIMARY_SERVICE(BT_UUID_MY_SERVICE),

    BT_GATT_CHARACTERISTIC(BT_UUID_MY_SENSOR,
		                   BT_GATT_CHRC_NOTIFY | BT_GATT_CHRC_INDICATE | BT_GATT_CHRC_READ,
						   BT_GATT_PERM_READ,
						   NULL, NULL, &sensor_value),
	BT_GATT_CCC(my_sensorbc_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

);

int my_service_send_sensor_notify(const struct Measurement *m)
{
	if (!notify_mysensor_enabled) {
		return -EACCES;
	}
	sensor_value = *m;

	return bt_gatt_notify(NULL, &oma_gatt_svc.attrs[2], &sensor_value, sizeof(sensor_value));
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
		m.d = direction;
	}
    return m;
}