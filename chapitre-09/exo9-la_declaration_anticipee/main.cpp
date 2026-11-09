#include <iostream>
#include <map>
#include <string>
#include <vector>

static bool ExigeDefinition(const std::string &emploi)
{
    return emploi == "VALEUR" || emploi == "BASE"
        || emploi == "CORPS" || emploi == "TAILLE";
}

int main()
{
    int u = 0;
    std::cin >> u;

    std::vector<std::string> ordre;       // premiere apparition de chaque type
    std::map<std::string, bool> inclure;  // vrai des qu'un emploi exige la definition

    for (int i = 0; i < u; ++i) {
        std::string type, emploi;
        std::cin >> type >> emploi;
        if (!inclure.count(type)) {
            inclure[type] = false;
            ordre.push_back(type);
        }
        if (ExigeDefinition(emploi))
            inclure[type] = true;
    }

    int a = 0;
    std::cin >> a;

    int inclusRetires = 0;
    for (int i = 0; i < a; ++i) {
        std::string type;
        std::cin >> type;
        if (inclure.count(type) && !inclure[type])
            ++inclusRetires; // inclus aujourd'hui, anticipable : l'inclusion peut partir
    }

    int inclus = 0, anticipe = 0;
    for (size_t i = 0; i < ordre.size(); ++i) {
        if (inclure[ordre[i]]) {
            ++inclus;
            std::cout << ordre[i] << " INCLURE\n";
        }
        else {
            ++anticipe;
            std::cout << ordre[i] << " ANTICIPER\n";
        }
    }

    std::cout << "INCLURE " << inclus << "\n";
    std::cout << "ANTICIPER " << anticipe << "\n";
    std::cout << "INCLUSIONS_RETIREES " << inclusRetires << "\n";
    return 0;
}