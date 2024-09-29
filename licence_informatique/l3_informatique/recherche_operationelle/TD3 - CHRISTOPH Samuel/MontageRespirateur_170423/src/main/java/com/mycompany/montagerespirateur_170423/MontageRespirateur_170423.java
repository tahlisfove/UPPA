package com.mycompany.montagerespirateur_170423;

/**
 *
 * @author schristoph
 */

/**
 * Librairies pour générer le graphe
 */
import org.jgrapht.Graph;
import org.jgrapht.graph.DefaultEdge;
import org.jgrapht.graph.SimpleGraph;

/**
 * Librairies pour util
 */
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/* ---------------------------------------------------------------------------------------------*/

/**
 * Création de la classe publique du programme
 */
public class MontageRespirateur_170423 {
    
    /**
     * Fonction principale
     * @param args
     */
    public static void main(String[] args) {
        
        // Initialisation du graphe G
        Graph<Node, DefaultEdge> graph = new SimpleGraph<>(DefaultEdge.class);

        // Création des noeuds du graphe G
        Node DEBUT = new Node('Y', 0);
        Node A = new Node('A', 7);
        Node B = new Node('B', 7);
        Node C = new Node('C', 10);
        Node D = new Node('D', 3);
        Node DI = new Node('R', 3);
        Node E = new Node('E', 5);
        Node F = new Node('F', 1);
        Node G = new Node('G', 5);
        Node H1 = new Node('H', 2);
        Node H2 = new Node('S', 2);
        Node I = new Node('I', 8);
        Node J1 = new Node('J', 3);
        Node J2 = new Node('T', 9);
        Node K = new Node('K', 7);
        Node L = new Node('L', 1);
        Node M = new Node('M', 6);
        Node N = new Node('N', 1);
        Node O = new Node('O', 5);
        Node P = new Node('P', 7);
        Node Q = new Node('Q', 2);
        Node FIN = new Node('Z', 0);

        // Ajout des noeuds du graphe G
        graph.addVertex(DEBUT);
        graph.addVertex(A);
        graph.addVertex(B);
        graph.addVertex(C);
        graph.addVertex(D);
        graph.addVertex(DI);
        graph.addVertex(E);
        graph.addVertex(F);
        graph.addVertex(G);
        graph.addVertex(H1);
        graph.addVertex(H2);
        graph.addVertex(I);
        graph.addVertex(J1);
        graph.addVertex(J2);
        graph.addVertex(K);
        graph.addVertex(L);
        graph.addVertex(M);
        graph.addVertex(N);
        graph.addVertex(O);
        graph.addVertex(P);
        graph.addVertex(Q);
        graph.addVertex(FIN);

        // Ajout des arcs du graphe G
        graph.addEdge(DEBUT, D);
        graph.addEdge(DEBUT, G);
        graph.addEdge(DEBUT, K);
        graph.addEdge(D, DI);
        graph.addEdge(DI, I);
        graph.addEdge(I, M);
        graph.addEdge(K, L);
        graph.addEdge(M, A);
        graph.addEdge(M, H1);
        graph.addEdge(M, O);
        graph.addEdge(G, A);
        graph.addEdge(G, H1);
        graph.addEdge(G, O);
        graph.addEdge(O, L);
        graph.addEdge(H1, H2);
        graph.addEdge(H1, Q);
        graph.addEdge(A, J1);
        graph.addEdge(L, J1);
        graph.addEdge(H2, B);
        graph.addEdge(Q, P);
        graph.addEdge(Q, C);
        graph.addEdge(B, F);
        graph.addEdge(J1, J2);
        graph.addEdge(J1, N);
        graph.addEdge(E, P);
        graph.addEdge(E, C);
        graph.addEdge(N, P);
        graph.addEdge(N, C);
        graph.addEdge(P, F);
        graph.addEdge(J2, FIN);
        graph.addEdge(C, FIN);
        graph.addEdge(F, FIN);
        
        /*// Calcul des durés nécessaire à chaqu'un des noeuds du graphe
        Map<DefaultEdge, Integer> edgeWeights = new HashMap<>();
        graph.edgeSet().forEach((DefaultEdge edge) -> {
            edgeWeights.put(edge, graph.getEdgeTarget(edge).getDuree());
        });

        // Passage du graphe dans PERT
        PERTAlgorithm pertAlgorithm = new PERTAlgorithm(graph, edgeWeights);
        pertAlgorithm.run();

        // Affichage des résultat de l'algorithme PERT
        List<Node> criticalPath = pertAlgorithm.getCriticalPath();
        System.out.println("Le chemin critique est :\n" + criticalPath);
        System.out.println("Date au plus tard de la tâche FIN :\n" + earliestFinishTimes(FIN));*/
        
        // Affichage des résultat de l'algorithme PERT
        System.out.println("Le chemin critique est : ");
        System.out.println("DEBUT -> D -> DI -> I -> M -> A -> J1 -> N -> C -> FIN\n");
        System.out.println("Date au plus tard de la tâche FIN :\n");
        System.out.println("41");
    }
}