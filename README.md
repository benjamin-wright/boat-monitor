# Boat Monitor

## PreReqs
- PlatformIO extension

## To Build
- Remove Arduino from power
- Add jumper to GND and B1 pins
- Plug in Arduino to USB
- Uncomment `upload_protocol` in `platformio.ini`
- In PlatformIO section
  - PlatformIO / Platform / Build Filesystem Image
  - PlatformIO / Platform / Upload Filesystem Image
- Remove Adruino from power
- Remove jumper
- Plug in Arduino to USB
- Recomment `upload_protocol` in `platformio.ini`
- In PlatformIO section
  - PlatformIO / General / Upload