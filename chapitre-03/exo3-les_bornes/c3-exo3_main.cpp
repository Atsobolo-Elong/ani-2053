#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include <stdio.h>

using namespace nkentseu;
using namespace nkentseu::renderer;

/*
Cette fonction m'épargne d'écrire le même code deux fois.
Elle prend en paramètre la largeur et la hauteur minimales
de chaque fenêtre.
*/
void firstwindow(const int MinWidth, const int MinHeight)
{
    // CONFIGURATION DE LA FENETRE :
    NkWindowConfig cfg;
    cfg.title = "EXERCICE-3 2 FENETRES";
    cfg.width = 800;
    cfg.height = 600;

    // DIMENSIONS MINIMALES :
    cfg.minWidth = MinWidth;
    cfg.minHeight = MinHeight;

    // CREATION DE LA FENETRE ET GESTION D'ERREUR
    NkWindow window;

    if (!window.Create(cfg)) {
        logger.Error("ECHEC DE CREATION DE LA FENETRE");
        return;
    }

    // CHOIX DE L'API GRAPHIQUE :
    NkContextDesc desc;
    desc.api = NkGraphicsApi::NK_GFX_API_OPENGL;

    // CREATION DU RENDER :
    NkRenderWindow target(window, desc);

    if (!target.IsValid()) {
        logger.Error("ECHEC DE CREATION DU RENDER");
        window.Close();
        return;
    }

    // CREATION DE LA BOUCLE PRINCIPALE :
    auto& events = NkEvents();
    bool running = true;

    // VARIABLES QUI CONTIENDRONT LES DIMENSIONS
    // DE LA FENETRE APRES LE DERNIER REDIMENSIONNEMENT
    int largeur = cfg.width;
    int hauteur = cfg.height;

    while (running && window.IsOpen()) {

        while (NkEvent* ev = events.PollEvent()) {

            // FERMETURE DE LA FENETRE
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
                running = false;
            }

            // REDIMENSIONNEMENT DE LA FENETRE
            if (auto* ev2 = ev->As<NkWindowResizeEvent>()) {

                largeur = ev2->GetWidth();
                hauteur = ev2->GetHeight();

                printf("\n Nouvelle taille : %d %s %d %s", largeur, " x ", hauteur, "\n");
            }
        }
    }

    // AFFICHAGE DE LA DERNIERE TAILLE RECUE
    printf("\n Taille minimale observee : %d %s %d %s", largeur, " x", hauteur, "\n");
}

int nkmain(const nkentseu::NkEntryState& State)
{
    // PREMIER TEST
    firstwindow(400, 350);

    // DEUXIEME TEST
    firstwindow(500, 450);

    return 0;
}