#include "NKWindow\NKWindow.h"
#include "NKWindow\NKMain.h" /* fournis le point d'entree natif */

int nkmain(const NkEntryState &state) {

    // configuration de la fenetre : titre, largeur et hauteur.
    NKWindowconfig cfg;
    cfg.title = "MA PREMIERE FENETRE";
    cfg.width = 800;
    cfg.height = 800;

    // creation de la fenetre.
    NKWindow window(cfg);
    if(!window.IsOpen) { // Dans le guide la forme ici est window.Create(cfg) et non Window.IsOpen()🥲
        logger.Error(" DE CREATION DE LA FENETRE"); /* en cas d'echec on signale l'erreur dans le log */
        return -1;
    }

    // boucle principal de la fenetre
    while(window.IsOpen()) { /* attente des evenements*/ }
    return 0;
}