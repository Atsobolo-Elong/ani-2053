#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Renderer/Resources/NkTexture.h"
#include "NKCanvas/Renderer/Resources/NkSprite.h"
#include "NKLogger/NkLogger.h"


using namespace nkentseu;
using namespace nkentseu::renderer;

// CETTE FONCTION A ETE PENSEE POUR EVITER D'OUVRIR CHAQUE FENTRE A LA MAIN...
void ouvrirFenetre(const NkWindowConfig &cfg) {

    //CREATION DDE LA FENETRE + GESTION D'ERREUR
    NkWindow window;

    if(!window.Create(cfg)) {
        logger.Error(" ECHEC DE CREATION DE LA FENETRE");
    }

    // CREATION DU CONTEXT ET CHOIX DE L'API GRAPHIQUE
    NkContextDesc desc;
    desc.api = NkGraphicsApi::NK_GFX_API_OPENGL;

    // CREATION DU RENDER
    NkRenderWindow target(window, desc);

    if (!target.IsValid()) {
        logger.Error("ECHEC DE CREATION DU RENDER");
        window.Close();
    }

    // EVENTS

    auto& events = NkEvents();
    bool running = true;

    // UTILISATION DU CALLBACK
    events.AddEventCallback<NkWindowCloseEvent>([&](NkWindowCloseEvent*) { running = false; });

    // BOUCLE PRINCIPALE 
    while( window.IsOpen() && running) {

        while(NkEvent *ev = events.PollEvent()) {
            // ATTENTES DES EVENEMENTS
        }
    }
   
}

int nkmain( const nkentseu::NkEntryState & state) {


     // CONFIGURATION DE LA FENETRE 1 : REDIMENTIONNEMENT INTERDIT
    NkWindowConfig cfg1;
    cfg1.title = "FENETRE 1 redimentionnement interdit";
    cfg1.width = 800;
    cfg1.height = 600;

    cfg1.resizable = false;

    ouvrirFenetre(cfg1);

    // CONFIGURATION DE LA FENETRE 2 :DEPLACEMENTS INTERDIT 

    NkWindowConfig cfg2;
    cfg2.title = "FENETRE 2 deplacement interdit";
    cfg2.width = 800;
    cfg2.height = 600;

    cfg2.movable = false;

    ouvrirFenetre(cfg2);

    // CONFIGURATION DE LA FENETRE 3 : MINIMISATION INTERDIT 

    NkWindowConfig cfg3;
    cfg3.title = "FENETRE 3 minimisation interdite";
    cfg3.width = 800;
    cfg3.height = 600;

    cfg3.minimizable = false;

    ouvrirFenetre(cfg3);



    // CONFIGURATION DE LA FENETRE 4 : MAXIMISATION INTERDITE 

    NkWindowConfig cfg4;
    cfg4.title = "FENETRE  MAXImisation interdite";
    cfg4.width = 800;
    cfg4.height = 600;

    cfg4.maximizable = false;

    ouvrirFenetre(cfg4);

    // CONFIGURATION DE LA FENETRE 5 :PASSAGE EN PLEIN ECRAN INTERDIT 

    NkWindowConfig cfg5;
    cfg5.title = "FENETRE 5 FULLSCREEN interdite";
    cfg5.width = 800;
    cfg5.height = 600;

    cfg5.canFullscreen = false;

    ouvrirFenetre(cfg5);

    // CONFIGURATION DE LA FENETRE 6 : DRAG AND DROP INTERDIT 

    NkWindowConfig cfg6;
    cfg6.title = "FENETRE 6 DRAG AND DROP interdite";
    cfg6.width = 800;
    cfg6.height = 600;

    cfg6.dropEnabled = false;

    ouvrirFenetre(cfg6);

    // CONFIGURATION DE LA FENETRE 7 : FERMETURE INTERDIT 

    NkWindowConfig cfg7;
    cfg7.title = "FENETRE 7 FERMETURE interdite";
    cfg7.width = 800;
    cfg7.height = 600;

    cfg7.closable = false;

    ouvrirFenetre(cfg7);



    return 0;



}