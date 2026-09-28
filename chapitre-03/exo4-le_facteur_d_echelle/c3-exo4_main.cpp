#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include <stdio.h>

using namespace nkentseu;
using namespace nkentseu::renderer;

static void afficherMesures(int windowWidth, int windowHeight, NkRenderWindow& target, NkWindow& window)
{
    const auto renderSize = target.GetSize();

    const float dpiScale = window.GetDpiScale();

    printf("\nFenetre (zone cliente) : %d x %d"
           "\nCible de rendu         : %d x %d"
           "\nFacteur d'echelle DPI  : %.2f"
           "\n",
           windowWidth, windowHeight,
           static_cast<int>(renderSize.x), static_cast<int>(renderSize.y),
           dpiScale);
}

void afficherTailles()
{
    // CONFIGURATION DE LE FENETRE
    NkWindowConfig cfg;
    cfg.title = "EXERCICE 4 - FACTEUR D'ECHELLE";
    cfg.width = 800;
    cfg.height = 600;

    // CREATION DE LA FENETRE
    NkWindow window;

    if (!window.Create(cfg)) {
        logger.Error("ECHEC DE CREATION DE LA FENETRE");
        return;
    }

    //  CREATION DU CONTEXTE GRAPHIQUE
    NkContextDesc desc;
    desc.api = NkGraphicsApi::NK_GFX_API_OPENGL;
     // CREATION DE LA CIBLE DU RENDU
    NkRenderWindow target(window, desc);

    if (!target.IsValid()) {
        logger.Error("ECHEC DE CREATION DE LA CIBLE DE RENDU");
        window.Close();
        return;
    }

    auto& events = NkEvents();
    bool running = true;


    const auto initialSize = target.GetSize();
    int windowWidth = static_cast<int>(initialSize.x);
    int windowHeight = static_cast<int>(initialSize.y);

    afficherMesures(windowWidth, windowHeight, target, window);

    // BOUCLE PRINCIPALE
    while (window.IsOpen() && running) {
        while (NkEvent* ev = events.PollEvent()) {

            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
                running = false;
            }

            if (auto* resize = ev->As<NkWindowResizeEvent>()) {
                windowWidth = resize->GetWidth();
                windowHeight = resize->GetHeight();

                target.OnResize(windowWidth, windowHeight);

                afficherMesures(windowWidth, windowHeight, target, window);
            }
        }
    }
}

int nkmain(const nkentseu::NkEntryState& State)
{
    afficherTailles();
    return 0;
}
