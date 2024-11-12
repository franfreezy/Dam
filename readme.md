Dam monitoring system
pi script

import paho.mqtt.client as mqtt

# MQTT Broker details
mqttServer = "public.shiftr.io"
mqttPort = 1883
mqttUser = "logistics"        # Replace with your username if applicable
mqttPassword = "uZlp3Dbsk6wYqWGe"  # Replace with your password if applicable
topic = "freezy/damsystem"

# Callback when connected to MQTT broker
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
        client.subscribe(topic)  # Subscribe to the topic
    else:
        print("Failed to connect, return code %d\n", rc)

# Callback when a message is received from the broker
def on_message(client, userdata, msg):
    print(f"Message received on topic {msg.topic}: {msg.payload.decode()}")
    # Process the received data (e.g., save to file, trigger an action, etc.)
    # For example, to save to a file:
    with open("received_data.txt", "a") as file:
        file.write(f"{msg.topic}: {msg.payload.decode()}\n")

# Set up the MQTT client
client = mqtt.Client("RaspberryPiClient")
client.username_pw_set(mqttUser, mqttPassword)
client.on_connect = on_connect
client.on_message = on_message

# Connect to the MQTT broker
client.connect(mqttServer, mqttPort)

# Run the network loop
client.loop_forever()