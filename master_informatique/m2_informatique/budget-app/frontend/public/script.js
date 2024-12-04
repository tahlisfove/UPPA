// Liste des utilisateurs actuels
let currentUsers = [];
// Identifiant du budget actuellement sélectionné
let currentBudgetId = null;


/******/


document.addEventListener('DOMContentLoaded', function () {
  // Gestionnaire de clic pour le bouton de déconnexion
  document.getElementById('logoutButton').addEventListener('click', function () {
    // Envoi d'une requête POST pour déconnecter l'utilisateur
    fetch('http://localhost:3002/auth/logout', {
      method: 'POST',
      credentials: 'include',
    })
    .then(response => {
      // Rediriger vers une autre page après la déconnexion
      if (response.ok) {
        alert('Déconnexion réussie');
        window.location.href = 'http://localhost:3000';
      } else {
        alert('Déconnexion réussie');
        window.location.href = 'http://localhost:3000'
      }
    })
  });
});


/******/


// Événement déclenché lorsque le DOM est complètement chargé
document.addEventListener('DOMContentLoaded', function () {
  loadBudgets();
  document.body.addEventListener('click', function(event) {
    if (event.target.closest('.budget-item')) {
      // Réinitialiser les valeurs des champs
      document.getElementById('amount').value = '';
      document.getElementById('transactionPerson').value = '';
      document.getElementById('description').value = '';
    }
  });
});


/******/


// Fonction de validation du montant pour s'assurer qu'il suit le format correct
function validateAmount(input) {
  // Expression régulière pour autoriser jusqu'à 6 chiffres avant la virgule et 2 après le point
  const regex = /^\d{0,6}(\.\d{0,2})?$/;

  if (!regex.test(input.value)) {
    input.value = input.value.slice(0, -1);
  }
}


/******/


// Ajout d'une transaction lorsqu'on clique sur le bouton 'addTransactionButton'
document.getElementById('addTransactionButton').addEventListener('click', function () {
  // Récupère le montant de la transaction
  const amount = parseFloat(document.getElementById('amount').value);
  // Récupère le nom de l'utilisateur
  const userName = document.getElementById('transactionPerson').value;
  // Récupère le nom de l'utilisateur
  const description = document.getElementById('description').value.trim();

  // Vérifie que les champs obligatoires sont remplis
  if (!amount || !userName) {
    alert("Veuillez remplir tous les champs !");
    return;
  }

  // Envoi de la transaction au serveur
  axios.post('http://localhost:3001/api/add-transaction', {
    sheetId: currentBudgetId,
    userName: userName,
    amount: amount,
    description: description
  })
  .then(() => {
    // Vider les champs après ajout
    document.getElementById('amount').value = '';
    document.getElementById('description').value = '';

    // Recharge les transactions et met à jour les totaux
    loadTransactions(currentBudgetId);
    updateBudgetTotal(currentBudgetId);
    loadBudgets();
  })
  .catch(error => {
    console.error("Erreur lors de l'ajout de la transaction :", error);
    alert("Impossible d'ajouter la transaction. Veuillez réessayer.");
  });
});


/******/


// Fonction pour charger les feuilles de budget depuis le serveur
function loadBudgets() {
  axios.get('http://localhost:3001/api/sheets')
    .then(function (response) {
      // Récupère les feuilles de budget
      const budgets = response.data;
      const budgetsContainer = document.getElementById('budgetsContainer');
      budgetsContainer.innerHTML = '';

      // Crée un élément HTML pour chaque feuille de budget
      budgets.forEach(budget => {
        const budgetDiv = document.createElement('div');
        budgetDiv.classList.add('budget-item');

        // Ajoute l'ID du budget en tant qu'attribut
        budgetDiv.setAttribute('data-budget-id', budget.id);
        budgetDiv.innerHTML = `
          <div class="div_h">
            <h3>${budget.name}</h3>
          </div>
          <div class="div_p">
            <p>${budget.total || 0}€</p>
          </div>
        `;

        // Ajoute un événement pour ouvrir les détails du budget lorsque l'on clique dessus
        budgetDiv.addEventListener('click', function () {
          // Ouvre les détails du budget
          openBudgetDetail(budget.name, budget.id);
          // Charge les transactions de ce budget
          loadTransactions(currentBudgetId);
        });

        // Ajoute la feuille de budget à l'interface
        budgetsContainer.appendChild(budgetDiv);
      });
    })
    .catch(function (error) {
      console.error('Erreur lors du chargement des feuilles de budget :', error);
    });
}


/******/


// Création d'une nouvelle feuille de budget lorsqu'on soumet le formulaire
document.getElementById('budgetForm').addEventListener('submit', function (event) {
  event.preventDefault();

    // Nom de la feuille de budget
  const budgetName = document.getElementById('budgetName').value;
  // Liste des utilisateurs séparés par une virgule
  const users = document.getElementById('users').value.split(',').map(user => user.trim());

  // Vérifie que tous les champs sont remplis
  if (!budgetName || !users.length) {
    alert("Veuillez remplir tous les champs !");
    return;
  }

  // Envoi des données pour créer une nouvelle feuille de budget
  axios.post('http://localhost:3001/api/create-sheet', {
    name: budgetName,
    users: users
  })
    .then(function (response) {
      // ID de la nouvelle feuille de budget
      const budgetId = response.data.sheetId;
      const budgetsContainer = document.getElementById('budgetsContainer');
      const budgetDiv = document.createElement('div');
      budgetDiv.classList.add('budget-item');
      budgetDiv.setAttribute('data-budget-id', budgetId);

      // Recharge la liste des feuilles de budget
      loadBudgets();
      
      // Ajoute un événement pour afficher les détails de la feuille de budget
      budgetDiv.addEventListener('click', function () {
        openBudgetDetail(budgetName, budgetId);
      });

      // Insère la nouvelle feuille en haut de la liste
      budgetsContainer.insertBefore(budgetDiv, budgetsContainer.firstChild);

      // Réinitialise le formulaire
      document.getElementById('budgetForm').reset();
    })
    .catch(function (error) {
      alert("Impossible de créer cette feuille. Veuillez choisir un autre nom.");
      console.error('Erreur lors de la création de la feuille de budget:', error);
    });
});


/******/


// Mettre à jour le nombre d'utilisateurs dans la liste pour les transactions
function updateTransactionPersonSelect(users) {
  const transactionPersonSelect = document.getElementById('transactionPerson');
  transactionPersonSelect.innerHTML = '';

  // Option par défaut dans le select
  const defaultOption = document.createElement('option');
  defaultOption.value = '';
  defaultOption.textContent = 'Sélectionner une personne';
  transactionPersonSelect.appendChild(defaultOption);

  // Ajout de chaque utilisateur à la liste déroulante
  users.forEach(user => {
    const option = document.createElement('option');
    option.value = user;
    option.textContent = user;
    transactionPersonSelect.appendChild(option);
  });
}


/******/


// Ouvrir le détail d'une feuille de budget
function openBudgetDetail(name, budgetId) {
  // Met à jour l'ID du budget actuellement ouvert
  currentBudgetId = budgetId;

  // Mise à jour du titre et de l'affichage des utilisateurs et des transactions
  document.getElementById('budgetDetailName').textContent = name;
  document.getElementById('budgetDetailUsers').innerHTML = "";
  document.getElementById('budgetDetailTransactions').innerHTML = "";

  // Récupérer les informations du budget, y compris le total
  axios.get(`http://localhost:3001/api/sheets/${budgetId}`)
    .then(function (response) {
      const budget = response.data;
      // Affiche le total du budget
      document.getElementById('budgetTotalAmount').textContent = `${budget.total}€`;
    })
    .catch(function (error) {
      console.error('Erreur lors de la récupération des informations du budget :', error);
    });

  // Récupérer les utilisateurs associés à ce budget
  axios.get(`http://localhost:3001/api/sheets/${budgetId}/users`)
    .then(function (response) {
      // Met à jour la liste des utilisateurs
      currentUsers = response.data;
      // Met à jour le select des personnes pour les transactions
      updateTransactionPersonSelect(currentUsers);

      // Crée une liste HTML pour afficher les utilisateurs
      const userList = document.createElement('ul');
      currentUsers.forEach(user => {
        const listItem = document.createElement('li');
        listItem.textContent = user;

        // Ajout d'un bouton pour supprimer un utilisateur
        const deleteButton = document.createElement('button');
        deleteButton.textContent = "Supprimer";
        deleteButton.addEventListener('click', function () {
          // Supprime l'utilisateur de la feuille de budget
          deleteUserFromSheet(budgetId, user, listItem);
        });

        // Ajoute le bouton à l'élément de la liste
        listItem.appendChild(deleteButton);
        // Ajoute l'élément à la liste
        userList.appendChild(listItem);
      });
      // Affiche la liste des utilisateurs
      document.getElementById('budgetDetailUsers').appendChild(userList);

      // Formulaire pour ajouter un nouvel utilisateur
      const addUserForm = document.createElement('div');
      addUserForm.innerHTML = `
        <input type="text" id="newUser" placeholder="Ajouter un utilisateur" />
        <button id="addUserButton">Ajouter</button>
      `;
      document.getElementById('budgetDetailUsers').appendChild(addUserForm);

      // Gestion de l'ajout d'un utilisateur
      document.getElementById('addUserButton').addEventListener('click', function () {
        // Récupère le nom de l'utilisateur à ajouter
        const newUser = document.getElementById('newUser').value.trim();
        if (!newUser) {
          alert("Veuillez entrer un nom valide !");
          return;
        }

        // Envoi de l'ajout de l'utilisateur au serveur
        axios.post(`http://localhost:3001/api/add-user`, {
          sheetId: budgetId,
          user: newUser
        })
          .then(function () {
            // Ajoute l'utilisateur à la liste locale
            currentUsers.push(newUser);
            // Met à jour la liste des utilisateurs dans le select
            updateTransactionPersonSelect(currentUsers);

            const newListItem = document.createElement('li');
            newListItem.textContent = newUser;

            // Ajout d'un bouton pour supprimer l'utilisateur
            const deleteButton = document.createElement('button');
            deleteButton.textContent = "Supprimer";
            deleteButton.addEventListener('click', function () {
              // Supprime un utilisateur de la feuille de budget actuelle
              deleteUserFromSheet(budgetId, newUser, newListItem);
            });
            newListItem.appendChild(deleteButton);

            // Ajoute le nouvel utilisateur à la liste
            userList.appendChild(newListItem);
            // Réinitialise le champ de saisie
            document.getElementById('newUser').value = "";

            // Recharge les transactions et recalcul les dettes
            loadTransactions(currentBudgetId);
          })
          .catch(function (error) {
            console.error('Erreur lors de l’ajout de l’utilisateur :', error);
            alert("Impossible d'ajouter l'utilisateur. Veuillez réessayer.");
          });
      });
    })
    .catch(function (error) {
      console.error('Erreur lors de la récupération des utilisateurs :', error);
    });

  // Récupérer les informations du budget et des transactions
  axios.get(`http://localhost:3001/api/sheets/${budgetId}`)
    .then(function (response) {
      const budget = response.data;
      document.getElementById('budgetTotalAmount').value = budget.total;

      // Récupérer les transactions associées à ce budget
      axios.get(`http://localhost:3001/api/sheets/${budgetId}/transactions`)
        .then(function (transactionResponse) {
          const transactions = transactionResponse.data;
          // Calcule les dettes des utilisateurs
          const transactionsSummary = calculateDebts(transactions, budget.total, currentUsers);
          // Affiche le résumé des dettes
          displayDebtSummary(transactionsSummary);
        })
        .catch(function (error) {
          console.error('Erreur lors de la récupération des transactions :', error);
        });
    })
    .catch(function (error) {
      console.error('Erreur lors de la récupération des informations du budget :', error);
    });

  // Affiche le détail du budget avec un overlay pour cacher la page principale
  document.getElementById('overlay').style.display = 'flex';
  document.getElementById('budgetDetail').style.display = 'flex';
  // Désactive le défilement de la page
  document.body.style.overflow = 'hidden';
}


/******/


// Supprimer un utilisateur d'une feuille
function deleteUserFromSheet(sheetId, userName, listItemElement) {
  // Vérifier si l'utilisateur a des transactions associées à lui
  axios.get(`http://localhost:3001/api/sheets/${sheetId}/transactions`)
    .then(function (response) {
      const transactions = response.data;

      // Vérifier si l'utilisateur a effectué des transactions
      const userHasTransactions = transactions.some(transaction => transaction.user_name === userName);

      // Si l'utilisateur a des transactions, empêcher la suppression
      if (userHasTransactions) {
        alert("Impossible de supprimer cet utilisateur car il y a des transactions associées à lui.");
        return;
      }

      // Si l'utilisateur n'a pas de transactions, procéder à la suppression
      axios.delete(`http://localhost:3001/api/sheets/${sheetId}/users/${userName}`)
        .then(function () {
          alert("Utilisateur supprimé avec succès !");
          listItemElement.remove();

          // Enlève l'utilisateur de la liste locale
          currentUsers = currentUsers.filter(user => user !== userName);
          // Met à jour la liste déroulante des utilisateurs pour les transactions
          updateTransactionPersonSelect(currentUsers);

          // Recalcule les dettes et met à jour l'affichage des transactions
          loadTransactions(sheetId);
        })
        .catch(function (error) {
          console.error("Erreur lors de la suppression de l'utilisateur :", error);
        });
    })
    .catch(function (error) {
      console.error("Erreur lors de la vérification des transactions :", error);
      alert("Une erreur est survenue lors de la vérification des transactions.");
    });
}


/******/


// Charger les feuilles de transactions
function loadTransactions(sheetId) {
  // Récupérer les transactions pour une feuille de budget spécifique
  axios.get(`http://localhost:3001/api/sheets/${sheetId}/transactions`)
    .then(response => {
      const transactions = response.data;
      const transactionList = document.getElementById('transactionItems');
      const noTransactionMessage = document.getElementById('aucunnetransaction');
      transactionList.innerHTML = '';

      // Gérer la visibilité du message "aucunnetransaction"
      if (transactions.length === 0) {
        // Affiche le message si aucune transaction
        noTransactionMessage.style.display = 'block';
      } else {
        // Cache le message si des transactions existent
        noTransactionMessage.style.display = 'none';
      }

      // Afficher chaque transaction dans une liste
      transactions.forEach(transaction => {
        const listItem = document.createElement('li');
        listItem.innerHTML = `
          <strong>${transaction.user_name}:</strong> ${transaction.amount}€
          <em>${transaction.description || ''}</em>
        `;

        // Ajouter un bouton de suppression pour chaque transaction
        const deleteButton = document.createElement('button');
        deleteButton.textContent = 'Supprimer';
        deleteButton.classList.add('delete-transaction-button');
        deleteButton.addEventListener('click', function () {
           // Supprime la transaction
          deleteTransaction(sheetId, transaction.id);
        });

        // Ajouter le bouton de suppression à l'élément de la transaction
        listItem.appendChild(deleteButton);

        // Ajouter l'élément de la transaction à la liste
        transactionList.appendChild(listItem);
      });

      // Recalculer les dettes et afficher le résumé des dettes
      axios.get(`http://localhost:3001/api/sheets/${sheetId}`)
        .then(function (response) {
          const budget = response.data;
          // Calcule le résumé des dettes
          const transactionsSummary = calculateDebts(transactions, budget.total, currentUsers);
          // Affiche le résumé des dettes
          displayDebtSummary(transactionsSummary);
        })
        .catch(function (error) {
          console.error('Erreur lors de la récupération des informations du budget :', error);
        });
    })
    .catch(error => {
      console.error("Erreur lors de la récupération des transactions :", error);
    });
}


/******/


// Fermer le détail de la feuille de budget
document.getElementById('closeBudgetDetailButton').addEventListener('click', function () {
  // Cacher le détail de la feuille de budget et l'overlay
  document.getElementById('budgetDetail').style.display = 'none';
  document.getElementById('overlay').style.display = 'none';
  // Réactiver le défilement de la page
  document.body.style.overflow = '';
});


/******/


// Supprimer la feuille de budget
document.getElementById('deleteBudgetButton').addEventListener('click', function () {
  if (currentBudgetId) {
    // Confirmer la suppression de la feuille de budget
    const confirmDelete = window.confirm("Êtes-vous sûr de vouloir supprimer cette feuille ?");
    
    // Si l'utilisateur annule, sortir de la fonction
    if (!confirmDelete) return;

    // Appeler l'API pour supprimer la feuille de budget
    axios.delete(`http://localhost:3001/api/delete-sheet/${currentBudgetId}`)
      .then(function () {
        alert("Feuille supprimée avec succès !");
        // Fermer la vue de la feuille de budget après suppression
        document.getElementById('budgetDetail').style.display = 'none';
        document.getElementById('overlay').style.display = 'none';
        // Réactive le défilement
        document.body.style.overflow = '';

        // Retirer la feuille de budget de l'interface
        const budgetDiv = document.querySelector(`[data-budget-id="${currentBudgetId}"]`);
        if (budgetDiv) {
          budgetDiv.remove();
        }
      })
      .catch(function (error) {
        console.error('Erreur lors de la suppression de la feuille de budget :', error);
      });
  }
});


/******/


// Fonction pour calculer les dettes entre les utilisateurs
function calculateDebts(transactions, totalBudget, users) {
  // Calcul de la part équitable par utilisateur
  const fairShare = totalBudget / users.length;
  console.log("Part équitable par utilisateur : ", fairShare);

  // Calcul des montants payés par chaque utilisateur
  const contributions = users.reduce((acc, user) => {
    const userTotal = transactions
      .filter(transaction => transaction.user_name === user)
      // Conversion en nombre
      .reduce((sum, transaction) => sum + parseFloat(transaction.amount), 0);
    acc[user] = userTotal;
    return acc;
  }, {});

  console.log("Montants payés par chaque utilisateur : ", contributions);

  // Calcul des excédents ou déficits pour chaque utilisateur
  const balances = users.map(user => {
    const paidAmount = contributions[user];
    const balance = paidAmount - fairShare;
    return { user, balance };
  });

  // Créanciers (ceux qui ont payé plus que leur part)
  const creditors = balances.filter(b => b.balance > 0);
  // Débiteurs (ceux qui doivent encore payer)
  const debtors = balances.filter(b => b.balance < 0);

  // Calcul des remboursements nécessaires entre débiteurs et créanciers
  let transactionsSummary = [];

  let i = 0;
  let j = 0;

  // Répartir les remboursements entre débiteurs et créanciers
  while (i < debtors.length && j < creditors.length) {
    const debtor = debtors[i];
    const creditor = creditors[j];

    // Montant à rembourser : le minimum entre ce que le débiteur doit et ce que le créancier attend
    const amountToPay = Math.min(Math.abs(debtor.balance), creditor.balance);

    console.log(`Transaction de ${debtor.user} à ${creditor.user} : ${amountToPay}€`);

    // Ajouter la transaction dans le résumé
    transactionsSummary.push({
      from: debtor.user,
      to: creditor.user,
      amount: amountToPay
    });

    // Mettre à jour les balances après le paiement
    debtors[i].balance += amountToPay;
    creditors[j].balance -= amountToPay;

    // Passer au débiteur suivant si sa dette est réglée
    if (debtor.balance === 0) i++;
    // Passer au créancier suivant si sa créance est réglée
    if (creditor.balance === 0) j++;
  }

  return transactionsSummary;
}


/******/


// Fonction pour afficher le résumé des dettes
function displayDebtSummary(transactionsSummary) {
  const debtSummaryContainer = document.getElementById('budgetDetailDebtSummary');
  debtSummaryContainer.innerHTML = '';

  if (transactionsSummary.length === 0) {
    debtSummaryContainer.innerHTML = '<p>Tous les utilisateurs ont payé la même somme. Il n\'y a pas de dettes.</p>';
  } else {
    const ul = document.createElement('ul');
    transactionsSummary.forEach(item => {
      const li = document.createElement('li');

      // Formater le montant avec 2 décimales
      const formattedAmount = parseFloat(item.amount).toFixed(2);
      li.textContent = `${item.from} doit ${formattedAmount}€ à ${item.to}`;
      ul.appendChild(li);
    });
    debtSummaryContainer.appendChild(ul);
  }
}


/******/


// Fonction pour supprimer une transaction
function deleteTransaction(sheetId, transactionId) {
  // Demander confirmation avant de supprimer la transaction
  const confirmDelete = window.confirm("Êtes-vous sûr de vouloir supprimer cette transaction ?");
  if (!confirmDelete) return;

  // Supprimer la transaction via l'API
  axios.delete(`http://localhost:3001/api/sheets/${sheetId}/transactions/${transactionId}`)
    .then(function () {
      alert("Transaction supprimée avec succès !");
      
      // Recharger les transactions et recalculer les dettes
      loadTransactions(sheetId);
      updateBudgetTotal(sheetId);
      loadBudgets();
    })
    .catch(function (error) {
      console.error('Erreur lors de la suppression de la transaction :', error);
      alert("Une erreur est survenue lors de la suppression de la transaction.");
    });
}


/******/


// Fonction pour mettre à jour le total du budget après modification
function updateBudgetTotal(sheetId) {
  // Récupérer les informations du budget
  axios.get(`http://localhost:3001/api/sheets/${sheetId}`)
    .then(function (response) {
      const budget = response.data;

      // Mettre à jour l'affichage du total du budget dans le DOM
      const budgetTotalAmount = document.getElementById('budgetTotalAmount');
      budgetTotalAmount.textContent = `${budget.total}€`;
      
      // Mettre à jour les dettes si nécessaire
      axios.get(`http://localhost:3001/api/sheets/${sheetId}/transactions`)
        .then(function (transactionResponse) {
          const transactions = transactionResponse.data;
          const transactionsSummary = calculateDebts(transactions, budget.total, currentUsers);
          displayDebtSummary(transactionsSummary);
        })
        .catch(function (error) {
          console.error('Erreur lors de la récupération des transactions :', error);
        });
    })
    .catch(function (error) {
      console.error('Erreur lors de la récupération des informations du budget :', error);
    });
}
