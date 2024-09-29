#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <libxml/parser.h>

void parseDays(xmlDocPtr doc,xmlNodePtr cur)/* printf day */
{
    xmlChar *day;
    cur = cur->xmlChildrenNode;
    while (cur!=NULL)
    {
        if ((!xmlStrcmp(cur->name,(const xmlChar *)"day")))
        {
            day = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            printf("day : %s\n", day);
            xmlFree(day);
        }
    cur = cur->next;/* prochain noeud */
    }
    return ;
}

void parseBooks(xmlDocPtr doc,xmlNodePtr cur)/* printf books */
{
    xmlChar *books;
    cur = cur->xmlChildrenNode;
    while (cur!=NULL)
    {
        if ((!xmlStrcmp(cur->name,(const xmlChar *)"book")))
        {
            books = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            printf("day : %s\n", books);
            xmlFree(books);
        }
    cur = cur->next;/* prochain noeud */
    }
    return ;
}

int main(int argc,const char *argv[])
{
    xmlDocPtr doc;/* pointer sur le document analyser (parsed)*/
    xmlNodePtr cur;/* pointer de noeux (node) */

    doc = xmlParseFile(argv[1]);/* pointeur pointe sur le document (lien du fichier dans argv[1]) */
    if (argc!=2)
    {
        printf("invalid number of arguments\n");
        fprintf(stderr,"erreur \n");
        printf("%d",errno);
        return 1;
    }
   if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return 1;
	}
    cur = xmlDocGetRootElement(doc);/* récupere l'element racine (root) */
    if (cur == NULL) {/* vérifie que le document contient quelque chose */
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return 1;
	}
    if (xmlStrcmp(cur->name, (const xmlChar *) "library")) { /* vérifie que le document est du bon type (library/book) */
		fprintf(stderr,"document of the wrong type, root node != library");
		xmlFreeDoc(doc);
		return 1;
	}
    printf("%s \n",cur->name);
    cur = cur->xmlChildrenNode;/* 1er enfant du noeud, ici il pointe sur le root donc library */
    while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"days"))){
            /* quand élem trouver, on essaye de l'afficher, le texte contenu dans un element est
            l'enfant du noeud de cet element */
			parseDays(doc,cur);/* appelle parseDays */
        }
    cur = cur->next;        
	}/* itère pour tout les enfants de "library" et cherche "days"  */
    while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"books"))){
            /* quand élem trouver, on essaye de l'afficher, le texte contenu dans un element est
            l'enfant du noeud de cet element */
        }
    cur = cur->next;        
	}/* itère pour tout les enfants de "library" et cherche "book"  */
    return 0;
}