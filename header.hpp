#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include<algorithm>
#include <math.h> 
using namespace std;

// le transformateur extrait les mots d'un fichier et les met dans un vecteur, il transforme donc un fichier 
// en un veteur de mots
class Transformateur
{
    public:
        vector<string> transformer(string);
};




class Analyseur // classe abstraite
{
    public:
        virtual vector<pair<string, double> > analyserVector(vector<string> const&) = 0; // methode virtuelle pure
        virtual map<string, double> analyserMap(vector<string> const& texte) = 0;
};

class AnalyseurOccurence : public Analyseur
{
    public:
        vector<pair<string, double> > analyserVector(vector<string> const&);
        map<string, double> analyserMap(vector<string> const&);
};

class AnalyseurFrequence : public Analyseur
{
    public:
        vector<pair<string, double> > analyserVector(vector<string> const&);
        virtual map<string, double> analyserMap(vector<string> const&);
};




    class Index

{
    protected:
        vector<string> bibliotheque = {}; // liste virtuelle des fichiers qui existe dans la base de recherche du moteur
        vector<tuple<string, int, string> > indexData = {}; // copie du contenu du fichier contenant les statistiques de l'indexation

    public:
        vector<tuple<string, int, string> > getIndexData();
        vector<string> getBibliotheque();
        void ajouterFichier(string);
        void supprimerFichier(string);
        void afficherFichiers();
        void sauvegarderFichiers();
        void restaurerFichiers();
        void afficherIndex();
        void sauvegarderIndex();
        void supprimerIndex();  // supprimer tout le fichier statistiques.txt => déindexation total
        void restaurerIndex();
        void supprimerFichierIndex(string const&); // supprimer les statistiques d'un fichier indexé, 
                                                              // le fichier n'est donc plus indexé
};

class IndexVector : public Index
{
    public:
        void indexer(vector<pair<string, double> > const&, string const&); // indexer un fichier,
                        // stats est le tableau résultant de la procédure de l'analyse du fichier de nomFichier
        
        void reindexer(vector<pair<string, double> > const&, string const&); // réindexer un fichier
};

class IndexMap : public Index
{
    public:
        void indexer(map<string, double>, string const&); // indexer un fichier,
                        // vecteurStat est le tableau résultant de la procédure de l'analyse du fichier de nomFichier

        void reindexer(map<string, double>, string const&); // réindexer un fichier
};




class Ordonnanceur //classe abstraite
{
    public:
        virtual vector<string> ordonnancer(vector<string> const&, Index&) = 0;

};

class OrdonnanceurBooleen : public Ordonnanceur //les fichiers qui contiennent tous les mots de la requete seront selectionnés sans ordre
{
    public:
        vector<string> ordonnancer(vector<string> const&, Index&);        
};

class OrdonnanceurScore : public Ordonnanceur  //les fichiers qui contiennent tous les mots de la requete seront selectionnés avec  ordre selon un score
{
    public:
        vector<string> ordonnancer(vector<string> const&, Index&);
};

class OrdonnanceurTFIDF : public Ordonnanceur  //les fichiers qui contiennent tous les mots de la requete seront selectionnés avec  ordre selon un score
{
    public:
        vector<string> ordonnancer(vector<string> const&, Index&);
};

// ordonanceurTFIDF

class MoteurDeRecherche
{
    public:
        vector<string> rechercher(Analyseur&, Index&, Ordonnanceur&);
};




