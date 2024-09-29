# oled.py

from machine import Pin
import ssd1306

def display_oled(oled, message, x, y, erase_first):
    message = str(message)  # Make sure it is a string in utf-8
    try:
        if erase_first == 1:
            oled.fill(0)
        oled.text(message, x, y)
        oled.show()
    except OSError as er:
        print('i2c error')
