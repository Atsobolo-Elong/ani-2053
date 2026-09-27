#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkMain.h"
#include "NKEvent/NkEventSystem.h"
#include "NKEvent/NkEvent.h"

#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Renderer/Shapes/NkRectangleShape.h"

using namespace nkentseu;
using namespace nkentseu::renderer;


// CETTE FOCNTION PERMET DE VERIFIER SI LA SOURIS SE TROUVE DANS UN RECTANGLE
static bool PointDansZone(
    float32 x,
    float32 y,
    const NkRectangleShape& zone)
{
    const auto bornes = zone.GetGlobalBounds();

    return x >= bornes.x
        && x <= bornes.x + bornes.width
        && y >= bornes.y
        && y <= bornes.y + bornes.height;
}


int nkmain(const NkEntryState& state)
{
    
    // CONFIGURATION DE LA FENETRE 
    NkWindowConfig cfg;
    cfg.title = "Exercice 6 - Les sept curseurs";
    cfg.width = 1050;
    cfg.height = 500;

    // CREATION DE LA FENETRE
     NkWindow window;
    if (!window.Create(cfg))
        return -1;


    // CREATION DU CONTEXTE GRAPHIQUE
    NkContextDesc desc;
    desc.api = NkGraphicsApi::NK_GFX_API_OPENGL;

    // CREATION DE LA CIBLE DE RENDU
    NkRenderWindow target(window, desc);

    if (!target.IsValid())
        return -1;


    // CREATION DES 7 ZONES
    NkRectangleShape zone1(math::NkVec2f{140.f, 360.f});
    NkRectangleShape zone2(math::NkVec2f{140.f, 360.f});
    NkRectangleShape zone3(math::NkVec2f{140.f, 360.f});
    NkRectangleShape zone4(math::NkVec2f{140.f, 360.f});
    NkRectangleShape zone5(math::NkVec2f{140.f, 360.f});
    NkRectangleShape zone6(math::NkVec2f{140.f, 360.f});
    NkRectangleShape zone7(math::NkVec2f{140.f, 360.f});


   
    // POSITION DES 7 ZONES
    zone1.SetPosition({20.f, 70.f});
    zone2.SetPosition({165.f, 70.f});
    zone3.SetPosition({310.f, 70.f});
    zone4.SetPosition({455.f, 70.f});
    zone5.SetPosition({600.f, 70.f});
    zone6.SetPosition({745.f, 70.f});
    zone7.SetPosition({890.f, 70.f});


    // COULEUR SUR LES ZONES
    zone1.SetFillColor({220, 70, 70, 255});
    zone2.SetFillColor({230, 150, 60, 255});
    zone3.SetFillColor({220, 210, 60, 255});
    zone4.SetFillColor({80, 190, 90, 255});
    zone5.SetFillColor({70, 170, 210, 255});
    zone6.SetFillColor({100, 100, 220, 255});
    zone7.SetFillColor({180, 90, 200, 255});


    
    // TABLEAU DES OBJETS (ISSUES DE LA CLASSE DE NkRectangeleShape)
    NkRectangleShape* zones[7] =
    {
        &zone1,
        &zone2,
        &zone3,
        &zone4,
        &zone5,
        &zone6,
        &zone7
    };


   // LES 7 FORMES DE CURSEURS
    NkWindow::NkCursorType curseurs[7] =
    {
        NkWindow::NkCursorType::Arrow,
        NkWindow::NkCursorType::TextInput,
        NkWindow::NkCursorType::Hand,
        NkWindow::NkCursorType::ResizeNS,
        NkWindow::NkCursorType::ResizeWE,
        NkWindow::NkCursorType::ResizeNWSE,
        NkWindow::NkCursorType::ResizeNESW
    };
    
    //CURSEUR INITIALE, CELUI QUI EST POSE UNE FOIS AU DEMARRAGE
    window.SetCursor(curseurs[0]);


   
    // BOUCLE PRINCIPALE
    while (window.IsOpen())
    {
        while (NkEvent* ev = NkEvents().PollEvent())
        {
            if (ev->Is<NkWindowCloseEvent>())
            {
                window.Close();
            }

            //DEPLACEMENT DE LA SOURIS
            else if (auto* mouvement = ev->As<NkMouseMoveEvent>())
            {
                float32 x = static_cast<float32>(mouvement->GetX());
                float32 y = static_cast<float32>(mouvement->GetY());

                // CHERCHE LA ZONE SURVOLEE
                for (int i = 0; i < 7; ++i)
                {
                    if (PointDansZone(x, y, *zones[i]))
                    {
                        window.SetCursor(curseurs[i]);
                        break;
                    }
                }
            }
        }


        // RENDU MISE A JOUR
        target.Clear({30, 30, 30, 255});

        target.Draw(zone1);
        target.Draw(zone2);
        target.Draw(zone3);
        target.Draw(zone4);
        target.Draw(zone5);
        target.Draw(zone6);
        target.Draw(zone7);

        target.Display();
    }

    return 0;
}