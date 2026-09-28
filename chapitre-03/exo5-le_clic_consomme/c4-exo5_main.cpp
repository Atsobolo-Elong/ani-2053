
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEventSystem.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkMouseEvent.h"

using namespace nkentseu;

#include <stdio.h>

int nkmain(const NkEntryState &state)
{
    NkWindowConfig cfg;
    cfg.title = "Clic consomme";
    cfg.width = 900;
    cfg.height = 600;

    NkWindow window(cfg);

    if (!window.IsOpen())
    {
        printf("[INIT] Impossible d'ouvrir la fenetre.\n");
        return -1;
    }

    printf("[INIT] Fenetre ouverte.\n");

    // Panneau imaginaire dans le coin superieur gauche.
    const uint32 panelX = 0;
    const uint32 panelY = 0;
    const uint32 panelWidth = 300;
    const uint32 panelHeight = 200;

    while (window.IsOpen())
    {
        while (NkEvent *ev = NkEvents().PollEvent())
        {
            if (ev->Is<NkWindowCloseEvent>())
            {
                printf("[WINDOW] Fermeture demandee.\n");
                return 0;
            }

            if (auto *press = ev->As<NkMouseButtonPressEvent>())
            {
                if (press->IsLeft())
                {
                    const uint32 x = press->GetX();
                    const uint32 y = press->GetY();

                    // Premier gestionnaire : panneau.
                    if (x >= panelX &&
                        x < panelX + panelWidth &&
                        y >= panelY &&
                        y < panelY + panelHeight)
                    {
                        printf("[PANNEAU] Clic consomme en (%u, %u).\n", x, y);

                        ev->MarkHandled();

                        printf("[PANNEAU] Evenement marque comme traite.\n");
                    }

                    // Second gestionnaire.
                    if (!ev->IsHandled())
                    {
                        printf("[SECOND] Clic recu en (%u, %u).\n", x, y);
                    }
                }
            }
        }
    }

    return 0;
}