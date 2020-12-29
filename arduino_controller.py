import serial
from serial.tools import list_ports

ARDUINO_VENDOR_ID = 9025
BAUD = 9600

def connect():
  # Look for the first connected Arduino
  ports = list_ports.comports()
  device = ""
  for p in ports:
    if p.vid == ARDUINO_VENDOR_ID:
      device = p.device
      break

  # Exit if none found
  if device == "":
    print("No Arduino found, exiting")
    exit()

  # Otherwise, init serial port
  arduino = serial.Serial(device, BAUD, timeout=2)

  return arduino
