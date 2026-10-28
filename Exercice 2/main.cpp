
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
using namespace std;

// Structure representant un vecteur 3D
struct Vec3 {
    float x, y, z;

    Vec3(float x = 0, float y = 0, float z = 0)
        : x(x), y(y), z(z) {}
};

// Calcul du produit scalaire
float produitScalaire(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Calcul de la norme d'un vecteur
float norme(const Vec3& v) {
    return sqrt(produitScalaire(v, v));
}

// Normalisation d'un vecteur
Vec3 normaliser(const Vec3& v) {
    float n = norme(v);

    if (n == 0)
        return Vec3();

    return Vec3(v.x / n, v.y / n, v.z / n);
}

// Classe abstraite Lumiere
class Lumiere {
public:
    virtual float intensite(const Vec3& position) const = 0;

    virtual ~Lumiere() {}
};

// Lumiere directionnelle
class LumiereDirectionnelle : public Lumiere {
private:
    Vec3 direction;
    float couleur;

public:
    LumiereDirectionnelle(Vec3 d, float c)
        : direction(normaliser(d)), couleur(c) {}

    float intensite(const Vec3& position) const override {
        return couleur;
    }
};

// Lumiere ponctuelle
class LumierePonctuelle : public Lumiere {
private:
    Vec3 positionLumiere;
    float attenuation;

public:
    LumierePonctuelle(Vec3 p, float a)
        : positionLumiere(p), attenuation(a) {}

    float intensite(const Vec3& position) const override {
        float dx = position.x - positionLumiere.x;
        float dy = position.y - positionLumiere.y;
        float dz = position.z - positionLumiere.z;

        float distance = sqrt(dx * dx + dy * dy + dz * dz);

        return 1.0f /
               (1.0f + attenuation * distance * distance);
    }
};

// Lumiere spot
class LumiereSpot : public Lumiere {
private:
    Vec3 positionLumiere;
    Vec3 direction;
    float angleOuverture;
    float puissance;

public:
    LumiereSpot(Vec3 p, Vec3 d, float angle, float puissance)
        : positionLumiere(p),
          direction(normaliser(d)),
          angleOuverture(angle),
          puissance(puissance) {}

    float intensite(const Vec3& position) const override {
        Vec3 versPoint(
            position.x - positionLumiere.x,
            position.y - positionLumiere.y,
            position.z - positionLumiere.z
        );

        float distance = norme(versPoint);

        if (distance == 0)
            return puissance;

        Vec3 directionPoint = normaliser(versPoint);

        float cosAngle = produitScalaire(
            direction, directionPoint
        );

        float seuil = cos(
            angleOuverture * 3.14159265f / 180.0f
        );

        // Verifier si le point est dans le cone lumineux
        if (cosAngle < seuil)
            return 0.0f;

        // Intensite diminue avec la distance
        return puissance / (1.0f + distance * distance);
    }
};

// Collection de lumieres
vector<unique_ptr<Lumiere> > lumieres;

// Fonction qui calcule l'eclairage total
float calculerEclairage(const Vec3& point) {
    float total = 0.0f;

    for (const auto& lumiere : lumieres) {
        total += lumiere->intensite(point);
    }

    return total;
}

// Fonction principale
int main() {
    // Creation des lumieres avec C++11
    lumieres.push_back(
        unique_ptr<Lumiere>(
            new LumiereDirectionnelle(
                Vec3(0, -1, 0), 0.5f
            )
        )
    );

    lumieres.push_back(
        unique_ptr<Lumiere>(
            new LumierePonctuelle(
                Vec3(0, 0, 0), 0.1f
            )
        )
    );

    lumieres.push_back(
        unique_ptr<Lumiere>(
            new LumiereSpot(
                Vec3(0, 0, 5),
                Vec3(0, 0, -1),
                30.0f,
                2.0f
            )
        )
    );

    // Points a tester
    Vec3 points[] = {
        Vec3(0, 0, 1),
        Vec3(2, 0, 0),
        Vec3(0, 0, 10)
    };

    // Calcul de l'eclairage pour chaque point
    for (int i = 0; i < 3; i++) {
        cout << "Point " << i + 1 << " : ("
             << points[i].x << ", "
             << points[i].y << ", "
             << points[i].z << ")" << endl;

        cout << "Eclairage total = "
             << calculerEclairage(points[i]) << endl;

        cout << "------------------------" << endl;
    }

    return 0;
}
