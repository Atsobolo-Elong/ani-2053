#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int S, V, F;

    // Lecture des trois nombres de libérations
    cin >> S >> V >> F;

    int N;
    cin >> N;

    // Tableau contenant les numéros des textures encore présentes
    vector<int> tableau;

    // État de chaque texture : true si elle a été libérée
    // L'indice 0 est inutilisé : les textures commencent à 1.
    vector<bool> liberees(1, false);

    // Nombre total de textures créées
    int creees = 0;

    // Fonction qui libère une texture un certain nombre de fois.
    // Elle retourne false si une double libération provoque un plantage.
    auto liberer = [&](int texture, int repetitions, const string& operation)
    {
        for (int i = 0; i < repetitions; ++i)
        {
            // Une texture déjà libérée ne peut pas l'être une deuxième fois
            if (liberees[texture])
            {
                cout << "PLANTAGE " << operation
                     << " TEXTURE " << texture << '\n';

                return false;
            }

            // Première libération
            liberees[texture] = true;
        }

        return true;
    };

    // Lecture et exécution des opérations
    for (int i = 1; i <= N; ++i)
    {
        string operation;
        cin >> operation;

        if (operation == "AJOUTE")
        {
            // Création d'une nouvelle texture
            ++creees;

            // Elle reçoit un numéro unique
            liberees.push_back(false);

            // Elle entre à la fin du tableau
            tableau.push_back(creees);
        }
        else if (operation == "SUPPRIME")
        {
            int index;
            cin >> index;

            // Récupération du numéro réel de la texture
            int texture = tableau[index];

            // Libération S fois
            if (!liberer(texture, S, to_string(i)))
                return 0;

            // Retrait de la texture du tableau
            tableau.erase(tableau.begin() + index);
        }
        else if (operation == "VIDE")
        {
            // Parcours du tableau du premier au dernier élément
            for (int texture : tableau)
            {
                // Libération V fois
                if (!liberer(texture, V, to_string(i)))
                    return 0;
            }

            // Toutes les textures quittent le tableau
            tableau.clear();
        }
    }

    // Fin du programme : libération des textures restantes
    for (int texture : tableau)
    {
        if (!liberer(texture, F, "FIN"))
            return 0;
    }

    // Aucun plantage : calcul des fuites
    vector<int> perdues;

    for (int texture = 1; texture <= creees; ++texture)
    {
        if (!liberees[texture])
        {
            perdues.push_back(texture);
        }
    }

    // Affichage du nombre de textures créées
    cout << "CREEES " << creees << '\n';

    // Affichage du nombre de fuites
    cout << "FUITES " << perdues.size() << '\n';

    // Affichage des numéros des textures perdues
    cout << "PERDUES";

    if (perdues.empty())
    {
        cout << " AUCUN";
    }
    else
    {
        for (int texture : perdues)
        {
            cout << " " << texture;
        }
    }

    cout << '\n';

    return 0;
}