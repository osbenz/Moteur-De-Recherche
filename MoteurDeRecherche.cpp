#include "header.hpp""

int main()
{
    MoteurDeRecherche moteurDeRecherche;
    AnalyseurOccurence analyseur;
    IndexVector indexVector;
    IndexMap indexMap;
    bool useVector = true;
    OrdonnanceurScore ordonnanceur;
    Transformateur transformateur;
    
    indexVector.restaurerIndex();
    indexVector.restaurerFichiers();
    IndexVector& index = indexVector;

    int numOp = 0;
    int choix;
    while (1)
    {
        cout << "\n \n \n \n\t\t******************************_____________________________*******************************\n"
            << "\t\t \t************************_______________________________************************\n"
            << "\t\t\t\t\t         _____________MENU_________________\n"
            << "\t\t\t\t 1) rechercher des fichiers \n"
            << "\t\t\t\t 2) ajouter un fichier a la base de recherche\n"
            << "\t\t\t\t 3) supprimer un fichier de la base de recherche\n"
            << "\t\t\t\t 4) afficher les fichiers de la base de recherche\n"
            << "\t\t\t\t 5) indexer un fichier\n"
            << "\t\t\t\t 6) afficher l'index\n"
            << "\t\t\t\t 7) reindexer un fichier\n"
            << "\t\t\t\t 8) supprimer un fichier de l'index\n"
            << "\t\t\t\t 9) supprimer l'index\n"
            << "\t\t\t\t10) configurer le moteur de recherche\n"
            << "\t\t\t\t11) quitter \n\n\n"
            << "saisissez votre choix: \n";

        cin >> choix;
        switch (choix)
        {
            case 1:
            {
                numOp++;
                cout << "\n\n_________________________________________RECHERCHER FICHIERS________________________________\n";
                if (index.getIndexData().size() == 0) cout << "l'index est vide, vous ne pouvez pas effectuez une recherche" << endl;
                else
                {
                    vector<string> resultat;
                    resultat = moteurDeRecherche.rechercher(analyseur, index, ordonnanceur);
                    if (resultat.size() == 0) cout << "aucun resultat trouve" << endl;
                    else
                    {
                        cout << endl << "resultats de la recherche:" << endl;
                        for (auto&& nomFichier : resultat) cout << nomFichier << endl;
                    }

                }
                break;
            }

            case 2:
            {
                numOp++;
                cout << "\n\n__________________________________________AJOUTER FICHIER______________________________________\n";
                cout << "donner le nom du fichier sans mentionner l'extension .txt" << endl;
                string nomFichier;
                cin.sync();
                cin >> nomFichier;
                index.ajouterFichier(nomFichier);
                break;
            }

            case 3:
            {
                numOp++;
                cout << "\n\n_________________________________________SUPPRIMER FICHIER________________________________\n";
                cout << "donner le nom du fichier sans mentionner l'extension .txt" << endl;
                string nomFichier;
                cin.sync();
                cin >> nomFichier;
                index.supprimerFichier(nomFichier);
                break;
            }

            case 4:
            {
                numOp++;
                cout << "\n\n_________________________________________AFFICHER FICHIERS________________________________\n";
                index.afficherFichiers();
                break;
            }

            case 5:
            {
                numOp++;
                cout << "\n\n_________________________________________INDEXER FICHIERS________________________________\n";
                cout << "donner le nom du fichier sans mentionner l'extension .txt" << endl;
                string nomFichier;
                cin.sync();
                cin >> nomFichier;
                if (useVector)
                    indexVector.indexer(analyseur.analyserVector(transformateur.transformer(nomFichier)), nomFichier);
                else
                    indexMap.indexer(analyseur.analyserMap(transformateur.transformer(nomFichier)), nomFichier);
                break;
            }


            case 6:
            {
                numOp++;
                cout << "\n\n_________________________________________AFFICHER INDEX________________________________\n";
                index.afficherIndex();
                break;
            }

            case 7:
            {
                numOp++;
                cout << "\n\n_________________________________________REINDEXER FICHIER________________________________\n";
                cout << "donner le nom du fichier sans mentionner l'extension .txt" << endl;
                string nomFichier;
                cin.sync();
                cin >> nomFichier;
                if (useVector)
                    indexVector.reindexer(analyseur.analyserVector(transformateur.transformer(nomFichier)), nomFichier);
                else
                    indexMap.reindexer(analyseur.analyserMap(transformateur.transformer(nomFichier)), nomFichier);
                break;
            }

            case 8:
            {
                numOp++;
                cout << "\n\n_________________________________________SUPPRIMER FICHIER INDEX________________________________\n";
                cout << "donner le nom du fichier sans mentionner l'extension .txt" << endl;
                string nomFichier;
                cin.sync();
                cin >> nomFichier;
                index.supprimerFichierIndex(nomFichier);
                break;
            }

            case 9:
            {
                numOp++;
                cout << "\n\n_________________________________________SUPRRIMER INDEX ________________________________\n";
                index.supprimerIndex();
                break;
            }

            case 10:
            {
                if (numOp == 0)
                {
                    cout << "\n\n____________________________CONFIGURER MOTEUR RECHERCHE________________________________\n";

                    int choix2;
                    bool rester = true;
                    while (rester)
                    {
                        cout << "1) AnalyseurOccurence     2) AnalyseurFrequence" << endl;
                        cout << "que  choisir?" << endl << endl;
                        cin >> choix2;
                        switch (choix2)
                        {
                            case 1:
                            {
                                AnalyseurOccurence analyseur;
                                rester = false;
                                break;
                            }

                            case 2:
                            {
                                AnalyseurFrequence analyseur;
                                rester = false;
                                break;
                            }

                            default:
                                cout << "choix invalide" << endl;
                        }
                    }

                    rester = true;
                    while (rester)
                    {
                        cout << "1) IndexVector     2) IndexMap" << endl;
                        cout << "que  choisir?" << endl << endl;
                        cin >> choix2;
                        switch (choix2)
                        {
                        case 1:
                        {
                            IndexVector indexVector;
                            useVector = true;
                            index.restaurerFichiers();
                            index.restaurerIndex();
                            rester = false;
                            break;
                        }

                        case 2:
                        {
                            IndexMap indexMap;
                            useVector = false;
                            index.restaurerFichiers();
                            index.restaurerIndex();
                            IndexMap& index = indexMap;
                            rester = false;
                            break;
                        }

                        default:
                            cout << "choix invalide" << endl;
                        }
                    }

                    rester = true;
                    while (rester)
                    {
                        cout << "1) OrdonnanceurBooleen     2) OrdonnanceurScore     3) OrdonnanceurTFIDF" << endl;
                        cout << "que  choisir?" << endl << endl;
                        cin >> choix2;

                        switch (choix2)
                        {
                            case 1:
                            {
                                OrdonnanceurBooleen ordonnanceur;
                                rester = false;
                                break;
                            }

                            case 2:
                            {
                                OrdonnanceurScore ordonnanceur;
                                rester = false;
                                break;
                            }

                            case 3:
                            {
                                OrdonnanceurTFIDF ordonnanceur;
                                rester = false;
                                break;
                            }

                            default:
                                cout << "choix invalide" << endl;
                        }
                    }
                }
                else cout << "vous ne pouvez pas changer la configuartion du moteur de recherche qu'au début du programme" << endl;
                break;
            }

            case 11:
            {
                index.sauvegarderIndex();
                index.sauvegarderFichiers();
                exit(0);
            }

            default:
                cout << "\t \t \t \t \t \t choix invalide" << endl;
        }
    }

}

