from time import sleep
import network

ssid = 'ValentinM'
password = '12341234'

station = network.WLAN(network.STA_IF)
station.active(False)
station.active(True)
station.scan()
station.connect(ssid, password)

print("Connecting to ", ssid)

while station.isconnected() == False:
    print('.', end = " ")
    sleep(1)

print('')
print(station.ifconfig())
