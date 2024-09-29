console.log("exo_10.js");

function mdp() {
  let mdp = window.prompt("mot de passe?");
  if (mdp == 'password') {
    return true;
  }
  else {
    window.alert("erreur")
    return false;
  }
}
