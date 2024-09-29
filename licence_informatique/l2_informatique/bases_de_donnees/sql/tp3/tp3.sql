-- TP3 --

-- a)
alter table FILMS modify(TITREFILMS varchar(70));

-- b)
alter table REALISATEURS add(PRENOMREAL varchar(50));

-- c)
update REALISATEURS set(PRENOMREAL='DANNY' where(CODREAL='DAN56'));

-- d)
update FILMS set BUDGET=(BUDGET*1.10);

-- e)
alter table films drop constraint FK_FILMS_REALISATEURS;
alter table REALISATEURS modify(CODREAL char(5));

-- f)
alter table FILMS add(CATEGORIE varchar(20));
update FILMS set(CATEGORIE='comédie' where(CODFILM='F020'));
update FILMS set(CATEGORIE='thriller' where(CODFILM='F019'));
update FILMS set(CATEGORIE='drame' where(CODFILM='F015'));

delete from JOUENT;
delete from ACTEURS;
delete from REALISATEURS;
delete from FILMS;