let nombre;

do {
  nombre = prompt('Entrez un nombre supérieur à 10');
  console.log(nombre);
} while ((nombre <= 10)||((nombre % 2) == 0 )||(isNaN(nombre) == true) || ((nombre % 1) != 0 ));

alert(nombre + ' est bien supérieur à 10 !');   