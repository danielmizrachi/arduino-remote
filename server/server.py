from flask import Flask, render_template

def create_app(arduino, port=8080, debug=True):
  app = Flask(__name__)

  @app.route("/")
  def index():
    return render_template("index.html")

  @app.route("/toggle/<int:pin>")
  def toggle(pin):
    arduino.write(pin)
    return ""

  app.run(port=port, debug=debug, use_reloader=False)

  return app
