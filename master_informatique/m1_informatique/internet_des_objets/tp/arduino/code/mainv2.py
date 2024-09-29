# main.py

import machine
from machine import Pin
import ssd1306
from wifi import connect_wifi
from oled import display_oled

ssid = 'ValentinM'
password = '12341234'

# Initialize OLED display
i2c = machine.SoftI2C(scl=Pin(15), sda=Pin(4))
oled = ssd1306.SSD1306_I2C(128, 64, i2c)

def welcome_msg():
    display_oled(oled, 'From MicroPython', 0, 0, 1)
    display_oled(oled, 'Hello BG', 0, 8, 0)

    connected_ssid = connect_wifi(ssid, password)  # Tentative de connexion au WiFi
    if connected_ssid:
        display_oled(oled, 'Connected', 0, 16, 0)
        display_oled(oled, connected_ssid, 0, 24, 0)

if __name__ == '__main__':
    welcome_msg()
