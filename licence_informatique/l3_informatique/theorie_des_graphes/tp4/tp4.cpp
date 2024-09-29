// Pour std::cout
#include <iostream>
using namespace std;
// Inclusion de la librairie boost.
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/bellman_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/reverse_graph.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/lexical_cast.hpp>
using namespace boost;

// Dans la structure, on définit les propriété des vertex, c'est à dire des noeux.
struct VertexProperties
{
    // Un identifiant désigné par une chaîne de caractéres.
    string id;
    // Un constructeur par défaut si aucune donnée n'est rentrée lors de la création du noeud.
    VertexProperties() : id(0) {}
    // La fonction qui permet d'assigner les valeur saisie par l'utilisateur au noeud correspondant.
    VertexProperties(string i) : id(i) {}
};

// Création de la propriété nécessaire a la création du coût de chaques arêtes.
typedef property<edge_weight_t, int> EdgeWeightProperty;
// Passage des paramètres nécéssaires à adjacency_list afin d'obtenir le graph désiré.
typedef adjacency_list<listS, vecS, directedS, VertexProperties, EdgeWeightProperty> Graph;
// Définiton du type sommets.
typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
// Définiton du type arêtes.
typedef typename graph_traits<Graph>::edge_descriptor Edge;

// Fonction d’application.
int main()
{
    // Création du graphe.
    Graph g;
    
    // Déclaration de tous les noeuds de nom : "X1", d'id : 1 dans le Graphe g.
    Vertex DEBUT = add_vertex(VertexProperties("DEBUT"),g);
    Vertex X1 = add_vertex(VertexProperties("X1"),g);
    Vertex X2 = add_vertex(VertexProperties("X2"),g);
    Vertex X3 = add_vertex(VertexProperties("X3"),g);
    Vertex X4 = add_vertex(VertexProperties("X4"),g);
    Vertex X5 = add_vertex(VertexProperties("X5"),g);
    Vertex X6 = add_vertex(VertexProperties("X6"),g);
    Vertex X7 = add_vertex(VertexProperties("X7"),g);
    Vertex X8 = add_vertex(VertexProperties("X8"),g);
    Vertex X9 = add_vertex(VertexProperties("X9"),g);
    Vertex X10 = add_vertex(VertexProperties("X10"),g);
    Vertex X11 = add_vertex(VertexProperties("X11"),g);
    Vertex X12 = add_vertex(VertexProperties("X12"),g);
    Vertex FIN = add_vertex(VertexProperties("FIN"),g);

    // Déclaration de tous les arcs et leurs coûts : arc X1 qui est dirigé vers arc X5 de coût 6 dans le graphe g.
    add_edge(DEBUT, X1, EdgeWeightProperty(4),g);
    add_edge(DEBUT, X2, EdgeWeightProperty(8),g);
    add_edge(DEBUT, X3, EdgeWeightProperty(1),g);
    add_edge(X3, X4, EdgeWeightProperty(1),g);
    add_edge(X1, X5, EdgeWeightProperty(6),g);
    add_edge(X1, X6, EdgeWeightProperty(3),g);
    add_edge(X2, X7, EdgeWeightProperty(5),g);
    add_edge(X5, X8, EdgeWeightProperty(3),g);
    add_edge(X6, X8, EdgeWeightProperty(3),g);
    add_edge(X7, X8, EdgeWeightProperty(3),g);
    add_edge(X4, X9, EdgeWeightProperty(1),g);
    add_edge(X9, X10, EdgeWeightProperty(2),g);
    add_edge(X8, X11, EdgeWeightProperty(2),g);
    add_edge(X10, X12, EdgeWeightProperty(5),g);
    add_edge(X11, X12, EdgeWeightProperty(5),g);
    add_edge(X12, FIN, EdgeWeightProperty(0),g);

    // Initialisation d'une dynamic_properties pour afficher les noeuds et arcs de notre Graphe g.
    dynamic_properties dp;
    // L'élément dp récupére chaque noeuds et arcs et leurs donnent un nom (ou un coût) pour la création du graphe en png.
    dp.property("node_id", get(vertex_index, g));
    dp.property("label", get(&VertexProperties::id, g));
    dp.property("label", get(edge_weight, g));
    dp.property("weight", get(edge_weight, g));

/*

    // Déclaration des variables pour stocker les résultats de l'algorithme de Dijkstra.
    const int num_vertices = 14;
    vector<Vertex> p(num_vertices(g));
    vector<int> d(num_vertices(g));

    // Exécution de l'algorithme de Dijkstra.
    dijkstra_shortest_paths(g, DEBUT, predecessor_map(make_iterator_property_map(p.begin(), 
    get(vertex_index, g))).distance_map(make_iterator_property_map(d.begin(), get(vertex_index, g))));

    // Affichage dans le terminal.
    cout << "Le chemin minimal du graphe est : \n";
    cout << vertex_names[source] << " -> " << vertex_names[target] << endl;
    cout << "Son temps d'exécution est de : \n" << distance[target] << endl;

    // Coloration des noeuds du graphe en vert, pour le chemin minimal.
    Vertex current = target;
    while (current != source)
    {
        Vertex next = predecessor[current];
        dp.property("color", "green")(edge(next, current, g));
        current = next;
    }

    // Déclaration des variables pour stocker les résultats de l'algorithme de Bellman.
    vector<int> distance(num_vertices);
    vector<Vertex> predecessor(num_vertices);

    // Exécution de l'algorithme de Bellman.
    bellman_ford_shortest_paths(g, num_vertices, vertex_distance_map(vertex_cost_map).weight_map(get(edge_weight, g))
    .distance_inf(numeric_limits<int>::max()).distance_zero(0), &distance[0], &predecessor[0],root_vertex(source));

    // Affichage dans le terminal.
    cout << "Le chemin critique du graphe est : \n";
    cout << vertex_names[source] << " -> " << vertex_names[target] << endl;
    cout << "Son temps d'exécution est de : \n" << distance[target] << endl;

    // Coloration des noeuds du graphe en rouge, pour le chemin critique.
    Vertex current = target;
    while (current != source)
    {
        Vertex next = predecessor[current];
        dp.property("color", "red")(edge(next, current, g));
        current = next;
    }

*/

    // Initialisation du graphe initials sous graph.dot.
    string graphDot = "graph.dot";
    ofstream FGraph(graphDot.c_str());

    // Création de l'image initiale sous graphe.png contenant le graphe g.
    write_graphviz_dp(FGraph, g, dp);
    system("dot -Grankdir=LR -Tpng graph.dot > graph.png");

    return 0;
}