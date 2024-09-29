let nombre;
let erreur;
let msg_error = "";
do {
    nombre = prompt(nombre,msg_error,'Entrez un nombre supérieur à 10,impair et entier');

    erreur = 0;
    if (nombre <= 10){
           
        erreur = erreur +1;
    }
    if (nombre >= 20){
        
        erreur = erreur +1;
    }
    if ((nombre % 2) == 0 ){
        
        erreur = erreur +1;
    }
    if (isNaN(nombre) == true){
       
        erreur = erreur +1;
    }
    if ((nombre % 1) != 0){
    
        erreur = erreur +1;
    }
    if (erreur != 0){
        if (erreur == 1){
            if (nombre <= 10){
           
                msg_error = "n'est pas superieur a 10";
            }
            if (nombre >= 20){
                
                msg_error = "n'est pas inferieur à 20";
            }
            if ((nombre % 2) == 0 ){
                
                msg_error = "n'est pas impair";
            }
            if (isNaN(nombre) == true){
               
                msg_error = "n'est pas un nombre";
            }
            if ((nombre % 1) != 0){
            
                msg_error = "n'est pas un entier";
            }
        }
        else{
            msg_error = "n'est ";
            if (nombre <= 10){
           
                msg_error = msg_error + ", ni superieur à 10";
            }
            if (nombre >= 20){
                
                msg_error = msg_error + ", ni inferieur a 20";
            }
            if ((nombre % 2) == 0 ){
                
                msg_error = msg_error + ", ni impair";
            }
            if (isNaN(nombre) == true){
               
                msg_error = msg_error + ", ni un nombre";
            }
            if ((nombre % 1) != 0){
            
                msg_error = msg_error + ", ni un entier";
            }
            msg_error = msg_error + ".";
        }
        
        
    }
  
  console.log(nombre);
} while (erreur != 0);

alert(nombre + ' est bien supérieur à 10 !');   