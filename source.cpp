#include "header.hpp"

vector<string> Transformateur::transformer(string nomFichier)
{
    vector<string> texte;
    string ligne, mot;
    ifstream ifs("../petit_corpus/" + nomFichier + ".txt");
    while (getline(ifs, ligne)) // lecture ligne par ligne du fichier
    {
        istringstream iss(ligne);
        while (iss >> mot) // lecture mot par mot de la ligne
        {
            for_each(mot.begin(), mot.end(), [](char& c) {c = tolower(c); }); // mettre tous les caracteres du mot en miniscule
            texte.push_back(mot);
        }
    }
    return texte;
}


vector<pair<string, double> > AnalyseurOccurence::analyserVector(vector<string> const& texte)
{
    vector< pair<string, double> > resultat;
    vector<string> tabMots; // tableau intermédiaire pour se débarasser des répétitions d'un mot

    // le cas où le tableau est vide
    if (texte.size() == 0) {
        resultat.push_back(make_pair("", 0));
        return resultat;
    }

    unsigned int occ(0); // compteur de nombre d'occurennce d'un mot dans un tableau
    for (auto&& mot1 : texte)
    {
        if (find(tabMots.begin(), tabMots.end(), mot1) == tabMots.end()) // si le mot n'exite pas dans le tableau intermédiare,
                                                                         //   càd on n'a pas    encore compté son nombre d'occurence
        {
            for (auto&& mot2 : texte)
                if (mot1 == mot2) occ++;
            resultat.push_back(make_pair(mot1, occ));
            tabMots.push_back(mot1);
            occ = 0;
        }
    }
    return resultat;
}


map<string, double> AnalyseurOccurence::analyserMap(vector<string> const& texte)
{
    map<string, double> resultat; 
    
    if (texte.size() == 0) {
        resultat[""] = 0;
    }
    else for (auto&& mot : texte) ++resultat[mot];
    
    return resultat;
}

vector<pair<string, double> > AnalyseurFrequence::analyserVector(vector<string> const& texte)
{
    vector< pair<string, double> > resultat;
    vector<string> tabMots; // tableau intermédiaire pour se débarasser des répétitions d'un mot

    // le cas où le tableau est vide
    if (texte.size() == 0) {
        resultat.push_back(make_pair("", 0));
        return resultat;
    }

    double  frq(0); // compteur de nombre d'occurennce d'un mot dans un tableau
    for (auto&& mot1 : texte)
    {
        if (find(tabMots.begin(), tabMots.end(), mot1) == tabMots.end()) // si le mot n'exite pas dans le tableau intermédiare,
                                                                         //   càd on n'a pas    encore compté son nombre d'occurence
        {
            for (auto&& mot2 : texte)
                if (mot1 == mot2) frq += 1.0 / texte.size();
            resultat.push_back(make_pair(mot1, frq));
            tabMots.push_back(mot1);
            frq = 0;
        }
    }
    return resultat;
}

map<string, double> AnalyseurFrequence::analyserMap(vector<string> const& texte)
{
    map<string, double> resultat; 

    if (texte.size() == 0) {
        resultat[""] = 0;
    }
    else for (auto&& mot : texte) resultat[mot] += 1.0 / texte.size();

    return resultat;
}

void Index::ajouterFichier(string nomFichier)
{
    bibliotheque.push_back(nomFichier);
    cout << "le fichier " << nomFichier << ".txt est ajoute a la base de recherche" << endl;
}

void Index::afficherFichiers()
{
    cout << "la base de recherche contient " << bibliotheque.size() << "fichiers" << endl;
    for (auto&& fichier : bibliotheque) cout << fichier << endl;
}

void Index::sauvegarderFichiers()
{
    ofstream bib("bibliotheque.txt");
    for (auto&& fichier : bibliotheque) bib << fichier << endl;
    bib.close();
    cout << "la liste des fichiers de la base de recherche est sauvegardée dans le fichier bibliotheque.txt" << endl;
}

void Index::restaurerFichiers()
{
    ifstream bib("bibliotheque.txt");
    string ligne;
    while (getline(bib, ligne)) bibliotheque.push_back(ligne);
    bib.close();
    cout << "la liste des fichiers de la base de recherche est restaure" << endl;
}

void Index::supprimerFichier(string nomFichier)
{
    int indice = -1;
    for (unsigned int i = 0; i < bibliotheque.size(); i++)
    {
        if (bibliotheque[i] == nomFichier)
        {
            indice = i;
            break;
        }
    }
    if (indice == -1) cout << "le fichier n'existe pas dans la base de recherche" << endl;
    else
    {
        bibliotheque.erase(bibliotheque.begin() + indice);
        supprimerFichierIndex(nomFichier); // quand le fichier est supprimé de la base de recherche, on doit aussi le supprimer
                                           // de l'index 
        cout << "le fichier est supprime de la base de recherche" << endl;
    }
}

vector<tuple<string, int, string> > Index::getIndexData()
{
    return indexData;
}

vector<string> Index::getBibliotheque()
{
    return bibliotheque;
}

void Index::afficherIndex()
{
    if (indexData.size() == 0) cout << "aucun fichier est indexe" << endl;
    else
    {
        for (auto&& triplet : indexData)
            cout << get<0>(triplet) << " " << get<1>(triplet) << " " << get<2>(triplet) << endl;
    }
}

void Index::supprimerFichierIndex(string const& nomFichier) // supprimer les statistiques d'un fichier indexé, 
                                                              // le fichier n'est donc plus indexé
{
    int indice = -1;
    for (unsigned int i = 0; i < indexData.size(); i++)
    {
        if (get<2>(indexData[i]) == nomFichier)
        {
            indice = i;
            break;
        }
    }
    if (indice == -1) cout << "le fichier " << nomFichier << ".txt" << "n'est pas deja indexe" << endl;
    else
    {
        indexData.erase(indexData.begin() + indice);
        cout << "le fichier " << nomFichier << ".txt" << " n'est plus indexe" << endl;
    }
}

void Index::restaurerIndex()
{
    ifstream stat("index.txt");
    string ligne, mot1, mot2;
    int nb;
    while (getline(stat, ligne))
    {
        istringstream iss(ligne);
        iss >> mot1;
        iss >> nb;
        iss >> mot2;
        indexData.push_back(make_tuple(mot1, nb, mot2));
    }
    stat.close();
    cout << "la liste des fichiers indexes est restaure" << endl;
}

void Index::sauvegarderIndex()
{
    ofstream stat("index.txt");
    for (auto&& triplet : indexData) stat << get<0>(triplet) << " " << get<1>(triplet) << " " << get<2>(triplet) << endl;
    stat.close();
    cout << "la liste des fichiers indexes est sauvegardee dans le fichier index.txt" << endl;
}

void Index::supprimerIndex() 
{
    indexData.clear();
    cout << "tout l'index est supprime" << endl;
}

void IndexVector::indexer(vector<pair<string, double> > const& stats, string const& nomFichier)
{
    if (find(bibliotheque.begin(), bibliotheque.end(), nomFichier) == bibliotheque.end())
        cout << "le fichier n'existe pas dans la base de recherche, ajouter le avant de l'indexer" << endl;
    else
    {
        unsigned int c = 0;
        for (auto&& triplet : indexData)
        {
            if (get<2>(triplet) == nomFichier)
            {
                cout << "le fichier est deja indexe" << endl;
                break;
            }
            c++;
        }
        if (c == indexData.size())
        {
            for (auto&& doublet : stats)
                indexData.push_back(make_tuple(doublet.first, doublet.second, nomFichier));
            cout << "le fichier est indexe" << endl;
        }
    }
}

void IndexVector::reindexer(vector<pair<string, double> > const& stats, string const& nomFichier) // réindexer un fichier
{
    supprimerFichierIndex(nomFichier);
    indexer(stats, nomFichier);
}

void IndexMap::indexer(map<string, double> stats, string const& nomFichier)
{
    if (find(bibliotheque.begin(), bibliotheque.end(), nomFichier) == bibliotheque.end())
        cout << "le fichier n'existe pas dans la base de recherche, ajouter le avant de l'indexer" << endl;
    else
    {
        unsigned int c = 0;
        for (auto&& triplet : indexData)
        {
            if (get<2>(triplet) == nomFichier)
            {
                cout << "le fichier est deja indexe" << endl;
                break;
            }
            c++;
        }
        if (c == indexData.size())
        {
            for (auto&& doublet : stats)
                indexData.push_back(make_tuple(doublet.first, doublet.second, nomFichier));
            cout << "le fichier est indexe" << endl;
        }
    }
}

void IndexMap::reindexer(map<string, double> stats, string const& nomFichier)
{
    supprimerFichierIndex(nomFichier);
    indexer(stats, nomFichier);
}

vector<string> OrdonnanceurBooleen::ordonnancer(vector<string> const& tabRequete, Index& index)
{
    // on ignore les mots vides en anglais lors de la recherche pour avoir des resultat plus pertinents
    vector<string> englishStopWords = { "a", "about", "above", "after", "again", "against", "all", "am",
                                "an", "and", "any", "are", "aren't", "as", "at", "be", "because",
                                "been", "before", "being", "below", "between", "both", "but", "by",
                                "can't", "cannot", "could", "couldn't", "did", "didn't", "do", "does",
                                "doesn't", "doing", "don't", "down", "during", "each", "few", "for",
                                "from", "further", "had", "hadn't", "has", "hasn't", "have", "haven't",
                                "having", "he", "he'd", "he'll", "he's", "her", "here", "here's", "hers",
                                "herself", "him", "himself", "his", "how", "how's", "i", "i'd", "i'll", "i'm"
                                "i've", "if", "in", "into", "is", "isn't", "it", "it's", "its", "itself"
                                "let's", "me", "more", "most", "mustn't", "my", "myself", "no", "nor" ,"not",
                                "of", "off", "on", "once", "only", "or", "other", "ought", "our", "ours",
                                "ourselves", "out", "over", "own", "same", "shan't", "she", "she'd", "she'll",
                                "she's", "should", "shouldn't", "so", "some", "such", "than", "that", "that's",
                                "the", "their", "theirs", "them", "themselves", "then", "there", "there's"
                                "these", "they", "they'd", "they'll", "they're", "they've", "this", "those",
                                "through", "to", "too", "under", "until", "up", "very", "was", "wasn't", "we",
                                "we'd", "we'll", "we're", "we've", "were", "weren't", "what", "what's", "when",
                                "when's", "where", "where's", "which", "while", "who", "who's", "whom", "why",
                                "why's", "with", "won't", "would", "wouldn't", "you", "you'd", "you'll",
                                "you're", "you've", "your", "yours", "yourself", "yourselves" };
    vector<string> motsCle;
    vector<string> resultat;
    unsigned int nb = 0;
    string repere;

    // prendre les mots de la requete sans les mots vides dans la langue anglaise
    for (auto&& mot : tabRequete)
    {
        if (find(englishStopWords.begin(), englishStopWords.end(), mot) == englishStopWords.end()) motsCle.push_back(mot);
    }

    repere = get<2>(index.getIndexData()[0]);
    for (auto&& triplet : index.getIndexData())
    {
        if (repere != get<2>(triplet))
        {
            if (nb == motsCle.size()) resultat.push_back(repere); // si le fichier contient tous les mots clés
            repere = get<2>(triplet);
            nb = 0;
        }
        if (find(motsCle.begin(), motsCle.end(), get<0>(triplet)) != motsCle.end()) nb++; // on compte combien de mots clés touvés
                                                                                          // par fichier indexé
    }
    if (nb == motsCle.size()) resultat.push_back(repere); // si le dernier fichier dans l'index contient tous les mots clés
    
    return resultat; // retourner les fichiers qui contiennent tous les mots clés
}

vector<string> OrdonnanceurScore::ordonnancer(vector<string> const& tabRequete, Index& index)
{
    vector<string> englishStopWords = { "a", "about", "above", "after", "again", "against", "all", "am",
                                "an", "and", "any", "are", "aren't", "as", "at", "be", "because",
                                "been", "before", "being", "below", "between", "both", "but", "by",
                                "can't", "cannot", "could", "couldn't", "did", "didn't", "do", "does",
                                "doesn't", "doing", "don't", "down", "during", "each", "few", "for",
                                "from", "further", "had", "hadn't", "has", "hasn't", "have", "haven't",
                                "having", "he", "he'd", "he'll", "he's", "her", "here", "here's", "hers",
                                "herself", "him", "himself", "his", "how", "how's", "i", "i'd", "i'll", "i'm"
                                "i've", "if", "in", "into", "is", "isn't", "it", "it's", "its", "itself"
                                "let's", "me", "more", "most", "mustn't", "my", "myself", "no", "nor" ,"not",
                                "of", "off", "on", "once", "only", "or", "other", "ought", "our", "ours",
                                "ourselves", "out", "over", "own", "same", "shan't", "she", "she'd", "she'll",
                                "she's", "should", "shouldn't", "so", "some", "such", "than", "that", "that's",
                                "the", "their", "theirs", "them", "themselves", "then", "there", "there's"
                                "these", "they", "they'd", "they'll", "they're", "they've", "this", "those",
                                "through", "to", "too", "under", "until", "up", "very", "was", "wasn't", "we",
                                "we'd", "we'll", "we're", "we've", "were", "weren't", "what", "what's", "when",
                                "when's", "where", "where's", "which", "while", "who", "who's", "whom", "why",
                                "why's", "with", "won't", "would", "wouldn't", "you", "you'd", "you'll",
                                "you're", "you've", "your", "yours", "yourself", "yourselves" };

    vector<string> motsCle;
    vector<unsigned int> tabScore;
    vector<string> resultat;
    unsigned int nb = 0, score = 0;
    string repere;

    for (auto&& mot : tabRequete)
    {
        if (find(englishStopWords.begin(), englishStopWords.end(), mot) == englishStopWords.end()) motsCle.push_back(mot);
    }

    repere = get<2>(index.getIndexData()[0]);
    for (auto&& triplet : index.getIndexData())
    {
        if (repere != get<2>(triplet))
        {
            if (nb == motsCle.size())
            {
                resultat.push_back(repere);
                tabScore.push_back(score);
            }
            repere = get<2>(triplet);
            nb = 0;
            score = 0;
        }
        if (find(motsCle.begin(), motsCle.end(), get<0>(triplet)) != motsCle.end())
        {
            nb++;
            score = score + get<1>(triplet);
        }
    }
    if (nb == motsCle.size())
    {
        resultat.push_back(repere);
        tabScore.push_back(score);
    }

    int N = tabScore.size();
    for (unsigned int i = N; i > 0; i--)
    {
        for (unsigned int j = 1; j < i; j++)
        {
            if (tabScore[j - 1] > tabScore[j])
            {
                score = tabScore[j - 1];
                tabScore[j - 1] = tabScore[j];
                tabScore[j] = score;
                repere = resultat[j - 1];
                resultat[j - 1] = resultat[j];
                resultat[j] = repere;
            }
        }
    }
   
    return resultat; // retourner les fichiers qui contiennent tous les mots clés ordonnés par un score
}

vector<string> OrdonnanceurTFIDF::ordonnancer(vector<string> const& tabRequete, Index& index)
{
    vector<string> englishStopWords = { "a", "about", "above", "after", "again", "against", "all", "am",
                                "an", "and", "any", "are", "aren't", "as", "at", "be", "because",
                                "been", "before", "being", "below", "between", "both", "but", "by",
                                "can't", "cannot", "could", "couldn't", "did", "didn't", "do", "does",
                                "doesn't", "doing", "don't", "down", "during", "each", "few", "for",
                                "from", "further", "had", "hadn't", "has", "hasn't", "have", "haven't",
                                "having", "he", "he'd", "he'll", "he's", "her", "here", "here's", "hers",
                                "herself", "him", "himself", "his", "how", "how's", "i", "i'd", "i'll", "i'm"
                                "i've", "if", "in", "into", "is", "isn't", "it", "it's", "its", "itself"
                                "let's", "me", "more", "most", "mustn't", "my", "myself", "no", "nor" ,"not",
                                "of", "off", "on", "once", "only", "or", "other", "ought", "our", "ours",
                                "ourselves", "out", "over", "own", "same", "shan't", "she", "she'd", "she'll",
                                "she's", "should", "shouldn't", "so", "some", "such", "than", "that", "that's",
                                "the", "their", "theirs", "them", "themselves", "then", "there", "there's"
                                "these", "they", "they'd", "they'll", "they're", "they've", "this", "those",
                                "through", "to", "too", "under", "until", "up", "very", "was", "wasn't", "we",
                                "we'd", "we'll", "we're", "we've", "were", "weren't", "what", "what's", "when",
                                "when's", "where", "where's", "which", "while", "who", "who's", "whom", "why",
                                "why's", "with", "won't", "would", "wouldn't", "you", "you'd", "you'll",
                                "you're", "you've", "your", "yours", "yourself", "yourselves" };

    vector<string> motsCle;
    float TF(0), IDF(0), DF(0), TF_IDF(1);
    vector<string> resultat;
    vector<pair<float, string> > temp;
    map<string, unsigned int> motsDocument;
    unsigned int motCleOcc = 0;
    string repere;

    for (auto&& mot : tabRequete)
    {
        if (find(englishStopWords.begin(), englishStopWords.end(), mot) == englishStopWords.end()) motsCle.push_back(mot);
    }

    // on compte combien de mots contient chaque fichier indexé
    repere = get<2>(index.getIndexData()[0]);
    for (auto&& triplet : index.getIndexData()) {
        if (repere != get<2>(triplet)) repere = get<2>(triplet);
        motsDocument[repere] += get<1>(triplet);
    }

    // TF-IDF 
    repere = get<2>(index.getIndexData()[0]);
    for (auto&& triplet1 : index.getIndexData()) {
        if (repere != get<2>(triplet1)) {
            if (TF_IDF != 0) temp.push_back(make_pair(TF_IDF, repere));
            repere = get<2>(triplet1);
        }
        if (find(motsCle.begin(), motsCle.end(), get<0>(triplet1)) != motsCle.end()) {
            TF = get<1>(triplet1) / motsDocument[repere];
            for (auto&& triplet2 : index.getIndexData()) {
                if ((get<0>(triplet2) == get<0>(triplet1)) && (get<2>(triplet2) != repere)) DF++;
            }
            IDF = log(index.getBibliotheque().size() / DF);
            TF_IDF *= IDF * TF;
        }
       
    }

    sort(temp.begin(), temp.end());
    for (auto&& doublet : temp)
        resultat.push_back(doublet.second);


    return resultat; // retourner les fichiers ordonnés par un score TF-IDF
}

vector<string> MoteurDeRecherche::rechercher(Analyseur& analyseur, Index& index, Ordonnanceur& ordonnanceur)
{
    vector<string> tabRequete;

    // lire la requête de l'utilisateur
    string requete;
    cout << "Qu'est-ce que vous cherchez?" << endl;
    cin.sync();
    getline(cin, requete);

    // mettre les mots de la phrase de l'utilisateur dans un  tableau
    istringstream iss(requete);
    string mot;
    while (iss >> mot)
    {
        for_each(mot.begin(), mot.end(), [](char& c) {c = tolower(c); });
        tabRequete.push_back(mot);
    }
    
    return ordonnanceur.ordonnancer(tabRequete, index);
}
























