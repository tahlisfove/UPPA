-- TP6 --

-- QUESTION 1 --
-- 1)
select*
    from FILMS
    where BUDGET > 1000000
;

-- 2)
select*
    from ACTEURS
    where SEXE = 'F'
    and NATIONACT = 'Américaine'
;

-- 3)
select NOMACT, PRENOMACT
    from ACTEURS
    where SEXE = 'M'
    and (NATIONACT = 'Francaise' or NATIONACT = 'Belge')
;

-- 4)
select TITREFILM
    from FILMS, REALISATEURS
    where FILMS.CODREAL = REALISATEURS.CODREAL
    and NOMREAL = 'Cameron'
    and PRENOMREAL = 'James'
;

-- 5)
select NOMACT, PRENOMACT
    from ACTEURS, JOUENT, FILMS
    where ACTEURS.CODACT = JOUENT.NACT
    and JOUENT.CODFILM = FILMS.CODFILM
    and TITREFILM = 'La plage'
    and (NATIONACT = 'Française' or NATIONACT = 'Américaine')
;

-- 6)
select A2.NOMACT, A2.PRENOMACT, A2.DNAISSACT
    from ACTEURS A1, ACTEURS A2
    where EXTRACT(YEAR from A1.DNAISSACT) = EXTRACT (YEAR from A2.DNAISSACT)
    and A1.NOMACT = 'Dujardin'
    and A1.PRENOMACT = 'Jean'
;

-- 7)
select REALISATEURS.CODREAL, NOMREAL, PRENOMREAL
    from REALISATEURS, FILMS
    where TITREFILM = 'Ensemble c’est tout'
    and DDECREAL < DATESORTIE
;

-- 8)
select distinct TITREFILM, NOMREAL
    from FILMS, JOUENT, REALISATEURS
    where FILMS.CODFILM = JOUENT.CODFILM
    and FILMS.CODREAL = REALISATEURS.CODREAL
    and NOMPERS = 'lieutenant Ellen Ripley'
;

-- 9)
select NOMREAL
    from REALISATEURS
    where CODREAL not in
        (select CODREAL
        from FILMS, JOUENT, ACTEURS
        where FILMS.CODFILM = JOUENT.CODFILM
        and ACTEURS.CODACT = JOUENT.NACT
        and NATIONACT = 'Américaine')
;

-- 10)
select distinct REALISATEURS.CODREAL, NOMREAL, PRENOMREAL
    from FILMS, JOUENT, ACTEURS, REALISATEURS
    where FILMS.CODFILM = JOUENT.CODFILM
    and REALISATEURS.CODREAL = FILMS.CODREAL
    and ACTEURS.CODACT = JOUENT.NACT
    and NATIONACT != 'Américaine'
;

-- 11)
select TITREFILM, DATESORTIE, BUDGET
    from FILMS, REALISATEURS
    where FILMS.CODREAL = REALISATEURS.CODREAL 
    and EXTRACT(YEAR from DATESORTIE)-EXTRACT(YEAR from DNAISSREAL) < 40
;

-- 12)
select CODFILM, TITREFILM
    from FILMS F
    where not exists (select NACT 
        from JOUENT, FILMS 
        where JOUENT.CODFILM = FILMS.CODFILM
        and TITREFILM = 'Noces rebelles'
    MINUS
        select NACT
        from JOUENT
        where CODFILM = F.CODFILM)
;

-- QUESTION 2 --
-- vérifié avec le SGBD ORACLE

-- QUESTION 3 --
-- a)
select distinct NATIONACT
    from ACTEURS
;

-- b)
select NOMREAL, PRENOMREAL
    from REALISATEURS
    where NATIONREAL = 'Américaine'
    and CODREAL not in (select CODREAL
        from JOUENT, ACTEURS, FILMS
        where NACT = CODACT
        and FILMS.CODFILM = JOUENT.CODFILM
        and NATIONACT = 'Française')
;