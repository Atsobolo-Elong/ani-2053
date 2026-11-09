#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Methode
{
    string nom;
    bool estConst;
    bool modifie;
    vector<string> appels;
    vector<int> indicesAppels;
};

int main()
{
    int n;
    cin >> n;

    vector<Methode> methodes(n);

    // Lecture des méthodes
    for (int i = 0; i < n; ++i)
    {
        int k;
        string declaration;

        cin >> methodes[i].nom
            >> declaration
            >> methodes[i].modifie
            >> k;

        methodes[i].estConst = (declaration == "const");

        // Lecture des noms des méthodes appelées
        for (int j = 0; j < k; ++j)
        {
            string appel;
            cin >> appel;

            methodes[i].appels.push_back(appel);
        }
    }

    // Associer chaque nom de méthode à son indice
    unordered_map<string, int> indices;

    for (int i = 0; i < n; ++i)
    {
        indices[methodes[i].nom] = i;
    }

    // Transformer les noms des méthodes appelées en indices
    for (int i = 0; i < n; ++i)
    {
        for (const string& appel : methodes[i].appels)
        {
            methodes[i].indicesAppels.push_back(indices[appel]);
        }
    }

    // 1. Déterminer les méthodes qui pourraient devenir const
    vector<bool> pourrait(n, false);

    // Première sélection : les méthodes qui ne modifient rien
    for (int i = 0; i < n; ++i)
    {
        if (!methodes[i].estConst && !methodes[i].modifie)
        {
            pourrait[i] = true;
        }
    }

    // Éliminer les méthodes qui appellent une méthode incompatible
    bool changement = true;

    while (changement)
    {
        changement = false;

        for (int i = 0; i < n; ++i)
        {
            if (!pourrait[i])
                continue;

            for (int appel : methodes[i].indicesAppels)
            {
                if (!methodes[appel].estConst && !pourrait[appel])
                {
                    pourrait[i] = false;
                    changement = true;
                    break;
                }
            }
        }
    }

    // 2. Afficher les méthodes qui pourraient devenir const
    cout << "POURRAIT";

    bool aucunePourrait = true;

    for (int i = 0; i < n; ++i)
    {
        if (pourrait[i])
        {
            cout << " " << methodes[i].nom;
            aucunePourrait = false;
        }
    }

    if (aucunePourrait)
        cout << " AUCUN";

    cout << '\n';

    // 3. Identifier les racines
    vector<bool> racines(n, false);

    cout << "RACINES";

    bool aucuneRacine = true;

    for (int i = 0; i < n; ++i)
    {
        if (!pourrait[i])
            continue;

        bool racine = true;

        for (int appel : methodes[i].indicesAppels)
        {
            if (!methodes[appel].estConst)
            {
                racine = false;
                break;
            }
        }

        if (racine)
        {
            racines[i] = true;
            cout << " " << methodes[i].nom;
            aucuneRacine = false;
        }
    }

    if (aucuneRacine)
        cout << " AUCUN";

    cout << '\n';

    // 4. Calculer le nombre de passes
    vector<bool> corrige = vector<bool>(n, false);

    int nombreCorrigees = 0;
    int passes = 0;

    // Compter les méthodes déjà déclarées const
    for (int i = 0; i < n; ++i)
    {
        if (methodes[i].estConst)
            corrige[i] = true;
    }

    // Traiter les méthodes de POURRAIT par passes simultanées
    while (nombreCorrigees < 1 ||
           true)
    {
        // Vérifier si toutes les méthodes de POURRAIT sont corrigées
        bool termine = true;

        for (int i = 0; i < n; ++i)
        {
            if (pourrait[i] && !corrige[i])
            {
                termine = false;
                break;
            }
        }

        if (termine)
            break;

        // Identifier toutes les méthodes corrigibles pendant cette passe
        vector<int> pretes;

        for (int i = 0; i < n; ++i)
        {
            if (!pourrait[i] || corrige[i])
                continue;

            bool peutEtreCorrigee = true;

            for (int appel : methodes[i].indicesAppels)
            {
                if (!corrige[appel])
                {
                    peutEtreCorrigee = false;
                    break;
                }
            }

            if (peutEtreCorrigee)
                pretes.push_back(i);
        }

        // Corriger toutes les méthodes en même temps
        for (int indice : pretes)
        {
            corrige[indice] = true;
            ++nombreCorrigees;
        }

        ++passes;
    }

    cout << "PASSES " << passes << '\n';

    return 0;
}