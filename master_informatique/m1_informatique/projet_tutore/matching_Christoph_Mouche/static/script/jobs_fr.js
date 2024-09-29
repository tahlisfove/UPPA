// trie les domaines et les métier par ordre alphabétique
function sortOptions(options) {
    return options.sort(function(a, b) {
        return a.localeCompare(b);
    });
}

// désactiver l'option sélectionnée dans les listes déroulantes
function disableSelectedOption(selectedElement, dropdown) {
    var options = dropdown.options;
    for (var i = 0; i < options.length; i++) {
        if (options[i].value === selectedElement) {
            options[i].disabled = true;
        } else {
            options[i].disabled = false;
        }
    }
}

// filtre les données en fonction du domaine sélectionné
function filterSecondElementsByFirstElement(selectedFirstElement, data) {
    return data.filter(function(row) {
        return row[0].trim() === selectedFirstElement;
    }).map(function(row) {
        return row[1].trim();
    });
}

// met à jour la deuxième liste déroulante en fonction du premier élément sélectionné
function updateSecondPartDropdown(selectedFirstElement, data) {
    var secondPartDropdown = document.getElementById('secondPartDropdown');
    var secondPartDropdownValue = secondPartDropdown.value;
    
    secondPartDropdown.innerHTML = '<option value="" disabled selected hidden>Choisissez un métier*</option>';
    var secondElements = filterSecondElementsByFirstElement(selectedFirstElement, data);

    // tri les éléments avant de les ajouter à la liste déroulante
    secondElements = sortOptions(secondElements);

    // ajoute les options à la deuxième liste déroulante
    secondElements.forEach(function(element) {
        var option = document.createElement('option');
        option.value = element;
        option.textContent = element;
        secondPartDropdown.appendChild(option);
    });

    // sélectionne l'option précédemment sélectionnée
    secondPartDropdown.value = secondPartDropdownValue;

    // désactive l'option sélectionnée dans la deuxième liste déroulante
    disableSelectedOption(selectedFirstElement, secondPartDropdown);
}

// récupére la description associée aux éléments sélectionnés dans les listes déroulantes
function getDescription(selectedFirstElement, selectedSecondElement, data) {
    var description = '';
    data.forEach(function(row) {
        if (row[0].trim() === selectedFirstElement && row[1].trim() === selectedSecondElement) {
            description = row[2].trim();
        }
    });
    return description;
}

// charge le fichier CSV depuis le git et affiche les éléments dans les listes déroulantes
Papa.parse('https://raw.githubusercontent.com/tahlisfove/matching_cvjob/dataset/jobs_descriptions_fr.csv', {

    download: true,
    header: false,
    complete: function(results) {
        var data = results.data;
        var firstPartDropdown = document.getElementById('firstPartDropdown');

        // créer un ensemble d'éléments uniques pour la première liste déroulante
        var firstElementsSet = new Set();
        data.forEach(function(row) {
            firstElementsSet.add(row[0].trim());
        });

        // tri les éléments avant de les ajouter à la première liste déroulante
        firstElementsSet = sortOptions(Array.from(firstElementsSet));

        // ajoute les éléments à la première liste déroulante
        firstElementsSet.forEach(function(element) {
            // vérifie si l'élément n'est pas vide
            if (element.trim() !== "") {
                var option = document.createElement('option');
                option.value = element;
                option.textContent = element;
                firstPartDropdown.appendChild(option);
            }
        });

        // gestionnaire d'événements pour détecter les changements de sélection dans la première liste déroulante
        firstPartDropdown.addEventListener('change', function() {
            // réinitialiser la deuxième liste déroulante et la description du métier précédent
            var secondPartDropdown = document.getElementById('secondPartDropdown');
            secondPartDropdown.selectedIndex = 0;
            document.getElementById('description').textContent = '';

            var selectedFirstElement = firstPartDropdown.value;
            updateSecondPartDropdown(selectedFirstElement, data);

            // active ou désactive la deuxième liste déroulante en fonction de la sélection de la première
            var secondPartDropdown = document.getElementById('secondPartDropdown');
            secondPartDropdown.disabled = selectedFirstElement === '';

            // désactiver l'option sélectionnée dans la première liste déroulante
            disableSelectedOption(selectedFirstElement, firstPartDropdown);
        });

        // gestionnaire d'événements pour détecter les changements de sélection dans la deuxième liste déroulante
        var secondPartDropdown = document.getElementById('secondPartDropdown');
        secondPartDropdown.addEventListener('change', function() {
            var selectedFirstElement = firstPartDropdown.value;
            var selectedSecondElement = secondPartDropdown.value;
            var description = getDescription(selectedFirstElement, selectedSecondElement, data);
            document.getElementById('description').textContent = description;

            // désactive l'option sélectionnée dans la deuxième liste déroulante
            disableSelectedOption(selectedSecondElement, secondPartDropdown);
        });
    }
});