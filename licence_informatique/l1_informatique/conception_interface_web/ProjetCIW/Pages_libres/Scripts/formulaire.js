function read(l_facturation)
{
  var l_adresse      =    document.getElementById("l_adresse");
  var l_code_postal  =    document.getElementById("l_code_postal");
  var l_ville        =    document.getElementById("l_ville");
  l_adresse.readOnly      =  l_facturation.checked ? true : false;
  l_code_postal.readOnly  =  l_facturation.checked ? true : false;
  l_ville.readOnly        =  l_facturation.checked ? true : false;
  var l_adresse = document.getElementById("l_adresse");
  l_adresse.value = document.getElementById("f_adresse").value;
  var l_code_postal = document.getElementById("l_code_postal");
  l_code_postal.value = document.getElementById("f_code_postal").value;
  var l_ville = document.getElementById("l_ville");
  l_ville.value = document.getElementById("f_ville").value;
  if(!l_adresse.disabled)
  {
    l_adresse.focus();
  } else
   {
     var l_adresse = document.getElementById("l_adresse");
     l_adresse.value = document.getElementById("1").value;
     var l_code_postal = document.getElementById("l_code_postal");
     l_code_postal.value = document.getElementById("1").value;
     var l_ville = document.getElementById("l_ville");
     l_ville.value = document.getElementById("1").value;
   }

}
