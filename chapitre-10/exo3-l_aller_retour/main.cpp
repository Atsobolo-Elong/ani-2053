#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cmath>

int main()
{
    // Dimensions de la fenêtre.
    double W, H;
    std::cin >> W >> H;

    // État initial de la caméra.
    double cx = 0.0;
    double cy = 0.0;
    double zoom = 1.0;

    // Lecture des commandes jusqu'à la fin de l'entrée.
    std::string commande;

    while (std::cin >> commande)
    {
        if (commande == "VERS_MONDE")
        {
            double px, py;
            std::cin >> px >> py;

            // Conversion des pixels vers les coordonnées du monde.
            double x = cx + (px - W / 2.0) / zoom;
            double y = cy + (py - H / 2.0) / zoom;

            // Évite l'affichage de -0.00.
            if (std::abs(x) < 0.005)
                x = 0.0;

            if (std::abs(y) < 0.005)
                y = 0.0;

            std::cout << std::fixed << std::setprecision(2);
            std::cout << "MONDE " << x << " " << y << '\n';
        }

        else if (commande == "VERS_PIXEL")
        {
            double mx, my;
            std::cin >> mx >> my;

            // Conversion du monde vers les pixels.
            double x = (mx - cx) * zoom + W / 2.0;
            double y = (my - cy) * zoom + H / 2.0;

            // Évite l'affichage de -0.00.
            if (std::abs(x) < 0.005)
                x = 0.0;

            if (std::abs(y) < 0.005)
                y = 0.0;

            std::cout << std::fixed << std::setprecision(2);
            std::cout << "PIXEL " << x << " " << y << '\n';
        }

        else if (commande == "DEPLACE")
        {
            double dx, dy;
            std::cin >> dx >> dy;

            // Le centre se déplace dans le sens opposé.
            cx -= dx / zoom;
            cy -= dy / zoom;
        }

        else if (commande == "ZOOM")
        {
            double f, px, py;
            std::cin >> f >> px >> py;

            // 1. Mémoriser le point du monde sous le curseur.
            double ax = cx + (px - W / 2.0) / zoom;
            double ay = cy + (py - H / 2.0) / zoom;

            // 2. Modifier le zoom.
            zoom *= f;

            // Respecter les limites du zoom.
            zoom = std::clamp(zoom, 0.02, 64.0);

            // 3. Recalculer le centre pour conserver le point sous le curseur.
            cx = ax - (px - W / 2.0) / zoom;
            cy = ay - (py - H / 2.0) / zoom;
        }

        else if (commande == "GRILLE")
        {
            double m;
            std::cin >> m;

            // Pas initial de la grille.
            double s = 1.0;

            // Agrandir le pas si les lignes sont trop rapprochées.
            while (s * zoom < m)
            {
                s *= 2.0;
            }

            // Réduire le pas autant que possible sans
            // passer sous l'espacement minimal demandé.
            while (s * 0.5 * zoom >= m)
            {
                s *= 0.5;
            }

            std::cout << std::fixed << std::setprecision(6);
            std::cout << "GRILLE " << s << '\n';
        }

        else if (commande == "ORIGINE")
        {
            // Réinitialiser la caméra.
            cx = 0.0;
            cy = 0.0;
            zoom = 1.0;
        }
    }

    // Affichage de l'état final de la caméra.
    if (std::abs(cx) < 0.005)
        cx = 0.0;

    if (std::abs(cy) < 0.005)
        cy = 0.0;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "CENTRE " << cx << " " << cy << '\n';
    std::cout << "ZOOM " << zoom << '\n';

    return 0;
}