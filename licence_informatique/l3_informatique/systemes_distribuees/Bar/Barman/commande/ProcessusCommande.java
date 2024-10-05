/**
 * Packages for communication in java RMI
 */
import java.rmi.server.UnicastRemoteObject;
import java.rmi.registry.LocateRegistry;
import java.rmi.NotBoundException;
import java.rmi.registry.Registry;
import java.rmi.RemoteException;
import java.rmi.Naming;

/**
 * Packages for networking
 */
import java.net.*;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.io.IOException;

/**
 * Packages for util
 */
import java.util.Scanner;
import java.util.Vector;
import java.util.Arrays;

/**
 * Implementation of ProcessusCommande class
 */
public class ProcessusCommande {

    /**
     * Indique si la méthode closeTerminal a déjà été appelée
     */
    public static boolean isCloseTerminalCalled = false;

    /**
     * Fonction pour fermer le terminal
     */
    public static void closeTerminal() {
        // Vérifie si la fonction est en cours d'exécution
        if (isCloseTerminalCalled) {
            return;
        }
        // Passe à true
        isCloseTerminalCalled = true;

        // Attend et gère les erreurs de l'attente pour un meilleur affichage visuel
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
            Thread.currentThread().interrupt();
        }

        // Affiche le menu de fermeture du fournisseur
        System.out.println("                                                                         ");
        System.out.println("                                    *                                    ");
        System.out.println("                                   ***                                   ");
        System.out.println("                                  *****                                  ");
        System.out.println("                                                                         ");
        System.out.println("  +---------------------------------------------------------------------+");
        System.out.println("  |         Merci d'utiliser le service DeLaChoppe, au revoir!          |");
        System.out.println("  +---------------------------------------------------------------------+");
        System.out.println("                                                                         ");

        // Attend et gère les erreurs de l'attente pour un meilleur affichage visuel
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
            Thread.currentThread().interrupt();
        }

        // Ferme le terminal
        try {
            String os = System.getProperty("os.name").toLowerCase();
            if (os.contains("nix") || os.contains("nux") || os.contains("aix") || os.contains("mac")) {
                String[] cmd = {"/bin/bash", "-c", "kill -9 $(ps -p $(ps -p $$ -o ppid=) -o ppid=)"};
                Runtime.getRuntime().exec(cmd);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Retire le programme du système
        System.exit(0);
    }

    /**
     * Main function
     */
    public static void main(String[] args) throws IOException {
    
    // Vérifie que tous les arguments ont été passés en ligne de commande
    if (args.length < 4) {
	    System.err.println("Un élément est mal récuperé: ProcessusCommande <adresse_ip_client> <port> <tireuse_vide> <adresse_ip_fournisseur>");
	    System.exit(1);
	}

    // Récupère les arguments passés en ligne de commande
    String adresseIp = args[0];
    int port = Integer.parseInt(args[1]);
    String fournisseurIp = args[2];
    int tireuseVide = Integer.parseInt(args[3]);

    try {
        // Récupère l'objet distant IBiere à partir du registre RMI
        IBiere stub = (IBiere) Naming.lookup("rmi://" + fournisseurIp + "/DedeLaChope");

        // Récupère la liste des bières blondes et ambrées disponibles chez le fournisseur
        Vector<Biere> blondes = stub.listeBlondes();
        Vector<Biere> ambrees = stub.listeAmbrees();

        // Crée un objet Scanner pour lire l'entrée utilisateur
        try (Scanner scanner = new Scanner(System.in)) {

            //Boucle principale pour afficher le menu et traiter les commandes de l'utilisateur
            while (true) {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    Thread.currentThread().interrupt();
                }

                // Affiche le menu de commande
                System.out.println("                                                                         ");
                System.out.println("                                                                         ");
                System.out.println("                                  *****                                  ");
                System.out.println("                                   ***                                   ");
                System.out.println("                                    *                                    ");
                System.out.println("                                                                         ");
                System.out.println("  +---------------------------------------------------------------------+");
                System.out.println("  |                         Menu de commande:                           |");
                System.out.println("  +---------------------------------------------------------------------+");
                System.out.println("  |               1. Afficher la liste futs disponibles                 |");
                System.out.println("  |                  2. Commander un fut de bière                       |");
                System.out.println("  +---------------------------------------------------------------------+");
                System.out.println("                                                                         ");

                // Lit l'entrée utilisateur
                System.out.println("Choisissez une option (1 ou 2) :");
                String choix_commande = scanner.nextLine();
                System.out.println("                                ");

                // Utilise une structure switch pour exécuter l'action choisie par l'utilisateur
                switch (choix_commande) {
                    
                    case "1":
                        // Affiche la liste des bières disponibles
                        System.out.println("  +---------------------------------------------------------------------+");
                        System.out.println("  |   	    Liste des bières disponibles chez le fournisseur:           |");
                        System.out.println("  +---------------------------------------------------------------------+");
                        System.out.println("                                                                         ");

                        // Affiche la liste des bières blondes disponibles
                        System.out.println("  -Blondes:");
                        for (Biere blonde : blondes) {
                            System.out.println("   - " + blonde.getNom() + " (" + blonde.getDegre() + "°)");
                        }
                        
                        // Affiche la liste des bières ambrées disponibles
                        System.out.println("  -Ambrées:");
                        for (Biere ambree : ambrees) {
                            System.out.println("   - " + ambree.getNom() + " (" + ambree.getDegre() + "°)");
                        }
                            
                        break;

                    case "2":
                        // Demande à l'utilisateur de choisir une bière à commander
                        if (tireuseVide == 1) {
                            System.out.println("  +---------------------------------------------------------------------+");
                            System.out.println("  |             Quelle bière blonde voulez-vous commander?              |");
                            System.out.println("  +---------------------------------------------------------------------+");
                            System.out.println("                                                                         ");

                            // Affiche les bières blondes disponibles pour le barman avant la commande
                            for (Biere blonde : blondes) {
                                System.out.println("   - " + blonde.getNom() + " (" + blonde.getDegre() + "°)");
                            }
                            System.out.println("                                                                    ");

                        } else if (tireuseVide == 2) {
                            System.out.println("  +---------------------------------------------------------------------+");
                            System.out.println("  |             Quelle bière ambrée voulez-vous commander?              |");
                            System.out.println("  +---------------------------------------------------------------------+");
                            System.out.println("                                                                         ");

                            // Affiche les bières ambrées disponibles pour le barman avant la commande
                            for (Biere ambree : ambrees) {
                                System.out.println("   - " + ambree.getNom() + " (" + ambree.getDegre() + "°)");
                            }
                            System.out.println("                                                                         ");
                        }

                        // Lit l'entrée utilisateur pour obtenir le nom de la bière à commander
                        System.out.println("Entrez le nom de la biére à commmander :");
                        String nomBiere = scanner.nextLine();
                        System.out.println("                                        ");

                        // Appelle la méthode acheterBiere() de l'objet distant pour acheter la bière demandée
                        Biere biereCommandee = stub.acheterBiere(nomBiere);

                        // Si la bière est disponible, affiche un message de confirmation et envoie les informations de la bière via UDP
                        if (biereCommandee != null) {
                            // Vérifie si la bière correspond au fût vide disponible
                            if ((tireuseVide == 1 && biereCommandee.getCouleur() == Biere.BLONDE) || (tireuseVide == 2 && biereCommandee.getCouleur() == Biere.AMBREE)) {
                                // Demande confirmation de l'achat à l'utilisateur
                                System.out.println("Voulez-vous confirmer l'achat de la bière " + biereCommandee.getNom() + " ? (oui/non)");

                                // Lit la réponse de l'utilisateur
                                String confirmation = scanner.nextLine();

                                // Si l'utilisateur confirme l'achat, affiche les informations de la bière et les envoie via UDP
                                if (confirmation.equalsIgnoreCase("oui")) {
                                    System.out.println("                                                                         ");
                                    System.out.println("  +---------------------------------------------------------------------+");
                                    System.out.println("  | 	            Informations sur la bière commandée:                |");
                                    System.out.println("  +---------------------------------------------------------------------+");
                                    System.out.println("                                                                         ");
                                    System.out.println("      - Nom : " + biereCommandee.getNom() + "                            ");
                                    System.out.println("      - Couleur : " + biereCommandee.getCouleur() + "                    ");
                                    System.out.println("      - Degré d'alcool : " + biereCommandee.getDegre() + "°              ");
                                    System.out.println("                                                                         ");
            
                                    // Obtient la couleur de la bière sous forme de chaîne de caractères
                                    String couleur = biereCommandee.getCouleur() == Biere.AMBREE ? "Ambrée" : "Blonde";

                                    // Crée un objet InetAddress pour le serveur UDP et un objet DatagramPacket pour les données à envoyer
                                    try {
                                        // Obtient l'adresse IP du serveur
                                        InetAddress serverAddress = InetAddress.getByName(adresseIp);
                                        // Obtient le port du serveur
                                        int serverPort = port;

                                        // Concatène les informations de la bière dans une chaîne de caractères
                                        String beerInfo = couleur + ", " + biereCommandee.getNom() + ", " + biereCommandee.getDegre() + "°";

                                        // Convertit les informations de la bière en octets et crée un DatagramPacket à envoyer
                                        byte[] sendData = beerInfo.getBytes();
                                        DatagramPacket packet = new DatagramPacket(sendData, sendData.length, serverAddress, serverPort);

                                        // Crée un objet DatagramSocket et envoie le paquet à l'aide de la méthode send()
                                        DatagramSocket udpSocket = null;
                                        try {
                                            // Crée un nouvel objet DatagramSocket
                                            udpSocket = new DatagramSocket();
                                            // Envoie le paquet à l'aide de la méthode send()
                                            udpSocket.send(packet);
                                        } catch (Exception e) {
                                            // Si une exception se produit pendant l'opération d'envoi, affiche un message d'erreur avec le message d'erreur correspondant
                                            System.out.println("                                                                         ");
                                            System.out.println("  +---------------------------------------------------------------------+");
                                            System.err.println("  |     Erreur lors de l'envoi des informations de la bière via UDP.    |");
                                            System.out.println("  +---------------------------------------------------------------------+");
                                            System.out.println("                                                                         ");
                                            System.err.println(e.getMessage());
                                        } finally {
                                            // Ferme l'objet DatagramSocket
                                            if (udpSocket != null) {
                                                udpSocket.close();
                                            }
                                        }
                                    } catch (Exception e) {
                                        // Si une exception se produit lors de la création de l'objet InetAddress, affiche un message d'erreur avec le message d'erreur correspondant
                                        System.out.println("                                                                         ");
                                        System.out.println("  +---------------------------------------------------------------------+");
                                        System.err.println("  |     Erreur lors de l'envoi des informations de la bière via UDP.    |");
                                        System.out.println("  +---------------------------------------------------------------------+");
                                        System.out.println("                                                                         ");
                                        System.err.println(e.getMessage());
                                    }

                                    // Ferme la console
                                    closeTerminal();

                                } else {
                                    // Affiche un message d'erreur si le barman annule la commande
                                    System.out.println("                                                                         ");
				     System.out.println("                                    *                                    ");
				     System.out.println("                                   ***                                   ");
				     System.out.println("                                  *****                                  ");
                                    System.out.println("                                                                         ");
                                    System.out.println("  +---------------------------------------------------------------------+");
                                    System.out.println("  |             Commande annulée, retour au menu principal.             |");
                                    System.out.println("  +---------------------------------------------------------------------+");
                                    System.out.println("                                                                         ");
                                }
                            } else {
                                // Affiche un message d'erreur si le type de bière ne correspond pas à celui du fût vide
                                System.out.println("                                                                         ");
                                System.out.println("  +---------------------------------------------------------------------+");
                                System.out.println("  |         Cette biére n'est pas compatible avec le fût vide.          |");
                                System.out.println("  +---------------------------------------------------------------------+");
                                System.out.println("                                                                         ");
                            }
                        } else {
                            // Affiche un message d'erreur si la bière n'existe pas chez le fournisseur DeLaChoppe
                            System.out.println("                                                                         ");
                            System.out.println("  +---------------------------------------------------------------------+");
                            System.out.println("  |          Bière inexistante chez le fournisseur DeLaChoppe.          |");
                            System.out.println("  +---------------------------------------------------------------------+");
                            System.out.println("                                                                         ");
                        }

                        break;

                    default:
                        // Affiche un message d'erreur si le choix de niveau de menu n'existe pas
                        System.out.println("                                                                         ");
                        System.out.println("  +---------------------------------------------------------------------+");
                        System.out.println("  |               Veuillez entrer un choix menu valide.                 |");
                        System.out.println("  +---------------------------------------------------------------------+");
                        System.out.println("                                                                         ");

                        break;
                    }
                }
            }
        } catch (NotBoundException e) {
            // Gestion des exceptions en cas d'erreur de liaison avec le registre
            System.out.println("                                                                         ");
            System.out.println("  +---------------------------------------------------------------------+");
            System.err.println("  |             Erreur de liaison avec le registre RMI.                 |");
            System.out.println("  +---------------------------------------------------------------------+");
            System.out.println("                                                                         ");
            System.err.println(e.getMessage());
        } catch (RemoteException e) {
            // Gestion des exceptions en cas d'erreur de communication RMI
            System.out.println("                                                                         ");
            System.out.println("  +---------------------------------------------------------------------+");
            System.err.println("  |             Erreur lors de la communication avec RMI.               |");
            System.out.println("  +---------------------------------------------------------------------+");
            System.out.println("                                                                         ");
            System.err.println(e.getMessage());
        }
    }
}
