// ajoute une transition a l'aide d'une div au chargement de la page
window.onload = () => {
    const anchors = document.querySelectorAll("a:not(.smooth-scroll, .skip-transition, .dc-fancybox, .ez-toc-link, .ez-toc-toggle, .ez-toc-btn)");
    const transition_el = document.querySelector('.digital-transition');
    
    // retire 'is-active' de l'élément 'digital-transition' après 400 ms
    setTimeout(() => {
        transition_el.classList.remove('is-active');
    }, 400);
    
    for (let i = 0; i < anchors.length; i++) {
        const anchor = anchors[i];
        anchor.addEventListener('click', e => {
            window.alert("class is " + e.currentTarget.className + " and current target is " + target);
            if (event.ctrlKey) { } else {
                e.preventDefault();
                let target = e.currentTarget.href;
                transition_el.classList.add('is-active');

                setTimeout(() => {
                    window.location.href = target;
                }, 600)
            };
        });
    }
}