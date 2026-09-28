#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include <stdio.h>

using namespace nkentseu;
using namespace nkentseu::renderer;

void firstwindow(const int MinWidth, const int MinHeight)
{
    NkWindowConfig cfg;
    cfg.title = "EXERCICE-3 2 FENETRES";
    cfg.width = 800;
    cfg.height = 600;

    cfg.minWidth = MinWidth;
    cfg.minHeight = MinHeight;

    NkWindow window;

    if (!window.Create(cfg)) {
        logger.Error("ECHEC DE CREATION DE LA FENETRE");
        return;
    }

    NkContextDesc desc;
    desc.api = NkGraphicsApi::NK_GFX_API_OPENGL;

    NkRenderWindow target(window, desc);

    if (!target.IsValid()) {
        logger.Error("ECHEC DE CREATION DU RENDER");
        window.Close();
        return;
    }

    auto& events = NkEvents();
    bool running = true;

    int largeur = cfg.width;
    int hauteur = cfg.height;

    while (running && window.IsOpen()) {
        while (NkEvent* ev = events.PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
                running = false;
            }

            if (auto* ev2 = ev->As<NkWindowResizeEvent>()) {
                largeur = ev2->GetWidth();
                hauteur = ev2->GetHeight();

                printf("\n Nouvelle taille : %d x %d\n", largeur, hauteur);
            }
        }
    }

    printf("\n Taille minimale observee : %d x %d\n", largeur, hauteur);
}

int nkmain(const nkentseu::NkEntryState& State)
{
    // PREMIER TEST : borne 400 x 350
    firstwindow(400, 350);

    // DEUXIEME TEST : borne 500 x 450
    firstwindow(500, 450);

    // TROISIEME TEST : aucune borne utilisateur
    firstwindow(0, 0);

    return 0;
}
