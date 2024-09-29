// réinitialise tout au chargement de la page
resetDropdowns();


/* VARIABLES GLOBALES */

// fichier selectionné
var selectedFile = null;

// tableau des infos candidats aprés matching
var matchingResultsArray = [];

// division d'affichage des résultats
var listeMatching = document.querySelector('.liste_matching');

// langue actuelle de la page
var langue = document.getElementById('langueweb');

// bordure de la division de sélection de fichier
var bordure_zip = document.getElementById('drag_div');

// bordure de la division de sélection de poste
var bordure_job = document.getElementById('domaine_div');

// bouton de matching
var boutonMatching = document.getElementById('match_button');

// bouton de nettoyage
var boutonReset = document.getElementById('reset_button');


/* FONCTIONS */

// fonction ouvrant le gestionnaire de fichier de l'ordinateur pour sélectionner le fichier
function openFileSelector() {
    var fileInput = document.createElement('input');
    fileInput.type = 'file';
    fileInput.accept = '.zip, .pdf';
    fileInput.style.display = 'none';

    // récupere et stocke le fichier dans un variable
    fileInput.addEventListener('change', function(event) {
        selectedFile = event.target.files[0];
        var nomFichierElement = document.getElementById('nomfichier');
        if (selectedFile) {
            nomFichierElement.textContent = selectedFile.name;
        } else {
            // actualise selon la langue le nom du fichier aprés dépôt
            if (langue.outerText == "En") {
                nomFichierElement.textContent = 'No files selected';
            } else {
                nomFichierElement.textContent = 'Aucun fichier sélectionné';
            }
        }
    });
    document.body.appendChild(fileInput);
    fileInput.click();
    fileInput.remove();
}

// fonction qui crée un "clignotement" pour l'attente de matching
function toggleWaitingMessage() {
    var matchingMessage = document.querySelector('.aucun_resultat p');
    var dotCount = 0;

    // ajoute un point toutes les secondes et réinitialise tout les 3 points
    var interval = setInterval(function() {
        if (matchingResultsArray.length > 0) {
            clearInterval(interval);
            return;
        }
        if (dotCount < 3) {
            matchingMessage.textContent += '.';
            dotCount++;
        } else {
            if (langue.outerText == "En") {
                matchingMessage.textContent = 'Waiting for matching';
            } else {
                matchingMessage.textContent = 'En attente de correspondance';
            }
            dotCount = 0;
        }
    }, 1000);
}

// fonction qui envoi la description du poste selectionné au fichier app.py de sorte à effectuer le matching
function sendJodesData(jodesContent) {
  var xhr = new XMLHttpRequest();
  xhr.open('POST', '/get_jodes', true);
  xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
  xhr.onload = function() {
      if (xhr.status === 200) {
          console.log('Réponse du serveur (jodes):', xhr.responseText);
      } else {
          console.error('Erreur lors de la récupération du contenu de jodes.');
      }
  };
  xhr.send('jodes_content=' + encodeURIComponent(jodesContent));
}

// fonction qui envoi le fichier.zip selectionné au fichier app.py de sorte à effectuer le matching
function sendCvzipData(cvzipContent) {
  var xhr = new XMLHttpRequest();
  xhr.open('POST', '/get_cvzip', true);
  xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
  xhr.onload = function() {
      if (xhr.status === 200) {
          console.log('Réponse du serveur (cvzip):', xhr.responseText);
      } else {
          console.error('Erreur lors de la récupération du contenu de cvzip.');
      }
  };
  xhr.send('cvzip_content=' + encodeURIComponent(cvzipContent));
}

// fonction modifiant le fond de couleur selon le pourcentage de matching obtenue
function getMatchingPercentageClass(percentage) {
    if (percentage < 30) {
        return 'pourcentage_back_red';
    } else if (percentage >= 30 && percentage <= 70) {
        return 'pourcentage_back_orange';
    } else {
        return 'pourcentage_back_green';
    }
}

// fonction affichant les résultats du matching
function displayMatchingResults() {
    // tri du tableau par ordre décroissant de pourcentage
    matchingResultsArray.sort((a, b) => b.matching_percentage - a.matching_percentage);

    // limite l'affichage aux 8 meilleurs candidats
    var resultsToShow = matchingResultsArray.slice(0, 8);

    // efface la liste précedente
    listeMatching.innerHTML = '';

    // parcourt le tableau de résultats et les ajoute à la liste
    resultsToShow.forEach(function(result) {
        var percentageClass = getMatchingPercentageClass(result.matching_percentage);
        var divMatchingInfo = document.createElement('div');
        divMatchingInfo.classList.add('matching-info');

        // insertion du contenu HTML avec les données dynamiques
        if (langue.outerText == "En") {
            divMatchingInfo.innerHTML = `
                <div class="div-container">
                    <p>cv n°${result.id} : <a href="${result.cv_link}" download>download cv</a></p>
                </div>
                <div class="pourcentage">
                    <p class="pourcentage_back ${percentageClass}">${result.matching_percentage}%</p>
                </div>
            `;
        } else {
            divMatchingInfo.innerHTML = `
                <div class="div-container">
                    <p>cv n°${result.id} : <a href="${result.cv_link}" download>télécharger le cv</a></p>
                </div>
                <div class="pourcentage">
                    <p class="pourcentage_back ${percentageClass}">${result.matching_percentage}%</p>
                </div>
            `;
        }
        // ajoute l'élément crée à la liste
        listeMatching.appendChild(divMatchingInfo);
    });
}

// fonction réinitialisant les liste et le texte additionel
function resetDropdowns() {
    const dropdown = document.getElementById('firstPartDropdown');
    dropdown.options[dropdown.selectedIndex].disabled = false;
    dropdown.selectedIndex = 0;
    document.getElementById('secondPartDropdown').selectedIndex = 0;
    document.getElementById('secondPartDropdown').disabled = true;
    document.querySelector('.textsup_area').value = '';
} 


/* GESTIONNAIRES */

// gestionnaire d'événements pour le dragover
document.getElementById('drag-drop-area').addEventListener('dragover', function(event) {
    event.preventDefault();
});

// gestionnaire d'événements pour le drop
document.getElementById('drag-drop-area').addEventListener('drop', function(event) {
    event.preventDefault();

    // récupére le fichier déposé
    var droppedFile = event.dataTransfer.files[0];

    // affiche le type MIME du fichier déposé
    console.log(droppedFile.type);
  
    // vérifie si le fichier est au format .zip ou .pdf
    if (droppedFile.type === 'application/zip' || droppedFile.type === 'application/pdf'  || droppedFile.type === 'application/x-zip-compressed' || droppedFile.type === 'application/x-gzip' || droppedFile.type === 'application/x-gtar' || droppedFile.type === 'application/x-tgz' || droppedFile.type === 'text/csv') {
        selectedFile = droppedFile;
        var nomFichierElement = document.getElementById('nomfichier');
        nomFichierElement.textContent = selectedFile.name;
    } else {
        // alert selon la lague actuelle de la page
        if (langue.outerText == "En") {
            alert('Please upload a .zip or .pdf file only.');
        } else {
            alert('Veuillez télécharger un fichier .zip ou .pdf uniquement.');
        }
    }
});

// permet de vider le fichier si l'élément file_clear est cliqué
document.getElementById('file_clear').addEventListener('click', function() {
    if (langue.outerText == "En") {
        document.getElementById('nomfichier').textContent = 'No file selected';
    } else {
        document.getElementById('nomfichier').textContent = 'Aucun fichier sélectionné';
    }
    selectedFile = null;
});

// permet de vider le poste si l'élément job_clear est cliqué
document.getElementById('job_clear').addEventListener('click', function() {
    resetDropdowns();
});

// permet de vider le texte supplémentaire si l'élément text_clear est cliqué
document.getElementById('text_clear').addEventListener('click', function() {
    document.querySelector('.textsup_area').value = '';
});

// gestionnaire d'événements sur le clic du bouton matching1
boutonMatching.addEventListener('click', function() {
    // variable récupérant le fichier zip
    var cvZipElement = document.getElementById('cvzip');

    // vérifie si un fichier à été sélectionné
    if (selectedFile) {
        // récupération de la description du poste
        var descriptionValue = document.getElementById('description').innerText;

        // récupération de la valeur du textarea
        var textSupValue = document.querySelector('.textsup_area').value;

        // concaténation des deux valeurs
        var combinedValue = descriptionValue + " " + textSupValue;

        // actualise la description compléte
        var majdescription = document.getElementById('jodes');
        majdescription.textContent = combinedValue;

        // Renomme le fichier avec le métier sélectionné
        var renamedFile = new File([selectedFile], "cv.zip", { type: selectedFile.type });

        // Affiche le nom du fichier renommé
        cvZipElement.textContent = renamedFile.name;
    }
});

// gestionnaire d'événements sur le clic du bouton matching2
document.getElementById('match_button').addEventListener('click', function() {
    // variable récupérant de la description complète du poste
    var jodesContent = document.getElementById('jodes').textContent;
    // variable récupérant le fichier déposé
    var cvzipContent = document.getElementById('cvzip').textContent;

     // appel AJAX pour récupérer les résultats de correspondance et les affichent
     fetch('/get_matching_results')
     .then(response => response.json())
     .then(data => {
         matchingResultsArray = data;
         console.log('Matching Results:', matchingResultsArray); // Log the received matching results
         displayMatchingResults();
     })
     .catch(error => console.error('Erreur lors de la récupération des résultats de correspondance:', error));

    // variable message d'erreur
    var errorMessage = '';

    // vérifie si un fichier est sélectionné
    if (!selectedFile) {
        bordure_zip.style.border = '2px solid #ba2121';
        if (langue.outerText == "En") {
            errorMessage += 'Please select a file ';
        } else {
            errorMessage += 'Veuillez sélectionner un fichier ';
        }
    }
    bordure_job.style.border = '2px solid #aaa';

    // vérifie si un poste est sélectionné
    if (secondPartDropdown.selectedIndex === 0) {
        bordure_job.style.border = '2px solid #ba2121';
        if (errorMessage != ''){
            if (langue.outerText == "En") {
                errorMessage += 'and a job';
            } else {
                errorMessage += 'et un poste';
            }
        } else {
            bordure_zip.style.border = '2px solid #aaa';
            if (langue.outerText == "En") {
                errorMessage += 'Please select a job\n';
            } else {
                errorMessage += 'Veuillez sélectionner un poste\n';
            }
        }
    }

    // si une condition n'est pas remplie, arrête l'exécution de la fonction
    if (errorMessage !== '') {
        alert(errorMessage);
        return;
    } else {
        bordure_zip.style.border = '2px solid #aaa';
        bordure_job.style.border = '2px solid #aaa';
    }

    // si tout est rempli correctement, envoie les données et récupère les données de matching
    sendJodesData(jodesContent);
    sendCvzipData(cvzipContent);

    // appel AJAX pour récupérer les résultats de correspondance et les affichent
    fetch('/get_matching_results')
        .then(response => response.json())
        .then(data => {
            matchingResultsArray = data;
            displayMatchingResults();
        })
        .catch(error => console.error('Erreur lors de la récupération des résultats de correspondance:', error));
    
        // réinitialise les liste et le texte additionel
        resetDropdowns();
});

// gestionnaire d'événements sur le clic du bouton reset
boutonReset.addEventListener('click', function() {
    // réinitialise la couleur des bordures
    bordure_zip.style.border = '2px solid #aaa';
    bordure_job.style.border = '2px solid #aaa';

    // réinitialise le fichier choisit
    selectedFile = null;

    // réinitialise les informations sélectionnées dans les dropdowns
    resetDropdowns();

    // réinitialise l'attente de matching selon la langue
    if (langue.outerText == "En") {
        document.getElementById('nomfichier').textContent = 'No file selected';
        listeMatching.innerHTML = '<div class="aucun_resultat"><p>Waiting for matching</p></div>';
    } else {
        document.getElementById('nomfichier').textContent = 'Aucun fichier sélectionné';
        listeMatching.innerHTML = '<div class="aucun_resultat"><p>En attente de correspondance</p></div>';
    }
    
    // relance l'affichage dynamique
    toggleWaitingMessage();
});


// affichage dynamique d'attente de matching ...
toggleWaitingMessage();