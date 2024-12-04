# Utilisation de l'image officielle Node.js
FROM node:16

# Définition du répertoire de travail
WORKDIR /app

# Copier le fichier package.json pour installer les dépendances
COPY package.json ./

# Installer les dépendances
RUN npm install

# Copier le reste de l'application
COPY . .

# Exposer le port sur lequel l'application écoute
EXPOSE 3002

# Démarrer l'application
CMD ["node", "auth.js"]