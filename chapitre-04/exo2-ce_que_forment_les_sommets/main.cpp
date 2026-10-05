#include <iostream>
#include <string>

int main()
{
    // Lecture du nombre de lignes à traiter.
    int n;
    std::cin >> n;

    // Compteurs pour le bilan final.
    int points = 0;
    int segments = 0;
    int triangles = 0;
    int refuses = 0;

    // On traite chaque type de primitive.
    for (int i = 0; i < n; ++i)
    {
        // type : nom de la primitive.
        // s    : nombre de sommets fournis.
        std::string type;
        int s;

        std::cin >> type >> s;

        // POINTS :
        // Chaque sommet forme directement un point.
        // Il n'y a donc aucun sommet restant.
        if (type == "POINTS")
        {
            std::cout << type << " " << s
                      << " " << s << " POINTS 0\n";

            points += s;
        }

        // LINES :
        // Un segment nécessite 2 sommets.
        // La division entière donne le nombre de segments.
        // Le modulo donne le nombre de sommets restants.
        else if (type == "LINES")
        {
            int count = s / 2;
            int rest = s % 2;

            std::cout << type << " " << s
                      << " " << count << " SEGMENTS "
                      << rest << "\n";

            segments += count;
        }

        // LINE_STRIP :
        // Avec au moins 2 sommets, une ligne brisée
        // forme s - 1 segments.
        // Avec 0 ou 1 sommet, aucun segment n'est formé.
        else if (type == "LINE_STRIP")
        {
            int count = s >= 2 ? s - 1 : 0;
            int rest = s >= 2 ? 0 : s;

            std::cout << type << " " << s
                      << " " << count << " SEGMENTS "
                      << rest << "\n";

            segments += count;
        }

        // TRIANGLES :
        // Un triangle nécessite 3 sommets.
        // La division donne le nombre de triangles.
        // Le modulo donne les sommets restants.
        else if (type == "TRIANGLES")
        {
            int count = s / 3;
            int rest = s % 3;

            std::cout << type << " " << s
                      << " " << count << " TRIANGLES "
                      << rest << "\n";

            triangles += count;
        }

        // TRIANGLE_STRIP et TRIANGLE_FAN :
        // Les deux primitives suivent la même règle :
        // à partir de 3 sommets, s sommets forment s - 2 triangles.
        //
        // Avec moins de 3 sommets, aucun triangle n'est formé
        // et tous les sommets restent inutilisés.
        else if (type == "TRIANGLE_STRIP" ||
                 type == "TRIANGLE_FAN")
        {
            int count = s >= 3 ? s - 2 : 0;
            int rest = s >= 3 ? 0 : s;

            std::cout << type << " " << s
                      << " " << count << " TRIANGLES "
                      << rest << "\n";

            triangles += count;
        }

        // Tout autre type est refusé.
        // Cela inclut notamment QUADS et les écritures incorrectes
        // comme "quads" ou "triangles".
        else
        {
            std::cout << type << " " << s << " REFUSE\n";

            ++refuses;
        }
    }

    // Affichage du bilan final.
    // Chaque type de primitive possède son propre total.
    std::cout << "POINTS " << points << "\n";
    std::cout << "SEGMENTS " << segments << "\n";
    std::cout << "TRIANGLES " << triangles << "\n";
    std::cout << "REFUSES " << refuses << "\n";

    return 0;
}