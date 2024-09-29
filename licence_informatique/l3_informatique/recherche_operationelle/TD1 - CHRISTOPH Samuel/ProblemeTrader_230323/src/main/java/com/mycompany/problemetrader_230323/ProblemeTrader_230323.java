package com.mycompany.problemetrader_230323;

/**
 *
 * @author schristoph
 */

/* ---------------------------------------------------------------------------------------------*/

/**
 * Librairies nécessaires pour générer le graphe
 */
import org.jgrapht.alg.interfaces.ShortestPathAlgorithm.SingleSourcePaths;
import org.jgrapht.alg.shortestpath.DijkstraShortestPath;
import org.jgrapht.alg.flow.MaximumFlowAlgorithmBase;
import org.jgrapht.alg.flow.EdmondsKarpMFImpl;
import org.jgrapht.graph.SimpleDirectedWeightedGraph;
import org.jgrapht.graph.*;

/**
 * Librairie pour à la gestion d'erreurs et d’affichage
 */
import java.io.IOException;
import java.util.Map;
import java.util.Set;

/* ---------------------------------------------------------------------------------------------*/

/**
 * Création de la classe publique du programme
 */
public class ProblemeTrader_230323 {
    
    /**
     * Fonction de création du graphe G
     * @return
     */
    public static SimpleDirectedWeightedGraph<String, DefaultWeightedEdge> g(){
        
        // Initialisation du graphe G
        SimpleDirectedWeightedGraph<String, DefaultWeightedEdge> graph = new SimpleDirectedWeightedGraph<>(DefaultWeightedEdge.class);
 
        // Création des noeuds du graphe G
        graph.addVertex("S");
        graph.addVertex("E1");
        graph.addVertex("E2");
        graph.addVertex("F1");
        graph.addVertex("F2");
        graph.addVertex("A1");
        graph.addVertex("A2");
        graph.addVertex("A3");
        graph.addVertex("P");
       
        // Création des arcs du graphe G
        DefaultWeightedEdge Se1 = graph.addEdge("S","E1"); 
        graph.setEdgeWeight(Se1, 100);
        DefaultWeightedEdge Se2 = graph.addEdge("S","E2"); 
        graph.setEdgeWeight(Se2, 100);
        DefaultWeightedEdge e1a1 = graph.addEdge("E1","A1"); 
        graph.setEdgeWeight(e1a1, 30);
        DefaultWeightedEdge e1f1 = graph.addEdge("E1","F1"); 
        graph.setEdgeWeight(e1f1, 60);
        DefaultWeightedEdge e2f1 = graph.addEdge("E2","F1"); 
        graph.setEdgeWeight(e2f1, 50);
        DefaultWeightedEdge e2f2 = graph.addEdge("E2","F2"); 
        graph.setEdgeWeight(e2f2, 40);
        DefaultWeightedEdge f1a1 = graph.addEdge("F1","A1"); 
        graph.setEdgeWeight(f1a1, 30);
        DefaultWeightedEdge f1a2 = graph.addEdge("F1","A2"); 
        graph.setEdgeWeight(f1a2, 50);
        DefaultWeightedEdge f1a3 = graph.addEdge("F1","A3"); 
        graph.setEdgeWeight(f1a3, 40);
        DefaultWeightedEdge f1f2 = graph.addEdge("F1","F2"); 
        graph.setEdgeWeight(f1f2, 20);
        DefaultWeightedEdge f2a3 = graph.addEdge("F2","A3"); 
        graph.setEdgeWeight(f2a3, 50);
        DefaultWeightedEdge a1P = graph.addEdge("A1","P"); 
        graph.setEdgeWeight(a1P, 1000);
        DefaultWeightedEdge a2P = graph.addEdge("A2","P"); 
        graph.setEdgeWeight(a2P, 1000);
        DefaultWeightedEdge a3P = graph.addEdge("A3","P"); 
        graph.setEdgeWeight(a3P, 1000);
        
        // Envoi du graphe G vers la fonction principale
        return graph;
    }
    
    /**
     * Fonction principale
     * @param args
     * @throws java.io.IOException
     */
    public static void main(String[] args) throws IOException {
        
        /* ------------------------------------------------------------------------------------------------ */
        
        // Lancement de l'algorithme EdmondKarp avec le graphe G
        SimpleDirectedWeightedGraph<String, DefaultWeightedEdge> graphBase = g();
        EdmondsKarpMFImpl<String, DefaultWeightedEdge> grapheEdmonds = new EdmondsKarpMFImpl<>(graphBase,MaximumFlowAlgorithmBase.DEFAULT_EPSILON);

	    // Calcul et affichage du chemin le plus court pour entre S et P        
        DijkstraShortestPath<String, DefaultWeightedEdge> dijkstraAlg = new DijkstraShortestPath<>(graphBase);
        SingleSourcePaths<String, DefaultWeightedEdge> iPaths = dijkstraAlg.getPaths("S");
        System.out.println("Chemin le plus court allant de S vers P:" + iPaths.getPath("P"));
        
        // Affichage du flot initial (vide).
        System.out.println("\nFlot initial " + iPaths.getWeight("S"));

        // Affichage du flot max apres passage dans l'algorithme EdmondsKarp
        System.out.println("\nFlot maximum actuel = " + grapheEdmonds.calculateMaximumFlow("S", "P"));

        // Affiche chaque arc du graphe G avec leur flux après passage dans EdmondKarp, un par ligne
        Map<DefaultWeightedEdge, Double> flowMap = grapheEdmonds.getFlowMap();
        System.out.println("\nFlux associés à chaque arc :");
        for (DefaultWeightedEdge edge : flowMap.keySet()) {
            System.out.println("Arc " + edge + " : " + flowMap.get(edge));
        }
        
        // Calcul de la capacité de la st-coupe et récupération des arcs
        Set<DefaultWeightedEdge> cutEdges = grapheEdmonds.getCutEdges();

        // Affichage des arcs un en dessous des autres ainsi que leur flux
        System.out.println("\nArcs de la st-coupe minimale:");
        for (DefaultWeightedEdge edge : cutEdges) {
            String debut = graphBase.getEdgeSource(edge);
            String fin = graphBase.getEdgeTarget(edge);
            double capacite = graphBase.getEdgeWeight(edge);
            System.out.println("De : " + debut + " à : " + fin + " avec capacité : " + capacite);
        }
    }
}