import wifi

pin16 = Pin(16, Pin.OUT)
pin16.value(1)

try:
    i2c = machine.SoftI2C(scl=Pin(15), sda=Pin(4))
    oled = ssd1306.SSD1306_I2C(128, 64, i2c)
    oled.fill(0)
    oled.text('From MicroPython', 0, 0)
    oled.text('Hello BG', 0, 8)
    oled.show()
    if wifi.station.isconnected() == True:
        oled.text('Connected', 0, 16)
        oled.text(wifi.station.ifconfig()[0], 0, 24)
        oled.show()    
except OSError as er:
     print('i2c error')
     
def display_oled(m, x, y, erase_first):
    m = str(m) #make sure it is string in utf-8
    try:
        if erase_first==1:
            oled.fill(0)
        oled.text(m, x, y)
        oled.show()
    except OSError as er:
        print('i2c error')
     
def welcome_msg():
    display_oled('From MicroPython', 0, 0, 1)
    display_oled('Hello BG', 0, 8, 0)
    if wifi.station.isconnected() == True:
        display_oled('Connected', 0, 16, 0)
        display_oled(wifi.station.ifconfig()[0], 0, 24, 0)
        
if __name__ == '__main__':
    welcome_msg()
