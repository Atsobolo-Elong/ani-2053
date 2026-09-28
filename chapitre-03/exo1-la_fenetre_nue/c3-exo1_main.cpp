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