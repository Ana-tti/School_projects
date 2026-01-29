#ifndef OMA_GATT_H
#define OMA_GATT_H
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


#define BT_UUID_MY_SERVICE_VAL \
    BT_UUID_128_ENCODE(0x12345678, 0x90AB, 0xCDEF, 0x1122, 0x334455667788)

#define BT_UUID_MY_SENSOR_VAL \
    BT_UUID_128_ENCODE(0x21436587, 0x09BA, 0xDCFE, 0xEFCD, 0xAB9078563412)

#define BT_UUID_MY_SERVICE BT_UUID_DECLARE_128(BT_UUID_MY_SERVICE_VAL)
#define BT_UUID_MY_SENSOR    BT_UUID_DECLARE_128(BT_UUID_MY_SENSOR_VAL)

int initializeADC(void);
struct Measurement readADCValue(void);
void printDebugInfo(void);
int my_service_send_sensor_notify(const struct Measurement *m);

struct Measurement
{
   uint32_t x;
   uint32_t y;
   uint32_t z;
   uint32_t d;
};


#ifdef __cplusplus
}
#endif

#endif /* OMA_GATT_H_ */