# wifi.py

import network
from time import sleep

def connect_wifi(ssid, password, max_retries=5):
    station = network.WLAN(network.STA_IF)
    station.active(False)
    station.active(True)
    station.scan()
    station.connect(ssid, password)

    print("Connecting to", ssid)

    retries = 0
    while not station.isconnected() and retries < max_retries:
        print('.', end=" ")
        sleep(1)
        retries += 1

    if station.isconnected():
        print("\nConnected to", ssid)
        return station.ifconfig()[0]
    else:
        print("\nFailed to connect to", ssid)
        return None
