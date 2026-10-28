
#include <iostream>
#include <string>
using namespace std;

// Classe abstraite
class SortieAudio {
public:
    virtual void ouvrir() = 0;
    virtual void jouer(const string& son) = 0;
    virtual void fermer() = 0;

    // Destructeur virtuel
    virtual ~SortieAudio() {
        cout << "Destruction de SortieAudio" << endl;
    }
};

// Classe HautParleur
class HautParleur : public SortieAudio {
public:
    void ouvrir() override {
        cout << "Haut-parleur ouvert." << endl;
    }

    void jouer(const string& son) override {
        cout << "Haut-parleur joue : " << son << endl;
    }

    void fermer() override {
        cout << "Haut-parleur ferme." << endl;
    }

    ~HautParleur() override {
        cout << "Destruction du HautParleur" << endl;
    }
};

// Classe CasqueBT
class CasqueBT : public SortieAudio {
public:
    void ouvrir() override {
        cout << "Casque Bluetooth connecte." << endl;
    }

    void jouer(const string& son) override {
        cout << "Casque Bluetooth joue : " << son << endl;
    }

    void fermer() override {
        cout << "Casque Bluetooth deconnecte." << endl;
    }

    ~CasqueBT() override {
        cout << "Destruction du CasqueBT" << endl;
    }
};

// Classe SortieHDMI
class SortieHDMI : public SortieAudio {
public:
    void ouvrir() override {
        cout << "Sortie HDMI activee." << endl;
    }

    void jouer(const string& son) override {
        cout << "Sortie HDMI transmet : " << son << endl;
    }

    void fermer() override {
        cout << "Sortie HDMI fermee." << endl;
    }

    ~SortieHDMI() override {
        cout << "Destruction de SortieHDMI" << endl;
    }
};

// Fonction de test polymorphe
void tester(SortieAudio* sortie) {
    sortie->ouvrir();
    sortie->jouer("Musique");
    sortie->fermer();
    cout << "------------------------" << endl;
}

int main() {
    // Tableau de pointeurs vers la classe de base
    SortieAudio* sorties[3];

    // Instanciation des classes derivees
    sorties[0] = new HautParleur();
    sorties[1] = new CasqueBT();
    sorties[2] = new SortieHDMI();

    // Parcours du tableau
    for (int i = 0; i < 3; i++) {
        tester(sorties[i]);
    }

    // Liberation de la memoire dynamique
    for (int i = 0; i < 3; i++) {
        delete sorties[i];
    }

    return 0;
}
