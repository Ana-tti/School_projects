import argparse
import asyncio
import logging
import struct
import mysql.connector
from db_conf import DB_CONF
from datetime import datetime
from typing import Optional
from bleak import BleakClient, BleakScanner
from bleak.backends.characteristic import BleakGATTCharacteristic

logger = logging.getLogger(__name__)

class Args(argparse.Namespace):
    name: Optional[str]
    address: Optional[str]
    macos_use_bdaddr: bool
    characteristic: str
    debug: bool
def save_to_mysql(x,y,z,d):
    try:
        conn = mysql.connector.connect(**DB_CONF)
        cur = conn.cursor()
        
        sql = """
        INSERT INTO rawdata (sensorvalue_a,sensorvalue_b ,sensorvalue_c, sensorvalue_d)
        VALUES (%s, %s, %s, %s)
        """
        cur.execute(sql, (x, y, z, d))
        conn.commit()

    except mysql.connector.Error as err:
        print(f"MySQL-virhe: {err}")
    finally:
        try:
            cur.close()
            conn.close()
        except:
            pass

def notification_handler(characteristic: BleakGATTCharacteristic, data: bytearray):
    """Simple notification handler which prints the data received."""
   #logger.info("%s: %r", characteristic.description, data)
    x, y, z, d = struct.unpack("<llll", data)
    print(f"{characteristic.description} decoded: x={x}, y={y}, z={z}, d={d}")
    logger.info("%s decoded: x=%d, y=%d, z=%d, d=%d", characteristic.description, x, y, z, d)
   # timestamp = datetime.now().isoformat()
   # with open("measurements.csv","a") as f:
   #     f.write(f"{timestamp},{x},{y},{z},{d}\n")
    save_to_mysql(x,y,z,d)

async def main(args: Args):
    logger.info("starting scan...")

    if args.address:
        device = await BleakScanner.find_device_by_address(
            args.address, cb={"use_bdaddr": args.macos_use_bdaddr}
        )
        if device is None:
            logger.error("could not find device with address '%s'", args.address)
            return
    elif args.name:
        device = await BleakScanner.find_device_by_name(
            args.name, cb={"use_bdaddr": args.macos_use_bdaddr}
        )
        if device is None:
            logger.error("could not find device with name '%s'", args.name)
            return
    else:
        raise ValueError("Either --name or --address must be provided")

    logger.info("connecting to device...")

    async with BleakClient(device) as client:
        logger.info("Connected")

        await client.start_notify(args.characteristic, notification_handler)
        await asyncio.sleep(5.0)
        await client.stop_notify(args.characteristic)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    device_group = parser.add_mutually_exclusive_group(required=True)

    device_group.add_argument(
        "--name",
        metavar="<name>",
        help="the name of the bluetooth device to connect to",
    )
    device_group.add_argument(
        "--address",
        metavar="<address>",
        help="the address of the bluetooth device to connect to",
    )

    parser.add_argument(
        "--macos-use-bdaddr",
        action="store_true",
        help="when true use Bluetooth address instead of UUID on macOS",
    )

    parser.add_argument(
        "characteristic",
        metavar="<notify uuid>",
        help="UUID of a characteristic that supports notifications",
    )

    parser.add_argument(
        "-d",
        "--debug",
        action="store_true",
        help="sets the log level to debug",
    )

    args = parser.parse_args(namespace=Args())

    log_level = logging.DEBUG if args.debug else logging.INFO
    logging.basicConfig(
        level=log_level,
        format="%(asctime)-15s %(name)-8s %(levelname)s: %(message)s",
    )

    asyncio.run(main(args))
