'''
 * Inits Arduino connection and webserver for remote control
 * Copyright (c) 2020 Daniel Mizrachi <mail@danmiz.net>
'''

from arduino_controller import Arduino
import server.server as server

arduino = Arduino()
app = server.create_app(arduino)
