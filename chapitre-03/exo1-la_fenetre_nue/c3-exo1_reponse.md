# EXERCICE 1 — La fenêtre nue

## Programme attendu

```
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state)
{
    // Configuration de la fenêtre : titre, largeur et hauteur.
    NkWindowConfig cfg;
    cfg.title = "MA PREMIERE FENETRE";
    cfg.width = 800;
    cfg.height = 800;

    // Création de la fenêtre.
    NkWindow window(cfg);

    if (!window.IsOpen())
    {
        return -1;
    }

    // Boucle principale de la fenêtre.
    while (window.IsOpen())
    {
        // Attente des événements.
    }

    return 0;
}
```
1. Nombre de lignes
```
Le programme comporte 23 lignes dans le rendu demandé.
```
2. Lecture des lignes du chapitre
```
Inclusion de 
NKWindow.h
#include "NKWindow/NKWindow.h"
Cette inclusion donne accès aux éléments nécessaires à la création et au contrôle de la fenêtre, notamment NkWindow et NkWindowConfig.
Inclusion de 
NKMain.h
#include "NKWindow/NKMain.h"
NKMain.h fournit le point d’entrée natif adapté à la plateforme. L’application définit ensuite la fonction nkmain().
Point d’entrée

using namespace nkentseu ; : espace de nom
int nkmain(const NkEntryState &state)
Cette fonction constitue le point d’entrée de l’application dans le modèle utilisé par Nkentseu.
Configuration
NkWindowConfig cfg;
cfg.title = "MA PREMIERE FENETRE";
cfg.width = 800;
cfg.height = 800;
NkWindowConfig définit la configuration de la fenêtre.
Les trois champs utilisés définissent respectivement :
le titre ;
la largeur ;
la hauteur.
Création de la fenêtre
NkWindow window(cfg);
Cette instruction crée la fenêtre à partir de la configuration cfg.
Vérification de l’ouverture
if (!window.IsOpen())
{
    return -1;
}
Après la création, IsOpen() permet de vérifier si la fenêtre est ouverte.
Les parenthèses sont nécessaires car IsOpen() est une fonction.
Boucle principale
while (window.IsOpen())
{
    // Attente des événements.
}
Tant que la fenêtre est ouverte, l’application reste dans sa boucle principale.
```

3. Corrections apportées après relecture
```
Plusieurs corrections ont été apportées au premier rendu :
NKWindowconfig → NkWindowConfig
window.IsOpen → window.IsOpen()
NKWindow\NKWindow.h → NKWindow/NKWindow.h
NKWindow\NKMain.h → NKWindow/NKMain.h
cfg.weight → cfg.width
```

# conclusion
Ces corrections permettent d’aligner les noms, les appels de fonctions et les chemins d’inclusion avec la syntaxe attendue.