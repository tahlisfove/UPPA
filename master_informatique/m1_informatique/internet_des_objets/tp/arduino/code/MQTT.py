import time
from umqtt.simple import MQTTClient
import network

# Replace these values with your network and MQTT broker information
ssid = "ValentinM"
password = "12341234"
mqtt_server = "test.mosquitto.org"
topicin = "UPPA/test"
topicout = "UPPA/Duboue/S25/temp"
msgTemp = "22.5"

# Function to connect to Wi-Fi
def connect_wifi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        print("Connecting to WiFi...")
        wlan.connect(ssid, password)
        while not wlan.isconnected():
            pass
    print("Connected to WiFi")
    print("IP address:", wlan.ifconfig()[0])

# Callback function to handle incoming MQTT messages
def callback(topic, msg):
    print("Message arrived [{}] {}".format(topic, msg.decode())

# Connect to Wi-Fi
connect_wifi()

# Create an MQTT client
client = MQTTClient("ESP8266Client", mqtt_server)
client.set_callback(callback)

# Connect to the MQTT broker
client.connect()

# Main loop
while True:
    try:
        # Check for incoming MQTT messages
        client.check_msg()

        # Publish a message
        print("Publishing: status=", end='')
        e = client.publish(topicout, msgTemp)
        print(e)
        
        # Delay before publishing again
        time.sleep(7.5)

    except Exception as e:
        print("Exception:", e)

# Disconnect from MQTT broker and Wi-Fi (not reached in this code)
client.disconnect()
