# Importation des modules nécessaires depuis Flask
from flask import Flask, render_template, request, jsonify
import nltk
from nltk.corpus import stopwords
from nltk.stem import WordNetLemmatizer
import pandas as pd
import numpy as np
from sklearn.metrics.pairwise import cosine_similarity
from transformers import DistilBertTokenizer, DistilBertModel
import torch
import os
from werkzeug.utils import secure_filename

# Define allowed file extensions for resume uploads
ALLOWED_EXTENSIONS = {'csv', 'pdf', 'zip'}
# Données de résultats de mise en correspondance
matching_results = [
    {
        "id": 2,
        "cv_link": "lien_vers_cv_1",
        "matching_percentage": 78
    },
    {
        "id": 11,
        "cv_link": "lien_vers_cv_2",
        "matching_percentage": 89
    },
    {
        "id": 12,
        "cv_link": "lien_vers_cv_2",
        "matching_percentage": 90
    },
    {
        "id": 6,
        "cv_link": "lien_vers_cv_2",
        "matching_percentage": 77
    },
    {
        "id": 1,
        "cv_link": "lien_vers_cv_2",
        "matching_percentage": 81
    },
    {
        "id": 9,
        "cv_link": "lien_vers_cv_2",
        "matching_percentage": 76
    },
    {
        "id": 16,
        "cv_link": "lien_vers_cv_2",
        "matching_percentage": 87
    },
    {
        "id": 8,
        "cv_link": "lien_vers_cv_2",
        "matching_percentage": 92
    },
]

matching_results1 = [
    {
        "id": 3,
        "cv_link": "lien_vers_cv_1",
        "matching_percentage": 81
    },
    {
        "id": 4,
        "cv_link": "lien_vers_cv_2",
        "matching_percentage": 87
    },
    {
        "id": 10,
        "cv_link": "lien_vers_cv_2",
        "matching_percentage": 90
    },
    {
        "id": 13,
        "cv_link": "lien_vers_cv_2",
        "matching_percentage": 93
    },
    {
        "id": 8,
        "cv_link": "lien_vers_cv_2",
        "matching_percentage": 14
    },
    {
        "id": 1,
        "cv_link": "lien_vers_cv_2",
        "matching_percentage": 34
    },
    {
        "id": 16,
        "cv_link": "lien_vers_cv_2",
        "matching_percentage": 43
    },
    {
        "id": 9,
        "cv_link": "lien_vers_cv_2",
        "matching_percentage": 15
    },
]
# Define the upload folder for resumes
UPLOAD_FOLDER = 'uploads'

# Charger le tokenizer BERT
tokenizer = DistilBertTokenizer.from_pretrained("distilbert-base-uncased")

# Charger le modèle BERT pré-entraîné
model = DistilBertModel.from_pretrained("distilbert-base-uncased")

# Données de résultats de mise en correspondance
matching_results = []

# Création de l'application Flask et placement dans le dossier source
app = Flask(__name__, template_folder='templates')
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

# Function to check if file extension is allowed
def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

# Route vers la page principale de l'application welcome
@app.route('/', methods=['GET', 'POST'])
def index():
    return render_template('en/welcome.html')

# Routes pour vers la page platform
@app.route('/welcome_fr')
def welcome_fr():
    return render_template('fr/welcome_fr.html')

# Route to execute the matching code
@app.route('/execute_matching', methods=['GET'])
def execute_matching():
    global matching_results
    
    # Charger les données
    job_descriptions = pd.read_csv("jobs_descriptions.csv")
    
    # Load resumes from the uploads folder
    resume_folder = app.config['UPLOAD_FOLDER']
    resume_files = os.listdir(resume_folder)
    resume_texts = []
    for resume_file in resume_files:
        with open(os.path.join(resume_folder, resume_file), 'r') as file:
            resume_texts.append(file.read())

    # Nettoyer le texte
    def preprocess_text(text):
        # Convertir en chaînes de caractères
        text = text.astype(str)
        # Convertir en minuscules
        text = text.str.lower()
        # Supprimer les caractères spéciaux
        text = text.str.replace(r'[@#&$%]', '', regex=True)
        text = text.str.replace(r'[,.;]', '', regex=True)
        # Supprimer les mots vides
        stop_words = set(stopwords.words('english'))
        text = text.apply(lambda x: [word for word in x.split() if word.lower() not in stop_words])
        # Lemmatisation
        lemmatizer = WordNetLemmatizer()
        text = text.apply(lambda x: [lemmatizer.lemmatize(word) for word in x])
        # Rejoindre les mots en une seule chaîne
        text = text.apply(lambda x: ' '.join(x))
        return text

    # Prétraiter les descriptions d'emploi et les CV
    job_descriptions['clean_text'] = preprocess_text(job_descriptions.iloc[:, 2])
    resume_texts_clean = preprocess_text(pd.Series(resume_texts))

    # Fonction pour obtenir les embeddings des phrases avec BERT
    def get_embeddings(texts):
        inputs = tokenizer(texts.tolist(), padding=True, truncation=True, return_tensors="pt")
        with torch.no_grad():
            outputs = model(**inputs)
        embeddings = outputs.last_hidden_state[:, 0, :]
        return embeddings

    # Limiter le nombre de CV à 20
    num_resumes = 20
    # Batch size for processing resumes
    batch_size = 10
    # Maximum sequence length
    max_seq_length = 64
    # Définir un seuil de similarité
    threshold = 0.7
    # Calculate job embeddings once outside the loop
    job_embeddings = get_embeddings(job_descriptions['clean_text'])

    # Attribuer les correspondances en fonction de la similarité
    matches = []
    for i, job_desc in enumerate(job_descriptions['clean_text']):
        for j in range(0, len(resume_texts_clean), batch_size):
            # Process resumes in batches
            batch_resume_texts = resume_texts_clean[j:j+batch_size]
            batch_resume_embeddings = get_embeddings(batch_resume_texts)

            # Calculate similarity for the current batch
            similarity_scores = cosine_similarity(job_embeddings[i:i+1], batch_resume_embeddings)
            
            # Identify matches in the current batch
            for k in range(len(batch_resume_texts)):
                similarity_score = similarity_scores[0, k]
                if similarity_score > threshold:
                    matches.append((i, j+k, similarity_score))

            # Clear variables from memory
            del batch_resume_texts, batch_resume_embeddings, similarity_scores

    # Store matching results globally
    matching_results2 = [{
        "job_id": match[0],
        "resume_id": match[1],
        "similarity_score": match[2]
    } for match in matches]

    return jsonify({'message': 'Matching completed successfully'})

# Routes pour vers la page platform
@app.route('/platform')
def platform():
    return render_template('en/platform.html')

# Routes pour vers la page platform_fr
@app.route('/platform_fr')
def platform_fr():
    return render_template('fr/platform_fr.html')

# Routes pour vers la page challenges
@app.route('/challenges')
def challenges():
    return render_template('en/challenges.html')

# Routes pour vers la page challenges_fr
@app.route('/challenges_fr')
def challenges_fr():
    return render_template('fr/challenges_fr.html')

# Routes pour vers la page us
@app.route('/us')
def us():
    return render_template('en/us.html')

# Routes pour vers la page us_fr
@app.route('/us_fr')
def us_fr():
    return render_template('fr/us_fr.html')

# Routes pour vers la page contact
@app.route('/contact')
def contact():
    return render_template('en/contact.html')

# Routes pour vers la page contact_fr
@app.route('/contact_fr')
def contact_fr():
    return render_template('fr/contact_fr.html')

# Routes pour vers la page legal
@app.route('/legal')
def legal():
    return render_template('en/legal.html')

# Routes pour vers la page legal_fr
@app.route('/legal_fr')
def legal_fr():
    return render_template('fr/legal_fr.html')

# Routes pour vers la page faq
@app.route('/faq')
def faq():
    return render_template('en/faq.html')

# Routes pour vers la page faq_fr
@app.route('/faq_fr')
def faq_fr():
    return render_template('fr/faq_fr.html')

# Routes pour vers la page login
@app.route('/login')
def login():
    return render_template('en/login.html')

# Routes pour vers la page login_fr
@app.route('/login_fr')
def login_fr():
    return render_template('fr/login_fr.html')

# Fonction pour récupérer les données du métier envoyées via POST
@app.route('/get_jodes', methods=['POST'])
def get_jodes():
    jodes_content = request.form['jodes_content']
    print("Contenu de l'élément jodes:", jodes_content)
    return jsonify({'message':'description bien recu'})

# Route to handle resume uploads
@app.route('/upload_resume', methods=['POST'])
def upload_resume():
    if 'file' not in request.files:
        return jsonify({'error': 'No file part'})
    file = request.files['file']
    if file.filename == '':
        return jsonify({'error': 'No selected file'})
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
        return jsonify({'message': 'File uploaded successfully'})
    else:
        return jsonify({'error': 'File type not allowed'})

# Point d'entrée de l'application Flask
if __name__ == '__main__':
    app.run(debug=True)
