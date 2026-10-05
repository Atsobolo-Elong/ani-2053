#include <iostream>



int main()
{
    long long colonnes;
    long long lignes;
    long long largeur;
    long long hauteur;
    long long frames;
    long long duree;
    long long plafond;

    std::cin >> colonnes>> lignes>> largeur>> hauteur>> frames>> duree>> plafond;

    int nombreDt;
    std::cin >> nombreDt;

    long long caseCourante = 0;
    long long tempsAccumule = 0;

    long long avances = 0;
    long long plafonnes = 0;

    for (int i = 0; i < nombreDt; ++i)
    {
        long long dt;
        std::cin >> dt;

        
        //    UN GRAND DT PEUT VENIR D'UN RETOUR DE VEILLE.
          //  ON LE LIMITE AVANT DE L'AJOUTER A L'HORLOGE.
        
        if (dt > plafond)
        {
            dt = plafond;
            ++plafonnes;
        }

        tempsAccumule += dt;

        
          //  PLUSIEURS CASES PEUVENT ETRE TRAVERSEES
        //    PENDANT UNE SEULE IMAGE.
        
        while (tempsAccumule >= duree)
        {
            tempsAccumule -= duree;
            caseCourante = (caseCourante + 1) % frames;
            ++avances;
        }

        const long long colonne = caseCourante % colonnes;
        const long long ligne = caseCourante / colonnes;

        const long long x = colonne * largeur;
        const long long y = ligne * hauteur;

        std::cout << caseCourante << ' ' << x << ' '<< y << ' '<< largeur << ' '<< hauteur << '\n';
    }

    std::cout << "AVANCES " << avances << '\n';
    std::cout << "PLAFONNES " << plafonnes << '\n';

    return 0;
}