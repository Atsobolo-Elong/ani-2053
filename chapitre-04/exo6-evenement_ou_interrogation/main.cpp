#include <iostream>
#include <string>

/*
    LES EVENEMENTS MODIFIENT L'ETAT.
    L'INTERROGATION OBSERVE CET ETAT UNE SEULE FOIS PAR IMAGE.
*/

enum Touche
{
    SPACE = 0,
    LEFT,
    RIGHT,
    NOMBRE_TOUCHES
};

int trouverTouche(const std::string& nom)
{
    if (nom == "SPACE")
        return SPACE;

    if (nom == "LEFT")
        return LEFT;

    if (nom == "RIGHT")
        return RIGHT;

    return -1;
}

int main()
{
    int vitesse;
    int nombreImages;

    std::cin >> vitesse >> nombreImages;

    bool enfoncee[NOMBRE_TOUCHES] = {false, false, false};

    int positionEvenements = 0;
    int positionInterrogation = 0;

    int sautsEvenements = 0;
    int sautsInterrogation = 0;
    int manques = 0;

    for (int image = 1; image <= nombreImages; ++image)
    {
        int nombreEvenements;
        std::cin >> nombreEvenements;

        int appuisSpace = 0;

        // LES EVENEMENTS SONT TRAITES DANS LEUR ORDRE D'ARRIVEE.
        for (int i = 0; i < nombreEvenements; ++i)
        {
            std::string evenement;
            std::cin >> evenement;

            if (evenement.size() < 2)
                continue;

            const char action = evenement[0];
            const int index = trouverTouche(evenement.substr(1));

            // UNE TOUCHE INCONNUE EST IGNOREE.
            if (index == -1)
                continue;

            if (action == '+')
            {
                if (index == SPACE)
                {
                    ++sautsEvenements;
                    ++appuisSpace;
                }

                if (index == RIGHT)
                    positionEvenements += vitesse;

                if (index == LEFT)
                    positionEvenements -= vitesse;

                enfoncee[index] = true;
            }
            else if (action == '-')
            {
                enfoncee[index] = false;
            }
        }

        // UN APPUI RELACHE DANS LA MEME IMAGE EST INVISIBLE A L'INTERROGATION.
        if (appuisSpace > 0 && !enfoncee[SPACE])
            manques += appuisSpace;

        // L'INTERROGATION SE FAIT UNE SEULE FOIS APRES TOUS LES EVENEMENTS.
        if (enfoncee[SPACE])
            ++sautsInterrogation;

        if (enfoncee[RIGHT])
            positionInterrogation += vitesse;

        if (enfoncee[LEFT])
            positionInterrogation -= vitesse;

        std::cout << image << ' '
                  << positionEvenements << ' '
                  << positionInterrogation << '\n';
    }

    std::cout << "SAUTS EVENEMENTS " << sautsEvenements << '\n';
    std::cout << "SAUTS INTERROGATION " << sautsInterrogation << '\n';
    std::cout << "MANQUES " << manques << '\n';

    return 0;
}