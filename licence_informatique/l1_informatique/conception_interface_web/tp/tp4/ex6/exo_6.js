console.log("exo_6.js");

function calc_age() {
  console.log("wtf")
  let naissance = parseInt(window.prompt("année de naissance?"));
  let année = 2020;

  age = année - naissance;

  window.alert("vous avez soit "+ age +" ans, soit "+ (age-1) +" ans.");
}
