#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    // Nombre de rectangles à traiter
    int n;
    std::cin >> n;

    // Compteur des rectangles dont l'angle est refusé
    int refuses = 0;

    // Traitement de chaque rectangle
    for (int i = 0; i < n; ++i)
    {
        std::string nom;

        int w, h;
        int px, py;
        int ox, oy;
        int sx, sy;
        int angle;

        // Lecture des caractéristiques du rectangle
        std::cin >> nom >> w >> h >> px >> py >> ox >> oy >> sx >> sy >> angle;

        // Normalisation de l'angle dans [0, 359]
        angle %= 360;

        if (angle < 0)
        {
            angle += 360;
        }

        // On ne conserve que les multiples de 90 degrés
        if (angle != 0 && angle != 90 && angle != 180 && angle != 270)
        {
            std::cout << nom << " ANGLE REFUSE\n";
            ++refuses;
            continue;
        }

        // Valeurs de cos(angle) et sin(angle)
        int c;
        int s;

        if (angle == 0)
        {
            c = 1;
            s = 0;
        }
        else if (angle == 90)
        {
            c = 0;
            s = 1;
        }
        else if (angle == 180)
        {
            c = -1;
            s = 0;
        }
        else
        {
            // angle == 270
            c = 0;
            s = -1;
        }

        // Les quatre coins locaux du rectangle
       
        int localX[4] = {0, w, w, 0};
        int localY[4] = {0, 0, h, h};

        // Coordonnées finales des quatre coins
        int worldX[4];
        int worldY[4];

        for (int j = 0; j < 4; ++j)
        {
            // On place le coin par rapport à l'origine
            int ax = (localX[j] - ox) * sx;
            int ay = (localY[j] - oy) * sy;

            // Rotation autour de l'origine
            int rx = ax * c - ay * s;
            int ry = ax * s + ay * c;

            // On ajoute la position du rectangle dans le monde.
            worldX[j] = px + rx;
            worldY[j] = py + ry;
        }

        // Calcul de la boîte englobante.
        int minX = worldX[0];
        int maxX = worldX[0];
        int minY = worldY[0];
        int maxY = worldY[0];

        for (int j = 1; j < 4; ++j)
        {
            minX = std::min(minX, worldX[j]);
            maxX = std::max(maxX, worldX[j]);

            minY = std::min(minY, worldY[j]);
            maxY = std::max(maxY, worldY[j]);
        }

        // Affichage des quatre coins dans l'ordre demandé 
        std::cout << nom << " COINS "<< worldX[0] << " " << worldY[0] << " "<< worldX[1] << " " << worldY[1] << " "<< worldX[2] << " " << worldY[2] << " "<< worldX[3] << " " << worldY[3] << "\n";

        // Affichage de la boîte englobante
        std::cout << nom << " BOITE "<< minX << " " << minY << " "<< maxX << " " << maxY << "\n";
    }

    // final des angles refusés
    std::cout << "REFUSES " << refuses << "\n";

    return 0;
}