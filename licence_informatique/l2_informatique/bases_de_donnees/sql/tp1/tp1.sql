-- TP1 --

create table FILMS(
    CODFILM char(5),
    TITREFILM varchar(60),
    DATESORTIE date,
    DUREE number(10),
    BUDGET number(20),
    CODREAL char(6),
    constraint PK_FILMS primary key(CODFILM),
    constraint FK_CODREAL_REALISATEURS foreign key(CODREAL) references REALISATEURS,
    constraint CK_DUREE CHECK(DUREE > 0),
    constraint CK_BUDGET CHECK(BUDGET > 0))
;

create table REALISATEURS(
    CODREAL varchar(6),
    NOMREAL varchar(20),
    NATIONREAL varchar(15),
    DNAISSREAL date,
    DDECREAL date,
    constraint PK_REALISATEURS primary key(CODREAL),
    constraint CK_DATEDDEC_REAL check(DNAISSREAL < DDECREAL))
;

create table ACTEURS(
    CODACT char(5),
    NOMACT varchar(20),
    PRENOMACT varchar(20),
    NATIONACT varchar(15),
    SEXE char(1),
    DNAISSACT date,
    DDECACT date,
    constraint PK_ACTEURS primary key(CODACT),
    constraint CK_SEXE check(SEXE = 'F' or SEXE = 'M'),
    constraint CK_DATEDDEC_ACT check(DNAISSACT < DDECACT))
;

create table JOUENT(
    CODFILM char(5),
    NACT char(5),
    NOMPERS varchar(40),
    constraint PK_JOUENT primary key(CODFILM,NACT),
    constraint FK_CODREAL_FILMS foreign key(CODFILM) references FILMS,
    constraint FK_CODACT_ACTEURS foreign key(NACT) references ACTEURS)
;

