#!/bin/bash

#-----------------------------------------------------
# Projet L1 - Introduction aux Systèmes d'Exploitation
#-----------------------------------------------------

# Remplacer les noms par les vôtres
auteur="CHRISTOPH Samuel"

# Les fichiers générés par le script
fichier_rst="tux.rst"
fichier_html="tux.html"
fichier_pdf="tux.pdf"

echo "Génération de ${fichier_rst}"

# Insertion d'un bloc de texte dans fichier_rst.
# Le texte concerné est compris entre les deux mots BLOC.
cat >> ${fichier_rst}  << BLOC
==============
TUX le Manchot
==============
---------------------------------------------------
Projet d\'Introduction aux Systèmes d\'Exploitation
---------------------------------------------------

:auteur: *${auteur}*
:Généré par: *$(whoami)*

Ce document a été généré  à partir du fichier \`\`tux.rst\`\` au
format \`reStructuredText\`_ lui-même créé par le script
\`\`tux.sh\`\`. Ce fichier  rst a  ensuite  été  converti en
HTML  et  PDF avec  les commandes \`\`rst2html\`\` et \`\`rst2pdf\`\`.


.. _reStructuredText: https://aful.org/wikis/interop/ReStructuredText

.. sidebar:: Références

   Les directives du format RST sont disponibles \`ici\`_.

.. _ici: http://docutils.sourceforge.net/docs/ref/rst/directives.html

L\'objectif est de compléter le script \`\`tux.sh\`\` afin que les
documents générés ressemblent le plus fidèlement possible au modèle fourni.

L'histoire de TUX
=================

Quelques années après le lancement du noyau Linux en 1991, le besoin d'un logo se fit sentir...

.. image::http://bjobard.perso.univ-pau.fr/Cours/ISE/Assets/Projet/Tr%C3%A8s_long_nom_pour_un_dossier_image/logo_tux.png
 :height:236px
 :width: 200 px
 :scale: 50 %
 alt: alternate text
 :align: center
.. figure:: TUX, la mascotte de Linux.

Manchot ou pingouin ?
---------------------

+-------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+
| **Noms et liens vers site web**                             | **Images**                                                                                                               |
+=============================================================+==========================================================================================================================+
+-------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+
| \`pingouin\` se dit auk en anglais                          | .. image::http://bjobard.perso.univ-pau.fr/Cours/ISE/Assets/Projet/Tr%C3%A8s_long_nom_pour_un_dossier_image/pingouin.jpg |
|   .._pingouin: https://fr.wikipedia.org/wiki/Pingouin       |   :height:320px                                                                                                          |
|                                                             |   :width: 213px                                                                                                          |
+-------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+
| Alors que \`manchot  \` se traduit par penguin !            | .. image::http://bjobard.perso.univ-pau.fr/Cours/ISE/Assets/Projet/Tr%C3%A8s_long_nom_pour_un_dossier_image/manchot.jpg  |
|  .._manchot: https://fr.wikipedia.org/wiki/Sphenisciformes  |    :height:172px                                                                                                         |
|                                                             |    :width: 240px                                                                                                         |
+-------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+
|      Pingouin ?                                            TUX                                                                                   Manchot !                             |
+-------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+


BLOC
cat >> ${fichier_rst}  << BLOC

Les manchots sont des geeks !
=============================
La commande \`\`screenfetch\`\` affiche le logo et des informations en temps réel sur la distribution Linux.

BLOC

echo -e "screenfetch " | screenfetch | boxes -d netdata -a c -s 45x25 >> ${fichier_rst}


paste -d '\t'  <( echo " fathi "c screenfetch -n -d '-RAM' | boxes -d stone ) <( echo " stone" | boxes -d stone) <( echo " stone" | boxes -d stone) <( echo " stone" | boxes -d stone)| boxes -d peek | boxes -d mouse

echo -e "Laisse tomber Charlie, tu n'es qu'un veau !" | cowthink -e \oO | boxes -d simple | tr 'w' '%' | tr '\/\' '---' >> ${fichier_rst}

cat >> ${fichier_rst}  << BLOC

Ici, la sortie de screenfetch est filtrée pour extraire des informations
qui sont stockées dans des variables et insérées dans
cette petite bande-dessinée générée par un enchaînement de commandes :

BLOC
cat >> ${fichier_rst}  << BLOC

ASCII Art
=========

Le tableau ci-dessous a été généré à l'aide de commandes.
Les images sont tirées directement du web, sans sauvegarde locale. La plus grande image fait exactement 78 caractères de large.
Les deux autres images font la même hauteur.

+-----------------------------------------------------------------------------------------------------------------------------------------------+
|jp2a --size=45x25 --background=light https://i.imgur.com/5pfElEi.jpeg                                                                          |
|                                                                                                                                               |
+------------------------------------------------------------------------+----------------------------------------------------------------------+
|                                                                        |                                                                      |
|jp2a --size=60x25 --background=light https://i.imgur.com/bdqwtzl.jpeg   | jp2a --size=45x25 --background=light https://i.imgur.com/uAWxbao.jpg |
+------------------------------------------------------------------------+----------------------------------------------------------------------+
BLOC

# Génération des formats HTML et PDF

echo "Génération de ${fichier_html}"
rst2html -d -t -s ${fichier_rst} ${fichier_html}
echo "Génération de ${fichier_pdf}"
rst2pdf           ${fichier_rst} ${fichier_pdf}