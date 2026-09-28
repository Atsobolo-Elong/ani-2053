#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEventSystem.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkKeyboardEvent.h"

#include <stdio.h>

using namespace nkentseu;

int nkmain(const NkEntryState& state)
{
    //CONFIGURATION DE LA FENETRE
    NkWindowConfig config;

    config.title = "Exercice 4 - Le pointeur qui meurt";
    config.width = 800;
    config.height = 450;

    // CREATION DE LA FENETRE
    NkWindow window;

    if (!window.Create(config))
    {
        return -1;
    }


    NkEvent* evenementConserve = nullptr;

    int compteur = 0;
    
    // BOUCLE 1
    while (window.IsOpen() && compteur < 20)
    {
        NkEvent* ev = NkEvents().PollEvent();

        if (ev)
        {
            compteur++;

            printf("[POLL] Evenement recu : %s\n",
                   ev->GetTypeStr());

           // ON CONSERVE VOLONTAIREMENT LE POINTEUR
            evenementConserve = ev;

            // ON PROVOQUE UN DEUXIEME POLLEVENT
            NkEvent* second = NkEvents().PollEvent();

            if (second)
            {
                printf("[POLL] Deuxieme evenement dans la meme frame : %s\n",
                       second->GetTypeStr());

                printf("[POLL] Contenu du pointeur conserve apres le second PollEvent : %s\n",
                       evenementConserve->GetTypeStr());
            }
        }

        if (ev && ev->Is<NkWindowCloseEvent>())
        {
            window.Close();
        }

        if (ev && ev->Is<NkKeyPressEvent>())
        {
            auto* key = ev->As<NkKeyPressEvent>();

            if (key->GetKey() == NkKey::NK_ESCAPE)
            {
                printf("[POLL] Echap recue : fin de la phase 1.\n");
                break;
            }
        }
    }

    printf("\n========================================\n");
    printf("PHASE 1 TERMINEE\n");
    printf("========================================\n");

   
     // Phase 2 : correction avec PollEventCopy()
  
    
    // BOUCLE 2
    while (window.IsOpen())
    {
        NkEventPtr copie = NkEvents().PollEventCopy();

        if (copie)
        {
            printf("[COPY] Evenement copie : %s\n",
                   copie->GetTypeStr());

            // ON PEUT CONSERVER ET REEUTILISER LA COPIE
            if (copie->Is<NkKeyPressEvent>())
            {
                auto* key = copie->As<NkKeyPressEvent>();

                if (key->GetKey() == NkKey::NK_ESCAPE)
                {
                    printf("[COPY] Echap recue.\n");
                    printf("[COPY] La copie reste valide pendant son utilisation.\n");
                    printf("[COPY] Fin du programme.\n");

                    window.Close();
                }
            }

            if (copie->Is<NkWindowCloseEvent>())
            {
                printf("[COPY] Evenement de fermeture recu.\n");
                window.Close();}
        }
    }

    printf("\n========================================\n");
    printf("FIN D'EXECUTION\n");
    printf("========================================\n");

    return 0;
}