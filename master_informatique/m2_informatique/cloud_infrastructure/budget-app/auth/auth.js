// Charge les variables d'environnement à partir du fichier .env
require('dotenv').config();

// Stratégie OAuth 2.0 pour l'authentification Google
const GoogleStrategy = require('passport-google-oauth20').Strategy;

// Framework pour créer des applications web en Node.js
const express = require('express');
// Middleware pour gérer les sessions
const session = require('express-session');
// Middleware pour analyser les cookies
const cookieParser = require('cookie-parser');
// Middleware pour activer les CORS
const cors = require('cors');

// Middleware pour l'authentification
const passport = require('passport');
// Création de l'application Express
const app = express();
// Définition du port
const port = 3002;


/*******/


// Lancement du service
app.listen(port, () => {
  console.log(`Auth service listening at http://localhost:${port}`);
});


/*******/


// Configuration de CORS
app.use(cors({
  origin: 'http://localhost:3017',
  methods: ['GET', 'POST'],
  credentials: true,
}));


/******/


// Configuration de Passport.js pour l'authentification Google OAuth
passport.use(new GoogleStrategy({
  clientID: process.env.GOOGLE_CLIENT_ID,
  clientSecret: process.env.GOOGLE_CLIENT_SECRET,
  callbackURL: "http://localhost:3002/auth/google/callback"
}, (token, tokenSecret, profile, done) => {
  // Fonction appelée après une authentification réussie
  return done(null, profile);
}));


/******/


// Sérialisation de l'utilisateur dans la session
passport.serializeUser((user, done) => {
  done(null, user);
});


/******/


// Désérialisation de l'utilisateur depuis la session
passport.deserializeUser((obj, done) => {
  done(null, obj);
});


/******/


// Middlewares pour la gestion des cookies et des sessions
app.use(cookieParser());
app.use(session({
  secret: 'secret_key',
  resave: false,
  saveUninitialized: true,
  cookie: { httpOnly: true }
}));
// Initialise Passport.js
app.use(passport.initialize());
// Permet à Passport de gérer les sessions
app.use(passport.session());


/*******/


// Démarrage de l'authentification Google
app.get('/auth/google', passport.authenticate('google', { scope: ['profile', 'email'] }));


/******/


// Callback après l'authentification Google
app.get('/auth/google/callback', 
  passport.authenticate('google', { failureRedirect: '/' }),
  (req, res) => {
    // Si l'authentification réussit, configure un cookie et redirige vers le frontend
    res.cookie('sessionid', req.user.id, {
      httpOnly: true,
      sameSite: 'None',
      secure: false,
      domain: 'localhost',
      path: '/'
    });
    // Redirection vers l'interface utilisateur
    res.redirect('http://localhost:3017');
  });


/******/


// Vérification de l'état de l'authentification
app.get('/auth/status', (req, res) => {
  if (req.cookies.sessionid) {
    // L'utilisateur est authentifié
    res.json({ authenticated: true, user: req.user });
  } else {
    // L'utilisateur n'est pas authentifié
    res.json({ authenticated: false });
  }
});