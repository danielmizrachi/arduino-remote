'''
 * Inits Arduino connection and webserver for remote control
 * Copyright (c) 2020 Daniel Mizrachi <mail@danmiz.net>
'''

from dotenv import load_dotenv
from arduino_controller import Arduino
import server.server as server

load_dotenv()
arduino = Arduino()
app = server.create_app(arduino)
