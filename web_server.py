import arduino_controller as controller
from time import sleep

arduino = controller.Arduino()

arduino.write(0)

arduino.close()
