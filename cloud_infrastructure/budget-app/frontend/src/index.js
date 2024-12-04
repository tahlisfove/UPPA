// Importe React pour créer des composants et gérer le rendu
import React from 'react';
// Importe ReactDOM pour interagir avec le DOM
import ReactDOM from 'react-dom';
// Le composant `App` représente l'application principale
import App from './App'; 

// Rendu de l'application dans le DOM
ReactDOM.render(
  <React.StrictMode> 
    <App /> 
  </React.StrictMode>,
  document.getElementById('root') 
);