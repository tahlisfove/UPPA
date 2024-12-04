-- Crée la table 'sheets' si elle n'existe pas déjà
CREATE TABLE IF NOT EXISTS sheets (
  id SERIAL PRIMARY KEY,
  name VARCHAR(50) NOT NULL,
  total DECIMAL DEFAULT 0,
  CONSTRAINT unique_name_per_sheet UNIQUE (name)
);

-- Crée la table 'sheet_users' pour lier les utilisateurs à une feuille
CREATE TABLE IF NOT EXISTS sheet_users (
  id SERIAL PRIMARY KEY,
  sheet_id INTEGER REFERENCES sheets(id) ON DELETE CASCADE,
  user_name VARCHAR(30) NOT NULL,
  CONSTRAINT unique_user_per_sheet UNIQUE (sheet_id, user_name)
);

-- Crée la table 'transactions' pour stocker les transactions
CREATE TABLE IF NOT EXISTS transactions (
  id SERIAL PRIMARY KEY,
  sheet_id INTEGER REFERENCES sheets(id) ON DELETE CASCADE,
  user_name VARCHAR(30) NOT NULL,
  amount DECIMAL NOT NULL,
  description VARCHAR(50)
);