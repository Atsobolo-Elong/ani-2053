#include <iostream>
#include <string>

int main()
{
    int nombreImages;
    std::cin >> nombreImages;

    // Compteurs des images restaurées et des champs modifiés.
    int restent = 0;
    int changes = 0;

    // Parcours de toutes les images reçues.
    for (int i = 1; i <= nombreImages; i++)
    {
        // Lecture des 13 valeurs de l'image.
        int id;
        double x, y, echelle, rotation, opacite;
        int miroirX, miroirY;
        int largeur, hauteur;
        int selectionne;
        std::string chemin;
        long long octets;

        std::cin >> id
                 >> x >> y
                 >> echelle
                 >> rotation
                 >> opacite
                 >> miroirX >> miroirY
                 >> largeur >> hauteur
                 >> selectionne
                 >> chemin
                 >> octets;

        // Une image sans octets ne peut pas être restaurée.
        if (octets == 0)
        {
            std::cout << "ITEM " << i << " SAUTE\n";
            continue;
        }

        // L'image revient : elle prend la prochaine place disponible.
        restent++;

        std::cout << "ITEM " << i << " " << restent;

        // Vérification du champ id.
        if (id != 0)
        {
            std::cout << " id";
            changes++;
        }

        // Vérification du champ selected.
        if (selectionne != 0)
        {
            std::cout << " selected";
            changes++;
        }

        // Vérification du champ sourcePath.
        if (chemin != "-")
        {
            std::cout << " sourcePath";
            changes++;
        }

        // Si aucun champ n'a changé pour cette image.
        if (id == 0 && selectionne == 0 && chemin == "-")
        {
            std::cout << " AUCUN";
        }

        std::cout << '\n';
    }

    // Résumé final.
    std::cout << "RESTENT " << restent << '\n';
    std::cout << "CHANGES " << changes << '\n';

    return 0;
}