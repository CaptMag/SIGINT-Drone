import asyncio, re
from bleak import *

async def main():
    async with BleakScanner() as scanner:

        devices = await scanner.discover(10.0, return_adv=True)
        n = 0
        for d in devices.items():
           n += 1
           count = f"[+] Real BLE Discovered! Device {n}"
           result = f"{devices[d][1]}"
           result.strip()

           if "local_name=" in list:
               print(count)
               device_name = result.split("local_name=")[1]
               print(f"Local Name: {device_name}\n")


if __name__ == "__main__":
    asyncio.run(main())

# password = ''
# encrypted = input ("Enter the password you want to decrypt")
# x = 0

# for i in encrypted:
#     password = password + chr (ord(i) - x)
#     x = x + 1

# print(password)