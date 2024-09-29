
import network
import machine
import usocket as socket

# Configuration du point d'accès Wi-Fi
ssid = 'ValentinM'
password = '12341234'

# Configuration du serveur web
web_page = """<!DOCTYPE html>
<html>
<head>
    <title>ESP32 Web Server</title>
</head>
<body>
    <h1>Hello from ESP32!</h1>
</body>
</html>
"""

# Fonction pour configurer le point d'accès Wi-Fi
def connect_to_wifi(ssid, password):
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        print('Connexion au réseau WiFi...')
        wlan.connect(ssid, password)
        while not wlan.isconnected():
            pass
    print('Connecté au réseau WiFi')
    print('Adresse IP:', wlan.ifconfig()[0])

# Fonction principale pour gérer les requêtes HTTP
# Fonction principale pour gérer les requêtes HTTP
def web_server():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(('', 8080))
    s.listen(5)
    
    while True:
        conn, addr = s.accept()
        print('Nouvelle connexion depuis', addr)
        request = conn.recv(1024)
        conn.send('HTTP/1.1 200 OK\n')
        conn.send('Content-Type: text/html\n')
        conn.send('Connection: close\n\n')
        conn.sendall(web_page)
        conn.close()  # Fermez la connexion ici

# Connexion au Wi-Fi
connect_to_wifi(ssid, password)

# Démarrage du serveur web
web_server()
