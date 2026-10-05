#include <iostream>
#include <string>
#include <vector>


struct Objet
{
    std::string nom;
    std::string parent;

    long long tx;
    long long ty;
    long long angle;
    long long echelle;

    long long mondeX;
    long long mondeY;
    long long mondeAngle;
    long long mondeEchelle;

    int profondeur;
};


 //   NORMALISE UN ANGLE POUR LE RAMENER ENTRE 0 ET 270.
long long normaliserAngle(long long angle)
{
    angle %= 360;

    if (angle < 0)
        angle += 360;

    return angle;
}


//    APPLIQUE LA ROTATION AUX QUATRE ANGLES POSSIBLES.
void tourner(long long x, long long y, long long angle,
             long long& rx, long long& ry)
{
    switch (normaliserAngle(angle))
    {
        case 0:
            rx = x;
            ry = y;
            break;

        case 90:
            rx = -y;
            ry = x;
            break;

        case 180:
            rx = -x;
            ry = -y;
            break;

        case 270:
            rx = y;
            ry = -x;
            break;
    }
}

int main()
{
    int nombreObjets;
    std::cin >> nombreObjets;

    std::vector<Objet> objets;
    objets.reserve(nombreObjets);

    int profondeurMax = 0;

    for (int i = 0; i < nombreObjets; ++i)
    {
        Objet objet;

        std::cin >> objet.nom>> objet.parent>> objet.tx>> objet.ty>> objet.angle>> objet.echelle;

           // UN OBJET RACINE EST DEJA DANS LE REPERE MONDE.
        if (objet.parent == "-")
        {
            objet.mondeX = objet.tx;
            objet.mondeY = objet.ty;
            objet.mondeAngle = normaliserAngle(objet.angle);
            objet.mondeEchelle = objet.echelle;
            objet.profondeur = 1;
        }
        else
        {
               // LE PARENT EST GARANTI D'ETRE DEJA LU.
            int indiceParent = -1;

            for (int j = 0; j < static_cast<int>(objets.size()); ++j)
            {
                if (objets[j].nom == objet.parent)
                {
                    indiceParent = j;
                    break;
                }
            }

            const Objet& parent = objets[indiceParent];

        
              //  L'ECHELLE DU PARENT EST APPLIQUEE AVANT LA ROTATION.
    
            const long long localX = objet.tx * parent.mondeEchelle;
            const long long localY = objet.ty * parent.mondeEchelle;

            long long rotationX;
            long long rotationY;

            tourner(localX, localY, parent.mondeAngle,
                    rotationX, rotationY);

            objet.mondeX = parent.mondeX + rotationX;
            objet.mondeY = parent.mondeY + rotationY;

            objet.mondeAngle =
                normaliserAngle(parent.mondeAngle + objet.angle);

            objet.mondeEchelle =
                parent.mondeEchelle * objet.echelle;

            objet.profondeur = parent.profondeur + 1;
        }

        if (objet.profondeur > profondeurMax)
            profondeurMax = objet.profondeur;

        objets.push_back(objet);
    }

       // LES OBJETS SONT AFFICHES DANS LEUR ORDRE DE LECTURE.
    for (const Objet& objet : objets)
    {
        std::cout << objet.nom << ' '<< objet.mondeX << ' '<< objet.mondeY << ' '<< objet.mondeAngle << ' '<< objet.mondeEchelle << '\n';
    }

    std::cout << "PROFONDEUR " << profondeurMax << '\n';

    return 0;
}