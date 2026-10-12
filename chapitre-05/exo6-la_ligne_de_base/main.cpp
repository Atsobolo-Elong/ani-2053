#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct Glyphe {
    int avance;
    int x0;
    int y0;
    int x1;
    int y1;
};

struct Correction {
    char premier;
    char second;
    int valeur;
};

int main() {
    int G;
    cin >> G;

    // LIRE LA TABLE DES GLYPHES
    unordered_map<char, Glyphe> glyphes;

    for (int i = 0; i < G; i++) {
        char c;
        Glyphe g;

        cin >> c >> g.avance
            >> g.x0 >> g.y0
            >> g.x1 >> g.y1;

        glyphes[c] = g;
    }

    int K;
    cin >> K;

    // LIRE LA TABLE DE CRENAGE
    vector<Correction> corrections(K);

    for (int i = 0; i < K; i++) {
        cin >> corrections[i].premier
            >> corrections[i].second
            >> corrections[i].valeur;
    }

    string texte;
    int ox, oy;

    cin >> texte >> ox >> oy;

    // INITIALISER LE CURSEUR
    int x = ox;
    int absents = 0;

    // INITIALISER LA BOITE ENGLOBANTE
    bool dessinPresent = false;
    int minx = 0;
    int miny = 0;
    int maxx = 0;
    int maxy = 0;

    // PARCOURIR LE TEXTE CARACTERE PAR CARACTERE
    for (size_t i = 0; i < texte.size(); i++) {
        char c = texte[i];

        // VERIFIER SI LE GLYPHE EXISTE
        auto trouve = glyphes.find(c);

        if (trouve == glyphes.end()) {
            cout << c << " ABSENT\n";
            absents++;
            continue;
        }

        const Glyphe& g = trouve->second;

        // AFFICHER LA POSITION DU CURSEUR
        cout << c << ' ' << x << '\n';

        // VERIFIER SI LE GLYPHE POSSEDE UN RECTANGLE DESSINABLE
        if (g.x1 > g.x0 && g.y1 > g.y0) {
            int gauche = x + g.x0;
            int haut = oy + g.y0;
            int droite = x + g.x1;
            int bas = oy + g.y1;

            // INITIALISER OU AGRANDIR LA BOITE ENGLOBANTE
            if (!dessinPresent) {
                minx = gauche;
                miny = haut;
                maxx = droite;
                maxy = bas;
                dessinPresent = true;
            } else {
                minx = min(minx, gauche);
                miny = min(miny, haut);
                maxx = max(maxx, droite);
                maxy = max(maxy, bas);
            }
        }

        // AVANCER LE CURSEUR
        x += g.avance;

        // APPLIQUER LE CRENAGE SI LE CARACTERE SUIVANT EXISTE
        if (i + 1 < texte.size()) {
            char suivant = texte[i + 1];

            // NE PAS CHERCHER DE CRENAGE APRES UN CARACTERE ABSENT
            if (glyphes.find(suivant) != glyphes.end()) {
                for (const Correction& correction : corrections) {
                    if (correction.premier == c &&
                        correction.second == suivant) {
                        x += correction.valeur;
                        break;
                    }
                }
            }
        }
    }

    // AFFICHER LA POSITION FINALE DU CURSEUR
    cout << "CURSEUR " << x << '\n';

    // TRAITER LE CAS OU AUCUN RECTANGLE N'A ETE DESSINE
    if (!dessinPresent) {
        cout << "BOITE AUCUNE\n";
        cout << "MONTE 0\n";
        cout << "DESCEND 0\n";
        cout << "ECRAN RIEN\n";
        cout << "ABSENTS " << absents << '\n';
        return 0;
    }

    // AFFICHER LA BOITE ENGLOBANTE
    cout << "BOITE "
         << minx << ' ' << miny << ' '
         << maxx << ' ' << maxy << '\n';

    // CALCULER LA HAUTEUR AU-DESSUS DE LA LIGNE DE BASE
    int monte = 0;

    if (miny < oy) {
        monte = oy - miny;
    }

    cout << "MONTE " << monte << '\n';

    // CALCULER LA HAUTEUR SOUS LA LIGNE DE BASE
    int descend = 0;

    if (maxy > oy) {
        descend = maxy - oy;
    }

    cout << "DESCEND " << descend << '\n';

    // DETERMINER SI LE TEXTE DEPASSE LE HAUT DE L'ECRAN
    string ecran;

    if (maxy <= 0) {
        ecran = "HORS";
    } else if (miny < 0) {
        ecran = "COUPE";
    } else {
        ecran = "VISIBLE";
    }

    cout << "ECRAN " << ecran << '\n';

    // AFFICHER LE NOMBRE DE CARACTERES ABSENTS
    cout << "ABSENTS " << absents << '\n';

    return 0;
}