import paho.mqtt.client as mqtt 
import time

mqtt_server = "test.mosquitto.org"
mqtt_port = 1883
mqtt_publish = "esp8266/PubA" 
mqtt_subscribe = "esp8266/PubB" 

received_message = None

def on_message(client, userdata, msg):
    global received_message
    received_message = msg.payload.decode()
    print(f"Message received on topic {msg.topic}: {received_message}")

# init client 
client = mqtt.Client()
client.on_message = on_message

# connect to the client 
client.connect(mqtt_server, mqtt_port, keepalive=60) 

client.loop_start() 

client.subscribe(mqtt_subscribe)

# publish a message from the user 
user_message = input(f"Enter a message to publish to {mqtt_publish}: ")
client.publish(mqtt_publish, user_message) 

start_time = time.time() 

# wait for 10 seconds for a message to be received 
while time.time() - start_time < 10:
    if received_message:
        break
    time.sleep(0.1)
