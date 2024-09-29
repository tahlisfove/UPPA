// réinitialise les champs de saisie lorsque la page se charge
document.addEventListener('DOMContentLoaded', function() {
    var emailInput = document.getElementById('emailID');
    var passwordInput = document.getElementById('password');

    emailInput.value = '';
    passwordInput.value = '';
});

// variables du nombre d'essais
var maxAttempts = 2;
var currentAttempts = 0;

// bloque ou permet à l'utilisateur d'entrer sur la plateforme EN
document.getElementById('loginForm').addEventListener('submit', function(event) {
    event.preventDefault();

    var emailInput = document.getElementById('emailID');
    var passwordInput = document.getElementById('password');
    var errorMessage = document.getElementById('errorMessage');

    errorMessage.innerText = '';

    // permet à l'utilisateur d'accéder à la plateforme
    if (emailInput.value === 'MatchifyJobs' && passwordInput.value === 'MatchifyJobs') {
        errorMessage.style.display = 'none';
        window.location.href = '/platform';
    } else { 
        if(currentAttempts < maxAttempts) {
            // permet à l'utilisateur de faire un nouvel essai
            currentAttempts++;
            errorMessage.innerText = 'Username or password incorrect.';
            errorMessage.classList.remove('hidden');
            emailInput.value = '';
            passwordInput.value = '';
            document.getElementById('emailID').focus();
        } else {
            // bloque l'utilisateur car trop de tentatives ratées
            errorMessage.innerText = 'You have exceeded the maximum number of attempts. Reloading the page.';
            errorMessage.classList.remove('hidden');
            emailInput.value = '';
            passwordInput.value = '';
            emailInput.disabled = true;
            passwordInput.disabled = true;
            
            // recharger la page après 5 secondes
            setTimeout(function() {
                location.reload();
            }, 5000);
        }
    }
});

// bloque ou permet à l'utilisateur d'entrer sur la plateforme FR
document.getElementById('loginFormFr').addEventListener('submit', function(event) { 
    event.preventDefault();

    var emailInput = document.getElementById('emailID');
    var passwordInput = document.getElementById('password');
    var errorMessage = document.getElementById('errorMessage');

    errorMessage.innerText = '';

    // permet à l'utilisateur d'accéder à la plateforme
    if (emailInput.value === 'MatchifyJobs' && passwordInput.value === 'MatchifyJobs') {
        errorMessage.style.display = 'none';
        window.location.href = '/platform_fr';
    } else { 
        if(currentAttempts < maxAttempts) {
            // permet à l'utilisateur de faire un nouvel essai
            currentAttempts++;
            errorMessage.innerText = 'Nom d\'utilisateur ou mot de passe incorrect.';
            errorMessage.classList.remove('hidden');
            emailInput.value = '';
            passwordInput.value = '';
            document.getElementById('emailID').focus();
        } else {
            // bloque l'utilisateur car trop de tentatives ratées
            errorMessage.innerText = 'Vous avez dépassé le nombre maximum de tentatives. Rechargement de la page.';
            errorMessage.classList.remove('hidden');
            emailInput.value = '';
            passwordInput.value = '';
            emailInput.disabled = true;
            passwordInput.disabled = true;
            
            // recharger la page après 5 secondes
            setTimeout(function() {
                location.reload();
            }, 5000);
        }
    }
});

// réinitialise le champs email au focus
document.getElementById('emailID').addEventListener('focus', function() {
    this.value = '';
});

// réinitialise le champs password au focus
document.getElementById('password').addEventListener('focus', function() {
    this.value = '';
});