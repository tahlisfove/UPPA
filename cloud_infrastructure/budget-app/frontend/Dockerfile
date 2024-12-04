# Étape 1 : Construction de l'application React
# Utilisation de l'image officielle Node.js
FROM node:16 AS build

# Définition du répertoire de travail
WORKDIR /app

# Empêcher les notifications de mise à jour de npm
ENV NO_UPDATE_NOTIFIER=true

# Copier le fichier package.json pour installer les dépendances
COPY ./frontend/package.json ./

# Installer les dépendances
RUN npm install

# Copier le reste de l'application
COPY ./frontend/ .

# Exécuter les dépendances
RUN npm run build

# Étape 2 : Configuration du serveur Nginx pour servir l'application
# Utilisation de l'image Nginx basée sur Alpine Linux
FROM nginx:alpine

# Copier vers le répertoire par défaut de Nginx pour les fichiers HTML
COPY --from=build /app/build /usr/share/nginx/html

# Exposer le port sur lequel l'application écoute
EXPOSE 3017

# Démarrer l'application "daemon off" pour que le processus reste en avant-plan
CMD ["nginx", "-g", "daemon off;"]