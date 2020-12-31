'''
 * Remote controller for a connected Arduino, built in Windows
 * Copyright (c) 2020 Daniel Mizrachi <mail@danmiz.net>
'''

import serial
from serial.tools import list_ports

class Arduino(serial.Serial):
  VENDOR_ID = 9025

  def __init__(self, baud=9600, read_timeout=1, write_timeout=None):
    super().__init__(None, baud, timeout=10, write_timeout=write_timeout)
    self.connected = False

    # Look for the first connected Arduino
    ports = list_ports.comports()
    device = ''
    for p in ports:
      if p.vid == self.VENDOR_ID:
        device = p.device
        break

    # Warn and return if none found
    if device == '':
      print('Warning: no connected Arduino found')
    else:
      # Otherwise, set port and open
      self.port = device
      self.open()

      # Block until Arduino confirms it's ready by sending number of pins available for control
      pin_count = self.read()
      self.timeout = read_timeout
      self.pin_count = int.from_bytes(pin_count, 'little')
      self.connected = True

      print('Arduino connected on port', device, 'with', self.pin_count, 'operable pins')

  def write(self, data):
    if type(data) == str:
      encoded = bytes(data, 'ascii')
    elif type(data) == int:
      encoded = bytes([data])
    else:
      encoded = bytes(data)

    return super().write(encoded)

def close(self):
  self.connected = False
  super().close()
