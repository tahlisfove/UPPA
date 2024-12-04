// Sélectionne l'élément avec l'identifiant 'loginButton' dans le DOM
document.getElementById('loginButton').addEventListener('click', () => {
    window.location.href = 'http://localhost:3002/auth/google';
});