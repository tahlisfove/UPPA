// Pour std::cout.
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

// Initialisation d'une boucle et d'un booléen.
bool stop = false;
int boucle = 0;
// Nombre de sommets du graphe.
const int x = 20;
// Différentes couleur possible pour notre graphe.
const int couleurs[x] = {0,1,2,3,5};

// Dans la structure, on définit les propriétés du graphe.
struct Graf
{
	int edges[x];
	char vertex_id[x];
	bool coloration[x];
	bool adj[x][x];
	int couleurs[x];
};

// Initialisation des différents degrés et sommets.
char vertex_names[x] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T'};
int degre[x];

// Création de notre graphe g à l'aide d'une matrice [x][x].
bool graf[x][x] = {
	0,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,
	0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,
	1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,
	0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,
	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,
	0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,
    1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,
	0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,
	0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
	0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
	0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
	0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0
};

// Algorithme de Welsh-Powell.
void Welsh_Powell(Graf g) 
{	
	// Initialisation des différentes variables.
	int edge = 0;
	int max = 0;
	boucle++;
	
	// Comptage des arêtes (adjacent ou non).
	if(boucle == 1)
		for(int i=0; i<x; i++)
			for(int j=0; j<x; j++)
				if(g.adj[i][j])
					degre[i]++;

	// Sélection du noeud possédant le degré le plus fort.
	for (int w=0; w<x; w++)
		if (!g.coloration[w])
		{
			g.edges[w] = degre[w];
			if (edge < g.edges[w])
			{
				edge = g.edges[w];
				max = w;
			}
		}

	// Coloriation du sommet avec le degré le plus grand en premier.
	g.couleurs[max] = couleurs[boucle];
	cout << "\nChangement de couleur:\nLe sommet " << g.vertex_id[max] << " est de couleur " << g.couleurs[max] << endl;

	// Coloriation des sommets non adjacents et non déja colorés au sommet précédent.
	for(int e=0; e<x; e++)
		if(!g.adj[max][e] && max!=e && !g.coloration[e])
		{
			for (int t=0; t<x ;t++)
			{
				// Création du booleen stop qui sort de la boucle si les régles ne sont pas respectés.
				if(g.adj[e][t] && g.couleurs[t]==g.couleurs[max]) stop = true;
				if(t == x-1 && !stop) 
				{
					g.couleurs[e] = couleurs[boucle];
					cout << "Le sommet " << g.vertex_id[e] << " est de couleur " << g.couleurs[e] << endl;
					g.coloration[e] = true;
					stop = false;
				}
				else if(t == x-1) stop = false;
			}
		}	
		// Initialisation du sommet possédant le degré le plus grand.
		g.coloration[max] = true;
	
	// Si le graphe est totalement coloré, la procédure de Welsh_powell prend fin.
	if(all_of(begin(g.coloration), end(g.coloration), [](bool i) { return i; }))
	{
		cout << "\nLe graphe G est totalement coloré\n" << endl;
	}
	// Sinon usage de la récursivité pour continuer la coloration du graphe.
	else Welsh_Powell(g);
}

// Fonction d’application.
int main()
{
	// Création du graphe.
	Graf g;

	// Initiation des couleurs du graphe.
	for(int y=0; y<x; y++)
	{
		g.couleurs[y] = 10;
		g.coloration[y] = false;
	}

	// Initiation de g avec une copie des valeurs d'une source vers destination.
	memcpy(&g.adj, &graf, sizeof(g.adj));
	memcpy(&g.vertex_id, &vertex_names, sizeof(g.vertex_id));

	// On lance la procédure de Welsh_Powell.
	Welsh_Powell(g); 
	return 0;
}