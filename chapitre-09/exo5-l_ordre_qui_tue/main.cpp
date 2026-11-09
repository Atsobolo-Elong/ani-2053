#include <iostream>
#include <map>
#include <string>
#include <vector>

// Etat d'un objet : present dans cet ensemble = deja libere.
static std::map<std::string, bool> gLiberes;

// Toutes les lignes DEPEND a b, dans l'ordre de lecture.
static std::vector<std::pair<std::string, std::string>> gDependances;

// Libere un objet : verifie ses dependances, affiche, dit s'il y a plantage.
// Renvoie false si le programme vient de mourir.
static bool Liberer(const std::string &nom, const std::string &mot)
{
    // Pour chaque DEPEND nom b, dans l'ordre de lecture :
    // si b est deja libere, c'est le plantage.
    for (const std::pair<std::string, std::string> &d : gDependances) {
        if (d.first == nom) {
            std::map<std::string, bool>::iterator it = gLiberes.find(d.second);
            if (it != gLiberes.end() && it->second) {
                std::cout << "PLANTAGE " << nom << " " << d.second << "\n";
                return false;
            }
        }
    }

    // Aucune dependance manquante : l'objet est libere.
    gLiberes[nom] = true;
    std::cout << mot << " " << nom << "\n";
    return true;
}

int main()
{
    // Pile de blocs : chacun garde ses objets dans l'ordre de declaration.
    std::vector<std::vector<std::string>> blocs(1);

    std::string op;
    while (std::cin >> op) {
        if (op == "DECL") {
            std::string x;
            std::cin >> x;
            blocs.back().push_back(x);
        }
        else if (op == "DEPEND") {
            std::string a, b;
            std::cin >> a >> b;
            gDependances.push_back(std::make_pair(a, b));
        }
        else if (op == "FERME") {
            std::string x;
            std::cin >> x;
            // Un objet deja libere ne se libere pas une seconde fois.
            std::map<std::string, bool>::iterator it = gLiberes.find(x);
            if (it == gLiberes.end() || !it->second) {
                if (!Liberer(x, "FERME"))
                    return 0;
            }
        }
        else if (op == "{") {
            blocs.push_back(std::vector<std::string>());
        }
        else if (op == "}") {
            // Destruction du bloc interieur, du dernier declare au premier.
            std::vector<std::string> &bloc = blocs.back();
            for (int i = (int)bloc.size() - 1; i >= 0; --i) {
                if (gLiberes.count(bloc[i]) && gLiberes[bloc[i]])
                    continue; // deja libere : saute, rien a afficher
                if (!Liberer(bloc[i], "DETRUIT"))
                    return 0;
            }
            blocs.pop_back();
        }
    }

    // La fin de l'entree ferme le bloc de la fonction.
    std::vector<std::string> &bloc = blocs.back();
    for (int i = (int)bloc.size() - 1; i >= 0; --i) {
        if (gLiberes.count(bloc[i]) && gLiberes[bloc[i]])
            continue;
        if (!Liberer(bloc[i], "DETRUIT"))
            return 0;
    }

    std::cout << "PROPRE\n";
    return 0;
}