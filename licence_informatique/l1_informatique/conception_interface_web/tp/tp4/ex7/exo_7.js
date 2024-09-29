console.log("exo_7.js");

function ouvre() {
  if (maFenetre === null) {
    maFenetre = window.open("https://www.youtube.com");
  } else {
    console.log("Une fenêtre est déjà ouverte");
  }
}

function ferme() {
  if (maFenetre !== null) {
    maFenetre.close("https://www.youtube.com");
    maFenetre = null;
  } else {
    console.log("aucune fenêtre n'est ouverte");
  }
}
