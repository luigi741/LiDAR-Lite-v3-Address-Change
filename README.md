# README.md

## LiDAR-Lite v3 I2C Address Change

The point of this repo is show an example of how to change the LiDAR-Lite v3's
default address (which is 0x62) to your own which you would need in case you are
planning to use multiple LiDAR sensors as I was. 

I spent way too long trying to figure it out, I read Garmin's technical specifications
and operating manual for the device (which I also recommend download at this link: https://static.garmin.com/pumac/LIDAR_Lite_v3_Operation_Manual_and_Technical_Specifications.pdf)
and it outlines what you need to do to change the default address. Below you can find
those steps:

1. Read the two byte serial number from 0x96 (High byte 0x16 and low byte 0x17)
2. Write the serial number HIGH byte to 0x18
3. Write the serial number LOW byte to 0x19
4. Write the desired new I2C address to 0x1A
5. Write 0x08 to 0x1E to disable the default address

I did this just using the default Arduino Wire library and programmatically executing
the above steps reading and writing to the LiDAR's registers.

