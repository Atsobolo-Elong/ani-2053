#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    long long D, C;
    cin >> D >> C;

    int N;
    cin >> N;

    vector<long long> temps(N);

    // LIRE LES INSTANTS DE LECTURE
    for (int i = 0; i < N; i++) {
        cin >> temps[i];
    }

    // INITIALISER LES BILANS
    int voixMax = 0;
    long long retardMax = 0;
    int coupes = 0;

    // MEMORISER LA FIN DU CHARGEMENT PRECEDENT
    long long finChargement = 0;

    // TRAITER CHAQUE LECTURE
    for (int i = 0; i < N; i++) {
        long long t = temps[i];

        // COMPTER LES LECTURES ENCORE ACTIVES
        int voix = 0;

        for (int j = 0; j <= i; j++) {
            if (temps[j] + D > t) {
                voix++;
            }
        }

        // METTRE A JOUR LE MAXIMUM DE VOIX
        if (voix > voixMax) {
            voixMax = voix;
        }

        // CALCULER LE DEBUT ET LA FIN DU CHARGEMENT
        long long debutChargement = max(t, finChargement);
        finChargement = debutChargement + C;

        // CALCULER LE RETARD DU CHARGEMENT
        long long retard = finChargement - t;

        if (retard > retardMax) {
            retardMax = retard;
        }

        // DETERMINER SI LA LECTURE EST COUPEE
        string etat = "ENTIER";

        if (i + 1 < N && temps[i + 1] < t + D) {
            etat = "COUPE";
            coupes++;
        }

        // AFFICHER LE RESULTAT DE LA LECTURE
        cout << t << ' '
             << voix << ' '
             << retard << ' '
             << etat << '\n';
    }

    // AFFICHER LES BILANS
    cout << "VOIX_MAX " << voixMax << '\n';
    cout << "RETARD_MAX " << retardMax << '\n';
    cout << "COUPES " << coupes << '\n';

    return 0;
}