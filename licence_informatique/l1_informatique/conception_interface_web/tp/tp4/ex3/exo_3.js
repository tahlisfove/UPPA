console.log("exo_3.js");

function indice(p,t){
  t= t /100;
  console.log(t);
  tcar= carre(t)
  let imc = p/tcar;
  return imc;
}

function carre(t){
   let tcar= t*t;
   console.log(tcar);
  return tcar;
}
