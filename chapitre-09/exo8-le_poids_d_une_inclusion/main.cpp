#include <iostream>
#include <map>
#include <string>
#include <vector>
 
struct Ligne {
    std::string op;
    std::string a;
    std::string b;
};
 
int main()
{
    int n = 0;
    std::cin >> n;
 
    std::vector<Ligne> lignes(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> lignes[i].op;
        if (lignes[i].op == "NEW" || lignes[i].op == "RESET" || lignes[i].op == "USE")
            std::cin >> lignes[i].a;
        else if (lignes[i].op == "MOVE" || lignes[i].op == "COPY")
            std::cin >> lignes[i].a >> lignes[i].b;
    }
 
    // Une seule ligne COPY : le programme ne compile pas.
    bool copie = false;
    for (int i = 0; i < n; ++i) {
        if (lignes[i].op == "COPY")
            copie = true;
    }
    if (copie) {
        for (int i = 0; i < n; ++i) {
            if (lignes[i].op == "COPY")
                std::cout << "REFUSE " << (i + 1) << "\n";
        }
        return 0;
    }
 
    std::map<std::string, int> tient;      // objet tenu, 0 = nul
    std::vector<std::string> apparition;   // ordre de premiere apparition
    std::map<std::string, bool> vueVar;
    int prochain = 1;
    int crees = 0, detruits = 0, nuls = 0;
 
    // Note la premiere apparition d'une variable.
    auto vue = [&](const std::string &v) {
        if (!vueVar[v]) {
            vueVar[v] = true;
            apparition.push_back(v);
        }
    };
 
    // Detruit l'objet numero o.
    auto detruire = [&](int o) {
        std::cout << "DETRUIT " << o << "\n";
        ++detruits;
    };
 
    for (int i = 0; i < n; ++i) {
        const std::string &op = lignes[i].op;
        const std::string &a = lignes[i].a;
        const int k = i + 1;
 
        if (op == "NEW") {
            vue(a);
            int objet = prochain++;
            ++crees;
            int ancien = tient[a];
            tient[a] = objet;
            if (ancien != 0)
                detruire(ancien);
        }
        else if (op == "MOVE") {
            vue(lignes[i].a);   // a apparait avant b
            vue(lignes[i].b);
            int objet = tient[lignes[i].a];
            tient[lignes[i].a] = 0;
            int ancien = tient[lignes[i].b];
            if (ancien != 0)
                detruire(ancien);
            tient[lignes[i].b] = objet;
        }
        else if (op == "RESET") {
            vue(a);
            int ancien = tient[a];
            tient[a] = 0;
            if (ancien != 0)
                detruire(ancien);
        }
        else if (op == "USE") {
            vue(a);
            if (tient[a] == 0) {
                std::cout << "NUL " << k << " " << a << "\n";
                ++nuls;
            }
        }
    }
 
    // Fin : les variables meurent en ordre inverse de leur premiere apparition.
    for (int i = (int)apparition.size() - 1; i >= 0; --i) {
        int objet = tient[apparition[i]];
        if (objet != 0)
            detruire(objet);
    }
 
    std::cout << "CREES " << crees << "\n";
    std::cout << "DETRUITS " << detruits << "\n";
    std::cout << "NULS " << nuls << "\n";
    return 0;
}