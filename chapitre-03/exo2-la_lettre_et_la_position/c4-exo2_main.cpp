#include "NKWindow/NKWindow.h"
#include "NKEvent/NkEventSystem.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKWindow/NKMain.h"

#include <stdio.h>

using namespace nkentseu;

int nkmain(const NkEntryState& state)
{
    // CONFIGURATION DE LA FENÊTRE
    NkWindowConfig config;
    config.title = "Exercice 2 - La lettre et la position";
    config.width = 900;
    config.height = 500;

    // CRÉATION DE LA FENÊTRE
    NkWindow window;

    if (!window.Create(config))
        return -1;

    // TOUCHE ET CODE (POSITION PHYSIQUE)
    NkKey derniereTouche = NkKey::NK_UNKNOWN;
    NkString derniereLettre = "";

    while (window.IsOpen())
    {
        while (NkEvent* ev = NkEvents().PollEvent())
        {
            if (ev->Is<NkWindowCloseEvent>())
            {
                window.Close();
            }
            else if (auto* key = ev->As<NkKeyPressEvent>())
            {
                derniereTouche = key->GetKey();
            }
            else if (auto* text = ev->As<NkTextInputEvent>())
            {
                if (text->IsPrintable())
                {
                    derniereLettre = text->GetUtf8();

                    // CODE PHYSIQUE CONVERTI EN ENTIER
                    int codePhysiqueConverti =
                        static_cast<int>(derniereTouche);

                    // CODE PHYSIQUE NON CONVERTI
                    int codePhysiqueNonConverti =
                        static_cast<int>(derniereTouche);

                    printf("Lettre : %s | ""Code physique converti : %d | ""Code physique non converti : %d\n", derniereLettre.CStr(), codePhysiqueConverti, codePhysiqueNonConverti );
                }
            }
        }
    }

    return 0;
}