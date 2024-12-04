// Importe le module `pg` pour interagir avec une base de données PostgreSQL
const { Pool } = require('pg');

// Importe le framework Express pour créer une application web en Node.js
const express = require('express');
// Importe le middleware CORS pour gérer les requêtes inter-origines
const cors = require('cors');
// Importe le middleware pour analyser les cookies
const cookieParser = require('cookie-parser');

// Crée une instance de l'application Express
const app = express();
// Définit le port sur lequel le serveur écoutera
const port = 3001;

// Active CORS avec les paramètres par défaut
app.use(cors());
// Permet de traiter les requêtes avec un corps JSON
app.use(express.json());
// Permet de lire et de gérer les cookies dans les requêtes HTTP
app.use(cookieParser());


/*******/


// Lancer le serveur sur le port spécifié
app.listen(port, () => {
  console.log(`Backend API is running on http://localhost:${port}`);
});


/******/


// Route principale pour vérifier que l'API fonctionne
app.get('/', (req, res) => {
  res.send('Hello from the backend!');
});


/*******/


// Configuration de la connexion à la base de données PostgreSQL
const pool = new Pool({
  user: 'your_db_user',
  host: 'db',
  database: 'budget_db',
  password: 'your_db_password',
  port: 5432,
});


/******/


// Route pour vérifier l'état de l'authentification
app.get('/api/status', (req, res) => {
  if (req.cookies.sessionid) {
    // Si présent, l'utilisateur est authentifié
    res.json({ authenticated: true });
  } else {
    // Sinon, l'utilisateur n'est pas authentifié
    res.json({ authenticated: false });
  }
});


/******/


// Route pour gérer la déconnexion
app.post('/auth/logout', (req, res) => {
  // Supprime la session
  req.session.destroy(err => {
    if (err) {
      return res.status(500).send('Erreur lors de la déconnexion');
    }
    // Supprime le cookie
    res.clearCookie('sessionid');
    res.status(200).json({ message: 'Déconnexion réussie' });
  });
});


/*******/


// Route pour créer une feuille de budget
app.post('/api/create-sheet', async (req, res) => {
  const { name, users } = req.body;

  // Validation des données envoyées par le client
  if (!name || !users || !Array.isArray(users)) {
    return res.status(400).json({ error: 'Nom de la feuille et utilisateurs sont requis' });
  }

  try {
    console.log("Données reçues :", { name, users });

    // Insérer la feuille dans la table "sheets" et récupérer son ID
    const result = await pool.query('INSERT INTO sheets(name) VALUES($1) RETURNING id', [name]);
    const sheetId = result.rows[0].id;

    console.log(`Feuille créée avec ID ${sheetId}`);

    // Insérer chaque utilisateur dans la table "sheet_users"
    const insertUserPromises = users.map(user =>
      pool.query('INSERT INTO sheet_users(sheet_id, user_name) VALUES($1, $2)', [sheetId, user])
    );
    await Promise.all(insertUserPromises);

    // Retourner l'ID de la feuille au client
    res.status(200).json({ sheetId });
  } catch (err) {
    console.error("Erreur lors de la création de la feuille :", err);
    res.status(500).json({ error: 'Erreur lors de la création de la feuille de budget' });
  }
});


/******/


// Route pour ajouter un utilisateur à une feuille de budget existante
app.post('/api/add-user', async (req, res) => {
  const { sheetId, user } = req.body;

  // Validation des données envoyées
  if (!sheetId || !user) {
    return res.status(400).json({ error: 'L\'ID de la feuille et le nom de l\'utilisateur sont requis' });
  }

  try {
    console.log(`Ajout de l'utilisateur ${user} à la feuille ${sheetId}`);

    // Insérer l'utilisateur dans la table "sheet_users"
    await pool.query('INSERT INTO sheet_users(sheet_id, user_name) VALUES($1, $2)', [sheetId, user]);

    res.status(200).json({ message: 'Utilisateur ajouté avec succès' });
  } catch (err) {
    console.error("Erreur lors de l'ajout de l'utilisateur :", err);

    // Gestion d'une erreur spécifique : utilisateur déjà existant
    if (err.code === '23505') {
      return res.status(400).json({ error: 'L\'utilisateur existe déjà dans cette feuille' });
    }
    res.status(500).json({ error: 'Erreur lors de l\'ajout de l\'utilisateur' });
  }
});


/******/


// Route pour récupérer toutes les feuilles de budget
app.get('/api/sheets', async (req, res) => {
  try {
    // Récupérer toutes les feuilles depuis la table "sheets"
    const result = await pool.query('SELECT id, name, total FROM sheets ORDER BY id DESC');
    res.status(200).json(result.rows);
  } catch (err) {
    console.error("Erreur lors de la récupération des feuilles :", err);
    res.status(500).json({ error: 'Erreur lors de la récupération des feuilles' });
  }
});


/******/


// Supprimer une feuille de budget
app.delete('/api/delete-sheet/:id', async (req, res) => {
  const { id } = req.params;

  try {
    // Supprimer les utilisateurs associés à la feuille
    await pool.query('DELETE FROM sheet_users WHERE sheet_id = $1', [id]);
    // Supprimer la feuille elle-même
    await pool.query('DELETE FROM sheets WHERE id = $1', [id]);

    console.log(`Feuille de budget avec ID ${id} supprimée avec succès`);
    res.status(200).json({ message: 'Feuille supprimée avec succès' });
  } catch (err) {
    console.error('Erreur lors de la suppression de la feuille', err);
    res.status(500).json({ error: 'Erreur lors de la suppression de la feuille', details: err });
  }
});


/******/


// Supprimer un utilisateur d'une feuille
app.delete('/api/sheets/:sheetId/users/:userName', async (req, res) => {
  const { sheetId, userName } = req.params;

  try {
    // Supprimer l'utilisateur spécifié de la feuille donnée
    const result = await pool.query(
      'DELETE FROM sheet_users WHERE sheet_id = $1 AND user_name = $2',
      [sheetId, userName]
    );

    // Vérification si la suppression a eu lieu
    if (result.rowCount === 0) {
      return res.status(404).json({ error: "Utilisateur ou feuille introuvable" });
    }

    console.log(`Utilisateur ${userName} supprimé de la feuille ${sheetId}`);
    res.status(200).json({ message: 'Utilisateur supprimé avec succès' });
  } catch (err) {
    console.error('Erreur lors de la suppression de l\'utilisateur :', err);
    res.status(500).json({ error: 'Erreur lors de la suppression de l\'utilisateur' });
  }
});


/******/


// Récupérer les utilisateurs d'une feuille
app.get('/api/sheets/:sheetId/users', async (req, res) => {
  const { sheetId } = req.params;

  try {
    // Requête pour obtenir les noms des utilisateurs associés à cette feuille
    const result = await pool.query(
      'SELECT user_name FROM sheet_users WHERE sheet_id = $1',
      [sheetId]
    );

    // Retourner uniquement les noms d'utilisateurs
    res.status(200).json(result.rows.map(row => row.user_name));
  } catch (err) {
    console.error("Erreur lors de la récupération des utilisateurs :", err);
    res.status(500).json({ error: 'Erreur lors de la récupération des utilisateurs' });
  }
});


/******/


// Récupérer les détails d'une feuille, y compris le total du budget
app.get('/api/sheets/:id', async (req, res) => {
  const sheetId = req.params.id;

  try {
    // Calculer le total des transactions associées à cette feuille
    const result = await pool.query(`
      SELECT SUM(amount) AS total
      FROM transactions
      WHERE sheet_id = $1
    `, [sheetId]);

    // Si aucune transaction, le total est de 0
    const total = result.rows[0].total || 0;

    // Récupérer les informations détaillées de la feuille
    const sheetResult = await pool.query('SELECT * FROM sheets WHERE id = $1', [sheetId]);

    // Vérification si la feuille existe
    if (sheetResult.rowCount === 0) {
      return res.status(404).json({ error: 'Feuille introuvable' });
    }

    const sheet = sheetResult.rows[0];
    sheet.total = total;

    // Retourner les informations complètes de la feuille
    res.status(200).json(sheet);
  } catch (err) {
    console.error("Erreur lors de la récupération des informations du budget :", err);
    res.status(500).json({ error: 'Erreur lors de la récupération des informations du budget' });
  }
});


/******/


// Ajouter une transaction
app.post('/api/add-transaction', async (req, res) => {
  const { sheetId, userName, amount, description } = req.body;

  // Vérification des données envoyées
  if (!sheetId || !userName || typeof amount !== 'number') {
    return res.status(400).json({ error: 'Tous les champs requis doivent être remplis.' });
  }

  try {
    // Requête SQL pour insérer une nouvelle transaction
    const query = `
      INSERT INTO transactions (sheet_id, user_name, amount, description)
      VALUES ($1, $2, $3, $4) RETURNING id;
    `;

    // Insérer les données dans la table `transactions`
    const result = await pool.query(query, [
      sheetId,
      userName,
      amount,
      // Description facultative, par défaut null
      description || null,
    ]);

    // Mise à jour du total associé à la feuille dans la table `sheets`
    const updateTotalQuery = `
      UPDATE sheets
      SET total = (
        SELECT COALESCE(SUM(amount), 0)
        FROM transactions
        WHERE sheet_id = $1
      )
      WHERE id = $1;
    `;
    await pool.query(updateTotalQuery, [sheetId]);

    // Retourner l'ID de la transaction insérée
    res.status(200).json({ transactionId: result.rows[0].id });
  } catch (error) {
    console.error("Erreur lors de l'ajout de la transaction :", error);
    res.status(500).json({ error: 'Erreur lors de l\'ajout de la transaction' });
  }
});


/******/


// Récupérer les transactions associées à une feuille
app.get('/api/sheets/:sheetId/transactions', async (req, res) => {
  const { sheetId } = req.params;

  try {
    // Requête SQL pour récupérer les transactions d'une feuille spécifique
    const query = `
      SELECT id, user_name, amount, description
      FROM transactions
      WHERE sheet_id = $1
      ORDER BY id DESC;
    `;
    const result = await pool.query(query, [sheetId]);

    // Retourner les transactions sous forme de tableau JSON
    res.status(200).json(result.rows);
  } catch (error) {
    console.error("Erreur lors de la récupération des transactions :", error);
    res.status(500).json({ error: "Erreur lors de la récupération des transactions." });
  }
});


/******/


// Fonction pour supprimer une transaction dans la base de données
const deleteTransactionFromDatabase = async (sheetId, transactionId) => {
  try {
    // Requête SQL pour supprimer une transaction en fonction de son ID et de la feuille associée
    const result = await pool.query(
      'DELETE FROM transactions WHERE sheet_id = $1 AND id = $2',
      [sheetId, transactionId]
    );

    // Vérification si une transaction a été supprimée
    if (result.rowCount === 0) {
      throw new Error('Transaction introuvable');
    }

    // Mise à jour du total après la suppression de la transaction
    const updateTotalQuery = `
      UPDATE sheets
      SET total = (
        SELECT COALESCE(SUM(amount), 0)
        FROM transactions
        WHERE sheet_id = $1
      )
      WHERE id = $1;
    `;
    await pool.query(updateTotalQuery, [sheetId]);
  } catch (err) {
    throw new Error('Erreur lors de la suppression de la transaction: ' + err.message);
  }
};


/******/


// Route pour supprimer une transaction
app.delete('/api/sheets/:sheetId/transactions/:transactionId', async (req, res) => {
  const { sheetId, transactionId } = req.params;

  try {
    // Appeler la fonction de suppression de transaction
    await deleteTransactionFromDatabase(sheetId, transactionId);

    // Confirmation de la suppression
    res.status(200).send({ message: 'Transaction supprimée avec succès' });
  } catch (error) {
    console.error('Erreur lors de la suppression de la transaction :', error);
    res.status(500).send({ message: 'Erreur lors de la suppression de la transaction' });
  }
});