
/**
 * Paquets pour la communication en Java RMI
 */
import java.rmi.server.UnicastRemoteObject;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.RemoteException;
import java.rmi.Naming;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.net.NetworkInterface;
import java.net.Inet4Address;
import java.util.Enumeration;

/**
 * Paquets pour Vector
 */
import java.util.Vector;

/**
 * Implémentation de la classe Fournisseur
 */
public class Fournisseur extends UnicastRemoteObject implements IBiere {

    /**
     * Initialisation du vecteur de bières BLONDES
     */
    protected Vector<Biere> blondes;

    /**
     * Initialisation du vecteur de bières AMBREES
     */
    protected Vector<Biere> ambrees;

    /**
     * Retourne la liste des bières blondes
     * 
     * @return Vector<Biere> La liste des bières blondes
     * @throws RemoteException
     */
    public Vector<Biere> listeBlondes() throws RemoteException {
        return blondes;
    }

    /**
     * Retourne la liste des bières ambrées
     * 
     * @return Vector<Biere> La liste des bières ambrées
     * @throws RemoteException
     */
    public Vector<Biere> listeAmbrees() throws RemoteException {
        return ambrees;
    }

    /**
     * Retourne un fût de bière correspondant au nom passé en paramètre
     * 
     * @param nom Le nom de la bière
     * @return Biere L'objet bière
     * @throws RemoteException
     */
    public Biere acheterBiere(String nom) throws RemoteException {
        Vector<Biere> toutes = new Vector<Biere>();
        Biere b;
        toutes.addAll(ambrees);
        toutes.addAll(blondes);

        // Supprime les espaces de début et de fin du nom d'entrée et le convertit en
        // minuscules
        String trimmedNom = nom.trim().toLowerCase();

        // Liste des bières disponibles
        for (int i = 0; i < toutes.size(); i++) {
            b = (Biere) toutes.elementAt(i);
            if (b.getNom().toLowerCase().equals(trimmedNom)) {
                return b;
            }
        }
        return null;
    }

    /**
     * Remplissage des deux tableaux de bières disponibles
     */
    protected void remplirCatalogue() {
        blondes = new Vector<Biere>();
        ambrees = new Vector<Biere>();

        // Ajout des bières BLONDES
        blondes.add(new Biere("Paix Dieu", Biere.BLONDE, 10));
        blondes.add(new Biere("Goudale", Biere.BLONDE, 7));
        blondes.add(new Biere("Delirium Tremens", Biere.BLONDE, 8));

        // Ajout des bières AMBREES
        ambrees.add(new Biere("Kwak", Biere.AMBREE, 8));
        ambrees.add(new Biere("Mousse Ta Shuc", Biere.AMBREE, 6));
        ambrees.add(new Biere("Queue de Charrue", Biere.AMBREE, 5));
    }

    /**
     * Constructeur de la classe Fournisseur qui initialise le catalogue de bières
     * 
     * @throws RemoteException
     */
    public Fournisseur() throws RemoteException {
        super();
        remplirCatalogue();
    }

    /**
     * Fonction principale pour démarrer le serveur
     * 
     * @param args
     */
    public static void main(String[] args) {
        Fournisseur fournisseur = null;
        try {
            NetworkInterface ni = NetworkInterface.getByName("eno1");
            Enumeration<InetAddress> inetAddresses = ni.getInetAddresses();
            InetAddress localAddress = null;
            while (inetAddresses.hasMoreElements()) {
                InetAddress ia = inetAddresses.nextElement();
                if (ia instanceof Inet4Address && !ia.isLinkLocalAddress()) {
                    localAddress = ia;
                    break;
                }
            }

            if (localAddress == null) {
                // Gestion d'erreur
                System.out.println("impossible de récupérer l'adresse IP de la machine");
                System.exit(1);
            }

            String adresse_ip = localAddress.getHostAddress();
            // Définition de la propriété système pour le nom d'hôte RMI
            System.setProperty("java.rmi.server.hostname", adresse_ip);

            // Création et enregistrement de l'objet distant
            fournisseur = new Fournisseur();
            Naming.rebind("DedeLaChope", fournisseur);

            // Serveur prêt
            System.out.println(" ");
            System.out.println("  +---------------------------------------------------------------------+");
            System.out.println("  |                      Service DeLaChoppe Ouvert!                     |");
            System.out.println("  +---------------------------------------------------------------------+");
            System.out.println("  |                                                                     |");
            System.out.println("  |                             " + adresse_ip + "                             |");
            System.out.println("  |                                                                     |");
            System.out.println("  +---------------------------------------------------------------------+");
            System.out.println(" ");

            // Gestion d'erreur pour Fournisseur
        } catch (Exception ex) {
            System.out.println(" ");
            System.out.println("  +---------------------------------------------------------------------+");
            System.out.println("  |           Impossible de lancer le fournisseur DeLaChoppe            |");
            System.out.println("  +---------------------------------------------------------------------+");
            System.out.println(" ");
            System.err.println(ex);
        }
    }
}
