

let message = '';

for (let i=1; i<10; i=i+1) {
  if (i == 9){
    message = message + i;
  }
  else{
    message = message + i + ', ' ;

  }
  
}
 


alert('Les dix chiffres : ' + message);

// affiche : Les dix chiffres : 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
