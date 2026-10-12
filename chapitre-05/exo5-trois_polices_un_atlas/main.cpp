#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Groupe {
    string police;
    long long n;
    long long w;
    long long h;
    long long xPremier;
    long long yPremier;
    long long xDernier;
    long long yDernier;
};

int main() {
    long long P, L;
    cin >> P >> L;

    int G;
    cin >> G;

    if (G == 0) {
        cout << "AUCUN\n";
        return 0;
    }

    vector<Groupe> groupes(G);
    long long besoin = 0;
    long long occupe = 0;

    // LIRE LES GROUPES ET CALCULER LES SURFACES
    for (int i = 0; i < G; i++) {
        cin >> groupes[i].police
            >> groupes[i].n
            >> groupes[i].w
            >> groupes[i].h;

        besoin += groupes[i].n
                * (groupes[i].w + P)
                * (groupes[i].h + P);

        occupe += groupes[i].n
                * groupes[i].w
                * groupes[i].h;
    }

    // CHOISIR LA LARGEUR INITIALE
    long long W = L;

    if (W == 0) {
        W = 512;

        while (W * W < 2 * besoin && W < 4096) {
            W *= 2;
        }
    }

    long long H = W;
    bool reussi = false;
    int essais = 0;

    // EFFECTUER AU PLUS HUIT ESSAIS
    for (int tentative = 1; tentative <= 8; tentative++) {
        essais = tentative;

        // REINITIALISER LE CURSEUR ET LES POSITIONS
        long long x = P;
        long long y = P;
        long long e = 0;

        bool echec = false;

        // RANGER LES GLYPHES GROUPE PAR GROUPE
        for (int i = 0; i < G && !echec; i++) {
            long long rw = groupes[i].w + P;
            long long rh = groupes[i].h + P;

            for (long long j = 0; j < groupes[i].n; j++) {

                // PASSER A L'ETAGERE SUIVANTE SI NECESSAIRE
                if (x + rw > W - P) {
                    x = P;
                    y = y + e + P;
                    e = 0;
                }

                // VERIFIER SI LE GLYPHE DEPASSE EN LARGEUR
                if (x + rw > W - P) {
                    echec = true;
                    break;
                }

                // VERIFIER SI LE GLYPHE DEPASSE EN HAUTEUR
                if (y + rh > H - P) {
                    echec = true;
                    break;
                }

                // ENREGISTRER LA POSITION DU PREMIER GLYPHE
                if (j == 0) {
                    groupes[i].xPremier = x;
                    groupes[i].yPremier = y;
                }

                // ENREGISTRER LA POSITION DU DERNIER GLYPHE
                if (j == groupes[i].n - 1) {
                    groupes[i].xDernier = x;
                    groupes[i].yDernier = y;
                }

                // PLACER LE GLYPHE SUIVANT
                x += rw;

                if (rh > e) {
                    e = rh;
                }
            }
        }

        // ARRETER SI TOUS LES GLYPHES TIENNENT
        if (!echec) {
            reussi = true;
            break;
        }

        // AGRANDIR LA TEXTURE SELON LA REGLE
        if (W == H) {
            W *= 2;
        } else {
            H = W;
        }
    }

    cout << "ESSAIS " << essais << '\n';

    // AFFICHER L'ECHEC SI AUCUN ESSAI N'A REUSSI
    if (!reussi) {
        cout << "ECHEC\n";
        return 0;
    }

    // AFFICHER LA TAILLE FINALE DE LA TEXTURE
    cout << "TEXTURE " << W << ' ' << H << '\n';

    // AFFICHER LE PREMIER ET LE DERNIER GLYPHE DE CHAQUE GROUPE
    for (int i = 0; i < G; i++) {
        cout << groupes[i].police << ' '
             << groupes[i].xPremier << ' '
             << groupes[i].yPremier << ' '
             << groupes[i].xDernier << ' '
             << groupes[i].yDernier << '\n';
    }

    // CALCULER LE POURCENTAGE DE SURFACE INUTILISEE
    long long surface = W * H;
    long long perdu = (surface - occupe) * 100 / surface;

    cout << "OCCUPE " << occupe << '\n';
    cout << "PERDU " << perdu << '\n';

    return 0;
}