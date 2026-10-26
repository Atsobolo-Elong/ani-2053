#include "NKWindow/NKMain.h"

#include "NKCanvas/App/NkCanvasApp.h"
#include "NKCanvas/Renderer/Core/NkDrawable.h"
#include "NKCanvas/Renderer/Core/NkRenderer2DTypes.h"
#include "NKCanvas/Renderer/Targets/NkRenderTarget.h"

using nkentseu::NkAppData;
using nkentseu::NkEntryState;
using nkentseu::renderer::NkCanvasApp;
using nkentseu::renderer::NkDrawable;
using nkentseu::renderer::NkPrimitiveType;
using nkentseu::renderer::NkRenderWindow;
using nkentseu::renderer::NkRenderStates;
using nkentseu::renderer::NkRenderTarget;
using nkentseu::renderer::NkVertex;

// Metadonnees lues par le runtime AVANT nkmain().
// Metadonnees lues par le runtime AVANT nkmain().
static const NkAppData AppDataAppelants = [] {
    NkAppData d{};
    d.appName = "Appelants";
    d.appVersion = "1.0.0";
    return d;
}();

NKENTSEU_DEFINE_APP_DATA(AppDataAppelants)

class AppelantsApp final : public NkCanvasApp {
private:
    // Objet de test : il envoie quatre sommets a la cible de rendu.
    class DeuxSegments final : public NkDrawable {
    public:
        void Draw(NkRenderTarget& target,
                  const NkRenderStates& states) const override {
            const NkVertex vertices[4] = {
                { 40.0f, 40.0f, 0.0f, 0.0f, 255, 255, 255, 255 },
                { 160.0f, 40.0f, 0.0f, 0.0f, 255, 255, 255, 255 },
                { 40.0f, 70.0f, 0.0f, 0.0f, 255, 255, 255, 255 },
                { 160.0f, 70.0f, 0.0f, 0.0f, 255, 255, 255, 255 }
            };

            // Point d'arret a placer ici pour relever la pile d'appels.
            target.Draw(vertices, 4, NkPrimitiveType::NK_LINES, states);
        }
    };

protected:
    void OnRender(NkRenderWindow& target) override {
        target.Clear();
        const DeuxSegments objet;

        // L'appel etudie : le compilateur voit NkDrawable, puis la repartition
        // virtuelle execute DeuxSegments::Draw.
        target.Draw(objet);
    }
};

int nkmain(const NkEntryState& state) {
    return NkCanvasApp::Run<AppelantsApp>(state);
}