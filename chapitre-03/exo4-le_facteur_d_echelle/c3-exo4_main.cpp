#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include <stdio.h>

using namespace nkentseu;
using namespace nkentseu::renderer;

void afficherTailles()
{
    //CONFIGURATION DE LA FENETRE
    NkWindowConfig cfg;

    cfg.title = "EXERCICE 4 FACTEUR D'ECHELLE";
    cfg.width = 800;
    cfg.height = 600;

    // CREATION DE LA FENETRE + GESTION D'ERREUR
    NkWindow window;

    if (!window.Create(cfg)) {
        logger.Error("ECHEC DE CREATION DE LA FENETRE");
        return;
    }

    // CONFIGURATION DE L'API GRAPHIQUE
    NkContextDesc desc;
    desc.api = NkGraphicsApi::NK_GFX_API_OPENGL;

    // CREATION DU RENDER (CIBLE DE RENDU) + GESTION D'ERREUR
    NkRenderWindow target(window, desc);

    if (!target.IsValid()) {
        logger.Error("ECHEC DE CREATION DU RENDER");
        window.Close();
        return;
    }

    //CREATION DE LA BOUCLE PRINCIPALE.
    auto& events = NkEvents();
    bool running = true;

    // TAILLE COURANTE DE LA FENETRE.
    int windowWidth = cfg.width;
    int windowHeight = cfg.height;

    while (window.IsOpen() && running) {

        while (NkEvent* ev = events.PollEvent()) {

            // FERMETURE DE LA FENETRE.
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            }

            // CHANGEMENT DE TAILLE DE LA FENETRE.
            if (auto* resize = ev->As<NkWindowResizeEvent>()) {

                windowWidth = resize->GetWidth();
                windowHeight = resize->GetHeight();

                // TAILLE DE LA CIBLE DU RENDU EN PIXEL
                const auto renderSize = target.GetSize();

                // Calcul du facteur d'échelle.
                float scaleX = static_cast<float>(renderSize.x) / static_cast<float>(windowWidth);

                float scaleY = static_cast<float>(renderSize.y) / static_cast<float>(windowHeight);

                printf("\n \n Fenetre : %d %s %d", windowWidth, " x ", windowHeight);
                printf("\n Cible de rendu : %f %s %f ", static_cast<float>(renderSize.x), " x ", static_cast<float>(renderSize.y));
                printf(" \n Facteur : %f %s %f %s ", scaleX, " x ", scaleY, "\n");

                // MODIFICATION DE LA CIBLE .
                target.OnResize(windowWidth, windowHeight);
            }
        }
    }
}

int nkmain(const nkentseu::NkEntryState& State)
{
    afficherTailles();

    return 0;
}