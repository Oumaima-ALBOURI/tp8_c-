
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

// Classe abstraite Plugin
class Plugin {
public:
    virtual string nom() const = 0;
    virtual string traiter(const string& texte) = 0;

    virtual ~Plugin() {}

    // Methode factory
    static unique_ptr<Plugin> creerPlugin(const string& type);
};

// Plugin 1 : Correcteur orthographique
class CorrecteurOrthographique : public Plugin {
public:
    string nom() const override {
        return "Correcteur orthographique";
    }

    string traiter(const string& texte) override {
        string resultat = texte;

        // Corrections simples
        size_t pos;

        while ((pos = resultat.find("bonjor")) != string::npos) {
            resultat.replace(pos, 6, "bonjour");
        }

        while ((pos = resultat.find("salu")) != string::npos) {
            resultat.replace(pos, 4, "salut");
        }

        while ((pos = resultat.find("ecole")) != string::npos) {
            resultat.replace(pos, 5, "ecole");
        }

        return resultat;
    }
};

// Plugin 2 : Traducteur francais vers anglais
class TraducteurAnglais : public Plugin {
public:
    string nom() const override {
        return "Traducteur anglais";
    }

    string traiter(const string& texte) override {
        string resultat = texte;

        // Traductions simples
        size_t pos;

        while ((pos = resultat.find("bonjour")) != string::npos) {
            resultat.replace(pos, 7, "hello");
        }

        while ((pos = resultat.find("chat")) != string::npos) {
            resultat.replace(pos, 4, "cat");
        }

        while ((pos = resultat.find("maison")) != string::npos) {
            resultat.replace(pos, 6, "house");
        }

        while ((pos = resultat.find("livre")) != string::npos) {
            resultat.replace(pos, 5, "book");
        }

        return resultat;
    }
};

// Plugin 3 : Analyseur de style
class AnalyseurStyle : public Plugin {
public:
    string nom() const override {
        return "Analyseur de style";
    }

    string traiter(const string& texte) override {
        int nbPhrases = 0;
        int nbLongues = 0;
        int longueur = 0;

        for (size_t i = 0; i < texte.size(); i++) {
            char c = texte[i];

            if (c == '.' || c == '!' || c == '?') {
                nbPhrases++;

                if (longueur > 50) {
                    nbLongues++;
                }

                longueur = 0;
            } else {
                longueur++;
            }
        }

        // Compter la derniere phrase si elle ne finit pas par une ponctuation
        if (longueur > 0) {
            nbPhrases++;

            if (longueur > 50) {
                nbLongues++;
            }
        }

        string resultat = texte;
        resultat += "\n[Analyse de style] Nombre de phrases : "
                    + to_string(nbPhrases);
        resultat += "\nPhrases trop longues : "
                    + to_string(nbLongues);

        if (nbLongues > 0) {
            resultat += "\nConseil : essayez de raccourcir les phrases.";
        } else {
            resultat += "\nLe texte est facile a lire.";
        }

        return resultat;
    }
};

// Implementation de la factory
unique_ptr<Plugin> Plugin::creerPlugin(const string& type) {
    if (type == "correcteur") {
        return unique_ptr<Plugin>(new CorrecteurOrthographique());
    }

    if (type == "traducteur") {
        return unique_ptr<Plugin>(new TraducteurAnglais());
    }

    if (type == "analyseur") {
        return unique_ptr<Plugin>(new AnalyseurStyle());
    }

    return nullptr;
}

// Programme principal
int main() {
    vector<unique_ptr<Plugin> > plugins;

    // Simulation du chargement des plugins
    plugins.push_back(Plugin::creerPlugin("correcteur"));
    plugins.push_back(Plugin::creerPlugin("traducteur"));
    plugins.push_back(Plugin::creerPlugin("analyseur"));

    string texte;

    cout << "Entrez un texte : ";
    getline(cin, texte);

    // Application successive des plugins
    for (size_t i = 0; i < plugins.size(); i++) {
        if (plugins[i]) {
            texte = plugins[i]->traiter(texte);

            cout << "\nPlugin applique : "
                 << plugins[i]->nom() << endl;

            cout << "Texte obtenu :\n"
                 << texte << endl;

            cout << "------------------------" << endl;
        }
    }

    return 0;
}
