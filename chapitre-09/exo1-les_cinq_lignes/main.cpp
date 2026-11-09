#include <iostream>
#include <string>
#include <algorithm>
#include <array>

using namespace std;

int main()
{
    // Lecture du nom de la classe
    string classe;

    if (!getline(cin, classe))
        return 0;

    // Les cinq membres, dans l'ordre demandé
    const array<string, 5> noms = {
        "DESTRUCTEUR",
        "COPIE",
        "AFFECTATION_COPIE",
        "DEPLACEMENT",
        "AFFECTATION_DEPLACEMENT"
    };

    // ABSENT par défaut pour chaque membre
    array<string, 5> etats = {
        "ABSENT",
        "ABSENT",
        "ABSENT",
        "ABSENT",
        "ABSENT"
    };

    string ligne;

    // Lecture des déclarations jusqu'à la fin de l'entrée
    while (getline(cin, ligne))
    {
        // 1. Supprimer tout ce qui suit le premier //
        size_t commentaire = ligne.find("//");

        if (commentaire != string::npos)
            ligne.erase(commentaire);

        // 2. Supprimer toutes les espaces
        ligne.erase(
            remove(ligne.begin(), ligne.end(), ' '),
            ligne.end()
        );

        // Une ligne vide est ignorée
        if (ligne.empty())
            continue;

        // 3. Reconnaître les cinq membres spéciaux

        // Destructeur
        if (ligne.find("~" + classe + "(") != string::npos)
        {
            if (ligne.size() >= 8 &&
                ligne.compare(ligne.size() - 8, 8, "=default;") == 0)
                etats[0] = "DEFAUT";

            else if (ligne.size() >= 7 &&
                     ligne.compare(ligne.size() - 7, 7, "=delete;") == 0)
                etats[0] = "SUPPRIME";

            else
                etats[0] = "ECRIT";
        }

        // Copie
        else if (ligne.find(classe + "(const" + classe + "&") == 0)
        {
            string prefixe = classe + "(const" + classe + "&";

            if (ligne.size() > prefixe.size() &&
                ligne[prefixe.size()] != '&')
            {
                if (ligne.size() >= 8 &&
                    ligne.compare(ligne.size() - 8, 8, "=default;") == 0)
                    etats[1] = "DEFAUT";

                else if (ligne.size() >= 7 &&
                         ligne.compare(ligne.size() - 7, 7, "=delete;") == 0)
                    etats[1] = "SUPPRIME";

                else
                    etats[1] = "ECRIT";
            }
        }

        // Affectation par copie
        else if (ligne.find(classe + "&operator=(const" + classe + "&") == 0)
        {
            string prefixe = classe + "&operator=(const" + classe + "&";

            if (ligne.size() > prefixe.size() &&
                ligne[prefixe.size()] != '&')
            {
                if (ligne.size() >= 8 &&
                    ligne.compare(ligne.size() - 8, 8, "=default;") == 0)
                    etats[2] = "DEFAUT";

                else if (ligne.size() >= 7 &&
                         ligne.compare(ligne.size() - 7, 7, "=delete;") == 0)
                    etats[2] = "SUPPRIME";

                else
                    etats[2] = "ECRIT";
            }
        }

        // Déplacement
        else if (ligne.find(classe + "(" + classe + "&&") == 0)
        {
            if (ligne.size() >= 8 &&
                ligne.compare(ligne.size() - 8, 8, "=default;") == 0)
                etats[3] = "DEFAUT";

            else if (ligne.size() >= 7 &&
                     ligne.compare(ligne.size() - 7, 7, "=delete;") == 0)
                etats[3] = "SUPPRIME";

            else
                etats[3] = "ECRIT";
        }

        // Affectation par déplacement
        else if (ligne.find(classe + "&operator=(" + classe + "&&") == 0)
        {
            if (ligne.size() >= 8 &&
                ligne.compare(ligne.size() - 8, 8, "=default;") == 0)
                etats[4] = "DEFAUT";

            else if (ligne.size() >= 7 &&
                     ligne.compare(ligne.size() - 7, 7, "=delete;") == 0)
                etats[4] = "SUPPRIME";

            else
                etats[4] = "ECRIT";
        }
    }

    // 4. Afficher les cinq états
    for (size_t i = 0; i < etats.size(); ++i)
    {
        cout << noms[i] << " " << etats[i] << '\n';
    }

    // 5. Compter les membres déclarés
    int nombreDeclares = 0;

    for (const string& etat : etats)
    {
        if (etat != "ABSENT")
            ++nombreDeclares;
    }

    // 6. Déterminer la règle suivie
    string regle;

    if (nombreDeclares == 0)
    {
        regle = "ZERO";
    }
    else if (nombreDeclares == 5)
    {
        regle = "CINQ";
    }
    else if (etats[0] != "ABSENT" &&
             etats[1] != "ABSENT" &&
             etats[2] != "ABSENT" &&
             etats[3] == "ABSENT" &&
             etats[4] == "ABSENT")
    {
        regle = "TROIS";
    }
    else
    {
        regle = "INCOMPLETE";
    }

    cout << "REGLE " << regle << '\n';

    // 7. Afficher les membres manquants si la règle est INCOMPLETE
    if (regle == "INCOMPLETE")
    {
        // Si un déplacement est déclaré, vérifier les cinq membres.
        // Sinon, vérifier uniquement les trois premiers.
        int limite = 3;

        if (etats[3] != "ABSENT" || etats[4] != "ABSENT")
            limite = 5;

        for (int i = 0; i < limite; ++i)
        {
            if (etats[i] == "ABSENT")
                cout << "MANQUE " << noms[i] << '\n';
        }
    }

    // 8. Déterminer si la classe possède une ressource
    cout << "POSSEDE "
         << (etats[0] == "ECRIT" ? "OUI" : "NON")
         << '\n';

    // 9. Déterminer si la classe représente un objet unique
    bool unique =
        etats[1] == "SUPPRIME" &&
        (etats[3] == "ECRIT" || etats[3] == "DEFAUT");

    cout << "UNIQUE " << (unique ? "OUI" : "NON") << '\n';

    return 0;
}