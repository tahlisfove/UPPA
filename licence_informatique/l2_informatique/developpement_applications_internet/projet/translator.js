"use strict";

// Demande le lancement de l'exécution quand toute la page Web sera chargée
window.addEventListener('load', go);

// SAM Design Pattern : http://sam.js.org/
let actions, model, state, view;

//-------------------------------------------------------------------- Init ---
// Point d'entrée de l'application
function go() {
  console.log('GO !');

  //sandbox();

  const data = {
    authors: 'Samuel CHRISTOPH',
    languagesSrc: ['fr', 'en', 'es'],
    languagesDst: ['fr', 'en', 'es', 'it', 'ar', 'eo', 'ja', 'zh'],
    langSrc: 'fr',
    langDst: 'en',
    translations : translations1,
  };
  actions.initAndGo(data);
}

//-------------------------------------------------------------------- Tests ---

function sandbox() {

  function action_display(data) {

    // console.log(data);
    if (!data.error) {
      const language = languages[data.languageDst].toLowerCase();
      console.log(`'${data.expression}' s'écrit '${data.translatedExpr}' en ${language}`);
    } else {
      console.log('Service de traduction indisponible...');
    }
  }

  const expr = 'asperge';
  const langSrc = 'fr';
  const langDst = 'en';
  googleTranslation(expr, langSrc, langDst, action_display );
}

//------------------------------------------------------------------ Données ---

// Correspondance entre codes de langue et leur nom
// Pour d'autres langues, voir ici :  https://fr.wikipedia.org/wiki/Liste_des_codes_ISO_639-1
const languages = {
  fr: 'Français',
  en: 'Anglais',
  es: 'Espagnol',
  it: 'Italien',
  ar: 'Arabe',
  eo: 'Espéranto',
  ja: 'Japonais',
  zh: 'Chinois',
};

//------------------------------------------------------------------ Actions ---
// Actions appelées dans le code HTML quand des événements surviennent
//
actions = {

  initAndGo(data) {
	let tab = [];

	//On initialise le tableau contenant les langues
	for(let i=0;i<data.languagesDst.length; i++){ 
		tab.push([data.languagesDst[i],0]);
	}
	//Puis remplissage de tab avec val de translations1
    for(let i = 0; i<data.translations.length; i++){ 
      for(let j = 0; j<tab.length; j++){
        if(data.translations[i][0] == tab[j][0]){
          tab[j][1]++;
        }
        if(data.translations[i][2] == tab[j][0]){
          tab[j][1]++;
        }
      }
    }

    model.samPresent({
      do:'init',
      authors: data.authors,
      langSrc: data.langSrc,
      langDst: data.langDst,
      languagesSrc: data.languagesSrc,
      languagesDst: data.languagesDst,
      translations: data.translations,
	  tab: tab,
    });
  },
  // TODO: Ajouter les autres actions...
  // Bouton en haut à droite : à propos
  apropos(){
    alert("Traducteur - Application Web\n\nAuteur(s) : " + model.app.authors);
  },

  ongletchange(data){
	if(data.active != model.tabs.ongletactif){
	  model.samPresent({do: 'ongletchange', active: data.active});
	}
  },

  pagination(data){
	let nouvpage;
	if(data.type == 'pre'){
		nouvpage = model.pagination.page - 1;
	}
	if(data.type == 'sui'){
		nouvpage = model.pagination.page + 1;
	}
	if(data.type == 'pag'){
		nouvpage = data.num;
	}
	model.samPresent({do: 'pagination', nouvpage: nouvpage});
  },

  changertradspage(data){
	model.samPresent({do: 'changertradspage', tradpage: data.e.target.value}); 
  },

  fleches(data){
	if(data.fleche == "btn btn-secondary"){
		model.samPresent({do: 'fleches'});
	}
  },

  languechange(data){
	let lang = data.e.target.value;
	model.samPresent({do: 'languechange', lang: lang, type: data.type});
  },


  selec(data){
	model.samPresent({do: 'selec', index: data.index});
  },

  suppr(){
	if(model.marked.values != ""){
		model.samPresent({do: 'suppr'});
	}
  },

  supprall(){
	if(model.translations.values != ""){
		if(confirm("Êtes-vous sûr de vouloir supprimer\n toutes les traductions?")){
			model.samPresent({do: 'supprall'});
		}
	}
  },

  expressionchange(data){
	  let texte = data.e.target.value;
	  model.samPresent({do: 'expressionchange', texte: texte});
  },
  
  colonnesTRI(data){
	model.samPresent({do: 'colonnesTRI', col: data.col});  
  },

  traduction(){
    function display(data) {
	  let trad = [];
      if (!data.error) {
        const language = languages[data.languageDst].toLowerCase();
		trad = [data.languageSrc, data.expression, data.languageDst,data.translatedExpr.toLowerCase()];
      } else {
		trad = [data.languageSrc, data.expression, data.languageDst, data.expression];
        console.log('Service de traduction indisponible...');
      }
	  model.samPresent({do: 'traduction', trad : trad});
    }
    const expr = model.request.expression.toLowerCase();
    const langSrc = model.request.langSrc;
    const langDst = model.request.langDst;
	if((expr != "")&&(langSrc != langDst)){
		googleTranslation(expr, langSrc, langDst, display );
	}

  },

};

//-------------------------------------------------------------------- Model ---
// Unique source de vérité de l'application
//
model = {
  tabs: {
	  // TODO: propriétés pour les onglets
    ongletactif: 'Traductions',
    values: [],
  },
  request: {
    languagesSrc: [],
    languagesDst: [],
    langSrc: '',
    langDst: '',
    expression: '',
	haschanged: false,
  },
  translations: {
    values:[
      // ['fr','Asperge','en','Asparagus'],
    ],
  },

  sorted: {
	  // TODO: propriétés pour trier les colonnes
	  tri: ['N','c'],
	  valuestris: [['N','c'],['Depuis','c'],['Expression','c'],['Vers','c'],['Traduction','c']],
  },

  marked: {
	  // TODO: propriétés pour les lignes marquées pour suppression
	  values: [],
  },

  pagination: {
	  // TODO: propriétés pour gérer la pagination
    tradpage: 9,
	  page: 1,
  },

  app: {
    authors: '',
    mode: 'main',    // in ['main', 'lang']
    sectionId: 'app',
  },


  // Demande au modèle de se mettre à jour en fonction des données qu'on
  // lui présente.
  // l'argument data est un objet confectionné dans les actions.
  // Les propriétés de data comportent les modifications à faire sur le modèle.

  samPresent(data) {

    switch (data.do) {

      case 'init':
        this.app.authors = data.authors;
        this.request.languagesSrc = data.languagesSrc;
        this.request.languagesDst = data.languagesDst;
        this.request.langSrc = data.langSrc;
        this.request.langDst = data.langDst;
        this.translations.values = data.translations;
		this.tabs.values = data.tab;
        break;


      case 'ongletchange': // TODO: Autres modifications de model...
		this.tabs.ongletactif = data.active;
        if(this.tabs.ongletactif != 'Traductions'){
          this.app.mode = 'lang';
        }
        else{
          this.app.mode = 'main';
        }
		this.pagination.page = 1;
		break;
		
		case 'pagination':
	    this.pagination.page = data.nouvpage;
		break;

		case 'changertradspage':
		let npages = Math.floor(state.translations.lenTabtr / data.tradpage);
		if(state.translations.lenTabtr % data.tradpage != 0){
			npages++;
		}

		if(npages < this.pagination.page){
			this.pagination.page = 1;
		}
		this.pagination.tradpage = data.tradpage;
		break;
		

	    case 'fleches':
	      let aux = this.request.langSrc;
	      this.request.langSrc = this.request.langDst;
	  	  this.request.langDst = aux;
	  	  break;

	  case 'languechange':
	  	if(data.type == 's'){
		  model.request.langSrc = data.lang;
	    }
		if(data.type == 'd'){
		  model.request.langDst = data.lang;
		}
		break;

	  
	  case 'selec':
		if(this.marked.values.includes(data.index)){
			this.marked.values.splice(this.marked.values.indexOf(data.index),1);
		}
		else{
			this.marked.values.push(data.index);
		}
		this.marked.values.sort(function(a, b){return a-b});
		
		break;

	  case 'suppr':
		let j;
		for(let i = this.marked.values.length-1; i>=0; i--){
			let index = this.marked.values[i];
			for(j = 0; j<this.tabs.values.length; j++){
				if((this.translations.values[index][0] == this.tabs.values[j][0])||(this.translations.values[index][2] == this.tabs.values[j][0])){
					this.tabs.values[j][1]--;
				}
			}
			this.translations.values.splice(index,1);
		}
		
		let z = 0;
		if(this.tabs.ongletactif != 'Traductions'){
			while((z < this.tabs.values.length)&&(this.tabs.values[z][0] != this.tabs.ongletactif)){
				z++;
			}
			if(this.tabs.values[z][1] == 0){
				this.tabs.ongletactif = 'Traductions';
				this.app.mode = 'main';
				this.pagination.page = 1;
			}
		}
		
		let n;
		if(this.tabs.ongletactif == 'Traductions'){
			n = this.translations.values.length;

		}
		else{
			n = 0;
			for(let i = 0; i<this.translations.values.length; i++){
				if((this.translations.values[i][0] == this.tabs.ongletactif)||(this.translations.values[i][2] == this.tabs.ongletactif)){
					n++;
				}
			}
			
		}
		let tradpage = this.pagination.tradpage;
		let np = Math.floor(n / tradpage);
		if(n % tradpage != 0){
			np++;
		}
		if((this.pagination.page > np)&&(this.pagination.page != 1)){
			this.pagination.page--;
		}
		
		this.marked.values = [];
	    break;

	  case 'supprall':
	    if(this.tabs.ongletactif == 'Traductions'){
		    this.tabs.values = [];
		    for(let i=0;i<this.request.languagesDst.length; i++){
			    this.tabs.values.push([this.request.languagesDst[i],0]);
		    }
			this.translations.values = [];
			
	    }
		else{
			for(let i = (this.translations.values.length-1); i>=0; i--){
				if((this.translations.values[i][0]==this.tabs.ongletactif)||(this.translations.values[i][2]==this.tabs.ongletactif)){

					for(let j = 0;j<this.tabs.values.length;j++){
						if((this.tabs.values[j][0] == this.translations.values[i][0]) || (this.tabs.values[j][0] == this.translations.values[i][2])){
							this.tabs.values[j][1]--;
						}
					}
					this.translations.values.splice(i,1);
				}
			}
		}
		this.marked.values = [];
		this.tabs.ongletactif = 'Traductions';
		this.app.mode = 'main';
		this.pagination.page = 1;
	    break;

	  case 'expressionchange':
	    this.request.expression = data.texte;
		this.request.haschanged = true;
		break;
		
	  case 'colonnesTRI':
		let i = 0;
		while((i<this.sorted.valuestris.length)&&(data.col != this.sorted.valuestris[i][0])){
			i++;
		}
		if(this.sorted.tri[0] == data.col){
			if(this.sorted.tri[1] == 'c'){
				this.sorted.tri[1] = 'd';
			}
			else{
				this.sorted.tri[1] = 'c';
			}
			this.sorted.valuestris[i][1] = this.sorted.tri[1];
		}
		else{
			this.sorted.tri = this.sorted.valuestris[i];
		}		
		break;

		case 'traduction':
	    this.translations.values.splice(this.translations.values.length,0,data.trad);
		for(let i = 0; i < model.tabs.values.length; i++){
			if((model.request.langSrc == model.tabs.values[i][0]) || (model.request.langDst == model.tabs.values[i][0])){
				model.tabs.values[i][1]++;
			}
		}
		this.request.expression = '';
	    break;
		

      default:
        console.error(`model.samPresent(), unknown do: '${data.do}' `);
    }

    // Demande à l'état de l'application de prendre en compte la modification
    // du modèle
    state.samUpdate(this);
  },

};
//-------------------------------------------------------------------- State ---
// État de l'application avant affichage
//
state = {
  tabs: { 
	  // TODO: données des onglets déduites de model
	 currentTab: [],
  },
  translations: {
	  // TODO: données de traductions déduites de model (par langue notamment)
    currentTabtr: [],
	lenTabtr: 0,
  },
  marked: {
    correspIndex: [],
    },


  samUpdate(model) {
	  // TODO: Toutes les mises à jour des données pour préparer l'affichage
	let newtab = [];
	this.tabs.currentTab = [];
    this.translations.currentTabtr = [];
	this.marked.correspIndex = [];
	
	//Copie des valeurs de model.tabs.values dans newtab
	for(let i = 0; i < model.tabs.values.length; i++){
		newtab[i] = model.tabs.values[i];
	}
	
	//Tri des onglets si model.tabs.ongletactif == 'Traductions'
	if(model.tabs.ongletactif == 'Traductions'){
	  let j = 0;
      for(let i = 0; i<newtab.length; i++){
	    if(newtab[i][1] != 0){
	      j = 0;
          while((j < this.tabs.currentTab.length) && (newtab[i][1] < this.tabs.currentTab[j][1])){
			j++;
		}
        this.tabs.currentTab.splice(j,0,[newtab[i][0],newtab[i][1]]);
	    }
	  }
	}
	
	//Tri des onglets si model.tabs.ongletactif != 'Traductions'
	else{
	  let i = 0;
	  while((i<newtab.length)&&(newtab[i][0] != model.tabs.ongletactif)){
		  i++;
	  }
	  this.tabs.currentTab[0] = newtab[i];
	  newtab.splice(i,1);

	  let j = 1;
      for(let i = 0; i<newtab.length; i++){
	    if(newtab[i][1] != 0){
	      j = 1;
          while((j < this.tabs.currentTab.length) && (newtab[i][1] < this.tabs.currentTab[j][1])){
			j++;
		}
        this.tabs.currentTab.splice(j,0,[newtab[i][0],newtab[i][1]]);
	    }
	  }
	}
	
	//--------------------------------- Tri supplémentaire alphabetique s'il y a le meme nombre de traductions
	let alphabetic = [];
	let deb;
	if(model.tabs.ongletactif == 'Traductions'){
		deb = 0;
	}
	else{
		deb = 1;
	}
	for(let i = deb; i<this.tabs.currentTab.length; i++){
		alphabetic[i] = this.tabs.currentTab[i]; 
	}
	
	alphabetic.sort(compareSecondColumn);

	function compareSecondColumn(a, b) {
		if (a[1] === b[1]) {
			return sortFunction(a, b);
		}
		else {
			return (a[1] > b[1]) ? -1 : 1;
		}
	}
	
	function sortFunction(a, b) {
		if (a[0] === b[0]) {
			return 0;
		}
		else {
			return (a[0] < b[0]) ? -1 : 1;
		}
	}
	
	let j = 0;
	for(let i = deb; i<this.tabs.currentTab.length; i++){
		this.tabs.currentTab[i] = alphabetic[j]; 
		j++;
	}
	
	//---------------------------------
	

	//Tri des traductions si model.app.mode == 'lang'
    if(model.app.mode == 'lang'){
      for(let i = 0; i<model.translations.values.length; i++){
        if(model.translations.values[i][0] == model.tabs.ongletactif){
          this.translations.currentTabtr.push(model.translations.values[i]);
		  this.marked.correspIndex.push(i);
        }
        if(model.translations.values[i][2] == model.tabs.ongletactif){
          this.translations.currentTabtr.push([model.translations.values[i][2], model.translations.values[i][3],model.translations.values[i][0],model.translations.values[i][1]]);
		  this.marked.correspIndex.push(i);
        }
      }
    }
	
	//Tri des traductions si model.app.mode != 'lang' (model.app.mode == 'main')
    else{
      for(let i = 0; i<model.translations.values.length; i++){
        this.translations.currentTabtr.push(model.translations.values[i]);
		this.marked.correspIndex.push(i);
      }
    }

	this.translations.lenTabtr = this.translations.currentTabtr.length;
	
	//Tri des colonnes
	let list = [];
	//Ajout des 3 tableaux dans un seul tableau
	for(let j = 0; j<this.marked.correspIndex.length; j++){
		list.push({'tab': this.translations.currentTabtr[j], 'realindex': this.marked.correspIndex[j]});
	}
	
	switch(model.sorted.tri[0]){
		
		case 'N':
			list.sort(function(a, b){return a.realindex-b.realindex}); 
			break;
			
		case 'Depuis':
			list.sort(function(a, b) {
				return ((a.tab[0] < b.tab[0]) ? -1 : ((a.tab[0] == b.tab[0]) ? 0 : 1));
			});
			break;
			
		case 'Expression':
			list.sort(function(a, b) {
				return ((a.tab[1] < b.tab[1]) ? -1 : ((a.tab[1] == b.tab[1]) ? 0 : 1));
			});
			break;
			
		case 'Vers':
			list.sort(function(a, b) {
				return ((a.tab[2] < b.tab[2]) ? -1 : ((a.tab[2] == b.tab[2]) ? 0 : 1));
			});
			break;
			
		case 'Traduction':
			list.sort(function(a, b) {
				return ((a.tab[3] < b.tab[3]) ? -1 : ((a.tab[3] == b.tab[3]) ? 0 : 1));
			});
			break;
			
		default:
			console.error("Error: model.sorted.tri");
		
	}
	
	//Inverser l'ordre du tableau&
	if(model.sorted.tri[1] == 'd'){
		list.reverse();
	}
	//Separation du tableau en 3 tableux
	for(let j = 0; j<this.marked.correspIndex.length; j++){
		this.translations.currentTabtr[j] = list[j].tab;
		this.marked.correspIndex[j] = list[j].realindex;
	}
	//pagination
	let tabTr = [];
	let tabcorrespIndex = [];
	let i = (model.pagination.page - 1)*model.pagination.tradpage;
	while((i<this.translations.currentTabtr.length)&&(i<model.pagination.tradpage*model.pagination.page)){
		tabTr.push(this.translations.currentTabtr[i]);
		tabcorrespIndex.push(this.marked.correspIndex[i]);
		i++;
	}
	this.translations.currentTabtr = tabTr;
	this.marked.correspIndex = tabcorrespIndex;
	
    this.samRepresent(model);
  },

  // Met à jour l'état de l'application, construit le code HTML correspondant,
  // et demande son affichage.
  samRepresent(model) {

	if(model.request.haschanged){
		model.request.haschanged = false;
	}
	else{
		let representation = '';
		let headerUI = view.headerUI(model,state);
		let tabsUI = view.tabsUI(model,state);
		let requestUI = view.requestUI(model,state);
		let transactionsUI = view.transactionsUI(model,state);

		representation += headerUI;
		representation += tabsUI;
		if(model.app.mode == 'main'){
		  representation += requestUI;
		}
		representation += transactionsUI;
		// TODO: la représentation de l'interface est différente selon
        //       qu'on affiche l'onglet 'Traductions' (avec formulaire de traduction)
        //       ou qu'on affiche les onglets par langue...

		representation = view.generateUI(model, this, representation);

		view.samDisplay(model.app.sectionId, representation);
	}
	
  },
};
//--------------------------------------------------------------------- View ---
// Génération de portions en HTML et affichage
//
view = {

  // Injecte le HTML dans une balise de la page Web.
  samDisplay(eltId, representation) {
    const elt = document.getElementById(eltId);
    elt.innerHTML = representation;
  },

  // Renvoit le HTML
  generateUI(model, state, representation) {
    return `
    <div class="container">
      ${representation}
    </div>
    `;
  },

  headerUI(model,state) {
    return `
    <section id="header" class="mt-4">
      <div class="row mb-4">
        <div class="col-6">
          <h1>Traducteur</h1>
		</div>
		<div class="col-6 text-right align-middle">
          <div class="btn-group mt-2">
            <button class="btn btn-primary">Charger</button>
            <button class="btn btn-ternary">Enregistrer</button>
            <button class="btn btn-secondary">Préférences</button>
            <button class="btn btn-primary" onclick="actions.apropos()">À propos</button>
		  </div>
		</div>
      </div>
    </section>
    `;
  },

  tabsUI(model,state){
    let itemlist = `
    <section id="tabs">
      <div class="row justify-content-start ml-1 mr-1">
        <ul class="nav nav-tabs">`

    let estactif = `class="nav-link"`;
	if(model.tabs.ongletactif == 'Traductions'){
        estactif = `class="nav-link active"`;
	}
	itemlist += `
          <li class="nav-item">
            <a ${estactif} onclick="actions.ongletchange({active: 'Traductions'})"
              href="#">Traductions
              <span class="badge badge-primary">${model.translations.values.length}</span>
            </a>
          </li>`;

	let i = 0;
	while((i<state.tabs.currentTab.length) && (i<3)){
		estactif = `class="nav-link"`;
	    if(model.tabs.ongletactif == state.tabs.currentTab[i][0]){
          estactif = `class="nav-link active"`;
		}
		itemlist += `<li class="nav-item">
            <a ${estactif} onclick="actions.ongletchange({active: '${state.tabs.currentTab[i][0]}'})" href="#">${languages[state.tabs.currentTab[i][0]]}
              <span class="badge badge-primary">${state.tabs.currentTab[i][1]}</span>
            </a>
          </li>`;
		i++;
	}
    itemlist += `<li class="nav-item">
            <select class="custom-select" id="selectFrom" onchange="actions.ongletchange({active: value})">
              <option selected="selected" value="0">Autre langue...</option>`;

    while(i<state.tabs.currentTab.length){
		itemlist += `<option value="${state.tabs.currentTab[i][0]}">${languages[state.tabs.currentTab[i][0]]} (${state.tabs.currentTab[i][1]})</option>`;
		i++;
	}

	itemlist += `</select>
          </li>
        </ul>
      </div>
    </section>
    <br />`;

    return itemlist;
   },

  requestUI(model,state){
	let ls = model.request.languagesSrc.map ( (v,i,a) =>{
	let selected = '';
	if(model.request.langSrc == v){
		selected = `selected="selected"`;
	}
	return	`
        <option ${selected} value="${v}">${languages[v]}</option>
	`;}).join("");

	let ld = model.request.languagesDst.map( (v,i,a) =>{
	let selected = '';
	if(model.request.langDst == v){
		selected = `selected = "selected"`;
	}
	return	`
        <option ${selected} value="${v}">${languages[v]}</option>
	`;}).join("");

	let fleche = `class="btn btn-secondary"`;

	if((model.request.langSrc == model.request.langDst)||(model.request.languagesDst.indexOf(model.request.langSrc) == -1)||(model.request.languagesSrc.indexOf(model.request.langDst) == -1)){
		fleche = `class="btn btn-ternary"`;
	}

	let traduire = `class="btn btn-primary"`;

	if(model.request.langSrc == model.request.langDst){
		traduire = `class="btn btn-ternary"`;
	}



    return`
    <section id="request">
      <form action="">
        <div class="form-group">
          <fieldset class="form-group">
            <div class="row align-items-end">
              <div class="col-sm-3 col-5">
                <div class="form-group">
                  <label for="selectFrom">Depuis</label>
                  <select onchange="actions.languechange({e:event, type:'s'})" class="custom-select" id="selectFrom">
					${ls}
                  </select>
                </div>
              </div>
              <div class="form-group col-sm-1 col-2">
                <button ${fleche} onclick="actions.fleches({fleche: className})" type="button">⇄</button>
              </div>
              <div class="col-sm-3 col-5">
                <div class="form-group">
                  <label for="selectTo">Vers</label>
                  <select onchange="actions.languechange({e:event, type:'d'})" class="custom-select" id="selectTo">
					${ld}
                  </select>
                </div>
              </div>
              <div class="col-sm-5 col-12">
                <div class="input-group mb-3">
                  <input onchange="actions.expressionchange({e:event})" value="${model.request.expression}" id="expressionText" type="text" class="form-control" placeholder="Expression..." />
                  <div class="input-group-append">
					<button onclick="actions.traduction()" ${traduire} type="button">Traduire</button>
                  </div>
                </div>
              </div>
            </div>
          </fieldset>
        </div>
      </form>
    </section>`;
  },
  
  transactionsUI(model,state){
	let suppr = `class="btn btn-ternary"`;
	if(model.marked.values != ""){
		suppr = `class="btn btn-secondary"`;
	}

	let supprall = `class="btn btn-secondary"`;
	if(model.translations.values == ""){
		supprall = `class="btn btn-ternary"`;
	}

	let list = state.translations.currentTabtr.map( (v,i,a) =>
	{
	let checkstateBox = '';
	if(model.marked.values.includes(state.marked.correspIndex[i])){
		checkstateBox = `checked="checked"`;
	}

	return	`
	            <tr>
              <td class="text-center text-secondary"> ${state.marked.correspIndex[i]} </td>
              <td class="text-center">
                <span class="badge badge-info">${a[i][0]}</span>
              </td>
              <td>${a[i][1]}</td>
              <td class="text-center">
                <span class="badge badge-info">${a[i][2]}</span>
              </td>
              <td>${a[i][3]}</td>
              <td class="text-center">
                <div class="form-check">
                  <input type="checkbox" class="form-check-input" onclick="actions.selec({index:${state.marked.correspIndex[i]}})" ${checkstateBox}/>
                </div>
              </td>
	</tr>`;}).join("");

    return`
    <section id="translations">
      <fieldset>
        <legend class="col-form-label">Traductions</legend>
        <div class="table-responsive">
          <table class="col-12 table table-sm table-bordered">
            <thead>
              <th class="align-middle text-center col-1">
                <a onclick="actions.colonnesTRI({col: 'N'})" href="#">N°</a>
              </th>
              <th class="align-middle text-center col-1">
                <a onclick="actions.colonnesTRI({col: 'Depuis'})" href="#">Depuis</a>
              </th>
              <th class="align-middle text-center ">
                <a onclick="actions.colonnesTRI({col: 'Expression'})" href="#">Expression</a>
              </th>
              <th class="align-middle text-center col-1">
                <a onclick="actions.colonnesTRI({col: 'Vers'})" href="#">Vers</a>
              </th>
              <th class="align-middle text-center ">
                <a onclick="actions.colonnesTRI({col: 'Traduction'})" href="#">Traduction</a>
              </th>
              <th class="align-middle text-center col-1">
                <div class="btn-group">
                  <button onclick="actions.suppr()" ${suppr}>Suppr.</button>
                </div>
              </th>
            </thead>
			${list}
            <tr>
              <td colspan="5" class="align-middle text-center"> </td>
              <td class="align-middle text-center">
                <div class="btn-group">
                  <button onclick="actions.supprall()" ${supprall}>Suppr. tous</button>
                </div>
              </td>
            </tr>
          </table>
        </div>
        ${this.paginationUI(model,state)}
      </fieldset>
    </section>`;
  },

  paginationUI(model,state){  
	let ntrads = state.translations.lenTabtr;
	let tradpage = model.pagination.tradpage;
	let npages = Math.floor(ntrads / tradpage);
	if(ntrads % tradpage != 0){
		npages++;
	}
	let activepre = `page-item`;
	let activesui = `page-item`;
	if((model.pagination.page == 1)||(npages == 0)){
		activepre = `page-item disabled`;
	}
	if((npages == model.pagination.page)||(npages == 0)){
		activesui = `page-item disabled`;
	}
	
	let pages = ``;
	let activepage = `page-item`;
	for(let i = 1; i<= npages; i++){
		activepage = `page-item`;
		if(model.pagination.page == i){
			activepage = `page-item active`;
		}
		pages += `<li class="${activepage}">
                    <a onclick="actions.pagination({type:'pag', num:${i}})" class="page-link" href="#">${i}</a>
                  </li>`;
	}
  
	let optionspages = ``;
	let activeoption = ``;
	for(let i = 3; i<=9; i += 3){
		activeoption = ``;
		if(tradpage == i){
			activeoption = `selected="selected"`;
		}
		optionspages += `<option ${activeoption} value="${i}">${i}</option>`; 
	}
	
	let result = `
        <section id="pagination">
          <div class="row justify-content-center">

            <nav class="col-auto">
              <ul class="pagination">
                <li class="${activepre}">			
                  <a onclick="actions.pagination({type: 'pre'})" class="page-link" href="#" tabindex="-1">Précédent</a>
                </li>
				  ${pages}
                <li class="${activesui}">
                  <a onclick="actions.pagination({type: 'sui'})" class="page-link" href="#">Suivant</a>
                </li>
              </ul>
            </nav>
            <div class="col-auto">
              <div class="input-group mb-3">
                <select onchange="actions.changertradspage({e:event})" class="custom-select" id="selectTo">
				  ${optionspages}
                </select>
                <div class="input-group-append">
                  <span class="input-group-text">par page</span>
                </div>
              </div>
            </div>

          </div>
        </section>
	`;
	
	return result;
  },


};