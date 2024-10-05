# Options de compilation pour le compilateur C (gcc)
CFLAGS = -Wall -g -Wextra -Werror -Wno-unused-variable -pedantic
# Options de compilation pour le compilateur Java (javac)
JAVACFLAGS = -d build
JAVAC = javac
CC = gcc

# Variables pour les ports et adresses IP
PORT_TCP = 4526
PORT_UDP = 5245

HOST_BAR = localhost
HOST_FOURNISSEUR = localhost

# Liste des fichiers sources en C
C_SOURCES = Bar/Barman/barman.c \
            Bar/Barman/controle/controle.c \
            Bar/Barman/controle/utils/utils.c \
            Bar/Barman/controle/udp/udp.c \
            Bar/Barman/controle/cleaning/cleaning.c \
            Bar/Barman/controle/mutex/mutex.c \
            Bar/Barman/main/main.c \
            Bar/Barman/main/scheduler/scheduler.c \
            Bar/Barman/communication/communication.c \
            Bar/Barman/communication/handler/handler.c \
            Bar/Tireuses/tireuses.c \
            Clients/tcp/tcp.c \
            Clients/clients.c

# Liste des fichiers sources en Java
J_SOURCES = Fournisseur/IBiere.java \
            Fournisseur/Biere.java \
            Fournisseur/Fournisseur.java 

# Liste des fichiers objets générés à partir des fichiers sources en C
OBJ_FILES = $(patsubst %.c,build/%.o,$(C_SOURCES))

# Liste des fichiers .class générés à partir des fichiers sources en Java
J_OBJ_FILES = $(patsubst %.java,build/%.class,$(J_SOURCES))

# Règle pour compiler les fichiers sources en C en fichiers objets
build/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Règle pour compiler les fichiers sources en Java en fichiers .class
build/%.class: %.java
	@mkdir -p $(dir $@)
	@$(JAVAC) $(JAVACFLAGS) Fournisseur/Biere.java Fournisseur/IBiere.java Fournisseur/Fournisseur.java

# Règle 'all' pour compiler et construire le projet
all: $(OBJ_FILES) $(J_OBJ_FILES) 	
	@$(CC) build/Bar/Tireuses/tireuses.o build/Bar/Barman/controle/cleaning/cleaning.o build/Bar/Barman/controle/udp/udp.o build/Bar/Barman/controle/utils/utils.o build/Bar/Barman/controle/mutex/mutex.o build/Bar/Barman/controle/controle.o -o build/controle -pthread -lrt
	@$(CC) build/Bar/Barman/main/main.o build/Bar/Barman/main/scheduler/scheduler.o build/Bar/Barman/controle/mutex/mutex.o build/Bar/Barman/controle/udp/udp.o build/Bar/Barman/controle/utils/utils.o build/Bar/Tireuses/tireuses.o build/Bar/Barman/controle/cleaning/cleaning.o -o build/main -pthread
	@$(CC) build/Clients/clients.o build/Clients/tcp/tcp.o build/Bar/Barman/controle/utils/utils.o -o build/clients -pthread
	@$(CC) build/Bar/Barman/communication/communication.o build/Bar/Barman/communication/handler/handler.o -o build/communication -pthread
	@$(CC) build/Bar/Barman/barman.o -o build/barman

# Règle 'rmi' pour lancer le rmiregistry
rmi:
	@echo "lancement du rmiregistry..."
	@cd build && gnome-terminal -- bash -c "rmiregistry; $SHELL"

# Règle 'fournisseur' pour lancer le fournisseur Java
fournisseur:
	@echo "ouverture du service DeLaChoppe..."
	@cd build && java Fournisseur

# Règle 'clients' pour compiler et lancer les clients en C
clients: Clients/clients.c Clients/tcp/tcp.c
	@echo "arrivée d'un client..."
	@./build/clients $(HOST_BAR) $(PORT_TCP)

# Règle 'bar' pour lancer le barman en C
bar :
	@echo "ouverture du bar..."
	./build/barman $(PORT_TCP) $(HOST_BAR) $(PORT_UDP) $(HOST_FOURNISSEUR)

# Règle 'clean' pour nettoyer les fichiers générés lors de la compilation et la construction
clean:
	@rm -rf build
