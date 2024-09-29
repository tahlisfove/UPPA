function changeColorDeFond() {
  var r = Math.floor(Math.random()*Math.floor(256));
  var g = Math.floor(Math.random()*Math.floor(256));
  var b = Math.floor(Math.random()*Math.floor(256));
  document.body.style.backgroundColor = "rgb(" + r + "," + g + "," + b + ")";
  return false;
}

function changeImageM1(url, nom) {
  console.log("DEBUG : changeImageM1 : url = "+url+", nom = "+nom);
  var bodyTag = document.body;
  var p1Tag   = bodyTag.childNodes[3];
  var bTag    = p1Tag.lastChild;
  var p2Tag   = bodyTag.childNodes[5];
  var imgTag  = p2Tag.firstChild;
  bTag.innerHTML = nom;
  imgTag.src = url;
  console.log("p1Tag  : "+ p1Tag.innerHTML);
  console.log("bTag   : "+ bTag.innerHTML);
  console.log("imgTag : "+ imgTag.src);
}

function changeImageM2(id_url, id_nom, url, nom) {
  var elem = document.getElementById(id_nom);
  elem.innerHTML = nom;
  document.getElementById(id_url).src = url;
}

function changeImageM3(url, nom) {
  document.querySelector("#mot").innerHTML = nom;
  document.querySelector("#img").src = url;
}
