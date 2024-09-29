// Pour std::cout.
#include <iostream>
using namespace std;
// Pour clock_t.
#include <time.h>
// Inclusion de la librairie Boost.
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/lexical_cast.hpp>
using namespace boost;
// Inclusion d'une recherche de couverture minimale avec l'algorithme de Kruskal.
#include <boost/graph/kruskal_min_spanning_tree.hpp>

// Dans la structure, on définit les propriété des vertex, c'est à dire des noeux.
struct VertexProperties
{
    // Un identifiant manuel (qui n'est pas assigné automatiquement par la librairie) donc 1,2,3, etc ...
    unsigned id;
    // Un constructeur par défaut si aucune donnée n'est rentrée lors de la création du noeud.
    VertexProperties() : id(0) {}
    // La fonction qui permet d'assigner les valeur saisie par l'utilisateur au noeud correspondant.
    VertexProperties(unsigned i) : id(i) {}
};

// Création de la propriété nécessaire a la création du coût de chaques arêtes.
typedef property<edge_weight_t, int> EdgeWeightProperty;
// Passage des paramètres nécéssaires à adjacency_list afin d'obtenir le graph désiré.
typedef adjacency_list<listS, vecS, undirectedS, VertexProperties, EdgeWeightProperty> Graph;
// Définiton du type noeuds.
typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
// Définiton du type arcs.
typedef typename graph_traits<Graph>::edge_descriptor Edge;

// Fonction d’application.
int main()
{
    // Création du graphe.
    Graph g;
    // Déclaration de tous les noeuds de nom : "1", "2", "3" ... dans le Graphe g.
    Vertex v1 = add_vertex(VertexProperties(1),g);
    Vertex v2 = add_vertex(VertexProperties(2),g);
    Vertex v3 = add_vertex(VertexProperties(3),g);
    Vertex v4 = add_vertex(VertexProperties(4),g);
    Vertex v5 = add_vertex(VertexProperties(5),g);
    Vertex v6 = add_vertex(VertexProperties(6),g);
    Vertex v7 = add_vertex(VertexProperties(7),g);
    Vertex v8 = add_vertex(VertexProperties(8),g);
    Vertex v9 = add_vertex(VertexProperties(9),g);
    Vertex v10 = add_vertex(VertexProperties(10),g);
    Vertex v11 = add_vertex(VertexProperties(11),g);
    Vertex v12 = add_vertex(VertexProperties(12),g);
    Vertex v13 = add_vertex(VertexProperties(13),g);
    Vertex v14 = add_vertex(VertexProperties(14),g);
    Vertex v15 = add_vertex(VertexProperties(15),g);
    Vertex v16 = add_vertex(VertexProperties(16),g);
    Vertex v17 = add_vertex(VertexProperties(17),g);
    Vertex v18 = add_vertex(VertexProperties(18),g);
    Vertex v19 = add_vertex(VertexProperties(19),g);
    Vertex v20 = add_vertex(VertexProperties(20),g);
    Vertex v21 = add_vertex(VertexProperties(21),g);
    Vertex v22 = add_vertex(VertexProperties(22),g);
    Vertex v23 = add_vertex(VertexProperties(23),g);
    Vertex v24 = add_vertex(VertexProperties(24),g);
    Vertex v25 = add_vertex(VertexProperties(25),g);
    Vertex v26 = add_vertex(VertexProperties(26),g);
    Vertex v27 = add_vertex(VertexProperties(27),g);
    Vertex v28 = add_vertex(VertexProperties(28),g);
    Vertex v29 = add_vertex(VertexProperties(29),g);
    Vertex v30 = add_vertex(VertexProperties(30),g);
    Vertex v31 = add_vertex(VertexProperties(31),g);
    Vertex v32 = add_vertex(VertexProperties(32),g);
    Vertex v33 = add_vertex(VertexProperties(33),g);
    Vertex v34 = add_vertex(VertexProperties(34),g);

    // Déclaration de tous les arcs et leurs coûts : arc v1 qui est dirigé vers arc v2 de coût 8 dans le Graphe g.
    add_edge(v1, v2, EdgeWeightProperty(8),g);
    add_edge(v1, v3, EdgeWeightProperty(13),g);
    add_edge(v1, v6, EdgeWeightProperty(12),g);
    add_edge(v1, v11, EdgeWeightProperty(1),g);
    add_edge(v2, v3, EdgeWeightProperty(10),g);
    add_edge(v2, v9, EdgeWeightProperty(21),g);
    add_edge(v3, v4, EdgeWeightProperty(11),g);
    add_edge(v3, v7, EdgeWeightProperty(13),g);
    add_edge(v3, v31, EdgeWeightProperty(40),g);
    add_edge(v4, v5, EdgeWeightProperty(4),g);
    add_edge(v4, v6, EdgeWeightProperty(2),g);
    add_edge(v4, v7, EdgeWeightProperty(22),g);
    add_edge(v5, v3, EdgeWeightProperty(4),g);
    add_edge(v6, v5, EdgeWeightProperty(5),g);
    add_edge(v7, v8, EdgeWeightProperty(2),g);
    add_edge(v7, v9, EdgeWeightProperty(8),g);
    add_edge(v8, v13, EdgeWeightProperty(1),g);
    add_edge(v9, v8, EdgeWeightProperty(10),g);
    add_edge(v9, v10, EdgeWeightProperty(9),g);
    add_edge(v10, v11, EdgeWeightProperty(1),g);
    add_edge(v10, v12, EdgeWeightProperty(14),g);
    add_edge(v10, v13, EdgeWeightProperty(2),g);
    add_edge(v11, v12, EdgeWeightProperty(14),g);
    add_edge(v11, v13, EdgeWeightProperty(23),g);
    add_edge(v12, v13, EdgeWeightProperty(7),g);
    add_edge(v13, v7, EdgeWeightProperty(12),g);
    add_edge(v13, v14, EdgeWeightProperty(10),g);
    add_edge(v14, v7, EdgeWeightProperty(8),g);
    add_edge(v14, v15, EdgeWeightProperty(10),g);
    add_edge(v15, v16, EdgeWeightProperty(11),g);
    add_edge(v15, v17, EdgeWeightProperty(9),g);
    add_edge(v16, v22, EdgeWeightProperty(9),g);
    add_edge(v16, v30, EdgeWeightProperty(5),g);
    add_edge(v16, v31, EdgeWeightProperty(6),g);
    add_edge(v16, v32, EdgeWeightProperty(13),g);
    add_edge(v16, v33, EdgeWeightProperty(11),g);
    add_edge(v16, v34, EdgeWeightProperty(13),g);
    add_edge(v17, v18, EdgeWeightProperty(10),g);
    add_edge(v18, v19, EdgeWeightProperty(7),g);
    add_edge(v18, v23, EdgeWeightProperty(7),g);
    add_edge(v19, v20, EdgeWeightProperty(6),g);
    add_edge(v19, v24, EdgeWeightProperty(8),g);
    add_edge(v20, v21, EdgeWeightProperty(9),g);
    add_edge(v21, v25, EdgeWeightProperty(2),g);
    add_edge(v22, v20, EdgeWeightProperty(10),g);
    add_edge(v22, v33, EdgeWeightProperty(7),g);
    add_edge(v23, v24, EdgeWeightProperty(4),g);
    add_edge(v23, v26, EdgeWeightProperty(8),g);
    add_edge(v24, v25, EdgeWeightProperty(15),g);
    add_edge(v24, v26, EdgeWeightProperty(6),g);
    add_edge(v25, v27, EdgeWeightProperty(3),g);
    add_edge(v25, v28, EdgeWeightProperty(4),g);
    add_edge(v26, v29, EdgeWeightProperty(10),g);
    add_edge(v27, v28, EdgeWeightProperty(2),g);
    add_edge(v28, v29, EdgeWeightProperty(7),g);
    add_edge(v30, v31, EdgeWeightProperty(2),g);
    add_edge(v30, v32, EdgeWeightProperty(10),g);
    add_edge(v31, v34, EdgeWeightProperty(8),g);
    add_edge(v32, v33, EdgeWeightProperty(1),g);

    // Initialisation du graphe avant passage dans kruskal sous graphe.dot.
    string graphDot = "graph.dot";
    ofstream FGraph(graphDot.c_str());
    // Initialisation du graphe résultat aprés passage dans kruskal sous kruskal.dot.
    string kruskalDot = "kruskal.dot";
    ofstream FKruskal(kruskalDot.c_str());

    // Initialisation d'une dynamic_properties pour afficher les noeuds et arcs de notre Graphe g.
    dynamic_properties dp;
    // L'élément dp récupére chaque noeuds et arcs et leurs donnent un nom (ou un coût) pour la création des graphes en png.
    dp.property("node_id", get(vertex_index, g));
    dp.property("label", get(&VertexProperties::id, g));
    dp.property("label", get(edge_weight, g));
    dp.property("weight", get(edge_weight, g));


/////////////////////////////////////////////////////////////////// PROCEDURE KRUSKAL /////////////////////////////////////////////////////////////////////////////

    // Création du graphe kruskal.
    Graph kruskal;
    // Initialisation du graphe kruskal avec les valeurs du Graph g.
    vector<graph_traits<Graph>::edge_descriptor> matKruskal;
    // Ajout du coût de chaque noeuds du graphe.
    property_map<Graph, edge_weight_t>::type weight = get(edge_weight, g);

    // Initialisation du temps avant et après passage du graphe dans l'algorithme de Kruskal pour couverture minimal (kruskal_minimum_spanning_tree).
    clock_t beginKruskal = clock();
    kruskal_minimum_spanning_tree(g, back_inserter(matKruskal));
    clock_t endKruskal = clock();

    // Calcul du temps mis pour trouver la couverture minimale du graphe.
    double time_spent = (double)(endKruskal - beginKruskal);

    // Initialisation du coût total.
    int totalWeight = 0;
    // Calcul du coût total minimal lors du passage dans l'algorithme
    for(int i=0; i < matKruskal.size(); i++)
    {
        totalWeight += get(weight, matKruskal[i]);
        add_edge(source(matKruskal[i], g), target(matKruskal[i], g), EdgeWeightProperty(get(weight, matKruskal[i])), kruskal);
    }

    // Affichage dans le terminal du temps et du coût total dans l'application de notre graphe.
    cout << "\n" << "Temps d'exécution de l'algorithme Kruskal : " << time_spent <<endl;
    cout << "Coût total du poid avec l'algorithme de Kruskal : " << totalWeight << "\n" << endl;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // Création de l'image sous graph.png contenant le graphe g.
    write_graphviz_dp(FGraph, g, dp);
    system("dot -Tpng graph.dot > graph.png");
    // Création de l'image finale sous kruskal.png contenant la couverture minimale du graphe g utilisant la méthode kruskal.
    write_graphviz_dp(FKruskal, kruskal, dp);
    system("dot -Tpng kruskal.dot > kruskal.png");

    return 0;
}