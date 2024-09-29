// variable de visibilité de la section "fin"
var finVisible = false;

// basculer l'affichage de la section "fin" en fonction de son état 
function toggleFin(btn) {
    var finDiv = document.getElementById("fin");
    if (!finVisible) {
        finDiv.style.display = "flex";
        btn.classList.add("active");
        finVisible = true;
    } else {
        finDiv.style.display = "none";
        btn.classList.remove("active");
        finVisible = false;
    }
}

// redirection vers les pages francaise
function redirectToFrenchWelcome() {
    window.location.href = "/welcome_fr";
}

function redirectToFrenchPlatform() {
    window.location.href = "/platform_fr";
}

function redirectToFrenchChallenges() {
    window.location.href = "/challenges_fr";
}

function redirectToFrenchUs() {
    window.location.href = "/us_fr";
}

function redirectToFrenchLegal() {
    window.location.href = "/legal_fr";
}

function redirectToFrenchFaq() {
    window.location.href = "/faq_fr";
}

function redirectToFrenchContact() {
    window.location.href = "/contact_fr";
}

// redirection vers les pages anglaises
function redirectToEnglishWelcome() {
    window.location.href = "/";
}

function redirectToEnglishPlatform() {
    window.location.href = "/platform";
}

function redirectToEnglishChallenges() {
    window.location.href = "/challenges";
}

function redirectToEnglishUs() {
    window.location.href = "/us";
}

function redirectToEnglishLegal() {
    window.location.href = "/legal";
}

function redirectToEnglishFaq() {
    window.location.href = "/faq";
}

function redirectToEnglishContact() {
    window.location.href = "/contact";
}

// masque la section "fin" lorsqu'un clic est effectué en dehors de celle-ci
document.addEventListener("click", function(event) {
    var finDiv = document.getElementById("fin");
    var debutDiv = document.getElementById("debut");
    if (!finDiv.contains(event.target) && !debutDiv.contains(event.target)) {
        finDiv.style.display = "none";
        var dropbtns = document.getElementsByClassName("dropbtn");
        for (var i = 0; i < dropbtns.length; i++) {
            dropbtns[i].classList.remove("active");
        }
        finVisible = false;
    }
});