-- TP2 --

-- 1)
insert into FILMS values('F011','Avatar','16/12/2009',162,500000000,'CAM043');
insert into ACTEURS values('SIG32','Weaver','Sigourney','Américaine','f','08/10/1949',null);
insert into JOUENT values('F011','SIG32','Grace Augustine');
insert into JOUENT values('F011','SAM01','Jack Sully');
insert into JOUENT values('F011','SIG32','Médecin');

-- dans FILMS
-- il faut insérer une ligne REALISATEUR avant d’insérer la ligne dans la table FILMS, en effet la
-- table référencée par une clé non définie.
-- insert into REALISATEURS values('CAM043','James Cameron','canadien','16/08/1954',null);

-- dans ACTEURS
-- la contrainte sexe n'est pas respectée, en effet il suffit de remplacer le f par un F majuscule.
-- insert into ACTEURS values('SIG32','Weaver','Sigourney','Américaine','F','08/10/1949',null);

-- dans JOUENT
-- le dernier cas il faut remplacer SIG32 par SIG33 car SIG32 en effet, la valeur de clé primaire n'est 
-- pas respectée, elle est déjà définie pour un autre acteur, de plus il faut avoir inséré auparavant 
-- la ligne concernant le film souhaité ainsi que les lignes des différents acteurs non définit.
-- insert into JOUENT values('F011','SIG32','Grace Augustine');
-- insert into JOUENT values('F011','SAM01','Jack Sully');
-- insert into JOUENT values('F011','SIG33','Médecin');

-- 2)
delete from JOUENT;
delete from ACTEURS;
delete from FILMS;

-- 3)
insert into REALISATEURS values('CAM043','James Cameron','canadien','16/08/1954',null);
insert into REALISATEURS values('CAM044','Ridley Scott','anglais','30/11/1937',null);
insert into REALISATEURS values('CAM045','Sam Mendes','anglais','01/08/1965',null);

insert into FILMS values('F011','Avatar','16/12/2009',162,500000000,'CAM043');
insert into FILMS values('F012','Alien, le retour','08/10/1986',147,null,'CAM043');
insert into FILMS values('F013','Alien, le huitième passager','12/09/1979',116,null,'CAM044');
insert into FILMS values('F014','Titanic','07/07/1998',194,null,'CAM043');
insert into FILMS values('F015','Les noces rebelles','21/01/2009',125,null,'CAM045');

insert into ACTEURS values('SIG31','Sam','Worthington','australien','M','02/08/1976',null);
insert into ACTEURS values('SIG32','Weaver','Sigourney','américaine','F','08/10/1949',null);
insert into ACTEURS values('SIG33','Zoe','Saldana','américaine','F','19/06/1978',null);
insert into ACTEURS values('SIG34','Stephan','Lang','américain','M','11/07/1952',null);
insert into ACTEURS values('SIG35','Michael','Biehn','américain','M','31/07/1956',null);
insert into ACTEURS values('SIG36','Lance','Henriksen','américain','M','05/05/1950',null);
insert into ACTEURS values('SIG37','Tom','Skerritt','américain','M','25/08/1933',null);
insert into ACTEURS values('SIG38','Leonardo','Di Caprio','américain','M','11/11/1974',null);
insert into ACTEURS values('SIG39','Kate','Winslet','anglaise','F','05/10/1975',null);

insert into JOUENT values('F011','SIG31','Jack Sully');
insert into JOUENT values('F011','SIG33','Neytiri');
insert into JOUENT values('F011','SIG32','Grace Augustine');
insert into JOUENT values('F011','SIG34','le colonel Miles Quaritch');
insert into JOUENT values('F012','SIG32','Lieutenant Ellen Riplay');
insert into JOUENT values('F012','SIG35','Caporal Dwayne Hicks');
insert into JOUENT values('F012','SIG36','Evêque');
insert into JOUENT values('F013','SIG32','Lieutenant Ellen Riplay');
insert into JOUENT values('F013','SIG37','Capitaine A.J. Dallas');
insert into JOUENT values('F014','SIG38','Jack Dawson');
insert into JOUENT values('F014','SIG39','Rose DeWitt Butaker');
insert into JOUENT values('F015','SIG38','Franck Wheeler');
insert into JOUENT values('F015','SIG39','April Wheeler');


 ---------------------------------------------------------------------------------------------------------


insert into REALISATEURS values('CAM046','Jean','américain','26/02/1900','18/07/1993','Negulesco');
insert into REALISATEURS values('CAM047','Guillaume','français','10/04/1973',null,'Canet');
insert into REALISATEURS values('CAM048','Claude','français','01/07/1934','12/01/2009','Berry');
insert into REALISATEURS values('CAM049','Danny','anglais','20/10/1956',null,'Boyle');
insert into REALISATEURS values('CAM050','Gilles','français','05/07/1972',null,'Lellouche');

insert into FILMS values('F016','Titanic',null,98,null,'CAM046','drame');
insert into FILMS values('F017','Les petits mouchoirs','20/10/2010',154,null,'CAM047','comédie dramatique');
insert into FILMS values('F018','Ensemble c est tout','21/03/2007',97,null,'CAM048','comédie dramatique');
insert into FILMS values('F019','La plage','16/02/2000',119,null,'CAM049','thriller');
insert into FILMS values('F020','Narco','01/12/2004',105,null,'CAM050','comédie');
