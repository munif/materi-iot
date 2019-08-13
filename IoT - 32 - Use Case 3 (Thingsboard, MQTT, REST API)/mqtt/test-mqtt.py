import paho.mqtt.client as paho
import os
import json
import time
from datetime import datetime

ACCESS_TOKEN = 'kuPyFpHiiMXOecZOuTwX'
broker = "18.221.254.87"
port = 1883

def on_publish(client, userdata, result):
    print("Data published to Thingsboard\n")
    pass

client1 = paho.Client("control1")
client1.on_publish = on_publish
client1.username_pw_set(ACCESS_TOKEN)
client1.connect(broker, port, keepalive=60)

while True:
    payload = "{"
    payload += "\"Humidity\": 60,"
    payload += "\"Temperature\": 25"
    payload += "}"

    ret = client1.publish("v1/devices/me/telemetry", payload)
    print("Please check Latest Telemetry field of your device")
    print(payload)
    time.sleep(5)
