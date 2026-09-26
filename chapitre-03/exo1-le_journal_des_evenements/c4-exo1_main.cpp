#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEventSystem.h"
#include "NKEvent/NkEvent.h"

#include <ctime>
#include <stdio.h>

using namespace nkentseu;

int nkmain(const NkEntryState& state)
{
    // CONFIGURATION DE LA FENETRE
    NkWindowConfig cfg;
    cfg.title = "Journal des evenements";
    cfg.width = 800;
    cfg.height = 600;

    NkWindow window;

    // CREATION DE LA FENETRE
    if (!window.Create(cfg))
        return -1;

    // COMPTEUR D'EVENEMENT
    int nombreEvenements = 0;

    // HEURE DE DEBUT DE LA MESURE.
    std::time_t debut = std::time(nullptr);

    // BOUCLE PRINCIPALE
    while (window.IsOpen())
    {

        while (NkEvent* ev = NkEvents().PollEvent())
        {
            // LE COMPTE INCREMENTE LORSU'UN EVENEMENT EST RECU
            ++nombreEvenements;

           // AFFICHAGE DE L'EVENEMENT ET DE LA FAMILLE
            printf("\n Evenement : %d %s %s %s", static_cast<int>(ev->GetCategory()), " - famille (code) : ", ev->GetTypeStr(),"\n");

             if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();        
            }
            else if (auto* kp = ev->As<NkKeyPressEvent>()) {
                if (kp->GetKey() == NkKey::NK_ESCAPE) window.Close();
            }

        }

        // L'HEURE ACTUELLE
        std::time_t maintenant = std::time(nullptr);

        // NOMBRE DE SECONDE ECOULES DEPUIS LE DEBUT DE LA MESURE
        double secondesEcoulees = std::difftime(maintenant, debut);

        // ON AFFICHE LE NOMBRE D'EVENEMENT APRES UNE SECONDE
        if (secondesEcoulees >= 1.0)
        {
            printf("\n Nombre d'evenements pendant 1 seconde : %d", nombreEvenements);

            // ON REMET TOUT A JOURS POUR UNE NOUVELLE PERIODE DE MESURE
            nombreEvenements = 0;
            debut = maintenant;
        }
    }

    return 0;
}