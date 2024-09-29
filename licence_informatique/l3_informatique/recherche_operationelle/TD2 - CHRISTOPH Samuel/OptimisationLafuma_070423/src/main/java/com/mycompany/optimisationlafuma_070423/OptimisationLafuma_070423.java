package com.mycompany.optimisationlafuma_070423;

/**
 *
 * @author schristoph
 */

/* ---------------------------------------------------------------------------------------------*/

/**
 * Librairies nécessaires pour générer le graphe
 */
import org.jgrapht.alg.shortestpath.BellmanFordShortestPath;
import org.jgrapht.graph.*;

/**
 * Librairie pour à la gestion d'erreurs
 */
import java.io.*;

/* ---------------------------------------------------------------------------------------------*/

/**
 * Création de la classe publique du programme
 */
public class OptimisationLafuma_070423 {
    
    /**
     * Fonction principale
     * @param args
     * @throws java.io.IOException
     */
    public static void main(String args[]) throws IOException {

        /* ------------------------------------------------------------------------------------------------ */
        /* ------------------------------------- VERSION GENTLEMEN ---------------------------------------- */
        /* ------------------------------------------------------------------------------------------------ */
        
        // Initialisation du graphe G Gentlemen
        SimpleDirectedWeightedGraph<String, DefaultWeightedEdge> g = new SimpleDirectedWeightedGraph<>(DefaultWeightedEdge.class);
         
        // Création des noeuds du graphe G Gentlemen
        g.addVertex("S");
        g.addVertex("F Avril");
        g.addVertex("F Mai");
        g.addVertex("F Juin");
        g.addVertex("F Juillet");
        g.addVertex("V Avril");
        g.addVertex("V Mai");
        g.addVertex("V Juin");
        g.addVertex("V Juillet");
        g.addVertex("P");
        
        // Création des arcs du graphe G Gentlemen (S)
        DefaultWeightedEdge edge1 = g.addEdge("S", "F Avril");
        DefaultWeightedEdge edge2 = g.addEdge("S", "F Mai");
        DefaultWeightedEdge edge3 = g.addEdge("S", "F Juin");
        DefaultWeightedEdge edge4 = g.addEdge("S", "F Juillet");
        
        // Création des arcs du graphe G Gentlemen (Avril)
        DefaultWeightedEdge edge5 = g.addEdge("F Avril", "V Avril");
        DefaultWeightedEdge edge6 = g.addEdge("F Avril", "V Mai");
        DefaultWeightedEdge edge7 = g.addEdge("F Avril", "V Juin");
        DefaultWeightedEdge edge8 = g.addEdge("F Avril", "V Juillet");

        // Création des arcs du graphe G Gentlemen (Mai)        
        DefaultWeightedEdge edge9 = g.addEdge("F Mai", "V Avril");
        DefaultWeightedEdge edge10 = g.addEdge("F Mai", "V Mai");
        DefaultWeightedEdge edge11 = g.addEdge("F Mai", "V Juin");
        DefaultWeightedEdge edge12 = g.addEdge("F Mai", "V Juillet");
        
        // Création des arcs du graphe G Gentlemen (Juin)
        DefaultWeightedEdge edge13 = g.addEdge("F Juin", "V Avril");
        DefaultWeightedEdge edge14 = g.addEdge("F Juin", "V Mai");
        DefaultWeightedEdge edge15 = g.addEdge("F Juin", "V Juin");
        DefaultWeightedEdge edge16 = g.addEdge("F Juin", "V Juillet");
        
        // Création des arcs du graphe G Gentlemen (Juillet)
        DefaultWeightedEdge edge17 = g.addEdge("F Juillet", "V Avril");
        DefaultWeightedEdge edge18 = g.addEdge("F Juillet", "V Mai");
        DefaultWeightedEdge edge19 = g.addEdge("F Juillet", "V Juin");
        DefaultWeightedEdge edge20 = g.addEdge("F Juillet", "V Juillet");
        
        // Création des arcs du graphe G Gentlemen (P)
        DefaultWeightedEdge edge21 = g.addEdge("V Avril", "P");
        DefaultWeightedEdge edge22 = g.addEdge("V Mai", "P");
        DefaultWeightedEdge edge23 = g.addEdge("V Juin", "P");
        DefaultWeightedEdge edge24 = g.addEdge("V Juillet", "P");
        
        /* -------------------------------------- Hypothèse 1 ----------------------------------------- */
        
        // Ajout des coûts de production sur chaque arcs
        g.setEdgeWeight(edge1, 0);
        g.setEdgeWeight(edge2, 0);
        g.setEdgeWeight(edge3, 0);
        g.setEdgeWeight(edge4, 0);
        g.setEdgeWeight(edge5, 200);
        g.setEdgeWeight(edge6, 210);
        g.setEdgeWeight(edge7, 220);
        g.setEdgeWeight(edge8, 230);
        g.setEdgeWeight(edge9, 195);
        g.setEdgeWeight(edge10, 180);
        g.setEdgeWeight(edge11, 190);
        g.setEdgeWeight(edge12, 200);
        g.setEdgeWeight(edge13, 180);
        g.setEdgeWeight(edge14, 165);
        g.setEdgeWeight(edge15, 150);
        g.setEdgeWeight(edge16, 160);
        g.setEdgeWeight(edge17, 215);
        g.setEdgeWeight(edge18, 200);
        g.setEdgeWeight(edge19, 185);
        g.setEdgeWeight(edge20, 170);
        g.setEdgeWeight(edge21, 0);
        g.setEdgeWeight(edge22, 0);
        g.setEdgeWeight(edge23, 0);
        g.setEdgeWeight(edge24, 0);
        
        // Calcul du chemin le plus court pour le graphe G Gentlemen
        BellmanFordShortestPath<String, DefaultWeightedEdge> gentlemen1 = new BellmanFordShortestPath<>(g);
        System.out.println("Hypothèse 1 : Gentleman : " + gentlemen1.getPath("S", "P").getVertexList());

        /* -------------------------------------- Hypothèse 2 ----------------------------------------- */
        
        // Actualisation des noeuds du graphe G Gentlemen (pour le mois de juillet)
        g.setEdgeWeight(edge17, 250);
        g.setEdgeWeight(edge18, 235);
        g.setEdgeWeight(edge19, 220);
        g.setEdgeWeight(edge20, 205);
        
        // Calcul du chemin le plus court pour le graphe G Gentlemen
        BellmanFordShortestPath<String, DefaultWeightedEdge> gentlemen2 = new BellmanFordShortestPath<>(g);
        System.out.println("Hypothèse 2 : Gentleman : " + gentlemen2.getPath("S", "P").getVertexList());
        
        /* -------------------------------------- Hypothèse 3 ----------------------------------------- */
        
        // Actualisation des noeuds du graphe G Gentlemen (pour le mois de juillet)
        g.setEdgeWeight(edge17, 285);
        g.setEdgeWeight(edge18, 270);
        g.setEdgeWeight(edge19, 255);
        g.setEdgeWeight(edge20, 240);
        
        // Calcul du chemin le plus court pour le graphe G Gentlemen
        BellmanFordShortestPath<String, DefaultWeightedEdge> gentlemen3 = new BellmanFordShortestPath<>(g);
        System.out.println("Hypothèse 3 : Gentleman : " + gentlemen3.getPath("S", "P").getVertexList() + "\n");
        
        /* ------------------------------------------------------------------------------------------------ */
        /* ---------------------------------------- VERSION LADY ------------------------------------------ */
        /* ------------------------------------------------------------------------------------------------ */
        
        // Initialisation du graphe L Lady
        SimpleDirectedWeightedGraph<String, DefaultWeightedEdge> l = new SimpleDirectedWeightedGraph<>(DefaultWeightedEdge.class);
        
        // Création des noeuds du graphe L Lady
        l.addVertex("S");
        l.addVertex("F Avril");
        l.addVertex("F Mai");
        l.addVertex("F Juin");
        l.addVertex("F Juillet");
        l.addVertex("V Avril");
        l.addVertex("V Mai");
        l.addVertex("V Juin");
        l.addVertex("V Juillet");
        l.addVertex("P");
        
        // Création des arcs du graphe L Lady (S)
        DefaultWeightedEdge edge25 = l.addEdge("S", "F Avril");
        DefaultWeightedEdge edge26 = l.addEdge("S", "F Mai");
        DefaultWeightedEdge edge27 = l.addEdge("S", "F Juin");
        DefaultWeightedEdge edge28 = l.addEdge("S", "F Juillet");  
        
        // Création des arcs du graphe L Lady (Avril)
        DefaultWeightedEdge edge29 = l.addEdge("F Avril", "V Avril");
        DefaultWeightedEdge edge30 = l.addEdge("F Avril", "V Mai");
        DefaultWeightedEdge edge31 = l.addEdge("F Avril", "V Juin");
        DefaultWeightedEdge edge32 = l.addEdge("F Avril", "V Juillet");
        
        // Création des arcs du graphe L Lady (Mai)
        DefaultWeightedEdge edge33 = l.addEdge("F Mai", "V Avril");
        DefaultWeightedEdge edge34 = l.addEdge("F Mai", "V Mai");
        DefaultWeightedEdge edge35 = l.addEdge("F Mai", "V Juin");
        DefaultWeightedEdge edge36 = l.addEdge("F Mai", "V Juillet");
        
        // Création des arcs du graphe L Lady (Juin)
        DefaultWeightedEdge edge37 = l.addEdge("F Juin", "V Avril");
        DefaultWeightedEdge edge38 = l.addEdge("F Juin", "V Mai");
        DefaultWeightedEdge edge39 = l.addEdge("F Juin", "V Juin");
        DefaultWeightedEdge edge40 = l.addEdge("F Juin", "V Juillet");
        
        // Création des arcs du graphe L Lady (Juilllet)
        DefaultWeightedEdge edge41 = l.addEdge("F Juillet", "V Avril");
        DefaultWeightedEdge edge42 = l.addEdge("F Juillet", "V Mai");
        DefaultWeightedEdge edge43 = l.addEdge("F Juillet", "V Juin");
        DefaultWeightedEdge edge44 = l.addEdge("F Juillet", "V Juillet");
        
        // Création des arcs du graphe L Lady (P)
        DefaultWeightedEdge edge45 = l.addEdge("V Avril", "P");
        DefaultWeightedEdge edge46 = l.addEdge("V Mai", "P");
        DefaultWeightedEdge edge47 = l.addEdge("V Juin", "P");
        DefaultWeightedEdge edge48 = l.addEdge("V Juillet", "P");
        
        /* -------------------------------------- Hypothèse 1 ----------------------------------------- */
        
        // Ajout des coûts de production sur chaque arcs
        l.setEdgeWeight(edge25, 0);
        l.setEdgeWeight(edge26, 0);
        l.setEdgeWeight(edge27, 0);
        l.setEdgeWeight(edge28, 0);
        l.setEdgeWeight(edge29, 210);
        l.setEdgeWeight(edge30, 220);
        l.setEdgeWeight(edge31, 230);
        l.setEdgeWeight(edge32, 240);
        l.setEdgeWeight(edge33, 200);
        l.setEdgeWeight(edge34, 185);
        l.setEdgeWeight(edge35, 195);
        l.setEdgeWeight(edge36, 205);
        l.setEdgeWeight(edge37, 185);
        l.setEdgeWeight(edge38, 170);
        l.setEdgeWeight(edge39, 155);
        l.setEdgeWeight(edge40, 165);
        l.setEdgeWeight(edge41, 225);
        l.setEdgeWeight(edge42, 210);
        l.setEdgeWeight(edge43, 195);
        l.setEdgeWeight(edge44, 180);
        l.setEdgeWeight(edge45, 0);
        l.setEdgeWeight(edge46, 0);
        l.setEdgeWeight(edge47, 0);
        l.setEdgeWeight(edge48, 0);
        
        // Calcul du chemin le plus court pour le graphe L Lady
        BellmanFordShortestPath<String, DefaultWeightedEdge> lady1 = new BellmanFordShortestPath<>(l);
        System.out.println("Hypothèse 1 : Lady : " + lady1.getPath("S", "P").getVertexList());
        
        /* -------------------------------------- Hypothèse 2 ----------------------------------------- */
        
        // Actualisation des noeuds du graphe L Lady (pour le mois de juillet)
        l.setEdgeWeight(edge41, 260);
        l.setEdgeWeight(edge42, 245);
        l.setEdgeWeight(edge43, 230);
        l.setEdgeWeight(edge44, 215);
        
        // Calcul du chemin le plus court pour le graphe L Lady
        BellmanFordShortestPath<String, DefaultWeightedEdge> lady2 = new BellmanFordShortestPath<>(l);
        System.out.println("Hypothèse 2 : Lady : " + lady2.getPath("S", "P").getVertexList());
        
        /* -------------------------------------- Hypothèse 3 ----------------------------------------- */
        
        // Actualisation des noeuds du graphe L Lady (pour le mois de juillet)
        l.setEdgeWeight(edge41, 260);
        l.setEdgeWeight(edge42, 245);
        l.setEdgeWeight(edge43, 230);
        l.setEdgeWeight(edge44, 215);
        
        // Calcul du chemin le plus court pour le graphe L Lady
        BellmanFordShortestPath<String, DefaultWeightedEdge> lady3 = new BellmanFordShortestPath<>(l);
        System.out.println("Hypothèse 3 : Lady : " + lady3.getPath("S", "P").getVertexList());
    }
}