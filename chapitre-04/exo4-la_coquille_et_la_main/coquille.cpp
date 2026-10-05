// j'ai decide de reprendre le programme realise a l'exercie 1

#include "NKWindow/NKWindow.h"
#include "NKCanvas/App/NkCanvasApp.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;
using namespace nkentseu::renderer;


// classe Fenetre qui herite de NkCanvas 
class FenetreApp : public NkCanvasApp
{
public:
    FenetreApp()
    {
        // configuration de la fenetre
        Config().title = "La fenetre nue";
        Config().width = 800;
        Config().height = 600;
        
        // j'ai choisi la couleur rouge 
        Config().clearColor = NkColor2D{255, 0, 0, 1};
    }
};

int nkmain(const NkEntryState& state)
{
    return NkCanvasApp::Run<FenetreApp>(state);
}