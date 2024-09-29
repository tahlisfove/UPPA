drop view lesAuteurs;
drop table Ecrit;
drop table Auteurs;
drop sequence codAut_sequence;
drop table HistoPret;
drop table Numeros;
drop table Revues;
drop table Pret;
drop table Exemplaires;
drop table Personnes;
drop table Bibliotheques;
drop table Livres;
drop table Traite;
drop table MotsCles;
drop table Ouvrages;

Create table Ouvrages(codOuv,titre,langue) as
select CODOUV,TITOUV,LANGUE
from TPBD.l2ouvrages
;

alter table Ouvrages
add CONSTRAINT pk_Ouvrages PRIMARY KEY (CodOuv)
;

Create table Livres(codOuv,titOuv,langue) as
select CODOUV,TITOUV,LANGUE
from TPBD.l2ouvrages
;

alter table Livres
add CONSTRAINT pk_Livres PRIMARY KEY (CodOuv)
;

alter table Livres 
add CONSTRAINT fk_Livres_Ouvrages FOREIGN KEY (CodOuv) references OUVRAGES
;


Create table Bibliotheques(codBib,nomBib,rueBib,cpBib,villeBib) as
select CODBIB,NOMBIB,RUEBIB,CPBIB,VILLEBIB
from TPBD.l2bibliotheques
;

alter table Bibliotheques
add CONSTRAINT pk_Bibliotheque PRIMARY KEY (codBib)
;

Create table Exemplaires(CodEx,CodOuv,dateEntBib,editeur,nbPag) as
select CODEX,o.CODOUV,DATEENTBIB,NOMEDIT,NBPAG
from TPBD.l2exemplaires e,TPBD.l2ouvrages o
where e.CodOuv = o.CodOuv 
;

alter table Exemplaires 
add CONSTRAINT check_codOuv_Exemplaires check(codOuv is NOT NULL)
;

alter table Exemplaires
add CONSTRAINT pk_Exemplaires PRIMARY KEY (CodEx)
;

alter table Exemplaires
add CONSTRAINT fk_Exemplaires_Livres FOREIGN KEY (CodOuv) references LIVRES
;

alter table Exemplaires
add (codBib char(4))
;

update Exemplaires e set e.codBib = (select CODBIB
    from TPBD.l2exemplaires_biblio b
    where b.codEx = e.codEx)
;

alter table Exemplaires 
add CONSTRAINT check_codBib_Exemplaires check(codBib is NOT NULL)
;

Create table Personnes(CodPers,nomPers,prenomPers,ruePers,cpPers,villePers,dNaiss,dateIns,codBib) as
select CODPERS,NOMPERS,PRENOMPERS,RUEPERS,CPPERS,VILLEPERS,DNAISS,DATINS,CODBIB
from TPBD.l2personnes 
;

alter table Personnes
add CONSTRAINT pk_Personnes PRIMARY KEY (codPers)
;

alter table Personnes
add CONSTRAINT fk_Personnes_Bibliotheques FOREIGN KEY (codBib) references BIBLIOTHEQUES
;

alter table Personnes 
add CONSTRAINT check_CodBib_Personnes check(codBib is NOT NULL)
;

Create table Pret(codEx,codPers,dateP) as
select CODEX,CODPERS,DATEP
from TPBD.l2pret
;

alter table Pret
add CONSTRAINT pk_Pret PRIMARY KEY (codEx)
;

alter table Pret
add CONSTRAINT fk_Pret_Exemplaires FOREIGN KEY (codEx) references EXEMPLAIRES
;

alter table Pret
add CONSTRAINT fk_Pret_Personnes FOREIGN KEY (codPers) references PERSONNES
;

alter table Pret 
add CONSTRAINT check_codPers_Personnes check(codPers is NOT NULL)
;


Create table Revues(
    codOuv char(4),
    titOuv varchar(110),
    langue varchar(10),
    anEditPN number,
    periodicite varchar(20),
    CONSTRAINT pk_Revues PRIMARY KEY (codOuv),
    CONSTRAINT fk_Revues_Ouvrages FOREIGN KEY (codOuv) references OUVRAGES
);

Create table Numeros(
    codOuv char(4),
    numParu number,
    titreNum varchar(110),
    dateParu date,
    nbOccur number,
    CONSTRAINT pk_Numeros PRIMARY KEY (codOuv,numParu),
    CONSTRAINT fk_Numeros_REVUES FOREIGN KEY (codOuv) references REVUES
);

Create table HistoPret(
    codEx char(5),
    datePret date,
    codPers char(4) NOT NULL,
    dateRet date,
    CONSTRAINT pk_HistoPret PRIMARY KEY (codEx,datePret),
    CONSTRAINT fk_HistoPret_Exemplaires FOREIGN KEY (codEx) references EXEMPLAIRES,
    CONSTRAINT fk_HistoPret_Personnes FOREIGN KEY (codPers) references PERSONNES
);

Create table Auteurs(
    codAut number,
    nomAut varchar(15),
    prenomAut varchar(15),
    CONSTRAINT pk_Auteurs PRIMARY KEY (codAut)
);

create view lesAuteurs(nomaut,prenomaut) 
as
select distinct nomaut,prenomaut
from TPBD.l2ouvrages
;

Create SEQUENCE codAut_sequence;
  
insert into Auteurs
select codAut_sequence.nextval,NOMAUT,PRENOMAUT
from lesAuteurs
;

Create table Ecrit(
    codAut number,
    codOuv char(4),
    CONSTRAINT pk_Ecrit PRIMARY KEY (codAut,codOuv),
    CONSTRAINT fk_Ecrit_Auteurs FOREIGN KEY (codAut) references AUTEURS,
    CONSTRAINT fk_Ecrit_Livres FOREIGN KEY (codOuv) references LIVRES
);

insert into Ecrit
select codAut,codOuv
from Auteurs A ,TPBD.l2ouvrages L
where L.nomaut = A.nomaut 
and L.prenomaut = A.prenomaut;

Create table MotsCles(
    codMot char(4),
    libelleMot varchar(15),
    codMotPere char(5),
    CONSTRAINT pk_codMot PRIMARY KEY (codMot),
    CONSTRAINT fk_MotsCles_MotsCles FOREIGN KEY (codMot) references MotsCles
);

Create table Traite(
    codOuv char(4),
    codMot char(5),
    CONSTRAINT pk_Traite PRIMARY KEY (codOuv,codMot),
    CONSTRAINT fk_Traite_Ouvrages FOREIGN KEY (codOuv) references Ouvrages,
    CONSTRAINT fk_Traite_MotsCles FOREIGN KEY (codMot) references MotsCles
);


drop trigger Trigger_delete_Pret;

Create or replace trigger Trigger_delete_Pret
after delete on PRET
for each row
begin
    insert into HistoPret values(:old.codEx,:old.dateP,:old.codPers,sysdate);
    update Personnes set dateDerRet = :new.dateP
        where :new.codPers = codPers;
    update Livres set dateDerRetL = sysdate
        where codOuv = ( Select codOuv
                        from Exemplaires e
                        where e.codEx=:old.codEx);
    update Livres set nbJourPret = nbJourPret +  trunc(sysdate - :old.dateP)
        where codOuv = ( Select codOuv
                        from Exemplaires e
                        where e.codEx=:new.codEx);
end;

delete
from PRET
where codEx='44U44';
insert into Pret values('44U44','AB22',sysdate);


drop trigger Trigger_Livres;

Create trigger Trigger_Livres
before insert on LIVRES 
for each row
begin
    insert into OUVRAGES values (:new.codOuv,:new.titOuv,:new.langue);
end
;

insert into LIVRES values ('ME48','L''alfabet pour les nuls','Français');


drop trigger Trigger_Revues;

Create trigger Trigger_Revues
before insert on REVUES
for each row
begin
    insert into OUVRAGES values (:new.codOuv,:new.titOuv,:new.langue);
end
;

insert into REVUES values ('ME49','L''alpha b pour les nuls version 2','Français',2026,'hebdo');


drop trigger Trigger_Revues_delete;

Create trigger Trigger_Revues_delete
after delete on REVUES
for each row
begin
    delete from OUVRAGES where codOuv = :old.codOUV;
end
;

delete from REVUES where codOuv='ME49';


drop trigger Trigger_Livres_delete;

Create trigger Trigger_Livres_delete
after delete on LIVRES
for each row
begin
    delete from OUVRAGES where codOuv = :old.codOUV;
end
;

delete from LIVRES where codOuv='ME48';


alter table Personnes
add (nbPret number default 0)
add (dateDerPret date)
add (dateDerRet date)
;

alter table Livres
add (nbPretL number default 0)
add (nbJourPret number default 0)
add (dateDerRetL date)
;


delete trigger Trigger_insert_Pret;

Create or replace trigger Trigger_contrainte_pret
before insert on Pret
for each row
declare 
    nb number;
begin    
    select count(codEx) into nb
        from Pret
        where codPers=:new.codPers;
        if (nb>7)
        then  
            raise_application_error(-20667,'pas plus de 10 livres emprunté');
        end if;
end;

insert into Pret values('44B44','AB22',sysdate);
        
Create or replace trigger Trigger_insert_Pret
after insert on Pret 
for each row
begin
    update Personnes set nbPret = nbPret +1
            where codPers=:new.codPers;
    update Personnes set dateDerPret = :new.dateP
        where codPers=:new.codPers;
    update Livres set nbPretL= nbPretL + 1
        where codOuv = ( Select codOuv
                        from Exemplaires e
                        where e.codEx=:new.codEx);
    
end;

/*
insert into Pret values('44U44','AB22',sysdate);
*/

Merge into Personnes pers
using (select codpers, max (datep) as datep  from Pret group by codpers) X
on (pers.codPers = X.codPers)
when matched then
update
set pers.dateDerPret = X.datep;

Merge into Personnes pers
using (select codpers, max (dateret) as dateret  from HistoPret group by codpers) X
on (pers.codPers = X.codPers)
when matched then
update
set pers.datederRet = X.dateret;

merge into Livres l
using (Select codOuv,count(e.codEx) as nbP
        from Pret pr,Exemplaires e
        where pr.codex = e.codex
        group by codOuv) p
on (p.codOuv=l.codOuv)
when matched then update set nbPretL = p.nbP;

merge into Album A
using (Select numAlb, count(codPers) as nbP
        from Present Pr,Personnages P
        where pr.codPers=p.codpers
        group by pr.numAlb)P
on (P.numAlb=A.numAlb)
when matched then update set nbPerso=p.nbP;
--                              TP3 

create or replace function Emprunter(nom_bib in varchar) return number is
-- declaration des vars
    codB bibliotheques.codBib%type;
    nbInscrit number;
    nbInscr number;
begin
-- 1) Recup codBib
    select codBib into codB
    from Bibliotheques
    where nom_bib=NOMBIB;

-- 2) Calculer nbr inscrit dans codB

    select count(codPers) into nbInscrit
    from Personnes p
    where p.codBib=codB;

-- 3) Calculer le nbr inscrit dans codB qui n'ont pas emprunté de livres depuis 1 an

    select count(codPers) into nbInscr
    from Personnes
    where codbib = codB 
        and (sysdate - datederPret > 365 or dateDerRet is null);
-- 4) retourner pourcent 
    
    
    return trunc(nbInscr/nbInscrit * 100);
    
    exception
        when NO_DATA_FOUND then
            return -1;
        when ZERO_DIVIDE then
            return -2;        
end;

select Emprunter('Médiathèque André Labarrère')
from dual;
commit;
