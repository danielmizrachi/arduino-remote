'''
 * Webserver serving Arduino remote control UI
 * Copyright (c) 2020 Daniel Mizrachi <mail@danmiz.net>
'''

from flask import Flask, render_template

def create_app(arduino, port=8080, debug=True):
  app = Flask(__name__)

  @app.route('/')
  def index():
    return render_template('index.jinja', arduino=arduino)

  @app.route('/toggle/<int:pin>')
  def toggle(pin):
    arduino.write(pin)

    bit_states = arduino.read(arduino.pin_count)
    states = [bool(bit) for bit in bit_states]

    return { 'states': states }

  app.run('0.0.0.0', port, debug, use_reloader=False)

  return app
