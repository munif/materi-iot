import paho.mqtt.client as paho
import os
import json
import time
from datetime import datetime

from random import random

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
    rand_humidity = random() * 10 + 60
    rand_temperature = random() * 5 + 25

    payload = "{"
    payload += "\"Humidity\": " + str(rand_humidity) +","
    payload += "\"Temperature\": " + str(rand_temperature)
    payload += "}"

    ret = client1.publish("v1/devices/me/telemetry", payload)
    print("Please check Latest Telemetry field of your device")
    print(payload)
    time.sleep(5)
