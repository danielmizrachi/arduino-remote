import serial
from serial.tools import list_ports

class Arduino(serial.Serial):
  VENDOR_ID = 9025

  def __init__(self, baud=9600, read_timeout=10, write_timeout=None):
    super().__init__(None, baud, timeout=read_timeout, write_timeout=write_timeout)

    # Look for the first connected Arduino
    ports = list_ports.comports()
    device = ""
    for p in ports:
      if p.vid == self.VENDOR_ID:
        device = p.device
        break

    # Exit if none found
    if device == "":
      print("No Arduino found, exiting")
      exit()

    # Otherwise, set port and open
    self.port = device
    self.open()

    # Block until Arduino confirms it's ready by sending one byte
    self.read()

  def write(self, data):
    if type(data) == str:
      encoded = bytes(data, "ascii")
    elif type(data) == int:
      encoded = bytes([data])
    else:
      encoded = bytes(data)

    return super().write(encoded)
