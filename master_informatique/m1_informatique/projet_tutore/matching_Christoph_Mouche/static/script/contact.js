// vide le formulaire au chargement de la page
document.addEventListener('DOMContentLoaded', function() {
    const successMessage = document.getElementById("success-message");
    successMessage.classList.add("hide");
    effacer_formulaire();
    cache.addEventListener("submit", function(event) {
        event.preventDefault();
            if (verification_formulaire()) {
                effacer_formulaire();
                cache.classList.add("hide");
                successMessage.classList.remove("hide");
            }
    });

    // faire apparaître le formulaire
    const sendAnotherMessageBtn = document.querySelector(".success-message .reload-btn");
    sendAnotherMessageBtn.addEventListener("click", function() {
        cache.classList.remove("hide");
        successMessage.classList.add("hide");
    });

    // vider le formulaire via le boutton clear
    const clearform = document.querySelector(".clear-btn");
    clearform.addEventListener("click", function() {
        effacer_formulaire();
    });

    // regex pour empecher l'écriture de lettres dans l'input phoneNumber
    document.getElementById('phoneNumber').addEventListener('input', function () {
        this.value = this.value.replace(/[^0-9.]/g, '')
    });
});

// réinitialisation du formulaire
function effacer_formulaire() {
    const contactForm = document.getElementById("contactForm");
    const inputs = contactForm.getElementsByTagName("input");

    for (let i = 0; i < inputs.length; i++) {
        inputs[i].value = "";
    }

    const textArea = contactForm.getElementsByTagName("textarea")[0];
    textArea.value = "";
    const companySizeSelect = document.getElementById("companySize");
    companySizeSelect.selectedIndex = 0;
}

// verification du formulaire
function verification_formulaire() {
    const elements = contactForm.elements;
    let result = true;

    for (let i = 0; i < elements.length; i++) {
        if (elements[i].hasAttribute && elements[i].hasAttribute('required')) {
            switch (elements[i].tagName) {
                case 'INPUT':
                    if (!elements[i].value) result = false;
                    break;
                case 'SELECT':
                    if (elements[i].selectedIndex === 0) result = false;
                    break;
                case 'TEXTAREA':
                    if (!elements[i].value) result = false;
                    break;
            }
        }
    }
    return result;
}