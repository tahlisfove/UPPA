// STL.
// pour std::cout.
#include <iostream>
// Inclusion de la librairie Boost.
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/reverse_graph.hpp>
#include <boost/graph/graph_utility.hpp>
using namespace std;
using namespace boost;

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

// Passe les paramètres nécéssaires à adjacency_list afin d'avoir le graph désiré
typedef adjacency_list <vecS, vecS, bidirectionalS, VertexProperties> Graph;
// bidirectionalS graphe orienté avec des arcs bidirectionnels.
// VertexProperties demande de prise en compte de nos noeuds personalisés et non les noeuds par default.
// Création du typedef Graph avec les paramètres ci-dessus.

// Création d'un DFS Visitor personnalisé pour noter et récupérer les sommets dans l'ordre date fin.
class custom_dfs_visitor_finish : public boost::default_dfs_visitor
{
    public:
        // On créee un constructeur qui va gébérer un vecteur dans lequel sera stocké le résultat de la recherche.
        custom_dfs_visitor_finish() : vv(new std::vector<int>()) {}
        // Ici on paramètre la recherche.
        template < typename Vertex, typename Graph >
        // Fonction de BGL, elle signifie que les noeuds sont ajoutés que lorsqu'ils sont des feuilles.
        void finish_vertex(Vertex u, const Graph & g) const
        {
            // On crée un tableau de noeuds.
            VertexProperties const& vertexProperties = g[u];
            // On affiche dans la console le deroulement de la recherche.
            std::cout << "Fin: " << vertexProperties.id <<endl;
            // On stocke l'id du noeud dans notre vecteur de int.
            vv->push_back(g[u].id);
        }
        // Fonction servant à restituer le vecteur.
        std::vector<int> &GetVectorF() const { return *vv; }

    private:
        // Déclaration du vecteur vv.
        boost::shared_ptr<std::vector<int> > vv;
};

// Création d'un DFS Visitor personnalisé pour noter et restituer les sommets dans l'ordre date fin.
class custom_dfs_visitor_discover : public boost::default_dfs_visitor
{
    public:
        // On créee un constructeur qui va gébérer un vecteur dans lequel sera stocké le résultat de la recherche.
        custom_dfs_visitor_discover() : vw(new std::vector<int>()) {}
        // Ici on paramètre la recherche.
        template < typename Vertex, typename Graph >
        // Fonction de BGL, elle signifie que les noeuds sont ajoutés que lorsqu'ils sont des feuilles.
        void discover_vertex(Vertex u, const Graph & g) const
        {
            // On crée un tableau de noeuds.
            VertexProperties const& vertexProperties = g[u];
            // On affiche dans la console les noeuds découvert lors de la recherche.
            std::cout << "Découvert: " << vertexProperties.id << "," <<endl;
            // On stocke l'id du noeud dans notre vecteur de int.
            vw->push_back(g[u].id);
        }
        // Fonction servant à restituer le vecteur.
        std::vector<int> &GetVectorD() const { return *vw; }

    private:
        // Déclaration du vecteur vw.
        boost::shared_ptr<std::vector<int> > vw;
};

// Fonction d’application.
int main(int, char*[])
{
    // Définiton des types noeuds et arcs
    typedef graph_traits<Graph>::vertex_descriptor vertex_t;
    typedef graph_traits<Graph>::edge_descriptor edge_t;

    //Création du graphe.
    Graph g;
    // Déclaration de tous les noeuds de nom : "1", "2", "3" ... dans le Graphe g.
    vertex_t V1 = add_vertex(VertexProperties(1),g);
    vertex_t V2 = add_vertex(VertexProperties(2),g);
    vertex_t V3 = add_vertex(VertexProperties(3),g);
    vertex_t V4 = add_vertex(VertexProperties(4),g);
    vertex_t V5 = add_vertex(VertexProperties(5),g);
    vertex_t V6 = add_vertex(VertexProperties(6),g);
    vertex_t V7 = add_vertex(VertexProperties(7),g);
    vertex_t V8 = add_vertex(VertexProperties(8),g);
    vertex_t V9 = add_vertex(VertexProperties(9),g);
    vertex_t V10 = add_vertex(VertexProperties(10),g);
    vertex_t V11 = add_vertex(VertexProperties(11),g);
    vertex_t V12 = add_vertex(VertexProperties(12),g);
    vertex_t V13 = add_vertex(VertexProperties(13),g);
    vertex_t V14 = add_vertex(VertexProperties(14),g);
    vertex_t V15 = add_vertex(VertexProperties(15),g);

    // Création d'un tableau Contenant le nom et la date de fin de chaque nœud : il est nécéssaire à la créaation de l'image.
    const string names [] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"};

    // Déclaration de tous les arcs (ex: nom : e1 qui est dirigé de A vers B dans le Graphe g).
    pair <Graph::edge_descriptor, bool> e1 = add_edge(V1, V2, g);
    pair <Graph::edge_descriptor, bool> e2 = add_edge(V1, V4, g);
    pair <Graph::edge_descriptor, bool> e3 = add_edge(V1, V10, g);
    pair <Graph::edge_descriptor, bool> e4 = add_edge(V1, V11, g);
    pair <Graph::edge_descriptor, bool> e5 = add_edge(V1, V15, g);
    pair <Graph::edge_descriptor, bool> e6 = add_edge(V2, V3, g);
    pair <Graph::edge_descriptor, bool> e7 = add_edge(V2, V6, g);
    pair <Graph::edge_descriptor, bool> e8 = add_edge(V2, V9, g);
    pair <Graph::edge_descriptor, bool> e9 = add_edge(V2, V14, g);
    pair <Graph::edge_descriptor, bool> e10 = add_edge(V3, V4, g);
    pair <Graph::edge_descriptor, bool> e11 = add_edge(V3, V7, g);
    pair <Graph::edge_descriptor, bool> e12 = add_edge(V4, V5, g);
    pair <Graph::edge_descriptor, bool> e13 = add_edge(V4, V9, g);
    pair <Graph::edge_descriptor, bool> e14 = add_edge(V4, V15, g);
    pair <Graph::edge_descriptor, bool> e15 = add_edge(V5, V6, g);
    pair <Graph::edge_descriptor, bool> e16 = add_edge(V5, V8, g);
    pair <Graph::edge_descriptor, bool> e17 = add_edge(V5, V12, g);
    pair <Graph::edge_descriptor, bool> e18 = add_edge(V6, V9, g);
    pair <Graph::edge_descriptor, bool> e19 = add_edge(V6, V14, g);
    pair <Graph::edge_descriptor, bool> e20 = add_edge(V7, V6, g);
    pair <Graph::edge_descriptor, bool> e21 = add_edge(V7, V15, g);
    pair <Graph::edge_descriptor, bool> e22 = add_edge(V8, V6, g);
    pair <Graph::edge_descriptor, bool> e23 = add_edge(V8, V7, g);
    pair <Graph::edge_descriptor, bool> e24 = add_edge(V8, V11, g);
    pair <Graph::edge_descriptor, bool> e25 = add_edge(V9, V7, g);
    pair <Graph::edge_descriptor, bool> e26 = add_edge(V9, V8, g);
    pair <Graph::edge_descriptor, bool> e27 = add_edge(V9, V10, g);
    pair <Graph::edge_descriptor, bool> e28 = add_edge(V10, V13, g);
    pair <Graph::edge_descriptor, bool> e29 = add_edge(V11, V10, g);
    pair <Graph::edge_descriptor, bool> e30 = add_edge(V11, V15, g);
    pair <Graph::edge_descriptor, bool> e31 = add_edge(V12, V11, g);
    pair <Graph::edge_descriptor, bool> e32 = add_edge(V13, V12, g);
    pair <Graph::edge_descriptor, bool> e33 = add_edge(V14, V11, g);
    pair <Graph::edge_descriptor, bool> e34 = add_edge(V14, V12, g);
    pair <Graph::edge_descriptor, bool> e35 = add_edge(V15, V10, g);
    pair <Graph::edge_descriptor, bool> e36 = add_edge(V15, V14, g);

    // Première recherche en profondeur, sur le graphe.
    custom_dfs_visitor_finish vis;
    cout << "Recherche en profondeur sur le Graphe:" << endl;
    depth_first_search(g , visitor(vis));   

    // Création des fichiers et streams nécessaires à la création des images.
    // Création du graphe normal.
    string filename = "graphe.dot";
    ofstream fout(filename.c_str());
    // Création du résultat.
    string filename2 = "dual.dot";
    ofstream fout2(filename2.c_str());
    // Création du graphe dual.
    string filename3 = "result.dot";
    ofstream fout3(filename3.c_str());

    // Création des images du graphe normal et du graphe dual.
    write_graphviz(fout, g, make_label_writer(&names[0]));
    system("dot -Tpng graphe.dot > graphe.png");
    write_graphviz(fout2, make_reverse_graph(g), make_label_writer(&names[0]));
    system("dot -Tpng dual.dot > dual.png");

    // Récupération de l'ordre date fin de la première recherche, et inversion de l'ordre pour l'avoir décroissant.
    vector<int> datefinDecroissant = vis.GetVectorF();
    reverse(datefinDecroissant.begin(), datefinDecroissant.end());

    // Création d'un vecteur aidant à isoler les composantes fortement connexes.
    // En ne contenant que les sommets pas encore explorés.
    vector<int> vect;
    for (int i = 0; i < 15; i++) {vect.push_back(i+1);}
    custom_dfs_visitor_discover tempVis;

    // On récupére dans indexmap l'index des noeuds de g.
    auto indexmap = get(vertex_index, g);
    // Dans colormap on crée des couleurs pour les noeuds à partir de leur index
    auto colormap = make_vector_property_map<default_color_type>(indexmap);
    vector<int> tempVect;
    vector<int> tempVect2;
    vector<int> tempDiff;

    // Parcours en profondeur sur le graphe dual, en suivant l'ordre date fin décroissant.
    cout <<endl<<endl<< "Recherche en profondeur sur le graphe dual, dans l'ordre décroissant de date fin:" <<endl;
    for (int i = 0; i < datefinDecroissant.size(); i++)
    {
        // On ne lance une recherche que sur les sommets que l'on n'a pas encore visité.
        vector<int>::iterator it = std::find(vect.begin(), vect.end(), datefinDecroissant[i]);
        if (it != vect.end())
        {
            cout <<endl<< "Recherche à partir de: " << datefinDecroissant[i] << endl;
            depth_first_visit(make_reverse_graph(g), i, tempVis, colormap);
            tempVect = tempVis.GetVectorD();
            set_difference(tempVect.begin(), tempVect.end(), tempVect2.begin(), tempVect2.end(), inserter(tempDiff, tempDiff.begin()));
            cout << "Composante fortement connexe trouvée: ";
            for (int p = 0; p < tempDiff.size(); p++)
              cout << tempDiff[p] << " ";
            cout <<endl;

            // Mise à jour du vecteur d'aide.
            for (int j = 0; j < tempDiff.size(); j++)
            {
                vector<int>::iterator it2 = std::find(vect.begin(), vect.end(), tempDiff[j]);
                if (it2 != vect.end()) {vect.erase(it2);}
            }
                // Pour la représentation graphique, suppression des arcs n'appartenant pas aux composantes fortement connexes.
                if (tempDiff.size() == 1)
                {
                    clear_out_edges(i,g);
                    clear_in_edges(i,g);
                }
                else for (int j = 0; j < tempDiff.size(); j++)
                {
                    for (int k = 0; k < vect.size(); k++)
                    {
                        remove_edge(tempDiff[j]-1, vect[k]-1, g);
                        remove_edge(vect[k]-1, tempDiff[j]-1, g);
                    }
                }
                tempVect2 = tempVect;
                tempDiff.clear();
          }
    }
    // Création de l'image finale, contenant les composantes fortement connexes.
    write_graphviz(fout3, g, make_label_writer(&names[0]));
    system("dot -Tpng result.dot > result.png");
    cout << endl;
    return 0;
}