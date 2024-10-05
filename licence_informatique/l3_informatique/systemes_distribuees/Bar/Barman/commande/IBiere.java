/**

    Packages pour la communication en Java RMI
    */
    import java.rmi.RemoteException;
    import java.rmi.Remote;
    import java.util.Vector;

/**

    Interface représentant la classe Bière
    */
    public interface IBiere extends Remote {

    /**
        Retourne la liste des bières blondes
        @return Vector<Biere> La liste des bières blondes
        @throws RemoteException
        */
        public Vector<Biere> listeBlondes() throws RemoteException;

    /**
        Retourne la liste des bières ambrées
        @return Vector<Biere> La liste des bières ambrées
        @throws RemoteException
        */
        public Vector<Biere> listeAmbrees() throws RemoteException;

    /**
        Achète un fût de bière pour la bière dont le nom est passé en paramètre
        @param nom Le nom de la bière
        @return Biere L'objet Biere
        @throws RemoteException
        */
        public Biere acheterBiere(String nom) throws RemoteException;
        }