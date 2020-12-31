from arduino_controller import Arduino
import server.server as server

arduino = Arduino()

app = server.create_app(arduino)
