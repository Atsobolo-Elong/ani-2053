#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEvent.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"

#include <string>

using namespace nkentseu;
using namespace nkentseu::renderer;

// LE NOM DU DOCUMENT EST AFFICHE DANS LE TITRE
static const char* NOM_DOCUMENT = "MonDocument";


// CETTE FONCTION PERMET DE CONTRUIRE LA FENETRE ET D'Y APPLIQUER LES MODIFICATIONS
void MettreAJourTitre( NkWindow& window, const char* nomDocument, bool documentModifie, uint32 largeur,   uint32 hauteur)
{
    std::string titre = nomDocument;

    // ON AJOUTE L'ASTERIQUE UNIQUEMENT SI LE DOCUMENT EST MODIFIE.
    if (documentModifie)
    {
        titre += " *";
    }

    // ON AJOUTE LA TAILLE COURANTE DE LA FENETRE
    titre += " - ";
    titre += std::to_string(largeur);
    titre += " x ";
    titre += std::to_string(hauteur);

    // ON UTILISE LA METHODE SetTitle() POUR APPLIQUER LES MODIFICATION APPLIQUES
    window.SetTitle(titre.c_str());
}


int nkmain(const nkentseu::NkEntryState& state)
{
    // CONFIGURATION DE LA FENETRE
    NkWindowConfig cfg;

    cfg.title = NOM_DOCUMENT;
    cfg.width = 800;
    cfg.height = 600;

    // CREATION DE LA FENETRE + GESTION D'ERREUR
    NkWindow window;

    if (!window.Create(cfg))
    {
        return -1;
    }

    // ETAT INITIALE DU DOCUMENT
    bool documentModifie = false;

    // PAR RAPPORT A LA L'EXO PRECEDENT J'AI DECIDE DE RECUPERER LA TAILLE RELLE DE LA FENETRE 
    // AVEC LA METHODE GetSize() de NkWindow.h
    math::NkVec2u taille = window.GetSize();

    uint32 largeur = taille.x;
    uint32 hauteur = taille.y;

  // MISE A JOUR DU TITRE AU DEMARRAGE COMME DEMANDER DANS LA CONSIGNE
    MettreAJourTitre( window, NOM_DOCUMENT, documentModifie, largeur, hauteur );

    // BOUCLE PRINCIPALE
    while (window.IsOpen())
    {
        while (NkEvent* ev = NkEvents().PollEvent())
        {


            // GESTION DES EVENTEMENT
            if (ev->Is<NkWindowCloseEvent>()) {
                 window.Close();          // l'utilisateur veut fermer
                }

            //MODIFICATION DU DOCUMENT S'EFFECTUE LORSQUE L'UTILISATION ENTRE LA TOUCHE "ENTRER"
            else if (auto* ev2 = ev->As<NkKeyPressEvent>()) {
                if (ev2->GetKey() == NkKey::NK_ENTER) documentModifie = true;
                MettreAJourTitre(window, NOM_DOCUMENT, documentModifie, largeur, hauteur);
            }

            // ICI LE TITRE EST ACTUALISE LORSQUE LA FENTRE CHANGE
            if (ev->Is<NkWindowResizeEvent>())
            {
                auto* resize = ev->As<NkWindowResizeEvent>();

                largeur = resize->GetWidth();
                hauteur = resize->GetHeight();

                // MISE A JOUR DE L'ETAT DE LA FENETRE
                MettreAJourTitre(window, NOM_DOCUMENT, documentModifie, largeur, hauteur);
            }
            
        }

    }

    return 0;
}