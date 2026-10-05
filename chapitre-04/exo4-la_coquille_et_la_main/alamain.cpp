#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"

#include <stdio.h>

using namespace nkentseu;
using namespace nkentseu::renderer;

int nkmain(const NkEntryState& state)
{
    // Configuration de la fentre
    NkWindowConfig config;
    config.title = "La coquille et la main";
    config.width = 800;
    config.height = 600;
    // creation de la fenetre
    NkWindow window;

    if (!window.Create(config))
        return 0;

    // creation du contexte graphique et choix de l'api native
    NkContextDesc desc;
    desc.api = NkGraphicsApi::NK_GFX_API_OPENGL;
    // creation de la cible du rendu
    NkRenderWindow target(window, desc);

    if (!target.IsValid())
    {
        window.Close();
        return 0;
    }

    auto& events = NkEvents();
    bool running = true;
    // boucle principale
    while (window.IsOpen() && running)
    {

        while (NkEvent* event = events.PollEvent())
        {
            if (event->Is<NkWindowCloseEvent>())
            {
                running = false;
                window.Close();
            }
        }

        target.Clear(NkColor2D{255, 0, 0, 1});
        target.Display();
    }

    window.Close();

    return 0;
}